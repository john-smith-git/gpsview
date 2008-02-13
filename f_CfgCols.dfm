object CfgColsForm: TCfgColsForm
  Left = 446
  Top = 260
  Width = 506
  Height = 485
  BorderIcons = [biSystemMenu]
  Caption = 'Cols configuration...'
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  ShowHint = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object btnCancel: TToolbarButton97
    Left = 386
    Top = 426
    Width = 111
    Height = 30
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    Flat = False
    ImageIndex = 34
    ModalResult = 2
    OnClick = btnCloseClick
  end
  object btnOk: TToolbarButton97
    Left = 267
    Top = 426
    Width = 111
    Height = 30
    Anchors = [akRight, akBottom]
    Default = True
    Caption = 'Ok'
    Flat = False
    ImageIndex = 32
    ModalResult = 1
    OnClick = btnOKClick
  end
  object Panel1: TPanel
    Left = 0
    Top = 5
    Width = 496
    Height = 416
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 1
      Top = 176
      Width = 494
      Height = 5
      Cursor = crVSplit
      Align = alTop
    end
    object list: HBkList
      Tag = 1
      Left = 1
      Top = 18
      Width = 494
      Height = 158
      TabStop = True
      Align = alTop
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 0
      OnDblClick = btnDelClick
      ItemHeight = 16
      BkColor = clWindow
      Header = HeaderControl1
      SectionDelimiters = ';'
      Options = [bkoVirtual, bkoColLines, bkoRowLines, bkoShowSelection]
      OnDrawItemSection = listDrawItemSection
    end
    object HeaderControl1: THeaderControl
      Left = 1
      Top = 1
      Width = 494
      Height = 17
      DragReorder = False
      Sections = <
        item
          ImageIndex = -1
          Text = 'Name'
          Width = 150
        end
        item
          ImageIndex = -1
          Text = 'Description'
          Width = 500
        end>
      Style = hsFlat
    end
    object Panel2: TPanel
      Left = 1
      Top = 181
      Width = 494
      Height = 32
      Align = alTop
      BevelInner = bvLowered
      TabOrder = 2
      object btnAdd: TToolbarButton97
        Left = 5
        Top = 5
        Width = 71
        Height = 22
        Caption = '&Add'
        OnClick = btnAddClick
      end
      object btnDel: TToolbarButton97
        Left = 80
        Top = 5
        Width = 71
        Height = 22
        Caption = '&Del'
        OnClick = btnDelClick
      end
      object btnUp: TToolbarButton97
        Left = 345
        Top = 5
        Width = 71
        Height = 22
        Anchors = [akTop, akRight]
        Caption = '&Up'
        OnClick = btnUpClick
      end
      object btnDn: TToolbarButton97
        Left = 420
        Top = 5
        Width = 71
        Height = 22
        Anchors = [akTop, akRight]
        Caption = 'Dow&n'
        OnClick = btnDnClick
      end
    end
    object HeaderControl2: THeaderControl
      Left = 1
      Top = 213
      Width = 494
      Height = 17
      DragReorder = False
      Sections = <
        item
          ImageIndex = -1
          Text = 'Name'
          Width = 150
        end
        item
          ImageIndex = -1
          Text = 'Description'
          Width = 500
        end>
      Style = hsFlat
    end
    object listAll: HBkList
      Left = 1
      Top = 230
      Width = 494
      Height = 185
      TabStop = True
      Align = alClient
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 4
      OnDblClick = btnAddClick
      ItemHeight = 16
      BkColor = clWindow
      Header = HeaderControl2
      SectionDelimiters = ';'
      Options = [bkoVirtual, bkoColLines, bkoRowLines, bkoShowSelection]
      OnDrawItemSection = listDrawItemSection
    end
  end
end
