object ListForm: TListForm
  Left = 440
  Top = 204
  Width = 546
  Height = 413
  Caption = 'GPS data list'
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
  object header: THeaderControl
    Left = 0
    Top = 31
    Width = 538
    Height = 17
    DragReorder = False
    Sections = <
      item
        ImageIndex = -1
        Width = 50
      end
      item
        ImageIndex = -1
        Width = 50
      end>
    Style = hsFlat
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 538
    Height = 31
    Align = alTop
    BevelInner = bvLowered
    TabOrder = 1
    object btnSave: TToolbarButton97
      Left = 190
      Top = 5
      Width = 66
      Height = 22
      Caption = 'Save'
      OnClick = btnSaveClick
    end
    object btnSet: TToolbarButton97
      Left = 260
      Top = 5
      Width = 66
      Height = 22
      Caption = 'Load'
      OnClick = btnSetClick
    end
    object btnDelete: TToolbarButton97
      Left = 330
      Top = 5
      Width = 66
      Height = 22
      Caption = 'Delete'
      OnClick = btnDeleteClick
    end
    object btnCfg: TToolbarButton97
      Left = 465
      Top = 5
      Width = 66
      Height = 22
      Caption = '&Config'
      OnClick = btnCfgClick
    end
    object cbKeyNum: TComboBox
      Left = 5
      Top = 5
      Width = 181
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnDropDown = cbKeyNumDropDown
    end
  end
  object list: HBkList
    Left = 0
    Top = 48
    Width = 538
    Height = 338
    TabStop = True
    Align = alClient
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 2
    OnDblClick = listDblClick
    Items.Strings = (
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0
      #0#0#0#0)
    ItemHeight = 16
    BkColor = clWindow
    ItemsCount = 10
    Header = header
    SectionDelimiters = ';'
    Options = [bkoVirtual, bkoColLines, bkoRowLines, bkoShowSelection]
    OnDrawItemSection = listDrawItemSection
  end
end
