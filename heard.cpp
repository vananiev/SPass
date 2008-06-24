//---------------------------------------------------------------------------

#include <vcl.h>
#include "func.h"
#pragma hdrstop

#include "heard.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

Tfrmpass *frmpass;
const up='+';
const down='-';
const left='L';
const right='R';
const middle='\r';
f obj;

//---------------------------------------------------------------------------
__fastcall Tfrmpass::Tfrmpass(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpass::wheel_down(TObject *Sender, TShiftState Shift,
      TPoint &MousePos, bool &Handled)
{
        obj.brain(down);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpass::wheel_up(TObject *Sender, TShiftState Shift,
      TPoint &MousePos, bool &Handled)
{
        obj.brain(up);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpass::mouse_down(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
          switch (Button)
                {
                case 0: obj.brain(left);break;
                case 1: obj.brain(right);break;
                case 2: obj.brain(middle);break;
                }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpass::key_down(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        switch(Key)
                {
                case 38:  obj.brain(up);break;
                case 40:  obj.brain(down);break;
                case 37:  obj.brain(left);break;
                case 39:  obj.brain(right);break;
                case ' ': obj.brain(middle);break;
                default: obj.brain(Key);
                }
}
//---------------------------------------------------------------------------


