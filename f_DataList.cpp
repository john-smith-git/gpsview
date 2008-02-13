#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...
//#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "BkList"
#pragma link "TB97Ctls"

#include "int.h"
#include "f_DataList.h"

static char DefCols[] = { 1, 2, 3, 4, 0 };

void NewDataList( PTForm Parent )
  {
    new TListForm( Parent );
}

//---------------------------------------------------------------------------
__fastcall TListForm::TListForm(TComponent* Owner)
    : TForm(Owner)
  {
     Data.OnChange.Add( idChange );
     Data.OnFollow.Add( idFollow );
     Cols.Set( DefCols );

     RecreateCols();
     idChange();
}

void __fastcall TListForm::idFollow( int idx ) { __try{ list->ItemIndex = idx; }catch(...){} }
void __fastcall TListForm::idChange( void )    { list->ItemsCount = Data.Count(); }

void __fastcall TListForm::RecreateCols( void )
  {  PGPSFieldInfo   fi;
     THeaderSection *s;
     int             n;

     for( int n = 0; n < header->Sections->Count; n++ )
       SOPT( Message("TH/Sec%d",n ), header->Sections->Items[n]->Width );

     header->Sections->Clear();

     s = header->Sections->Add();
       s->Width = 30;
       s->Text  = "N";

     for( int n = 0; n < Cols.Count(); n++ ) {
       fi = &GPSFields[ Cols[n] ];
       s  = header->Sections->Add();

       s->Width = GOPT( Message("TH/Sec%d",n+1 ), 100 );
       s->Text  = fi->Name;
     }
     list->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TListForm::FormClose(TObject *Sender, TCloseAction &Action)
  {
     Action = caFree;
     Data.OnChange.Delete( idChange );
     Data.OnFollow.Delete( idFollow );
}
//---------------------------------------------------------------------------
bool __fastcall TListForm::listDrawItemSection(TObject *Sender,
      TCanvas *dc, int Index, THeaderSection *Section, const MyRect &Rect,
      const TOwnerDrawState &State)
  {
     if ( Section->Index == 0 )
       TC_TextOut( dc, Rect.Inflated(-2,-1), Message( "%d", Index+1 ), DT_SINGLELINE|DT_RIGHT|DT_VCENTER );
      else {
       int idx = Section->Index-1;
       if ( idx < 0 || idx >= Cols.Count() )
         return false;

       TC_TextOut( dc, Rect.Inflated(-2,-1),
                   Field2Str( Data, Index, Cols[ idx ] ),
                   DT_SINGLELINE|DT_RIGHT|DT_VCENTER );
     }

 return true;
}
//---------------------------------------------------------------------------
void __fastcall TListForm::cbKeyNumDropDown(TObject *Sender)
  {  PHConfigItem cfg = Opt->SubKey( "Table" );

     cbKeyNum->Clear();
     for( int n = 0; n < cfg->LeathCount(); n++ )
       cbKeyNum->Items->Add( cfg->Leath(n)->GetName() );
}
//---------------------------------------------------------------------------
void __fastcall TListForm::btnSaveClick(TObject *Sender)
  {
     if ( !cbKeyNum->Text.Length() ||
          !Cols.Count() )
       return;

     PHConfigItem cfg = Opt->SubKey( "Table" );
     if ( !cfg ) return;
     cfg = cfg->ConfigGetCreate( cbKeyNum->Text.c_str() );
     if ( !cfg ) return;

     char b[ GPS_MAX_COLS+1 ];

     int n;
     for( n = 0; n < GPS_MAX_COLS && n < Cols.Count(); n++ )
       b[n] = (char)(Cols[n] + 1);
     b[n] = 0;

     cfg->Write( "", b );
     for( n = 0; n < header->Sections->Count; n++ )
       cfg->Write( Message("Sec%d",n ), header->Sections->Items[n]->Width );
}
//---------------------------------------------------------------------------
void __fastcall TListForm::btnSetClick(TObject *Sender)
{
     if ( !cbKeyNum->Text.Length() )
       return;

     PHConfigItem cfg = Opt->SubKey( "Table" );
     if ( !cfg ) return;
     cfg = cfg->ConfigGetCreate( cbKeyNum->Text.c_str() );
     if ( !cfg ) return;

     CONSTSTR m = cfg->Read( "", "" );
     if ( !m || !m[0] )
       return;

     Cols.Set( m );
     RecreateCols();
     for( int n = 0; n < header->Sections->Count; n++ )
       header->Sections->Items[n]->Width = cfg->Read( Message("Sec%d",n ), header->Sections->Items[n]->Width );
}
//---------------------------------------------------------------------------
void __fastcall TListForm::btnDeleteClick(TObject *Sender)
  {
     if ( !cbKeyNum->Text.Length() )
       return;

     PHConfigItem cfg = Opt->SubKey( "Table" );
     if ( !cfg ) return;
     cfg = cfg->Locate( cbKeyNum->Text.c_str() );
     if ( !cfg ) return;

     cfg->Delete(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TListForm::btnCfgClick(TObject *Sender)
  {
     if ( ConfigureCols( this, Cols, false ) )
       RecreateCols();
}
//---------------------------------------------------------------------------
void __fastcall TListForm::listDblClick(TObject *Sender)
  {
     Data.Follow( list->ItemIndex );
}
//---------------------------------------------------------------------------

