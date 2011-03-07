object frmMain: TfrmMain
  Left = 443
  Top = 258
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1072#1088#1086#1083#1100
  ClientHeight = 335
  ClientWidth = 373
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 22
    Width = 30
    Height = 13
    Caption = #1048#1084#1103':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 50
    Width = 63
    Height = 13
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 100
    Width = 41
    Height = 13
    Caption = #1051#1086#1075#1080#1085':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 130
    Width = 49
    Height = 13
    Caption = #1055#1072#1088#1086#1083#1100':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clFuchsia
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 160
    Width = 98
    Height = 13
    Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1086':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object edDes: TEdit
    Left = 80
    Top = 48
    Width = 281
    Height = 21
    Color = cl3DLight
    TabOrder = 1
    OnChange = edDesChange
  end
  object edLog: TEdit
    Left = 112
    Top = 96
    Width = 249
    Height = 21
    Color = clRed
    TabOrder = 2
    OnChange = edLogChange
  end
  object edPass: TEdit
    Left = 112
    Top = 128
    Width = 249
    Height = 21
    Color = clFuchsia
    TabOrder = 3
    OnChange = edPassChange
  end
  object mAdd: TMemo
    Left = 112
    Top = 160
    Width = 249
    Height = 169
    Color = clLime
    ScrollBars = ssBoth
    TabOrder = 4
    OnChange = mAddChange
  end
  object edName: TComboBox
    Left = 80
    Top = 16
    Width = 281
    Height = 21
    Color = cl3DLight
    ItemHeight = 13
    TabOrder = 0
    OnSelect = edNameSelect
  end
  object btnSave: TButton
    Left = 8
    Top = 184
    Width = 81
    Height = 17
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Default = True
    TabOrder = 5
    OnClick = btnSaveClick
  end
  object btnDel: TButton
    Left = 296
    Top = 72
    Width = 65
    Height = 17
    Caption = #1059#1076#1072#1083#1080#1090#1100
    TabOrder = 6
    OnClick = btnDelClick
  end
  object Tray: TTrayIcon
    Visible = True
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
  end
end
