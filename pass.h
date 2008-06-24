//---------------------------------------------------------------------------

#ifndef passH
#define passH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrmpass : public TForm
{
__published:	// IDE-managed Components
        void __fastcall key_press(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall Tfrmpass(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpass *frmpass;
//---------------------------------------------------------------------------
#endif
