#include <all_wlib.h>
#pragma hdrstop
//  Какой-то русский текст, чтобы ФАР дурака не валял...

#include "int.h"

int _matherr(struct _exception *e)
  {
     RTLog( "Math error! Type: %d in \"%s\" with args: %lf, %lf",
            e->type, e->name, e->arg1, e->arg2 );
     e->retval = -1;
 return 1;
}

/*******************************************************************
   LOCALS
 *******************************************************************/
static PHOperation       Rop       = NULL;
static PPRPeriod         ROPPeriod = NULL;
static PHLogComboBox     LogList   = NULL;
static HGetStringProc_t  OldLogName;

static CONSTSTR RTL_CALLBACK idGetLogName( void ) { return LogList ? LogList->LogFile.c_str() : NULL; }

/*******************************************************************
   GPS_Data
 *******************************************************************/
/*******************************************************************
   INIT
 *******************************************************************/
void UtilsInit( TForm *Owner, PHLogComboBox lList, PHCfgStorage cfg )
  {  char str[ MAX_PATH_SIZE ];

     LogList       = lList;
     ROPPeriod     = new PRPeriod( 400 );
     Rop           = new HOperation( Owner );

     if (cfg)   cfg->FileName  = CTGetArgPathName( "CFG", cfg->FileName.c_str(),  str, ARRAY_SIZE(str) );
     if (lList) lList->LogFile = CTGetArgPathName( "LOG", lList->LogFile.c_str(), str, ARRAY_SIZE(str) );

     //Create handle
     if (lList) (void)lList->Handle;

     OldLogName = SetLogNameProc( idGetLogName );

     RTLog( "------------------------------------------" );
     char nm[ MAX_PATH_SIZE ];
     time_t tm;
     nm[ GetModuleFileName( NULL, nm, sizeof(nm) ) ] = 0;
     RTLog( LNG("Programm: %s"), nm );
     if ( !GetFileTimes( nm, &tm, NULL, NULL ) )
       RTLog( LNG("Version: Error getting programm version!") );
      else {
       PRTime ctm;
       ctm.Set( tm );
       RTLog( LNG("Vesion: %s"), ctm.GetStr(NULL,0) );
     }
     RTLog( "------------------------------------------" );
}

void UtilsShutdown( void )
  {
     RTLog( LNG("Shutting down...") );
     LogList = NULL;
     delete ROPPeriod; ROPPeriod = NULL;
     delete Rop;       Rop       = NULL;
     SetLogNameProc( OldLogName );
}

/*******************************************************************
   UTILS
 *******************************************************************/
// --------------------------------------------------------------------------------
PHOperation  RTGetOperation( void )  { TraceAssert(Rop);       return Rop; }
PPRPeriod    RTGetIdlePeriod( void ) { TraceAssert(ROPPeriod); return ROPPeriod; }
// --------------------------------------------------------------------------------
int RTLog( CONSTSTR msg,... )
  {  va_list a;

     if ( LogList ) {
       va_start( a,msg );
         LogList->AddV( msg, a );
       va_end( a );
     }
 return 1;
}

int RTLogV( CONSTSTR msg,va_list a )
  {
     if ( LogList ) LogList->AddV( msg, a );
 return 1;
}

int RTLogR( CONSTSTR msg,... )
  {  va_list a;

     if ( LogList ) {
       va_start( a,msg );
         LogList->AddV( msg, a );
       va_end( a );
     }

     va_start( a,msg );
       RTGetOperation()->SetTextV(  msg,a );
     va_end( a );
 return 1;
}

int RTLogRV( CONSTSTR msg,va_list a )
  {
     if ( LogList ) LogList->AddV( msg, a );
     RTGetOperation()->SetTextV(  msg,a );
 return 1;
}

void RTErrorMessage( HWND w,CONSTSTR fmt,... )
  {  va_list  argptr;
     MyString m;

     va_start(argptr,fmt);
       RTLogV(fmt,argptr);
     va_end(argptr);

     va_start(argptr,fmt);
       m.vprintf( fmt, argptr );
       MessageBox( w ? w : Application->Handle,
                   m.Text(),
                   LNG("Error..."),
                   MB_ICONHAND|MB_OK );
     va_end(argptr);
}

void RTErrorMessageV( HWND w,CONSTSTR fmt,va_list a )
  {  MyString m;

     RTLogV(fmt,a);
     m.vprintf( fmt, a );
     MessageBox( w ? w : Application->Handle, m.Text(), LNG("Error..."), MB_ICONHAND|MB_OK );
}

void RTSayMessage( HWND w,CONSTSTR fmt,... )
  {  va_list  argptr;
     MyString m;

     va_start(argptr,fmt);
       m.vprintf( fmt, argptr );
       MessageBox( w ? w : Application->Handle, m.Text(), LNG("Warning..."), MB_ICONHAND|MB_OK );
     va_end(argptr);
}

void RTSayMessageV( HWND w,CONSTSTR fmt,va_list a )
  {  MyString m;

     m.vprintf( fmt, a );
     MessageBox( w ? w : Application->Handle, m.Text(), LNG("Warning..."), MB_ICONHAND|MB_OK );
}
/*******************************************************************
   GPSColArray
 *******************************************************************/
bool GPSColArray::Has( int idx )
  {
     for( int n = 0; n < Count(); n++ )
       if ( Item(n) == idx )
         return true;
 return false;
}
void GPSColArray::Set( CONSTSTR p )
  {
     DeleteAll();
     for( ; *p; p++ )
       Add( (int)(*p - 1) );
}
void GPSColArray::Set( const GPSColArray& ar )
  {
     DeleteAll();
     for( int n = 0; n < ar.Count(); n++ )
       Add( ar[n] );
}
/*******************************************************************
   GPSDataArray
 *******************************************************************/
void GPSDataArray::Changed( void )
  {
     for( int n = 0; n < OnChange.Count(); n++ )
       OnChange[n]();
}
void GPSDataArray::Refilter( void )
  {
     for( int n = 0; n < OnRefilter.Count(); n++ )
       OnRefilter[n]();
}
void GPSDataArray::Follow( int idx )
  {
     if ( idx >= 0 && idx < Count() )
       for( int n = 0; n < OnFollow.Count(); n++ )
         OnFollow[n]( idx );
}
/*******************************************************************
   FIELDS
 *******************************************************************/
GPSDataArray Data;

bool idVGetLatDiff( PDataGPS p, int, LPVOID buff, size_t bsz ) { *((double*)buff) = p->GGA.Lat - p->RMC.Lat; return true; }
bool idVGetLonDiff( PDataGPS p, int, LPVOID buff, size_t bsz ) { *((double*)buff) = p->GGA.Lon - p->RMC.Lon; return true; }

bool idVGetGGALatMove( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev )
       *((double*)buff) = 0;
      else
       *((double*)buff) = p->GGA.Lat - prev->GGA.Lat;
 return true;
}
bool idVGetGGALonMove( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev )
       *((double*)buff) = 0;
      else
       *((double*)buff) = p->GGA.Lon - prev->GGA.Lon;
 return true;
}
bool idVGetVTGSpeedInc( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev ||
          p->Time == prev->Time )
       return false;

     if ( IS_FLAG( prev->Valid, GPV_VTG ) &&
          IS_FLAG( p->Valid, GPV_VTG ) )
       *((double*)buff) = Abs(p->VTG.SpeedKm - prev->VTG.SpeedKm) / 3600 * 1000 / (p->Time - prev->Time);
      else
     if ( IS_FLAG( prev->Valid, GPV_RMC ) &&
          IS_FLAG( p->Valid, GPV_RMC ) )
       *((double*)buff) = GPS_KNOT_TO_KM( Abs(p->RMC.GroundSpeed - prev->RMC.GroundSpeed) ) / 3600 * 1000 / (p->Time - prev->Time);
      else
       return false;

 return true;
}
bool idVGetRMCSpeedInc( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev ||
          p->Time == prev->Time )
       return false;

     if ( IS_FLAG( prev->Valid, GPV_RMC ) &&
          IS_FLAG( p->Valid, GPV_RMC ) )
       *((double*)buff) = GPS_KNOT_TO_KM(Abs(p->RMC.GroundSpeed - prev->RMC.GroundSpeed)) / 3600 * 1000 / (p->Time - prev->Time);
      else
       return false;

 return true;
}

bool idVGetGGADist( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev ||
          !IS_FLAG( prev->Valid, GPV_GGA ) )
       return false;

     if ( !prev->GGA.n || !prev->GGA.e ||
          !p->GGA.n    || !p->GGA.e )
       return false;

     *((int*)buff) = prev->LengthToGGA( *p );
 return true;
}

bool idVGetRMCDist( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {  PDataGPS prev = Data.Item( idx-1 );
     if ( !prev ||
          !IS_FLAG( prev->Valid, GPV_RMC ) )
       return false;

     if ( !prev->RMC.n || !prev->RMC.e ||
          !p->RMC.n || !p->RMC.e )
       return false;

     int x = Abs(prev->RMC.n - p->RMC.n),
         y = Abs(prev->RMC.e - p->RMC.e);
     if ( !x && !y ) {
       *((int*)buff) = 0;
       return true;
     }

     *((int*)buff) = prev->LengthToRMC( *p );
 return true;
}
bool idVGetRMCSpeedKm( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {
     *((double*)buff) = GPS_KNOT_TO_KM( p->RMC.GroundSpeed );
 return true;
}
bool idVGetRMCSpeedM( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {
     *((double*)buff) = GPS_KNOT_TO_KM(p->RMC.GroundSpeed) / 3600 * 1000;
 return true;
}
bool idVGetNDiff( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {
     *((int*)buff) = p->GGA.n - p->RMC.n;
 return true;
}
bool idVGetEDiff( PDataGPS p, int idx, LPVOID buff, size_t bsz )
  {
     *((int*)buff) = p->GGA.e - p->RMC.e;
 return true;
}

GPSFieldInfo GPSFields[] = {
 /*001*/ { 0,        GPT_TIME,        OffsetOf( DataGPS, Time ), "Time", "Data packet time" },
 /*002*/ { 0,        GPT_VALIDF,      OffsetOf( DataGPS, Valid), "Valid", "Valid flags" },

//GGA
#define D( tp, nm, h, desc )  { GPV_GGA,  tp, OffsetOf( DataGPS, GGA ) + OffsetOf( GPN_DataGGA, nm ), h, desc },
 /*003*/   D( GPT_DOUBLE,      Lat,             "GGA Lat",   "Latitude" )
 /*004*/   D( GPT_DOUBLE,      Lon,            "GGA Lon",   "Longitude" )
 /*005*/   D( GPT_QUALITY,     Quality,          "GGA Qual",  "Quality 0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid" )
 /*006*/   D( GPT_INT,         SatsInUse,      "GGA nsats", "Num of Sats In Use" )
 /*007*/   D( GPT_DOUBLE,      HDOP,                 "GGA HDOP",  "GGA HDOP" )
 /*008*/   D( GPT_DOUBLE,      Alt,             "GGA Alt",   "Altitude: mean-sea-level (geoid) meters" )
#undef D

//GSA
#define D( tp, nm, h, desc )  { GPV_GSA,  tp, OffsetOf( DataGPS, GSA ) + OffsetOf( GPN_DataGSA, nm ), h, desc },
 /*009*/   D( GPT_MODE,        Mode,                "GSA Mode",  "GSA Mode M = manual, A = automatic 2D/3D" )
 /*010*/   D( GPT_FIXMODE,     FixMode,             "GSA FixM",  "GSA Fix Mode 1 = fix not available, 2 = 2D, 3 = 3D" )
 /*011*/   D( GPT_SATS,        SatsInSolution,       "GSA nsats", "GSA Sats In Solution" )
 /*012*/   D( GPT_DOUBLE,      PDOP,                 "GSA PDOP",  "GSA PDOP")
 /*013*/   D( GPT_DOUBLE,      HDOP,                 "GSA HDOP",  "GSA HDOP")
 /*014*/   D( GPT_DOUBLE,      VDOP,                 "GSA VDOP",  "GSA VDOP")
#undef D

//GSV
 /*015*/   { GPV_GSV,  GPT_SATINFO, OffsetOf( DataGPS, GSV),    "GSV SatInfo", "Sattelites information" },

//RMC
#define D( tp, nm, h, desc )  { GPV_RMC,  tp, OffsetOf( DataGPS, RMC ) + OffsetOf( GPN_DataRMC, nm ), h, desc },
 /*016*/   D( GPT_VALID,       Valid,           "RMC Valid", "RMC Valid A = Data valid, V = navigation rx warning" )
 /*017*/   D( GPT_DOUBLE,      Lat,             "RMC Lat",   "RMC Latitude" )
 /*018*/   D( GPT_DOUBLE,      Lon,            "RMC Lon",   "RMC Longitude" )
 /*019*/   D( GPT_DOUBLE,      GroundSpeed,          "RMS SpdKn", "RMC speed over ground, knots" )
 /*020*/   D( GPT_DOUBLE,      Course,               "RMC Cource","RMC course over ground, degrees true" )
 /*021*/   D( GPT_DOUBLE,      MagVar,               "RMS MVari", "magnitic variation, degrees East(+)/West(-)" )
#undef D

//VTG
#define D( tp, nm, h, desc )  { GPV_VTG,  tp, OffsetOf( DataGPS, VTG ) + OffsetOf( GPN_DataVTG, nm ), h, desc },
 /*022*/   D( GPT_DOUBLE,      CourceI,                 "VTG ICourse", "VTG ist course" )
 /*023*/   D( GPT_DOUBLE,      CourceM,                 "VTG MCourse", "VTG magn course" )
 /*024*/   D( GPT_DOUBLE,      SpeedU,                  "VTG SpdKn",   "VTG speed in knots" )
 /*025*/   D( GPT_DOUBLE,      SpeedKm,                 "VTG SpdKm",   "VTG speed in km/h" )
#undef D

//Coord diff
 /*026*/   { GPV_RMC|GPV_GGA,  GPT_VIRTUAL|GPT_DOUBLE, 0,  "v LatDiff", "RMC/GGA lat difference", idVGetLatDiff },
 /*027*/   { GPV_RMC|GPV_GGA,  GPT_VIRTUAL|GPT_DOUBLE, 0,  "v LonDiff", "RMC/GGA lon difference", idVGetLonDiff },

//Coords move
 /*028*/   { GPV_GGA,          GPT_VIRTUAL|GPT_DOUBLE, 0,  "v Lat+",    "GGA lat move from last pos", idVGetGGALatMove },
 /*029*/   { GPV_GGA,          GPT_VIRTUAL|GPT_DOUBLE, 0,  "v Lon+",    "GGA lon move from last pos", idVGetGGALonMove },

//NE
#define D( tp, nm, h, desc )  { GPV_GGA,  tp, OffsetOf(DataGPS,GGA)+OffsetOf(GPN_DataGGA,nm), h, desc },
 /*030*/   D( GPT_INT, n,  "GGA n",    "GGA northing" )
 /*031*/   D( GPT_INT, e,  "GGA e",    "GGA easting" )
#undef D
#define D( tp, nm, h, desc )  { GPV_RMC,  tp, OffsetOf(DataGPS,RMC)+OffsetOf(GPN_DataRMC,nm), h, desc },
 /*032*/   D( GPT_INT, n,  "RMC n",    "RMC northing" )
 /*033*/   D( GPT_INT, e,  "RMC e",    "RMC easting" )
#undef D
 /*034*/   { 0,                GPT_VIRTUAL|GPT_DOUBLE, 0,  "v Spd+",    "VTG or RMC speed increment", idVGetVTGSpeedInc },
 /*035*/   { GPV_GGA,          GPT_VIRTUAL|GPT_INT,    0,  "v GGA +",   "GGA distance",        idVGetGGADist },
 /*036*/   { GPV_RMC,          GPT_VIRTUAL|GPT_INT,    0,  "v RMC +",   "RMC distance",        idVGetRMCDist },
 /*037*/   { GPV_RMC,          GPT_VIRTUAL|GPT_DOUBLE, 0,  "RMC SpdKm", "RMC speed in km\\h",  idVGetRMCSpeedKm },
 /*038*/   { GPV_RMC,          GPT_VIRTUAL|GPT_DOUBLE, 0,  "RMC SpdM",  "RMC speed in m\\s",   idVGetRMCSpeedM },
 /*039*/   { GPV_RMC,          GPT_VIRTUAL|GPT_DOUBLE, 0,  "RMC Spd+",  "RMC speed increment", idVGetRMCSpeedInc },
 /*040*/   { GPV_GGA|GPV_RMC,  GPT_VIRTUAL|GPT_INT,    0,  "N Diff",    "GGA/RMC north difference", idVGetNDiff },
 /*041*/   { GPV_GGA|GPV_RMC,  GPT_VIRTUAL|GPT_INT,    0,  "E Diff",    "GGA/RMC easting difference", idVGetEDiff },
{0}};

//---------------------------------------------------------------------------
static CONSTSTR idDouble2Str( LPVOID p ) { return Message( "%3.6lf", *((double*)p) ); }
static CONSTSTR idInt2Str( LPVOID p )    { return Message( "%d", *((int*)p) ); }
static CONSTSTR idByte2Str( LPVOID p )   { return Message( "%c", *((char*)p) ); }
static CONSTSTR idQuality( LPVOID p ) {
     switch( *((BYTE*)p) ) {
       case 0: return "NF";
       case 1: return "F";
       case 2: return "F sps";
       case 3: return "F pps";
       case 6: return "F drm";
       default: return Message( "Unk: %d", *((BYTE*)p) );
     }
}
static CONSTSTR idFixMode( LPVOID p ) {
     switch( *((BYTE*)p) ) {
       case 1: return "NF";
       case 2: return "2d";
       case 3: return "3d";
       default: return Message( "Unk: %d", *((BYTE*)p) );
     }
}
static CONSTSTR idDataValid( LPVOID p ) {
     switch( *((char*)p) ) {
       case 'A': return "Valid";
       case 'V': return "Warning";
       default: return Message( "Unk: %02X", *((BYTE*)p) );
     }
}
static CONSTSTR idSatInfo2Str( LPVOID _p ) {
  PGPN_DataGSV p = (PGPN_DataGSV)_p;
  static PathString str;

     str = "";
     for( int n = 0; n < NP_MAX_CHAN; n++ )
       if ( p->SatInfo[n].IsUsed )
         str.cat( "%d[%d] ", p->SatInfo[n].SatID, p->SatInfo[n].Quality );
 return str.c_str();
}
static CONSTSTR idSats2Str( LPVOID _p )
  {  WORD *p = (WORD*)_p;
     static PathString str;

     str = "";
     for( ; *p; p++ )
       str.cat( "%d ", *p );

 return str.c_str();
}
static CONSTSTR idTime2Str( LPVOID _p )
  {  static char str[ 20 ];
     strftime( str,sizeof(str),"%d-%m-%Y %H:%M:%S",localtime( (time_t*)_p ) );
 return str;
}
static CONSTSTR idValidField( LPVOID _p )
  {  WORD p = *(WORD*)_p;
     static PathString str;

     str = "";
     if ( IS_FLAG( p, GPV_GGA ) ) str.cat( "GGA " );
     if ( IS_FLAG( p, GPV_GSA ) ) str.cat( "GSA " );
     if ( IS_FLAG( p, GPV_GSV ) ) str.cat( "GSV " );
     if ( IS_FLAG( p, GPV_RMC ) ) str.cat( "RMC " );
     if ( IS_FLAG( p, GPV_VTG ) ) str.cat( "VTG " );

 return str.c_str();
}

typedef CONSTSTR (*GPSData2Str)( LPVOID );
GPSData2Str Info2StrTypes[] = {
  /*GPT_DOUBLE    double*/ idDouble2Str,
  /*GPT_INT       int*/    idInt2Str,
  /*GPT_VALID     BYTE*/   idDataValid,
  /*GPT_MODE      BYTE*/   idByte2Str,
  /*GPT_FIXMODE   BYTE*/   idFixMode,
  /*GPT_QUALITY   BYTE*/   idQuality,
  /*GPT_SATINFO   GPN_DataGSV*/idSatInfo2Str,
  /*GPT_TIME      time_t*/ idTime2Str,
  /*GPT_SATS      WORD[]*/ idSats2Str,
  /*GPT_VALIDF    WORD*/   idValidField,
};

CONSTSTR Field2Str( GPSDataArray& ar, int dIdx, int fIdx )
  {  if ( fIdx < 0 || fIdx >= ARRAY_SIZE(GPSFields) )
       return "Inv field idx";

     PDataGPS p = ar.Item( dIdx );
     if ( !p ) return "Inv data idx";

     PGPSFieldInfo fi = &GPSFields[ fIdx ];
     if ( fi->ValidCheck &&
          !IS_FLAG( p->Valid, fi->ValidCheck ) )
       return "";

     WORD tp = fi->Type & GPT_MASK;
     if ( tp >= ARRAY_SIZE(Info2StrTypes) )
       return "Inv type";


     if ( IS_FLAG( fi->Type, GPT_VIRTUAL ) ) {
       static BYTE buff[ 500 ];
       if ( !fi->GetData ||
            !fi->GetData( p, dIdx, buff, sizeof(buff) ) )
         return "";

       return Info2StrTypes[ tp ]( buff );
     } else
       return Info2StrTypes[ tp ]( (LPVOID)( ((LPBYTE)p) + fi->Off ) );
}

//---------------------------------------------------------------------------
bool IsFieldNumber( int fIdx )
  {  if ( fIdx < 0 || fIdx >= ARRAY_SIZE(GPSFields) )
       return false;

     switch( GPSFields[ fIdx ].Type&GPT_MASK ) {
       case GPT_DOUBLE:
       case GPT_INT:
       case GPT_VALID:
       case GPT_MODE:
       case GPT_FIXMODE:
       case GPT_QUALITY:
       case GPT_TIME:    return true;

       case GPT_VALIDF:
       case GPT_SATINFO:
       case GPT_SATS:
       default:          return false;
     }
}

//---------------------------------------------------------------------------
double idDouble2Num( LPVOID p ) { return *((double*)p); }
double idInt2Number( LPVOID p ) { return *((int*)p); }
double idDataValid2Number( LPVOID p ) {
  switch( *((char*)p) ) {
    case 'A': return 100;
    case 'V': return HAVENO_NUMBER;
     default: return ERROR_NUMBER;
  }
}
double idMode2Number( LPVOID p ) {
  switch( *((char*)p) ) {
    case 'M': return 10;
    case 'A': return 5;
     default: return ERROR_NUMBER;
  }
}
double idFixMode2Number( LPVOID p ) {
  switch( *((BYTE*)p) ) {
    case 1: return HAVENO_NUMBER;
    case 2: return 50;
    case 3: return 100;
    default: return ERROR_NUMBER;
  }
}
double idQuality2Number( LPVOID p ) {
  switch( *((BYTE*)p) ) {
    case 0: return HAVENO_NUMBER;
    case 1: return 100;
    case 2: return 200;
    case 3: return 300;
    case 6: return 600;
    default: return ERROR_NUMBER;
  }
}
double idTime2Number( LPVOID p ) {
  return *((time_t*)p);
}

typedef double (*GPSData2Number)( LPVOID );
GPSData2Number Info2NumberTypes[] = {
  /*GPT_DOUBLE    double*/ idDouble2Num,
  /*GPT_INT       int*/    idInt2Number,
  /*GPT_VALID     BYTE*/   idDataValid2Number,
  /*GPT_MODE      BYTE*/   idMode2Number,
  /*GPT_FIXMODE   BYTE*/   idFixMode2Number,
  /*GPT_QUALITY   BYTE*/   idQuality2Number,
  /*GPT_SATINFO   GPN_DataGSV*/NULL,
  /*GPT_TIME      time_t*/ idTime2Number,
  /*GPT_SATS      WORD[]*/ NULL,
  /*GPT_VALIDF    WORD*/   NULL,
};

double Field2Number( GPSDataArray& ar, int dIdx, int fIdx )
  {  if ( fIdx < 0 || fIdx >= ARRAY_SIZE(GPSFields) )
       return ERROR_NUMBER;

     if ( !IsFieldNumber( fIdx ) )
       return ERROR_NUMBER;

     PDataGPS p = ar.Item( dIdx );
     if ( !p ) return ERROR_NUMBER;

     PGPSFieldInfo fi = &GPSFields[ fIdx ];
     if ( fi->ValidCheck &&
          !IS_FLAG( p->Valid, fi->ValidCheck ) )
       return HAVENO_NUMBER;

     WORD tp = fi->Type & GPT_MASK;
     if ( tp >= ARRAY_SIZE(Info2StrTypes) )
       return ERROR_NUMBER;


     if ( IS_FLAG( fi->Type, GPT_VIRTUAL ) ) {
       static BYTE buff[ 500 ];
       if ( !fi->GetData )
         return ERROR_NUMBER;
       if ( !fi->GetData( p, dIdx, buff, sizeof(buff) ) )
         return HAVENO_NUMBER;

       return Info2NumberTypes[ tp ]( buff );
     } else
       return Info2NumberTypes[ tp ]( (LPVOID)( ((LPBYTE)p) + fi->Off ) );
}

