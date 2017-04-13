// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include "d:\libreria\formas\Pendient\Cpendien.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TCPendiente::TCPendiente(TComponent* Owner) : TForm(Owner)
{
}

// Al activar la forma
void __fastcall TCPendiente::FormActivate(TObject *Sender)
{
   Estado = false;        
}

// Al teclear el boton de aceptar
void __fastcall TCPendiente::BAceptarClick(TObject *Sender)
{
   Estado = true;        
   Close();        
}

// Deshacer el ultimo cambio
void __fastcall TCPendiente::DeshacerClick(TObject *Sender)
{
   SendMessage(Memo1->Handle,WM_UNDO,0,0); 
}

// Corta el texto seleccionado
void __fastcall TCPendiente::Corta1Click(TObject *Sender)
{
   Memo1->CutToClipboard();                
}

// Copia el texto seleccionado
void __fastcall TCPendiente::Copia1Click(TObject *Sender)
{
   Memo1->CopyToClipboard();
}

// Pega el texto del bufer
void __fastcall TCPendiente::Pegar1Click(TObject *Sender)
{
   Memo1->PasteFromClipboard();
}

// Selecciona todo el texto
void __fastcall TCPendiente::Selecciona1Click(TObject *Sender)
{
   Memo1->SelectAll();
}


void __fastcall TCPendiente::Edit1KeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}












