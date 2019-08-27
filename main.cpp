//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "file.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TfrmMain *frmMain;
void change();
char pass[1024]="";
bool file_find(char *adr);
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSaveClick(TObject *Sender)
{
        String  A =  edDes->Text + "\r\n" + edLog->Text + "\r\n" + edPass->Text
                + "\r\n" + mAdd->Lines->Text;
        /*mAdd->Lines->Insert(0,edPass->Text);
        mAdd->Lines->Insert(0,edLog->Text);
        mAdd->Lines->Insert(0,edDes->Text);*/
        //����������
        File_Adr adr = file_adr_split (ParamStr(0).c_str());
        strcat(adr.fdir,"Data\\");
        if(!pass[0])      //���������?
                add_to_file_string( A.c_str(),(adr.fdir + edName->Text + ".key").c_str());
        else
                add_to_file_string( A.c_str(),(adr.fdir + edName->Text + ".key").c_str(),pass);
        //for(int i=0;i<3;i++) mAdd->Lines->Delete(0);
        btnSave->Caption="���������";
        //�������� ���� �������
        edName->Items->Clear();
        seach_dir(adr.fdir,file_find,false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edDesChange(TObject *Sender)
{
            change();
}
//---------------------------------------------------------------------------
void change()
{
        frmMain->btnSave->Caption="���������";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edLogChange(TObject *Sender)
{
        change();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edPassChange(TObject *Sender)
{
        change();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mAddChange(TObject *Sender)
{
        change();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
        //��� ���� � ������
        PasswordDlg.
        strcpy(pass,InputBox("������� ����","��� ���� ��� ���������� ������� ��� ����������, ����� �� ��������� ������: ", "�� ���������").c_str());
        if(!strcmp(pass,"�� ���������")) pass[0]=0;
        //�������� ���� �������
        //����� ���������
        File_Adr adr = file_adr_split (ParamStr(0).c_str());
        strcat(adr.fdir,"Data\\");
        seach_dir(adr.fdir,file_find,false);
}
//---------------------------------------------------------------------------
bool file_find(char *adr)
{
        File_Adr b = file_adr_split (adr);
        frmMain->edName->Items->Add(b.fname);
        return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edNameSelect(TObject *Sender)
{
        char string[10000];
        string[0]=0;
        File_Adr adr = file_adr_split (ParamStr(0).c_str());
        strcat(adr.fdir,"Data\\");
        if(!pass[0])        //���������?
                get_from_file( (adr.fdir + edName->Text + ".key").c_str(),string);
        else
                get_from_file( (adr.fdir + edName->Text + ".key").c_str(),string,pass);
        mAdd->Lines->Clear();
        mAdd->Lines->Add(string);
        mAdd->Lines->SetText(mAdd->Lines->Text.SubString(0,mAdd->Lines->Text.Length()-2).c_str());
        edDes->Text = mAdd->Lines->operator [](0);
        edLog->Text = mAdd->Lines->operator [](1);
        edPass->Text = mAdd->Lines->operator [](2);
        for(int i=0;i<3;i++) mAdd->Lines->Delete(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnDelClick(TObject *Sender)
{
        if(MessageDlg("�� �������, ��� ������ ������� ������ ?", mtInformation,mbOKCancel,NULL) == 1){
                File_Adr adr = file_adr_split (ParamStr(0).c_str());
                strcat(adr.fdir,"Data\\");
                if(DeleteFile(adr.fdir + edName->Text + ".key"))
                        ShowMessage("������ ������� �������." );
                        else
                        ShowMessage(adr.fdir+edName->Text+".key" + "\r\n�� ������� ������� ������ ���������� �������. ��� ����� ������� ���� ����.");
                //�������� ���� �������
                edName->Items->Clear();
                seach_dir(adr.fdir,file_find,false);
                }
}
//---------------------------------------------------------------------------

