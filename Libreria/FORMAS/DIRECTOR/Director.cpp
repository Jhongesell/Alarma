// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include "d:\libreria\formas\director\Director.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------


__fastcall TCapturadireccion::TCapturadireccion(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TCapturadireccion::AceptarClick(TObject *Sender)
{
   Estado = true;        
   Close();        
}

void __fastcall TCapturadireccion::FormActivate(TObject *Sender)
{
   Estado = false;        
}

// Deshacer la ultima modificación
void __fastcall TCapturadireccion::DeshacerClick(TObject *Sender)
{
   SendMessage(Memo1->Handle,WM_UNDO,0,0);        
}

// Cortar el texto seleccionado
void __fastcall TCapturadireccion::Corta1Click(TObject *Sender)
{
   Memo1->CutToClipboard();                
}

// Copia el texto seleccionado
void __fastcall TCapturadireccion::Copia1Click(TObject *Sender)
{
   Memo1->CopyToClipboard();        
}

// Pega en texto del bufer
void __fastcall TCapturadireccion::Pegar1Click(TObject *Sender)
{
   Memo1->PasteFromClipboard();        
}

// Selecciona todo el texto
void __fastcall TCapturadireccion::Selecciona1Click(TObject *Sender)
{
   Memo1->SelectAll();        
}

void __fastcall TCapturadireccion::Edit1KeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}

