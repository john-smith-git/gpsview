#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...
//#pragma package(smart_init)
#pragma resource "*.dfm"

#include "int.h"
#include "f_Config.h"
#pragma link "TB97Ctls"

//---------------------------------------------------------------------------
bool Configure( TForm *Parent )
  {  HAutoPtr<TConfigForm> d( new TConfigForm(Parent) );
 return d->ShowModal() == mrOk;
}

//---------------------------------------------------------------------------
//  TConfigForm
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm( TComponent* Owner )
  : TForm(Owner)
  {
     pages->ActivePageIndex = 0;
     HLoadFormPos( Opt->SubKey("CfgWindow"), this );
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::FormShow(TObject *Sender)
  {
    //options -> Fields
     chAutosave->Checked             = GOPT( "Autosave",       true );
     chSaveViewPos->Checked          = GOPT( "SaveViewPos",    true );

     chAskQuit->Checked              = GOPT( "AskQuit",        true );

     chProcessWOCRC->Checked         = GOPT( "ProcessWOCRC",   true );
     chProcessCRCErr->Checked        = GOPT( "ProcessCRCErr",  false );
     chLogUnkCmd->Checked            = GOPT( "LogUnkCmd",      true );
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::btnOKClick(TObject *Sender)
  {
     HSaveFormPos( Opt->SubKey("CfgWindow"), this );

    //Fields -> options
     SOPT( "Autosave",            chAutosave->Checked );
     SOPT( "SaveViewPos",         chSaveViewPos->Checked );

     SOPT( "AskQuit",             chAskQuit->Checked );

     SOPT( "ProcessWOCRC",        chProcessWOCRC->Checked );
     SOPT( "ProcessCRCErr",       chProcessCRCErr->Checked );
     SOPT( "LogUnkCmd",           chLogUnkCmd->Checked );

   //Close
     ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::btnCloseClick(TObject *Sender)
  {
     ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
