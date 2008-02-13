#ifndef __MY_INT
#define __MY_INT

#include "HCFGStorage.h"
#include "HLog.h"
#include "pNMEA.h"

LOCALSTRUCTBASE( DataGPS, public GPS_NMEAParser )
  int     RMC_x, RMC_y;
  int     GGA_x, GGA_y;
};

typedef void __fastcall(__closure *GPSDataChangeEvent)( void );
typedef void __fastcall(__closure *GPSDataFollowEvent)( int idx );

LOCALCLASSBASE( GPSDataArray, public MyRefArray<DataGPS> )
  public:
    GPSDataArray( void ) : MyRefArray<DataGPS>( 100,1000 ) {}

    void Changed( void );
    void Follow( int idx );
    void Refilter( void );

    MyValArray<GPSDataChangeEvent> OnChange;
    MyValArray<GPSDataFollowEvent> OnFollow;
    MyValArray<GPSDataChangeEvent> OnRefilter;
};
extern GPSDataArray Data;

//---------------------------------------------------------------------------
#define GPT_DOUBLE    0x0000    // double
#define GPT_INT       0x0001    // int
#define GPT_VALID     0x0002    // BYTE         'A' - valid, 'V' - warning
#define GPT_MODE      0x0003    // BYTE         M = manual, A = automatic 2D/3D
#define GPT_FIXMODE   0x0004    // BYTE         1 = fix not available, 2 = 2D, 3 = 3D
#define GPT_QUALITY   0x0005    // BYTE         0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid
#define GPT_SATINFO   0x0006    // GPN_DataGSV
#define GPT_TIME      0x0007    // time_t
#define GPT_SATS      0x0008    // WORD[]
#define GPT_VALIDF    0x0009    // WORD

#define GPT_VIRTUAL   0x1000

#define GPT_MASK      0x00FF
#define GPT_ALLTYPE   GPT_MASK

typedef bool (*GPSGetVirtualData)( PDataGPS p, int idx, LPVOID buff, size_t bsz );

LOCALSTRUCT( GPSFieldInfo )
  WORD                  ValidCheck;
  WORD                  Type;
  DWORD                 Off;
  CONSTSTR              Name;
  CONSTSTR              Desc;
  GPSGetVirtualData     GetData;
};

extern GPSFieldInfo GPSFields[];

//---------------------------------------------------------------------------
#define GPS_MAX_COLS 50

LOCALCLASSBASE( GPSColArray, public MyValArray<int> )
  public:
    GPSColArray( void ) : MyValArray<int>( 10, 10 ) {}

    bool Has( int idx );
    void Set( CONSTSTR p );
    void Set( const GPSColArray& p );
};

//---------------------------------------------------------------------------
// PROCS
//---------------------------------------------------------------------------
/*[utils.cpp]*/
void         UtilsInit( TForm *Owner, PHLogComboBox lList, PHCfgStorage cfg );
void         UtilsShutdown( void );

PHOperation  RTGetOperation( void );
PPRPeriod    RTGetIdlePeriod( void );
class HRop {
   PHOperation op;
  public:
    __fastcall HRop( void )          { op = RTGetOperation(); op->IncShow(); }
    __fastcall HRop( PHOperation p ) { op = p; if (op) op->IncShow(); }
    __fastcall ~HRop()               { if (op) op->SetText(NULL); }

   PHOperation operator->() { return op; }

   void Close( void ) { if (op) { op->SetText(NULL); op = NULL; } }
};

int          RTLog( CONSTSTR msg,... );
int          RTLogV( CONSTSTR msg,va_list a );
int          RTLogR( CONSTSTR msg,... );
int          RTLogRV( CONSTSTR msg,va_list a );
void         RTErrorMessage( HWND w,CONSTSTR fmt,... );
void         RTErrorMessageV( HWND w,CONSTSTR fmt,va_list a );
void         RTSayMessage( HWND w,CONSTSTR fmt,... );
void         RTSayMessageV( HWND w,CONSTSTR fmt,va_list a );

#define ERROR_NUMBER   -777.0
#define HAVENO_NUMBER  0.0

bool         IsFieldNumber( int fIdx );
CONSTSTR     Field2Str( GPSDataArray& ar, int dIdx, int fIdx );
double       Field2Number( GPSDataArray& ar, int dIdx, int fIdx );

//[f_Config.cpp]
bool Configure( TForm *Parent );

//[f_DataList.cpp]
void NewDataList( PTForm Parent );

//[f_DataGraph.cpp]
void NewDataGraph( PTForm Parent );

//[f_DataPath.cpp]
void NewDataPath( PTForm Parent );

//[f_CfgCols.cpp]
bool ConfigureCols( TForm *Parent, GPSColArray& Cols, bool NumberOnly );

//---------------------------------------------------------------------------
// DATA
//---------------------------------------------------------------------------
extern PHStorageLink       Opt;
extern GPN_Filter          FOpts;

#define COL( n )         STrim( (char*)StrGetCol( m, n, "," ))
#define GOPT( nm, v )    Opt->Read( nm, v )
#define SOPT( nm, v )    Opt->Write( nm, v )

#define LNG
#define SLNG( v )        v
#endif