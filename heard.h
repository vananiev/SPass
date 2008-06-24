//---------------------------------------------------------------------------

#ifndef heardH
#define heardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrmpass : public TForm
{
__published:	// IDE-managed Components
        void __fastcall wheel_down(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
        void __fastcall wheel_up(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
        void __fastcall mouse_down(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall key_down(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall Tfrmpass(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpass *frmpass;
//---------------------------------------------------------------------------
#endif
