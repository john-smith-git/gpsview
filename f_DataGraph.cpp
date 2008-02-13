#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...
//#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "HGraph"
#pragma link "HValGraph"
#pragma link "TB97Ctls"
#pragma link "HWindow"
#pragma link "HMenus"

#include "int.h"
#include "f_DataGraph.h"

void NewDataGraph( PTForm Parent ) { new TDataGraphForm( Parent ); }

HGraphColor clrs[] = {
  { clYellow, clRed,   0 },  //Error
  { clSilver, clGray,  0 },  //None
  { clBlack,  clWhite, 0 },  //Value
};

//---------------------------------------------------------------------------
__fastcall TDataGraphForm::TDataGraphForm(TComponent* Owner)
    : TForm(Owner)
  {
     for( int n = 0; GPSFields[n].Name; n++ )
       if ( IsFieldNumber(n) )
         cbTypes->Items->AddObject( Message( "%s - %s", GPSFields[n].Name, GPSFields[n].Desc ),
                                    (TObject*)n );
     SendMessage( cbTypes->Handle, CB_SETDROPPEDWIDTH, 300, 0 );

     graph->ColorIndex[0] = clrs[0];
     graph->ColorIndex[1] = clrs[1];
     graph->ColorIndex[2] = clrs[2];

     graph->HScale->GridVisible       = GOPT( "Graph/VVisible",           true );
     graph->HScale->GridMinVisible    = GOPT( "Graph/VVMinVisible",       true );
     graph->VScale->GridVisible       = GOPT( "Graph/VHVisible",          true );
     graph->VScale->GridMinVisible    = GOPT( "Graph/VHMinVisible",       true );
     graph->ShowValueBack             = GOPT( "Graph/VStateBk",           true );
     graph->ShowValueTick             = GOPT( "Graph/VValueTick",         false );
     graph->DrawAllValues             = GOPT( "Graph/VAllValues",         false );
     graph->GraphLineType             = (HGLineType)GOPT( "Graph/Line",   (int)gltHisto );
     graph->PointType                 = (HGPointType)GOPT( "Graph/Point", (int)gptNone );

     Data.OnChange.Add( idChange );
     Data.OnFollow.Add( idFollow );
     Data.OnRefilter.Add( idRefilter );

     __try{ cbTypes->ItemIndex = GOPT( "GraphType", -1 ); }catch(...){}
     idChange();
}
void __fastcall TDataGraphForm::idRefilter( void )  { SetupState(); }

void __fastcall TDataGraphForm::idFollow( int idx )
  {  PDataGPS p = Data.Item(idx);
     if ( !p ) return;

     double vmin = DateToDouble( p->Time-1 ),
            vmax = DateToDouble( p->Time+1 );

     graph->HScale->SelectionStart->Value = vmin;
     graph->HScale->SelectionEnd->Value   = vmax;

     vmin = Min( vmin, graph->HScroller->Start->Value );
     vmax = Max( vmax, graph->HScroller->Finish->Value );
     graph->HRuller->SetupVisibleRange( vmin, vmax );

     graph->Invalidate();
}

void TDataGraphForm::SetupState( void )
  {  HGraphValue val;
     int         cl, n;

     for( n = 0; n < graph->ValuesCount; n++ ) {
       graph->GetValueItem( n, &val );
       if ( val.Y == ERROR_NUMBER ||
            val.Y == HAVENO_NUMBER )
         continue;

       do{
         PDataGPS d = Data.Item(n);
         if ( !d )
           cl = 0;
          else 
           cl = d->IsDataValid( FOpts, Data.Item(n-1) ) ? 2 : 0;
       }while(0);

       val.ColorIndex = cl;
       graph->SetValueItem( n, &val );
     }
     graph->Invalidate();
}

void __fastcall TDataGraphForm::idChange( void )
  {  int idx;

     idx = cbTypes->ItemIndex;
     if ( idx < 0 || idx >= cbTypes->Items->Count )
       return;
     idx = (int)cbTypes->Items->Objects[ idx ];
     if ( !IsFieldNumber(idx) )
       return;

     PGPSFieldInfo fi = &GPSFields[idx];

     HRop rop;
     rop->SetAbort( true );
     RTGetIdlePeriod()->Reset();

     graph->ClearValues();
     double minv = ERROR_NUMBER,
            maxv = ERROR_NUMBER;

     for( int n = 0; n < Data.Count(); n++ ) {

       if ( RTGetIdlePeriod()->End() ) {
         rop->SetText( "Setting graph for [%s]...\n%d of %d", fi->Name, n, Data.Count() );
         rop->SetProgress( n * 100 / Data.Count() );
         if ( rop->isAborted() )
           break;
       }

       double v = Field2Number( Data, n, idx );
       int cl;
       if ( v == ERROR_NUMBER )  cl = 0; else
       if ( v == HAVENO_NUMBER ) cl = 1; else
         cl = 2;

       if ( Abs(v) > 0.000001 ) {
         if ( minv == ERROR_NUMBER ) minv = v; else minv = Min( v, minv );
         if ( maxv == ERROR_NUMBER ) maxv = v; else maxv = Max( v, maxv );
       }

       graph->AddValue( cl, DateToDouble( Data[n]->Time ), v, 0 );
     }

     if ( Data.Count() ) {
       double w = maxv-minv;
       if ( w < 0.000001 ) {
         graph->VScale->SetGridSize( 1, 1 );
         graph->VScroller->Step->Value = 1;
         graph->VRuller->Setup( minv-1, maxv+1,
                                Max( minv-1, graph->VScroller->Start->Value ),
                                Min( maxv+1, graph->VScroller->Finish->Value ) );
       } else {
         graph->VScale->SetGridSize( w/10, w/100 );
         graph->VRuller->Setup( minv-w/1000, maxv+w/1000, minv-w/1000, maxv+w/1000 );
         graph->VScroller->Step->Value = w/100;
       }

       minv = DateToDouble( Data[0]->Time );
       maxv = DateToDouble( Data[ Data.Count()-1 ]->Time );
       w = maxv-minv;
       if ( w < 0.000001 )
         graph->HScroller->Setup( minv-1, maxv+1,
                                  minv-1, maxv+1 );
        else {
         w = graph->HScroller->Step->Value;
         graph->HScroller->Setup( minv-w, maxv+w,
                                  Max( minv-w, graph->HScroller->Start->Value ),
                                  Min( maxv+w, graph->HScroller->Finish->Value ) );
       }
     }

     SetupState();
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::ToolbarButton971Click(TObject *Sender)
  {
     idChange();
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::FormClose(TObject *Sender,TCloseAction &Action)
{
     SOPT( "Graph/VVisible",           graph->HScale->GridVisible   );
     SOPT( "Graph/VVMinVisible",       graph->HScale->GridMinVisible);
     SOPT( "Graph/VHVisible",          graph->VScale->GridVisible   );
     SOPT( "Graph/VHMinVisible",       graph->VScale->GridMinVisible);
     SOPT( "Graph/VStateBk",           graph->ShowValueBack         );
     SOPT( "Graph/VValueTick",         graph->ShowValueTick         );
     SOPT( "Graph/VAllValues",         graph->DrawAllValues         );
     SOPT( "Graph/Line",               (int)graph->GraphLineType );
     SOPT( "Graph/Point",              (int)graph->PointType );

     Action = caFree;

     Data.OnChange.Delete( idChange );
     Data.OnFollow.Delete( idFollow );
     Data.OnRefilter.Delete( idRefilter );
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::B1Click(TObject *Sender) { graph->HScale->GridVisible = !graph->HScale->GridVisible; }
void __fastcall TDataGraphForm::S1Click(TObject *Sender) { graph->HScale->GridMinVisible = !graph->HScale->GridMinVisible; }
void __fastcall TDataGraphForm::B2Click(TObject *Sender) { graph->VScale->GridVisible = !graph->VScale->GridVisible; }
void __fastcall TDataGraphForm::S2Click(TObject *Sender) { graph->VScale->GridMinVisible = !graph->VScale->GridMinVisible; }
void __fastcall TDataGraphForm::S3Click(TObject *Sender) { graph->ShowValueBack = !graph->ShowValueBack; }
void __fastcall TDataGraphForm::S4Click(TObject *Sender) { graph->ShowValueTick = !graph->ShowValueTick; }
void __fastcall TDataGraphForm::D1Click(TObject *Sender) { graph->DrawAllValues = !graph->DrawAllValues; }
void __fastcall TDataGraphForm::H2Click(TObject *Sender) { graph->GraphLineType = gltHisto; }
void __fastcall TDataGraphForm::L1Click(TObject *Sender) { graph->GraphLineType = gltLine; }
void __fastcall TDataGraphForm::B3Click(TObject *Sender) { graph->GraphLineType = gltBar; }
void __fastcall TDataGraphForm::D2Click(TObject *Sender) { graph->PointType = graph->PointType == gptCircle ? gptNone : gptCircle; }
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::HPopupMenu1MenuItemCheck( TObject *Sender,TMenuItem *mi )
  {
     switch( mi->Tag ) {
       case 100: mi->Checked = graph->HScale->GridVisible; break;
       case 101: mi->Checked = graph->HScale->GridMinVisible; break;
       case 102: mi->Checked = graph->VScale->GridVisible; break;
       case 103: mi->Checked = graph->VScale->GridMinVisible; break;
       case 104: mi->Checked = graph->ShowValueBack; break;
       case 105: mi->Checked = graph->ShowValueTick; break;
       case 106: mi->Checked = graph->DrawAllValues; break;
       case 107: mi->Checked = graph->GraphLineType == gltHisto; break;
       case 108: mi->Checked = graph->GraphLineType == gltLine; break;
       case 109: mi->Checked = graph->GraphLineType == gltBar; break;
       case 110: mi->Checked = graph->PointType == gptCircle; break;
     }
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::graphDblClick(TObject *Sender)
  {
     Data.Follow( graph->FindNearest(graph->HScale->CursorPos) );
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::graphHOnCursorChange(TObject *Sender)
  {  int fidx, idx;

     do{
       idx = cbTypes->ItemIndex;
       if ( idx < 0 || idx >= cbTypes->Items->Count ) break;

       idx = (int)cbTypes->Items->Objects[ idx ];
       if ( !IsFieldNumber(idx) ) break;
       fidx = idx;

       idx = graph->FindNearest(graph->HScale->CursorPos);
       PDataGPS p = Data.Item( idx );
       if ( !p ) break;

       status->Panels->Items[1]->Text = Message( "%d", idx+1 );
       status->Panels->Items[2]->Text = GPSFields[fidx].Name;
       status->Panels->Items[3]->Text = Field2Str( Data, idx, fidx );
       return;
     }while(0);

     status->Panels->Items[1]->Text = "";
     status->Panels->Items[2]->Text = "";
     status->Panels->Items[3]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::graphHOnSelectFinish( TObject *Sender, double HSStart, double HSEnd, double VSStart, double VSEnd )
  {
     graph->HRuller->SetupVisibleRange( HSStart, HSEnd );
}
//---------------------------------------------------------------------------
void __fastcall TDataGraphForm::btnRefilterClick(TObject *Sender)
  {
     SetupState();
}
//---------------------------------------------------------------------------
