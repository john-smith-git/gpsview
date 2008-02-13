#ifndef __PATH_FORM
#define __PATH_FORM

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "TB97Ctls.hpp"
#include "HMenus.h"
#include <Dialogs.hpp>
#include <Menus.hpp>

LOCALCLASSBASE( GPSPointsArray, public MyValArray<int> )
  public:
    GPSPointsArray( void ) : MyValArray<int>( 100, 1000 ) { SelectIndex = -1; }

    int FindNearestGGA( int n, int e );
    int FindNearestRMC( int n, int e );
    int FindNearest( int tp, int n, int e ) { return tp == 2 ? FindNearestRMC(n,e) : FindNearestGGA(n,e); }

    int SelectIndex;
};

class TPathForm : public TForm {
  __published:
        TPanel *Panel1;
        TCheckBox *chDAll;
        TCheckBox *chDFiltered;
        TStatusBar *status;
        TLabel *Label1;
        TEdit *Edit1;
        TUpDown *btnInterval;
        TToolbarButton97 *ToolbarButton971;
        TComboBox *cbType;
        TToolbarButton97 *btnZAdd;
        TToolbarButton97 *btnZDel;
        TScrollBox *scroll;
        TPaintBox *paint;
        TToolbarButton97 *ToolbarButton972;
        HPopupMenu *HPopupMenu1;
        TMenuItem *O1;
        TSaveDialog *save;
        TCheckBox *chDX;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall paintPaint(TObject *Sender);
        void __fastcall idInvalidate(TObject *Sender);
        void __fastcall paintDblClick(TObject *Sender);
        void __fastcall idRecreate(TObject *Sender);
        void __fastcall btnZAddClick(TObject *Sender);
        void __fastcall btnZDelClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall O1Click(TObject *Sender);
        void __fastcall paintMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall paintMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  private:
    void __fastcall idChange( void );
    void __fastcall idFollow( int idx );
    void __fastcall idRefilter( void );

  private:
    GPSPointsArray gData;
    MyRect         gBounds;

    GPSPointsArray aData;
    MyRect         aBounds;

    MyRect         dBounds,
                   DrawRect;
    int            FollowIndex;
    int            BaseW;

    MyPoint        mDown;

  public:
    __fastcall TPathForm(TComponent* Owner);

    int __fastcall E2X( int v );
    int __fastcall N2Y( int v );
    int __fastcall X2E( int v );
    int __fastcall Y2N( int v );

    void SetDBounds( MyRect& b, PDataGPS p );
    void FromNE( PDataGPS p, int& x, int& y );
    void DrawArray( TCanvas *dc, const GPSPointsArray& ar, TColor cl, int& nDraw );

    DEF_PROP_VP( int, Zoom, ; )
};

#endif
