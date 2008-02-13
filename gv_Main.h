#ifndef __MAIN_FORM
#define __MAIN_FORM

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "HCFGStorage.h"
#include "HExcept.h"
#include "HLog.h"
#include "HMenus.h"
#include "XPMenu.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "HWindow.h"
#include "TB97Ctls.hpp"

class TMainForm : public TForm {
  __published:
        HMainMenu *MainMenu;
        TMenuItem *F1;
        TMenuItem *mnuLoad;
        TMenuItem *mnuClear;
        TMenuItem *mnuConfig;
        TMenuItem *N5;
        TMenuItem *mnuSaveCfg;
        TMenuItem *mnuExit;
        HExceptionDialog *HExceptionDialog1;
        HCfgStorage *cfg;
        HLogComboBox *cbLog;
        TMenuItem *N1;
        TXPMenu *XPMenu1;
        TOpenDialog *open;
        TSaveDialog *save;
        TMenuItem *Window1;
        TMenuItem *mnuNewWindow;
        TMenuItem *Hide1;
        TMenuItem *N8;
        TMenuItem *ArrangeAll1;
        TMenuItem *Cascade1;
        TMenuItem *Tile1;
        TMenuItem *N2;
        TMenuItem *T1;
        TMenuItem *G1;
        TMenuItem *N3;
        TMenuItem *Previous1;
        HWindow *wndFilter;
        TLabel *Label2;
        TLabel *Label3;
        TToolbarButton97 *btnRefilter;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *edtDOPMin;
        TCheckBox *chMove;
        TEdit *edtMoveDiff;
        TCheckBox *chMaxSpeedInc;
        TEdit *edtMaxSpeedInc;
        TCheckBox *chMaxPrevDiff;
        TEdit *edtMovePrevDiff;
        TMenuItem *P1;
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mnuExitClick(TObject *Sender);
        void __fastcall mnuSaveCfgClick(TObject *Sender);
        void __fastcall mnuConfigClick(TObject *Sender);
        void __fastcall mnuLoadClick(TObject *Sender);
        void __fastcall T1Click(TObject *Sender);
        void __fastcall Tile1Click(TObject *Sender);
        void __fastcall Cascade1Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall Previous1Click(TObject *Sender);
        void __fastcall ArrangeAll1Click(TObject *Sender);
        void __fastcall Hide1Click(TObject *Sender);
        void __fastcall mnuClearClick(TObject *Sender);
        void __fastcall G1Click(TObject *Sender);
        void __fastcall btnRefilterClick(TObject *Sender);
        void __fastcall P1Click(TObject *Sender);
  private:
    bool idOnUnknownCommand( CONSTSTR s );
    bool idOnCommandParceError( CONSTSTR s );
    bool idOnNoCRC( CONSTSTR s );
    bool idOnCRCError( CONSTSTR s );

  public:
    __fastcall TMainForm(TComponent* Owner);

    bool LoadNMEAFile( CONSTSTR fnm );
    void LoadCfg( void );
    void SaveCfg( TObject *Sender /*=NULL*/ );
};

#endif
