//---------------------------------------------------------------------------
#include <vcl.h>
#include "\libreria\cadenas.hpp"
#include "d:\libreria\formas\FCap1.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// Constructor
__fastcall TCaptura1Form::TCaptura1Form(TComponent* Owner) : TForm(Owner)
{
}

// Cierra la ventana
void __fastcall TCaptura1Form::BitBtn1Click(TObject *Sender)
{
   st = true;
   Close();        
}

// Abre la ventana con un solo campo de captura
void TCaptura1Form::Abrir(const char *tit, const char *eti, const char *txt, const char *hlp)
{
   Caption = tit;
   Label1->Caption = eti;
   Edit1->Text = txt; 
   StatusBar->SimpleText = (AnsiString) hlp;
   st = false;
   ShowModal();
}


void __fastcall TCaptura1Form::Edit1KeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      Cadenas ca;
      if (ca.Lg_cadena_sin_espacios_final(Edit1->Text.c_str())) PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}

