#include <all_wlib.h>
#pragma hdrstop
USERES("GPSView.res");
USEFORM("gv_Main.cpp", MainForm);
USEUNIT("utils.cpp");
USEFORM("f_Config.cpp", ConfigForm);
USEFORM("f_DataList.cpp", ListForm);
USEFORM("f_CfgCols.cpp", CfgColsForm);
USEFORM("f_DataGraph.cpp", DataGraphForm);
USEFORM("f_DataPath.cpp", PathForm);
USELIB("..\LIBS\GeoTransLib.lib");
USEUNIT("..\LIBS\GPS\pNMEA.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
  {
    try {
      Application->Initialize();
      Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
    }
    catch (Exception &exception) {
       Application->ShowException(&exception);
    }
 return 0;
}