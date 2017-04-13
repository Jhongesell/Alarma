//---------------------------------------------------------------------------
#include <vcl.h>
#include "d:\libreria\formas\agenda\Cagenda.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TCapturaAgenda::TCapturaAgenda(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCapturaAgenda::FormActivate(TObject *Sender)
{
   Estado = false;        
}


void __fastcall TCapturaAgenda::AceptarClick(TObject *Sender)
{
   Estado = true;        
   Close();        
}


void __fastcall TCapturaAgenda::EditKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}

// Deshacer ultimos cambios
void __fastcall TCapturaAgenda::Deshacer1Click(TObject *Sender)
{
   SendMessage(Memo1->Handle,WM_UNDO,0,0); 
}

// Corta el texto seleccionado
void __fastcall TCapturaAgenda::Cortar1Click(TObject *Sender)
{
   Memo1->CutToClipboard();                
}

// Copia el texto seleccionado
void __fastcall TCapturaAgenda::Copiar1Click(TObject *Sender)
{
   Memo1->CopyToClipboard();
}

// Pegar el texto copiado o cortado
void __fastcall TCapturaAgenda::Pegar1Click(TObject *Sender)
{
   Memo1->PasteFromClipboard();
}

// Selecciona todo el texto
void __fastcall TCapturaAgenda::SeleccionarTodo1Click(TObject *Sender)
{
   Memo1->SelectAll();
}


