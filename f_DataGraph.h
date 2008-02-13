#ifndef __GRAPH_FORM
#define __GRAPH_FORM

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>

#include "HGraph.h"
#include "HValGraph.h"
#include "TB97Ctls.hpp"
#include "HMenus.h"
#include "HWindow.h"

class TDataGraphForm : public TForm {
  __published:
        TPanel *Panel1;
        TComboBox *cbTypes;
        TLabel *Label1;
        TToolbarButton97 *ToolbarButton971;
        HValueGraph *graph;
        TToolbarButton97 *ToolbarButton972;
        HPopupMenu *HPopupMenu1;
        TMenuItem *H1;
        TMenuItem *B1;
        TMenuItem *S1;
        TMenuItem *V1;
        TMenuItem *B2;
        TMenuItem *S2;
        TMenuItem *S3;
        TMenuItem *S4;
        TMenuItem *D1;
        TMenuItem *G1;
        TMenuItem *H2;
        TMenuItem *L1;
        TMenuItem *B3;
        TMenuItem *D2;
        TStatusBar *status;
        void __fastcall ToolbarButton971Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall B1Click(TObject *Sender);
        void __fastcall S1Click(TObject *Sender);
        void __fastcall B2Click(TObject *Sender);
        void __fastcall S2Click(TObject *Sender);
        void __fastcall S3Click(TObject *Sender);
        void __fastcall S4Click(TObject *Sender);
        void __fastcall D1Click(TObject *Sender);
        void __fastcall HPopupMenu1MenuItemCheck(TObject *Sender,
          TMenuItem *Item);
        void __fastcall H2Click(TObject *Sender);
        void __fastcall L1Click(TObject *Sender);
        void __fastcall B3Click(TObject *Sender);
        void __fastcall D2Click(TObject *Sender);
        void __fastcall graphDblClick(TObject *Sender);
        void __fastcall graphHOnCursorChange(TObject *Sender);
        void __fastcall graphHOnSelectFinish(TObject *Sender,
          double HSStart, double HSEnd, double VSStart, double VSEnd);
        void __fastcall btnRefilterClick(TObject *Sender);
  private:
    void __fastcall idChange( void );
    void __fastcall idFollow( int idx );
    void __fastcall idRefilter( void );

  public:
    __fastcall TDataGraphForm(TComponent* Owner);

    void SetupState( void );
};

#endif
