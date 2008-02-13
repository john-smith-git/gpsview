object PathForm: TPathForm
  Left = 545
  Top = 205
  Width = 602
  Height = 250
  Caption = 'Data path'
  Color = clBtnFace
  Constraints.MinHeight = 250
  Constraints.MinWidth = 150
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 594
    Height = 25
    Align = alTop
    BevelInner = bvLowered
    TabOrder = 1
    object Label1: TLabel
      Left = 395
      Top = 5
      Width = 62
      Height = 13
      Caption = 'Path interval '
    end
    object ToolbarButton971: TToolbarButton97
      Left = 3
      Top = 2
      Width = 58
      Height = 21
      Caption = 'Refresh'
      Flat = False
      OnClick = idRecreate
    end
    object btnZAdd: TToolbarButton97
      Left = 127
      Top = 2
      Width = 21
      Height = 21
      Caption = '+'
      Flat = False
      OnClick = btnZAddClick
    end
    object btnZDel: TToolbarButton97
      Left = 151
      Top = 2
      Width = 21
      Height = 21
      Caption = '-'
      Flat = False
      OnClick = btnZDelClick
    end
    object ToolbarButton972: TToolbarButton97
      Left = 180
      Top = 2
      Width = 51
      Height = 21
      DropdownAlways = True
      DropdownArrow = False
      DropdownMenu = HPopupMenu1
      Caption = 'Export'
      Flat = False
    end
    object chDAll: TCheckBox
      Left = 259
      Top = 3
      Width = 47
      Height = 17
      Caption = 'All'
      TabOrder = 0
      OnClick = idInvalidate
    end
    object chDFiltered: TCheckBox
      Left = 329
      Top = 3
      Width = 62
      Height = 17
      Caption = 'Filtered'
      TabOrder = 1
      OnClick = idInvalidate
    end
    object Edit1: TEdit
      Left = 460
      Top = 3
      Width = 36
      Height = 19
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 2
      Text = '0'
    end
    object btnInterval: TUpDown
      Left = 496
      Top = 3
      Width = 15
      Height = 19
      Associate = Edit1
      Min = 0
      Position = 0
      TabOrder = 3
      Wrap = False
    end
    object cbType: TComboBox
      Left = 65
      Top = 2
      Width = 56
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      OnClick = idRecreate
      Items.Strings = (
        'GGA'
        'RMC')
    end
    object chDX: TCheckBox
      Left = 524
      Top = 3
      Width = 42
      Height = 17
      Caption = 'dX'
      TabOrder = 5
      OnClick = idInvalidate
    end
  end
  object status: TStatusBar
    Left = 0
    Top = 204
    Width = 594
    Height = 19
    Panels = <
      item
        Alignment = taRightJustify
        Bevel = pbNone
        Text = 'N'
        Width = 20
      end
      item
        Width = 80
      end
      item
        Alignment = taRightJustify
        Bevel = pbNone
        Text = 'E'
        Width = 20
      end
      item
        Width = 80
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object scroll: TScrollBox
    Left = 0
    Top = 25
    Width = 594
    Height = 179
    HorzScrollBar.Style = ssHotTrack
    HorzScrollBar.Tracking = True
    VertScrollBar.Style = ssHotTrack
    VertScrollBar.Tracking = True
    Align = alClient
    BorderStyle = bsNone
    TabOrder = 0
    TabStop = True
    object paint: TPaintBox
      Left = 10
      Top = 10
      Width = 100
      Height = 100
      OnDblClick = paintDblClick
      OnMouseDown = paintMouseDown
      OnMouseMove = paintMouseMove
      OnPaint = paintPaint
    end
  end
  object HPopupMenu1: HPopupMenu
    Left = 205
    Top = 20
    object O1: TMenuItem
      Caption = 'OZI Explorer track file...'
      OnClick = O1Click
    end
  end
  object save: TSaveDialog
    Options = [ofOverwritePrompt, ofExtensionDifferent, ofPathMustExist, ofEnableSizing]
    Title = 'Select file to export...'
    Left = 240
    Top = 20
  end
end
