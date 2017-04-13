//---------------------------------------------------------------------------
#include <vcl.h>
#include "d:\libreria\Formas\2D\CDim2D.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// Constructor de la clase
__fastcall TCDim2DForm::TCDim2DForm(TComponent* Owner): TForm(Owner)
{
   Estado = false;
}

// Al presionar la tecla ENTER
void __fastcall TCDim2DForm::Edit1KeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}

// Al precionar el boton
void __fastcall TCDim2DForm::BitBtn1Click(TObject *Sender)
{
   Estado = true;
   Close();        
}

