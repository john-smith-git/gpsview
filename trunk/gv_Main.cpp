#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...
//#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "HCFGStorage"
#pragma link "HExcept"
#pragma link "HLog"
#pragma link "HMenus"
#pragma link "XPMenu"

#include "int.h"
#include "gv_Main.h"
#pragma link "HWindow"
#pragma link "TB97Ctls"

TMainForm      *MainForm;
PHStorageLink   Opt;
GPN_Filter      FOpts;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
  {
   //Prop values
     wndFilter->WindowState = hcbMinimize;

   //Init
     Initialize_Engine();
     UtilsInit( this, cbLog, cfg );
     RTLog( "Starting..." );

     Opt = new HStorageLink;
       Opt->Storage = cfg;
       Opt->KeyPath = "IDE";

   //Do load
     cfg->Load();

     LoadCfg();

     RTLog( "OK" );
}
//---------------------------------------------------------------------------
void TMainForm::LoadCfg( void )
  {
     //Load changes
     HLoadFormPos( Opt->SubKey("Window"), this );

     FOpts.Doppler           = GOPT( "Graph/DOP",                4.9 );
     FOpts.UseMaxMove        = GOPT( "Graph/ChMaxMove",          true );
     FOpts.MaxMove           = GOPT( "Graph/MaxMoveDiff",        10 );
     FOpts.UseMaxSpeedInc    = GOPT( "Graph/ChMaxSpeedInc",      false );
     FOpts.MaxSpeedInc       = GOPT( "Graph/MaxSpeedInc",        1.5 );
     FOpts.UseMaxPrevMove    = GOPT( "Graph/ChMaxPrevDiff",      false );
     FOpts.MaxPrevMove       = GOPT( "Graph/MovePrevDiff",       10 );

     edtDOPMin->Text         = Message( "%3.2lf", FOpts.Doppler );
     chMove->Checked         = FOpts.UseMaxMove;
     edtMoveDiff->Text       = FOpts.MaxMove;
     chMaxSpeedInc->Checked  = FOpts.UseMaxSpeedInc;
     edtMaxSpeedInc->Text    = Message( "%3.2lf", FOpts.MaxSpeedInc );
     chMaxPrevDiff->Checked  = FOpts.UseMaxPrevMove;
     edtMovePrevDiff->Text   = FOpts.MaxPrevMove;
}

void TMainForm::SaveCfg( TObject *Sender )
  {
     if ( Sender &&
          !AskYesNo( Handle, NULL, LNG("Save configuration?") ) )
      return;

    //Save changes
     HSaveFormPos( Opt->SubKey("Window"), this );

     SOPT( "Graph/DOP",           FOpts.Doppler         );
     SOPT( "Graph/ChMaxMove",     FOpts.UseMaxMove      );
     SOPT( "Graph/MaxMoveDiff",   FOpts.MaxMove         );
     SOPT( "Graph/ChMaxSpeedInc", FOpts.UseMaxSpeedInc );
     SOPT( "Graph/MaxSpeedInc",   FOpts.MaxSpeedInc );
     SOPT( "Graph/ChMaxPrevDiff", FOpts.UseMaxPrevMove  );
     SOPT( "Graph/MovePrevDiff",  FOpts.MaxPrevMove     );

    //Do save
     if ( !cfg->Save() && Sender )
       RTErrorMessage( Handle,
                       LNG("Error storing config.\nFile: %s\nError: %s"),
                       cfg->FileName.c_str(), FIO_ERROR );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
  {
     if ( GOPT( "AskQuit", true ) &&
          !AskYesNo( Handle, NULL, LNG("Terminate programm?") ) ) {
       CanClose = false;
       return;
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//Autosave
    RTLog( LNG("Save cfg...") );
    if ( GOPT( "Autosave",true ) )
      SaveCfg(NULL);

//Shutdown
    RTLog( LNG("Shutdown programm...") );
    Notification( cfg, opRemove );
    UtilsShutdown();
    delete Opt; Opt = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mnuSaveCfgClick(TObject *Sender)  { SaveCfg( Sender ); }
void __fastcall TMainForm::mnuExitClick(TObject *Sender)     { Close(); }
//---------------------------------------------------------------------------
void __fastcall TMainForm::mnuConfigClick(TObject *Sender)
{
      if ( !Configure(this) )
        return;
}
//---------------------------------------------------------------------------
bool TMainForm::idOnUnknownCommand( CONSTSTR s )
  {
     if ( GOPT( "LogUnkCmd",true ) )
       RTLog( "Unknown command: [%s]", s );
 return true;
}
bool TMainForm::idOnCommandParceError( CONSTSTR s )
  {
    RTLog( "Parce error [%s]: %s", s, FIO_ERROR );
 return true;
}
bool TMainForm::idOnNoCRC( CONSTSTR s )
  {
    RTLog( "Have no CRC: [%s]", s );
 return GOPT( "ProcessWOCRC",true );
}
bool TMainForm::idOnCRCError( CONSTSTR s )
  {
    RTLog( "CRC error: [%s]", s );
 return GOPT( "ProcessCRCErr",false );
}

bool TMainForm::LoadNMEAFile( CONSTSTR fnm )
  {  FILE *f = fopen( fnm, "rt" );
     if ( !f )
       return false;

     HRop        rop;
     rop->SetAbort( true );
     RTGetIdlePeriod()->Reset();

     MyRefArray<PathString> Commands, Except;

     DataGPS it;
       it.OnUnknownCommand    = idOnUnknownCommand;
       it.OnCommandParceError = idOnCommandParceError;
       it.OnNoCRC             = idOnNoCRC;
       it.OnCRCError          = idOnCRCError;

     PathString *p;

     Data.DeleteAll();
     Data.Changed();

     int  nLines = 0;
     bool rc;
     __try{
       char buff[ 1000 ], *m;
       int  n;

       //Get data
       while( !feof(f) && fgets(buff,sizeof(buff),f) != NULL ) {
         m = strchr( buff,'\r' ); if ( m ) *m = 0;
         m = strchr( buff,'\n' ); if ( m ) *m = 0;
         for( m = buff; *m && strchr( " \t\b", *m ) != NULL; )
           m++;
         if ( !*m || *m != '$' ) continue;

         nLines++;
         if ( RTGetIdlePeriod()->End() ) {
           rop->SetText( "Loading [%s]...\n%d", fnm, Data.Count() );
           if ( rop->isAborted() ) {
             rc = true;
             break;
           }
         }

         rc = false;
         for( n = 0; n < Commands.Count(); n++ ) {
           p = Commands[n];

           if ( StrNCmp( p->c_str(), m, 6 ) == 0 ) {

             if ( *((DWORD*)(p->c_str() + 3)) == MK_ID('G','S','V',',') ) {
               if ( StrGetCol( m,3,",")[0] != '1' )
                 break;
             }
             rc = true;
             break;
           }
         }

         if ( !rc ) {
           Commands.Add( PathString(m) );
           continue;
         }

         it.Time = 0;
         for( n = 0; n < Commands.Count(); n++ ) {
           p = Commands[n];
           it.ProcessCommand( p->c_str() );
         }

         if ( it.Valid )
           Data.Add( it );

         Commands.DeleteAll();
       }/*file*/
     }__finally{
       HSaveError _err;
       fclose(f);
     }

     RTLog( "Loaded %d items from %d lines", Data.Count(), nLines );
  return true;
}

void __fastcall TMainForm::mnuLoadClick(TObject *Sender)
  {
     open->InitialDir = MakeStartLocalPath( GOPT("LastPath","") ).c_str();
     if ( !open->Execute() ) return;
     SOPT( "LastPath", FPath( MakeStartRelativePath(open->FileName).c_str() ) );

     bool rc = true;
     switch( open->FilterIndex ) {
       case 1: rc = LoadNMEAFile( open->FileName.c_str() ); break;
     }

     Caption = "GPSView";
     if ( !rc )
       RTErrorMessage( Handle,
                       "Error loading input file.\nFile: %s\nError: %s",
                       open->FileName.c_str(),
                       FIO_ERROR );
      else
       Caption = Message( "GPSView: [%s]", open->FileName.c_str() );

     Data.Changed();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Tile1Click(TObject *Sender)       { Tile(); }
void __fastcall TMainForm::Cascade1Click(TObject *Sender)    { Cascade(); }
void __fastcall TMainForm::N3Click(TObject *Sender)          { Next(); }
void __fastcall TMainForm::Previous1Click(TObject *Sender)   { Previous(); }
void __fastcall TMainForm::ArrangeAll1Click(TObject *Sender) { ArrangeIcons(); }
void __fastcall TMainForm::Hide1Click(TObject *Sender)       { if ( ActiveMDIChild ) ActiveMDIChild->Close(); }
void __fastcall TMainForm::T1Click(TObject *Sender)          { NewDataList( this ); }
void __fastcall TMainForm::G1Click(TObject *Sender)          { NewDataGraph( this ); }
void __fastcall TMainForm::P1Click(TObject *Sender)          { NewDataPath(this); }
//---------------------------------------------------------------------------
void __fastcall TMainForm::mnuClearClick(TObject *Sender)
  {
    Data.DeleteAll();
    Data.Changed();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnRefilterClick(TObject *Sender)
  {
     FOpts.Doppler         =  atof(edtDOPMin->Text.c_str());
     FOpts.UseMaxMove      =  chMove->Checked;
     FOpts.MaxMove         =  atoi(edtMoveDiff->Text.c_str());
     FOpts.UseMaxSpeedInc  =  chMaxSpeedInc->Checked;
     FOpts.MaxSpeedInc     =  atof(edtMaxSpeedInc->Text.c_str());
     FOpts.UseMaxPrevMove  =  chMaxPrevDiff->Checked;
     FOpts.MaxPrevMove     =  atoi(edtMovePrevDiff->Text.c_str());

     Data.Refilter();
}
//---------------------------------------------------------------------------


