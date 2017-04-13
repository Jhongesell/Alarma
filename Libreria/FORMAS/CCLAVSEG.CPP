//---------------------------------------------------------------------------
#include <vcl.h>
#include "\libreria\cadenas.hpp"
#include "d:\libreria\formas\CClavSeg.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall TCapturaClaveSeguridadForm::TCapturaClaveSeguridadForm(TComponent* Owner) : TForm(Owner)
{
   Estado = false;
}

void __fastcall TCapturaClaveSeguridadForm::BitBtn1Click(TObject *Sender)
{
   Estado = true;
}



void __fastcall TCapturaClaveSeguridadForm::Edit1KeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      Cadenas ca;
      if (ca.Lg_cadena_sin_espacios_final(Edit1->Text.c_str())) PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}


