#ifndef __CONFIG_COLS_FORM__
#define __CONFIG_COLS_FORM__
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
#include "BkList.h"

class TCfgColsForm : public TForm {
__published:    // IDE-managed Components
        TToolbarButton97 *btnCancel;
        TToolbarButton97 *btnOk;
        TPanel *Panel1;
        HBkList *list;
        THeaderControl *HeaderControl1;
        TPanel *Panel2;
        TToolbarButton97 *btnAdd;
        TToolbarButton97 *btnDel;
        TToolbarButton97 *btnUp;
        TToolbarButton97 *btnDn;
        TSplitter *Splitter1;
        THeaderControl *HeaderControl2;
        HBkList *listAll;
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnCloseClick(TObject *Sender);
        bool __fastcall listDrawItemSection(TObject *Sender, TCanvas *dc,
          int Index, THeaderSection *Section, const MyRect &Rect,
          const TOwnerDrawState &State);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnUpClick(TObject *Sender);
        void __fastcall btnDnClick(TObject *Sender);
  public:
    GPSColArray AllCols;
  public:
    __fastcall TCfgColsForm(TComponent* Owner );

    GPSColArray Cols;
    bool        NumberOnly;

    DEF_PROP_P( int, ColIndex, { return Cols.Item(list->ItemIndex); } )
    DEF_PROP_P( int, AllIndex, { return AllCols.Item(listAll->ItemIndex); } )
};
#endif
