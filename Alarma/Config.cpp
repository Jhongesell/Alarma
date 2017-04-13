//---------------------------------------------------------------------------
#include <vcl.h>
#include "Config.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TConfigurarForm  *ConfigurarForm;


__fastcall TConfigurarForm::TConfigurarForm(TComponent* Owner): TForm(Owner)
{
   st = false;
}

// Aceptar modificaciones
void __fastcall TConfigurarForm::btAceptarClick(TObject *Sender)
{
   st = true;
   Close();
}

// Cambia el tipo de letra
void __fastcall TConfigurarForm::btTipoLetraClick(TObject *Sender)
{
   FontDialog->Font = Label1->Font;
   if(FontDialog->Execute()) Label1->Font = FontDialog->Font;
}   

// Cambia color del texto
void __fastcall TConfigurarForm::btColorTextoClick(TObject *Sender)
{
   ColorDialog->Color = Label1->Font->Color;
   if (ColorDialog->Execute()) Label1->Font->Color = ColorDialog->Color;
}

// Cambia el color del fondo
void __fastcall TConfigurarForm::btColorFondoClick(TObject *Sender)
{
   ColorDialog->Color = Label1->Color;
   if (ColorDialog->Execute()) Label1->Color = ColorDialog->Color;
}


void TConfigurarForm::Abrir(const TColor txt, const TColor fdo, TFont *fnt)
{
   Label1->Font->Color = txt;
   Label1->Color = fdo;
   Label1->Font = fnt;
   ShowModal();
}



