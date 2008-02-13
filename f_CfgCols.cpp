#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...
//#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "TB97Ctls"
#pragma link "BkList"

#include "int.h"
#include "f_CfgCols.h"

//---------------------------------------------------------------------------
bool ConfigureCols( TForm *Parent, GPSColArray& Cols, bool NumberOnly )
  {  HAutoPtr<TCfgColsForm> d( new TCfgColsForm(Parent) );

     d->NumberOnly = NumberOnly;
     d->Cols.Set( Cols );

     if ( d->ShowModal() == mrOk ) {
       Cols.Set( d->Cols );
       return true;
     } else
       return false;
}

//---------------------------------------------------------------------------
//  TCfgColsForm
//---------------------------------------------------------------------------
__fastcall TCfgColsForm::TCfgColsForm( TComponent* Owner )
  : TForm(Owner)
  {
     NumberOnly = false;
     HLoadFormPos( Opt->SubKey("CfgColWindow"), this );
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::FormShow(TObject *Sender)
  {
    //options -> Fields
    list->ItemsCount = Cols.Count();

    int cn = 0;
    for( int n = 0; GPSFields[n].Name; n++ )
      if ( !NumberOnly ||
           IsFieldNumber(n) ) {
        cn++;
        AllCols.Add( n );
      }
    listAll->ItemsCount = cn;
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnOKClick(TObject *Sender)
  {
     HSaveFormPos( Opt->SubKey("CfgColWindow"), this );

   //Close
     ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnCloseClick(TObject *Sender)
  {
     ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
bool __fastcall TCfgColsForm::listDrawItemSection(TObject *Sender,
      TCanvas *dc, int Index, THeaderSection *Section, const MyRect &Rect,
      const TOwnerDrawState &State)
  {  int idx = ((HCustomBkList*)Sender)->Tag ? Cols[ Index ] : AllCols[ Index ];
     PGPSFieldInfo fi = &GPSFields[ idx ];

     CONSTSTR m;
     switch( Section->Index ) {
       case 0: m = fi->Name; break;
       case 1: m = fi->Desc; break;
     }

     TC_TextOut( dc, Rect.Inflated( -2, -1 ), m, DT_SINGLELINE|DT_VCENTER|DT_LEFT );
 return true;
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnAddClick(TObject *Sender)
  {  int aidx = AllIndex;

     if ( aidx >= 0 && !Cols.Has(aidx) ) {
       int num = list->ItemIndex != -1 ? (list->ItemIndex+1) : Cols.Count();

       Cols.AddAt( num, aidx );

       list->ItemsCount = Cols.Count();
       list->ItemIndex  = num;
     }
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnDelClick(TObject *Sender)
{
     if ( list->ItemIndex >= 0 ) {
       Cols.DeleteNum( list->ItemIndex );
       list->ItemsCount = Cols.Count();
     }
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnUpClick(TObject *Sender)
  {
     if ( list->ItemIndex > 0 ) {
       Cols.Swap( list->ItemIndex, list->ItemIndex-1 );
       list->ItemIndex = list->ItemIndex-1;
       list->Invalidate();
     }
}
//---------------------------------------------------------------------------
void __fastcall TCfgColsForm::btnDnClick(TObject *Sender)
{
     if ( list->ItemIndex < Cols.Count() ) {
       Cols.Swap( list->ItemIndex, list->ItemIndex+1 );
       list->ItemIndex = list->ItemIndex+1;
       list->Invalidate();
     }
}
//---------------------------------------------------------------------------

