#ifndef __LIST_FORM
#define __LIST_FORM

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BkList.h"
#include "TB97Ctls.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

class TListForm : public TForm {
  __published:
        THeaderControl *header;
        TPanel *Panel1;
        HBkList *list;
        TComboBox *cbKeyNum;
        TToolbarButton97 *btnSave;
        TToolbarButton97 *btnSet;
        TToolbarButton97 *btnDelete;
        TToolbarButton97 *btnCfg;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        bool __fastcall listDrawItemSection(TObject *Sender, TCanvas *dc,
          int Index, THeaderSection *Section, const MyRect &Rect,
          const TOwnerDrawState &State);
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall cbKeyNumDropDown(TObject *Sender);
        void __fastcall btnSetClick(TObject *Sender);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall btnCfgClick(TObject *Sender);
        void __fastcall listDblClick(TObject *Sender);
  private:
    GPSColArray Cols;

  private:
    void __fastcall idChange( void );
    void __fastcall idFollow( int idx );

  public:
    __fastcall TListForm(TComponent* Owner);

    void __fastcall RecreateCols( void );
};

#endif
 