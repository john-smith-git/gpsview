#ifndef __CONFIG_FORM__
#define __CONFIG_FORM__
//  Какой-то русский текст, чтобы ФАР дурака не валял...

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>

#include "TB97Ctls.hpp"

class TConfigForm : public TForm {
__published:    // IDE-managed Components
        TPageControl *pages;
        TTabSheet *TabSheet1;
        TToolbarButton97 *btnCancel;
        TToolbarButton97 *btnOk;
        TGroupBox *GroupBox10;
        TCheckBox *chAutosave;
        TCheckBox *chSaveViewPos;
        TGroupBox *GroupBox12;
        TCheckBox *chAskQuit;
        TGroupBox *GroupBox1;
        TCheckBox *chProcessWOCRC;
        TCheckBox *chProcessCRCErr;
        TCheckBox *chLogUnkCmd;
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnCloseClick(TObject *Sender);
  private:
    void __fastcall idPluginsChanged( int idx );
  public:
    __fastcall TConfigForm(TComponent* Owner );
};
#endif
