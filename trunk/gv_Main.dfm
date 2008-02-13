object MainForm: TMainForm
  Left = 473
  Top = 187
  Width = 696
  Height = 600
  Caption = 'GPSView'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object cbLog: HLogComboBox
    Left = 0
    Top = 533
    Width = 688
    Height = 21
    TabStop = False
    Style = csDropDownList
    BiDiMode = bdLeftToRight
    Color = clBtnFace
    Ctl3D = False
    DropDownCount = 20
    ItemHeight = 13
    ParentBiDiMode = False
    ParentCtl3D = False
    TabOrder = 0
    Align = alBottom
    Options = [acbLog, acbIndexOnLast, acbFileLog]
    LogFile = 'GPSView.log'
  end
  object wndFilter: HWindow
    Left = 0
    Top = 0
    Width = 688
    Height = 59
    Align = alTop
    TabOrder = 1
    BorderLeft.Options = [hcoSysColor, hcoSysFont, hcoLabel, hcoCaptionDblClick, hcoSizeClickRoll, hcoFlat]
    BorderLeft.Buttons = [hcbClose, hcbRoller, hcbCaption]
    BorderLeft.ScrollSize = 70
    BorderLeft.Bk = clGray
    BorderLeft.ActiveBk = 6956042
    BorderLeft.Fore = 13160660
    BorderLeft.ActiveFore = clWhite
    BorderLeft.ButtonColor = 13160660
    BorderLeft.Visible = False
    BorderLeft.Font.Charset = DEFAULT_CHARSET
    BorderLeft.Font.Color = clWindowText
    BorderLeft.Font.Height = -11
    BorderLeft.Font.Name = 'Tahoma'
    BorderLeft.Font.Style = [fsBold]
    BorderLeft.Borders = []
    BorderTop.Type = hbtNSRoller
    BorderTop.Caption = '  Filter'
    BorderTop.Options = [hcoSysFont, hcoLabel, hcoCaptionDblClick, hcoSizeClickRoll, hcoFlat]
    BorderTop.Buttons = [hcbCaption]
    BorderTop.Size = 13
    BorderTop.SizePercent = False
    BorderTop.ScrollSize = 70
    BorderTop.Bk = clGray
    BorderTop.ActiveBk = 12615808
    BorderTop.Fore = 13160660
    BorderTop.ActiveFore = clYellow
    BorderTop.ButtonColor = 13160660
    BorderTop.Font.Charset = DEFAULT_CHARSET
    BorderTop.Font.Color = clWindowText
    BorderTop.Font.Height = -11
    BorderTop.Font.Name = 'Tahoma'
    BorderTop.Font.Style = [fsBold]
    BorderTop.Borders = []
    BorderRight.Type = hbtNSScroller
    BorderRight.Options = [hcoSysColor, hcoSysFont, hcoCaptionDblClick, hcoSizeClickRoll, hcoFlat]
    BorderRight.Buttons = []
    BorderRight.Size = 7
    BorderRight.ScrollSize = 50
    BorderRight.Bk = clGray
    BorderRight.ActiveBk = 6956042
    BorderRight.Fore = 13160660
    BorderRight.ActiveFore = clWhite
    BorderRight.ButtonColor = 13160660
    BorderRight.Visible = False
    BorderRight.Font.Charset = DEFAULT_CHARSET
    BorderRight.Font.Color = clWindowText
    BorderRight.Font.Height = -11
    BorderRight.Font.Name = 'Tahoma'
    BorderRight.Font.Style = [fsBold]
    BorderRight.Borders = []
    BorderBottom.Type = hbtNSScroller
    BorderBottom.Options = [hcoSysColor, hcoSysFont, hcoCaptionDblClick, hcoSizeClickRoll, hcoFlat]
    BorderBottom.Buttons = []
    BorderBottom.Size = 7
    BorderBottom.ScrollSize = 50
    BorderBottom.Bk = clGray
    BorderBottom.ActiveBk = 6956042
    BorderBottom.Fore = 13160660
    BorderBottom.ActiveFore = clWhite
    BorderBottom.ButtonColor = 13160660
    BorderBottom.Visible = False
    BorderBottom.Font.Charset = DEFAULT_CHARSET
    BorderBottom.Font.Color = clWindowText
    BorderBottom.Font.Height = -11
    BorderBottom.Font.Name = 'Tahoma'
    BorderBottom.Font.Style = [fsBold]
    BorderBottom.Borders = []
    OutBorder = HBOX_None
    InBorder = HBOX_None
    PaintActive = [alTop, alBottom, alLeft, alRight]
    ActiveType = hwaAllways
    Active = True
    Actions = [hcbNone, hcbMinimize, hcbMaximize, hcbClose, hcbRoller, hcbRestore, hcbHelp, hcbCaption, hcbResize]
    ActionsOnParent = [hcbMinimize, hcbMaximize, hcbClose, hcbRoller, hcbRestore, hcbHelp, hcbCaption, hcbResize]
    StateBorder = alTop
    SavedRect = False
    SavedRectX = 0
    SavedRectY = 31
    SavedRectX1 = 607
    SavedRectY1 = 116
    InternalWindowState = 0
    object Label2: TLabel
      Left = 75
      Top = 6
      Width = 46
      Height = 13
      Caption = 'DOP limit:'
      ParentShowHint = False
      ShowHint = True
    end
    object Label3: TLabel
      Left = 175
      Top = 26
      Width = 40
      Height = 13
      Caption = 'Max diff:'
      ParentShowHint = False
      ShowHint = True
    end
    object btnRefilter: TToolbarButton97
      Left = 5
      Top = 4
      Width = 61
      Height = 22
      Caption = 'Fi&lter'
      Flat = False
      OnClick = btnRefilterClick
    end
    object Label4: TLabel
      Left = 345
      Top = 26
      Width = 40
      Height = 13
      Caption = 'Max diff:'
      ParentShowHint = False
      ShowHint = True
    end
    object Label5: TLabel
      Left = 475
      Top = 26
      Width = 40
      Height = 13
      Caption = 'Max diff:'
      ParentShowHint = False
      ShowHint = True
    end
    object Label6: TLabel
      Left = 275
      Top = 25
      Width = 8
      Height = 13
      Caption = 'm'
    end
    object Label7: TLabel
      Left = 445
      Top = 25
      Width = 23
      Height = 13
      Caption = 'm\ss'
    end
    object Label8: TLabel
      Left = 575
      Top = 25
      Width = 8
      Height = 13
      Caption = 'm'
    end
    object edtDOPMin: TEdit
      Left = 125
      Top = 2
      Width = 31
      Height = 21
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
    object chMove: TCheckBox
      Left = 175
      Top = 4
      Width = 161
      Height = 17
      Hint = 'Check max difference between'#10'coordinates reported by GGA and RMS'
      Caption = 'Check max move difference'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
    end
    object edtMoveDiff: TEdit
      Left = 225
      Top = 22
      Width = 46
      Height = 21
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object chMaxSpeedInc: TCheckBox
      Left = 345
      Top = 4
      Width = 126
      Height = 17
      Hint = 'Check for max speed increment'
      Caption = 'Check max speed inc'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
    end
    object edtMaxSpeedInc: TEdit
      Left = 395
      Top = 22
      Width = 46
      Height = 21
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
    end
    object chMaxPrevDiff: TCheckBox
      Left = 475
      Top = 4
      Width = 136
      Height = 17
      Hint = 
        'Check for max difference reported'#10'by GGA and RMS from previous p' +
        'osition'
      Caption = 'Check max coord diff'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
    end
    object edtMovePrevDiff: TEdit
      Left = 525
      Top = 21
      Width = 46
      Height = 21
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
    end
  end
  object MainMenu: HMainMenu
    OwnerDraw = True
    Left = 124
    Top = 14
    object F1: TMenuItem
      Caption = '&F Files'
      object mnuLoad: TMenuItem
        Caption = '&L Load...'
        ImageIndex = 15
        ShortCut = 16463
        OnClick = mnuLoadClick
      end
      object mnuClear: TMenuItem
        Caption = '&C Clear'
        OnClick = mnuClearClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object mnuConfig: TMenuItem
        Caption = '&F Options...'
        ImageIndex = 5
        ShortCut = 120
        OnClick = mnuConfigClick
      end
      object mnuSaveCfg: TMenuItem
        Caption = '&S Save configuration...'
        ShortCut = 8312
        OnClick = mnuSaveCfgClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mnuExit: TMenuItem
        Caption = '&X Exit'
        ImageIndex = 8
        ShortCut = 32856
        OnClick = mnuExitClick
      end
    end
    object Window1: TMenuItem
      Caption = '&Window'
      object mnuNewWindow: TMenuItem
        Caption = 'New window'
        object T1: TMenuItem
          Caption = 'Table'
          ShortCut = 16468
          OnClick = T1Click
        end
        object G1: TMenuItem
          Caption = 'Graph'
          ShortCut = 16455
          OnClick = G1Click
        end
        object P1: TMenuItem
          Caption = 'Path'
          ShortCut = 16464
          OnClick = P1Click
        end
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Tile1: TMenuItem
        Caption = 'Tile'
        OnClick = Tile1Click
      end
      object Cascade1: TMenuItem
        Caption = 'Cascade'
        OnClick = Cascade1Click
      end
      object ArrangeAll1: TMenuItem
        Caption = 'Arrange All'
        OnClick = ArrangeAll1Click
      end
      object N3: TMenuItem
        Caption = 'Next'
        ShortCut = 117
        OnClick = N3Click
      end
      object Previous1: TMenuItem
        Caption = 'Previous'
        ShortCut = 8309
        OnClick = Previous1Click
      end
      object N8: TMenuItem
        Caption = '-'
      end
      object Hide1: TMenuItem
        Caption = 'Close'
        ShortCut = 16471
        OnClick = Hide1Click
      end
    end
  end
  object HExceptionDialog1: HExceptionDialog
    Options = [vclxEnabled, vclxDumpToFile, vclxReadCode, vclxLoadExports, vclxLoadLocals, vclxDisasmCode, vclxPrintStackData, vclxPrintData]
    Left = 158
    Top = 14
  end
  object cfg: HCfgStorage
    AutoSave = False
    AutoLoad = False
    FileName = 'GPSView.hcfg'
    Left = 193
    Top = 14
  end
  object XPMenu1: TXPMenu
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Color = clBtnFace
    IconBackColor = clBtnFace
    MenuBarColor = clBtnFace
    SelectColor = clHighlight
    SelectBorderColor = clHighlight
    SelectFontColor = clMenuText
    DisabledColor = clInactiveCaption
    SeparatorColor = clBtnFace
    CheckedColor = clHighlight
    IconWidth = 24
    DrawSelect = True
    UseSystemColors = True
    OverrideOwnerDraw = False
    Gradient = False
    FlatMenu = True
    AutoDetect = True
    Active = True
    Left = 225
    Top = 14
  end
  object open: TOpenDialog
    FileName = 'txt'
    Filter = 'NMEA log file (*.txt)|*.txt;*.log'
    Options = [ofExtensionDifferent, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Select input file...'
    Left = 295
    Top = 15
  end
  object save: TSaveDialog
    Options = [ofOverwritePrompt, ofExtensionDifferent, ofPathMustExist, ofEnableSizing]
    Left = 260
    Top = 15
  end
end
