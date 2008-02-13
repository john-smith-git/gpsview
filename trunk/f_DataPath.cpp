#include <all_wlib.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "int.h"
#include "f_DataPath.h"
#pragma link "HMenus"
#pragma link "TB97Ctls"

void NewDataPath( PTForm Parent ) { new TPathForm( Parent ); }

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int FindLength( int idx, size_t n_off, size_t e_off, int n, int e )
  {  PDataGPS p = Data.Item(idx);
     if ( !p ) return -1;

     double a1 = n - *( (int*) ( ((LPBYTE)p) + n_off ) ),
            a2 = e - *( (int*) ( ((LPBYTE)p) + e_off ) );
     a1 = a1*a1;
     a2 = a2*a2;
     if ( a1 < 0.001 ) return a2;
     if ( a2 < 0.001 ) return a1;

 return (int)sqrt( a1 + a2 );
}

int FindNearest( int *ar, size_t cn, size_t inc,
                 size_t n_off, size_t e_off,
                 int n, int e )
  {  int sz, szI;

     if ( !cn ) return -1;

     sz  = FindLength( *ar, n_off, e_off, n, e );
     szI = 0;

     for( size_t i = inc; i < cn; i += inc ) {
       int v = FindLength( ar[i], n_off, e_off, n, e );
       if ( v >= 0 && v < sz ) {
         sz  = v;
         szI = i;
       }
     }

 return szI;
}

int FindNearestAr( int *ar, size_t cn,
                 size_t n_off, size_t e_off,
                 int n, int e )
  {  size_t step;
     int    idx,
            idxadd = 0;

#define DELIMITER 100
     do{
       step = Max( 1U, cn / DELIMITER );
       idx  = FindNearest( ar, cn, step, n_off, e_off, n, e );
       if ( idx < 0 || step == 1 )
         return idx+idxadd;

       ar      = ar + idx;
       idxadd += idx;
       cn     /= DELIMITER;
     }while( 1 );
#undef DELIMITER
}

int GPSPointsArray::FindNearestGGA( int n, int e )
  {  int idx = FindNearestAr( Items(), Count(),
                              OffsetOf(DataGPS,GGA) + OffsetOf(GPN_DataGGA,n),
                              OffsetOf(DataGPS,GGA) + OffsetOf(GPN_DataGGA,e),
                              n, e );
 return Item(idx);
}

int GPSPointsArray::FindNearestRMC( int n, int e )
  {  int idx = FindNearestAr( Items(), Count(),
                              OffsetOf(DataGPS,RMC) + OffsetOf(GPN_DataGGA,n),
                              OffsetOf(DataGPS,RMC) + OffsetOf(GPN_DataGGA,e),
                              n, e );
 return Item(idx);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TPathForm::TPathForm(TComponent* Owner)
    : TForm(Owner)
  {
     scroll->DoubleBuffered = true;
     FollowIndex    = -1;
     BaseW          = 300;
     Zoom           = 100;

     Data.OnChange.Add( idChange );
     Data.OnFollow.Add( idFollow );
     Data.OnRefilter.Add( idRefilter );

     chDAll->Checked           = GOPT( "Path/DAll",      true );
     chDFiltered->Checked      = GOPT( "Path/DFiltered", true );
     btnInterval->Position     = GOPT( "Path/Interval",  10 );
     cbType->ItemIndex         = GOPT( "Path/Type",      1 );
     chDX->Checked             = GOPT( "Path/DX",        false );

     idChange();
}

void __fastcall TPathForm::FormClose(TObject *Sender, TCloseAction &Action)
  {
     Action = caFree;

     Data.OnChange.Delete( idChange );
     Data.OnFollow.Delete( idFollow );
     Data.OnRefilter.Delete( idRefilter );

     SOPT( "Path/DAll",      chDAll->Checked );
     SOPT( "Path/DFiltered", chDFiltered->Checked );
     SOPT( "Path/Interval",  (int)btnInterval->Position );
     SOPT( "Path/Type",      cbType->ItemIndex );
     GOPT( "Path/DX",        chDX->Checked );
}

DECL_PROP_SET( TPathForm, int, Zoom )
  {
     FZoom = val;

     paint->Width  = MulDiv( BaseW, Zoom, 100 );
     paint->Height = MulDiv( BaseW, Zoom, 100 );

     DrawRect = GetScaledRect( MyRect(0,0,paint->Width,paint->Height),
                               Max( 1, dBounds.Width() ), Max( 1, dBounds.Height() ),
                               GSR_SCALE_PAGE|GSR_HCENTER|GSR_VCENTER );

     HRop rop;
     RTGetIdlePeriod()->Reset();
     for( int n = 0; n < Data.Count(); n++ ) {
       PDataGPS p = Data[n];

       if ( RTGetIdlePeriod()->End() )
         RTGetOperation()->SetText( "Calc points...\n%d of %d (%d%%)", n+1, Data.Count(), n*100/Data.Count() );

       if ( IS_FLAG( p->Valid, GPV_GGA ) &&
            p->GGA.e && p->GGA.n ) {
         p->GGA_x = E2X( p->GGA.e );
         p->GGA_y = N2Y( p->GGA.n );
       } else {
         p->GGA_x = 0;
         p->GGA_y = 0;
       }

       if ( IS_FLAG( p->Valid, GPV_RMC ) &&
            p->RMC.n && p->RMC.e ) {
         p->RMC_x = E2X( p->RMC.e );
         p->RMC_y = N2Y( p->RMC.n );
       } else {
         p->RMC_x = 0;
         p->RMC_y = 0;
       }
     }
}

void __fastcall TPathForm::idRefilter( void )   { idChange(); }
void __fastcall TPathForm::idFollow( int idx )  { FollowIndex = idx; idInvalidate(NULL); }

void TPathForm::SetDBounds( MyRect& b, PDataGPS p )
  {
     if ( cbType->ItemIndex == 1 ) {
       if ( b.IsNull() )
         b.Set( p->RMC.e, p->RMC.n, p->RMC.e, p->RMC.n );
        else {
         b.x  = Min( b.x,  p->GGA.e );
         b.y  = Min( b.y,  p->GGA.n );
         b.x1 = Max( b.x1, p->GGA.e );
         b.y1 = Max( b.y1, p->GGA.n );
       }
     } else {
       if ( b.IsNull() )
         b.Set( p->GGA.e, p->GGA.n, p->GGA.e, p->GGA.n );
        else {
         b.x  = Min( b.x,  p->GGA.e );
         b.y  = Min( b.y,  p->GGA.n );
         b.x1 = Max( b.x1, p->GGA.e );
         b.y1 = Max( b.y1, p->GGA.n );
       }
     }
}

void __fastcall TPathForm::idChange( void )
  {  DataGPS last, lastgood;
     memset( &last, 0, sizeof(last) );
     memset( &lastgood, 0, sizeof(lastgood) );

     gData.DeleteAll();
     gBounds.SetNull();

     aData.DeleteAll();
     aBounds.SetNull();

     int pInt = btnInterval->Position;

     for( int n = 0; n < Data.Count(); n++ ) {
       PDataGPS p = Data[n];

       if ( !p->IsDataFixed() )
         continue;

       SetDBounds( aBounds, p );
       aData.Add( n );

       if ( !p->IsDataValid( FOpts, &last ) ) {
         last = *p;
         continue;
       }
       last = *p;

       SetDBounds( gBounds, p );

       if ( !IS_FLAG( lastgood.Valid, GPV_GGA ) ||
            !pInt ||
            lastgood.LengthToGGA( *p ) > pInt ) {
         gData.Add( n );
         lastgood = *p;
       }
     }

     if ( aData.Count() ) {
       dBounds.Set( aBounds );
       if ( gData.Count() )
         dBounds.Or( gBounds );

       int w = dBounds.Width(),
           h = dBounds.Height();
       if ( w > h )
         dBounds.Inflate( 0, (w-h) / 2 );
        else
       if ( h > w )
         dBounds.Inflate( (h-w) / 2, 0 );
     }

     status->Panels->Items[7]->Text = Message( "Data: %d, Good: %d, All: %d",
                                               Data.Count(), gData.Count(), aData.Count() );
     Zoom = Zoom;
     idInvalidate(NULL);
}
//---------------------------------------------------------------------------
int __fastcall TPathForm::E2X( int v ) { return DrawRect.x + MulDiv( v-dBounds.x, DrawRect.Width(), dBounds.Width() ); }
int __fastcall TPathForm::N2Y( int v ) { return DrawRect.y1 + MulDiv( dBounds.y-v, DrawRect.Height(), dBounds.Height() ); }
int __fastcall TPathForm::X2E( int v ) { return dBounds.x + MulDiv( v-DrawRect.x, dBounds.Width(), DrawRect.Width() ); }
int __fastcall TPathForm::Y2N( int v ) { return dBounds.y + MulDiv( DrawRect.y1-v, dBounds.Height(), DrawRect.Height() ); }

void TPathForm::FromNE( PDataGPS p, int& x, int& y )
  {
     if ( cbType->ItemIndex == 1 ) {
       x = p->RMC_x;
       y = p->RMC_y;
     } else {
       x = p->GGA_x;
       y = p->GGA_y;
     }
}
void TPathForm::DrawArray( TCanvas *dc, const GPSPointsArray& ar, TColor cl, int& nDraw )
  {  int          n,
                  x, y, x1, y1, idx;
     PDataGPS     p;

     if ( ar.Count() <= 1 )
       return;

     p  = Data.Item( ar[0] );
     if ( !p ) {
       RTLog( "Indexes mitsmatch! (%d)", ar[0] );
       return;
     }

     MyRect dr;
     dr.x  = scroll->HorzScrollBar->Position;
     dr.y  = scroll->VertScrollBar->Position;
     dr.x1 = dr.x + scroll->Width;
     dr.y1 = dr.y + scroll->Height;

     dc->Pen->Width = 3;
     FromNE( p, x, y );

     for( n = 1; n < ar.Count(); x = x1, y = y1, n++ ) {
       idx = ar[n];
       p = Data.Item( idx );
       if ( !p ) {
         RTLog( "Indexes mitsmatch! (%d)", idx );
         break;
       }

       FromNE( p, x1, y1 );
       if ( x == x1 && y == y1 ||
            !dr.Contains( x1, y1 ) && !dr.Contains( x, y ) )
         continue;

       dc->Pen->Width = 1;
       TC_Line( dc, x, y, x1, y1, cl );
       nDraw++;

       dc->Pen->Width = 1;
       if ( idx == FollowIndex ) {
         TC_Line( dc, x1-10, y1, x1+10, y1, clBlack );
         TC_Line( dc, x1, y1-10, x1, y1+10, clBlack );
         TC_FillEllipse( dc, MyRect(x1-3,y1-3,x1+3,y1+3), clGreen );
       } else
       if ( idx == ar.SelectIndex ) {
         TC_FillEllipse( dc, MyRect(x1-3,y1-3,x1+3,y1+3), clLime );
       } else
       if ( chDX->Checked ) {
         TC_Line( dc, x1-4, y1, x1+4, y1, clBlack );
         TC_Line( dc, x1, y1-4, x1, y1+4, clBlack );
       }
     }

}
void __fastcall TPathForm::paintPaint(TObject *Sender)
  {  TCanvas *dc = paint->Canvas;

     TC_Fill( dc, MyRect(0,0,paint->Width,paint->Height), clGray );
     TC_Fill( dc, DrawRect, clWhite );

     int nDraw = 0;
     TIME_TYPE b,e;

     GET_TIME( b );
     if ( chDAll->Checked )      DrawArray( dc, aData, clRed, nDraw );
     if ( chDFiltered->Checked ) DrawArray( dc, gData, clNavy, nDraw );
     GET_TIME( e );
     status->Panels->Items[5]->Text = Message( "%d (%1.3lf)", nDraw, CMP_TIME(e,b) );
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::idInvalidate(TObject *Sender)
  {
    paint->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::paintDblClick(TObject *Sender)
  {
     Data.Follow( aData.SelectIndex );
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::idRecreate(TObject *Sender)
  {
     idChange();
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::btnZAddClick(TObject *Sender)
  {
     Zoom = Zoom * 2;
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::btnZDelClick(TObject *Sender)
{
     Zoom = Max( 100, Zoom/2 );
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
  {
     if ( Key == 'D' )         scroll->HorzScrollBar->Position = scroll->HorzScrollBar->Position+50; else
     if ( Key == 'A' )         scroll->HorzScrollBar->Position = scroll->HorzScrollBar->Position-50; else
     if ( Key == 'W' )         scroll->VertScrollBar->Position = scroll->VertScrollBar->Position-50; else
     if ( Key == 'S' )         scroll->VertScrollBar->Position = scroll->VertScrollBar->Position+50; else
     if ( Key == '+' )         btnZAddClick(NULL); else
     if ( Key == '-' )         btnZDelClick(NULL); else
     if ( Key == VK_ADD )      btnZAddClick(NULL); else
     if ( Key == VK_SUBTRACT ) btnZDelClick(NULL); else
      ;
}
//---------------------------------------------------------------------------
#define OZI_TR_FILEHEADER "OziExplorer Track Point File Version 2.1"

bool idOziExport( GPSPointsArray& ar, CONSTSTR fnm )
  {  FILE *f = fopen( fnm, "wt" );
     if ( !f )
       return false;

     PRTime   tm;
     int      n, nPt, idx;
     PDataGPS p;
     bool     rc = false;

     __try{
       p = Data.Item( ar[0] );
       if ( !p ) {
         SetError( "Invalid data index %d", 0 );
         return false;
       }

       tm.Set( p->Time );
       fprintf( f,
                OZI_TR_FILEHEADER "\n"
                "WGS 84\n"
                "Altitude is in Feet\n"
                "Reserved 3\n"
                "0,3,65280,%s,1,0,2,8421376\n"
                "%d\n",
                /* 4*/ Message( "Track log - %s",tm.GetStr(NULL,0) ),
                ar.Count(),
                0 );

       for( nPt = n = 0; n < ar.Count(); n++ ) {
         p = Data.Item( ar[n] );
         if ( !p ) {
           SetError( "Invalid data index %d", 0 );
           return false;
         }

         char dS[ 20 ],
              tS[ 20 ];

         tm.Set( p->Time );
         fprintf( f,
                  "  %3.6lf,  %3.6lf,0,  %4.1lf,%6.7lf, %s, %s\n",
                  /* 1*/p->GGA.Lat,
                  /* 2*/p->GGA.Lon,
                  /* 3*/ //0
                  /* 4*/p->GGA.Alt * 3.280947537649,
                  /* 5*/DateToDouble( p->Time ),
                  /* 6*/tm.GetStr( dS, sizeof(dS), "%d-%b-%Y" ),
                  /* 7*/tm.GetStr( tS, sizeof(tS), "%H:%M:%S" ),
                  0 );
         nPt++;
       }/*FILE*/

       rc = true;
     }__finally{
       HSaveError _err;
       fclose(f);
     }

     RTLog( "%d track points saved to file: %s", nPt, fnm );
 return rc;
}

void __fastcall TPathForm::O1Click(TObject *Sender)
  {
     if ( !gData.Count() ) return;

     save->DefaultExt = "plt";
     save->Filter     = "OZI explorer track files (PLT)|*.plt";
     save->InitialDir = MakeStartLocalPath( GOPT("LastPath","") ).c_str();
     if ( !save->Execute() ) return;
     SOPT( "LastPath", FPath( MakeStartRelativePath(save->FileName).c_str() ) );

     if ( !idOziExport( gData, save->FileName.c_str() ) )
       RTErrorMessage( Handle,
                       "Error save data\n"
                       "File: %s\n"
                       "Error: %s",
                       save->FileName.c_str(), FIO_ERROR );
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::paintMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
  {
     mDown.Set( X, Y );
     HClientToClient( paint, scroll, mDown );
}
//---------------------------------------------------------------------------
void __fastcall TPathForm::paintMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
  {
     if ( Shift.Contains(ssLeft) ) {
       MyPoint p( X, Y);
       HClientToClient( paint, scroll, p );

       if ( mDown.x != p.x || mDown.y != p.y ) {
         if ( mDown.x != p.x ) scroll->HorzScrollBar->Position = scroll->HorzScrollBar->Position + (mDown.x-p.x);
         if ( mDown.y != p.y ) scroll->VertScrollBar->Position = scroll->VertScrollBar->Position + (mDown.y-p.y);
         mDown.Set( p.x, p.y );
       }
     } else {
       int x = X2E( X ),
           y = Y2N( Y );

       int  sel;
       bool rp = false;

       sel = gData.FindNearest( cbType->ItemIndex, y, x );
       if ( gData.SelectIndex != sel ) {
         gData.SelectIndex = sel;
         rp                = true;
       }

       sel = aData.FindNearest( cbType->ItemIndex, y, x );
       if ( aData.SelectIndex != sel ) {
         aData.SelectIndex = sel;
         rp = true;
       }

       status->Panels->Items[1]->Text = Message( "%d", y );
       status->Panels->Items[3]->Text = Message( "%d", x );
       status->Panels->Items[4]->Text = Message( "%d/%d", gData.SelectIndex, aData.SelectIndex );

       if ( rp )
         idInvalidate(NULL);
     }
}
//---------------------------------------------------------------------------
