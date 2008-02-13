object ConfigForm: TConfigForm
  Left = 446
  Top = 260
  Width = 506
  Height = 485
  BorderIcons = [biSystemMenu]
  Caption = 'Configuration...'
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
  Scaled = False
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
  object pages: TPageControl
    Left = 0
    Top = 5
    Width = 497
    Height = 417
    ActivePage = TabSheet1
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = '&1 Programm'
      object GroupBox10: TGroupBox
        Left = 0
        Top = 0
        Width = 489
        Height = 56
        Align = alTop
        Caption = ' Programm '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object chAutosave: TCheckBox
          Left = 7
          Top = 16
          Width = 386
          Height = 17
          Hint = 'Aautomatically save settings on exist'
          Caption = 'Autosave settings on exit'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
        object chSaveViewPos: TCheckBox
          Left = 7
          Top = 32
          Width = 386
          Height = 17
          Hint = 'Save current view position '
          Caption = 'Save view position'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
      end
      object GroupBox12: TGroupBox
        Left = 0
        Top = 56
        Width = 489
        Height = 45
        Align = alTop
        Caption = ' Confirmations '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object chAskQuit: TCheckBox
          Left = 8
          Top = 17
          Width = 296
          Height = 17
          Hint = 'Display confirmation dialog on attempt to eist from programm'
          Caption = 'On programm terminate'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 101
        Width = 489
        Height = 90
        Align = alTop
        Caption = ' NMEA '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        object chProcessWOCRC: TCheckBox
          Left = 7
          Top = 16
          Width = 386
          Height = 17
          Hint = 'Process commands without CRC'
          Caption = 'Process commands without CRC'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
        object chProcessCRCErr: TCheckBox
          Left = 7
          Top = 34
          Width = 386
          Height = 17
          Hint = 'Process commands with CRC errors'
          Caption = 'Process commands with CRC errors'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
        object chLogUnkCmd: TCheckBox
          Left = 7
          Top = 54
          Width = 386
          Height = 17
          Hint = 'Save to log unknown commands processed'
          Caption = 'Log unknown commands'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
        end
      end
    end
  end
end
