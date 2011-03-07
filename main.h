//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *edDes;
        TEdit *edLog;
        TEdit *edPass;
        TMemo *mAdd;
        TComboBox *edName;
        TButton *btnSave;
        TButton *btnDel;
        TTrayIcon *Tray;
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall edDesChange(TObject *Sender);
        void __fastcall edLogChange(TObject *Sender);
        void __fastcall edPassChange(TObject *Sender);
        void __fastcall mAddChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall edNameSelect(TObject *Sender);
        void __fastcall btnDelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
