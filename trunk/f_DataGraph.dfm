object DataGraphForm: TDataGraphForm
  Left = 409
  Top = 289
  Width = 615
  Height = 391
  Caption = 'Data graph'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 607
    Height = 31
    Align = alTop
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 5
      Top = 10
      Width = 27
      Height = 13
      Caption = 'Value'
    end
    object ToolbarButton971: TToolbarButton97
      Left = 200
      Top = 5
      Width = 61
      Height = 22
      Caption = '&Fill'
      OnClick = ToolbarButton971Click
    end
    object ToolbarButton972: TToolbarButton97
      Left = 270
      Top = 5
      Width = 46
      Height = 22
      DropdownAlways = True
      DropdownArrow = False
      DropdownMenu = HPopupMenu1
      Caption = 'Cfg'
    end
    object cbTypes: TComboBox
      Left = 50
      Top = 5
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object graph: HValueGraph
    Left = 0
    Top = 31
    Width = 607
    Height = 314
    Align = alClient
    Color = clBtnFace
    TabOrder = 1
    OnDblClick = graphDblClick
    HScroller.Min.Value = 39484.9460948264
    HScroller.Min.TimeValue = 39484.9460948264
    HScroller.Max.Value = 39484.9877614931
    HScroller.Max.TimeValue = 39484.9877614931
    HScroller.Start.Value = 39484.9665809375
    HScroller.Start.TimeValue = 39484.9665809375
    HScroller.Finish.Value = 39484.9672753819
    HScroller.Finish.TimeValue = 39484.9672753819
    HScroller.Step.Value = 1.15740740740741E-5
    HScroller.Step.TimeValue = 1.15740740740741E-5
    VScroller.Min.Value = -10
    VScroller.Min.TimeValue = -10
    VScroller.Max.Value = 10
    VScroller.Max.TimeValue = 10
    VScroller.Start.Value = -2
    VScroller.Start.TimeValue = -2
    VScroller.Finish.Value = 4
    VScroller.Finish.TimeValue = 4
    VScroller.Step.Value = 0.5
    VScroller.Step.TimeValue = 0.5
    VScroller.Orientation = Vertical
    HScale.TimeValue = True
    HScale.MinValue.Value = 1.15740740740741E-5
    HScale.MinValue.TimeValue = 1.15740740740741E-5
    HScale.BigValue.Value = 0.000694444444444444
    HScale.BigValue.TimeValue = 0.000694444444444444
    HScale.SelectionBrush.Color = clYellow
    HScale.CursorPen.Color = 30976
    HScale.LabelFormat = 'hh'#39':'#39'nn'#39':'#39'ss'#39#13#39'mm'#39'.'#39'dd'#39'.'#39'yyyy'
    HScale.LabelOnEvery = True
    HScale.LabelPointType = lptT
    HScale.LabelFont.Charset = DEFAULT_CHARSET
    HScale.LabelFont.Color = clWindowText
    HScale.LabelFont.Height = -8
    HScale.LabelFont.Name = 'Small Fonts'
    HScale.LabelFont.Style = []
    HScale.TickMinWidth = 5
    HScale.GridPen.Color = 16744576
    HScale.GridBigPen.Color = 16719904
    VScale.MinValue.Value = 1E-8
    VScale.MinValue.TimeValue = 1E-8
    VScale.BigValue.Value = 1
    VScale.BigValue.TimeValue = 1
    VScale.Transparent = False
    VScale.SelectionBrush.Color = 11316396
    VScale.CursorPen.Color = 30976
    VScale.LabelFormat = '##0.##'
    VScale.LabelWidth = 40
    VScale.LabelPointType = lptFillRect
    VScale.LabelFont.Charset = DEFAULT_CHARSET
    VScale.LabelFont.Color = clWindowText
    VScale.LabelFont.Height = -8
    VScale.LabelFont.Name = 'Small Fonts'
    VScale.LabelFont.Style = []
    VScale.TickMinWidth = 5
    VScale.GridPen.Color = 16744576
    VScale.GridBigPen.Color = 16719904
    BorderType = HBOX_Rect
    AutoSelect = gstHorizontal
    HOnCursorChange = graphHOnCursorChange
    HOnSelectFinish = graphHOnSelectFinish
    BackoffWidth.Value = 0.000289351851851852
    BackoffWidth.TimeValue = 0.000289351851851852
    ColorsCount = 3
    GraphBkColor = clBtnFace
    LabelBkColor = clBtnFace
    ShowValueTick = True
    ValuePen.Width = 3
    GraphLineType = gltHisto
    PointType = gptCircle
  end
  object status: TStatusBar
    Left = 0
    Top = 345
    Width = 607
    Height = 19
    Panels = <
      item
        Alignment = taRightJustify
        Bevel = pbNone
        Text = 'Idx'
        Width = 30
      end
      item
        Width = 50
      end
      item
        Alignment = taRightJustify
        Bevel = pbNone
        Width = 100
      end
      item
        Width = 150
      end>
    SimplePanel = False
  end
  object HPopupMenu1: HPopupMenu
    OnMenuItemCheck = HPopupMenu1MenuItemCheck
    Left = 275
    Top = 25
    object H1: TMenuItem
      Caption = 'Horz grid'
      object B1: TMenuItem
        Tag = 100
        Caption = 'Big visible'
        OnClick = B1Click
      end
      object S1: TMenuItem
        Tag = 101
        Caption = 'Small visible'
        OnClick = S1Click
      end
    end
    object V1: TMenuItem
      Caption = 'Vert grid'
      object B2: TMenuItem
        Tag = 102
        Caption = 'Big visible'
        OnClick = B2Click
      end
      object S2: TMenuItem
        Tag = 103
        Caption = 'Small visible'
        OnClick = S2Click
      end
    end
    object G1: TMenuItem
      Caption = 'Graph type'
      object H2: TMenuItem
        Tag = 107
        Caption = 'Histogramm'
        OnClick = H2Click
      end
      object L1: TMenuItem
        Tag = 108
        Caption = 'Line'
        OnClick = L1Click
      end
      object B3: TMenuItem
        Tag = 109
        Caption = 'Bar'
        OnClick = B3Click
      end
    end
    object S3: TMenuItem
      Tag = 104
      Caption = 'Show values back'
      OnClick = S3Click
    end
    object S4: TMenuItem
      Tag = 105
      Caption = 'Show values ticks'
      OnClick = S4Click
    end
    object D1: TMenuItem
      Tag = 106
      Caption = 'Draw all values'
      OnClick = D1Click
    end
    object D2: TMenuItem
      Tag = 110
      Caption = 'Draw point symbol'
      OnClick = D2Click
    end
  end
end
