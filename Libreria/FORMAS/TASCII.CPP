// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdio.h>
#include "d:\libreria\formas\TASCII.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TTablaASCIIForm::TTablaASCIIForm(TComponent* Owner) : TForm(Owner)
{
   Visualiza_titulo();
}

void __fastcall TTablaASCIIForm::Salir1Click(TObject *Sender)
{
   Close();        
}


void __fastcall TTablaASCIIForm::Tipodeletra1Click(TObject *Sender)
{
   FontDialog->Font = Editor->Font;
   if(FontDialog->Execute()) Editor->Font = FontDialog->Font;
   Visualiza_titulo();
}

// Visualiza en el titulo el tipo de letra activo
void TTablaASCIIForm::Visualiza_titulo(void)
{
   char xcad[100];
   sprintf(xcad,"Tabla ASCII (%s)",Editor->Font->Name.c_str());
   Caption = xcad;
}

// Muestra la ventana de acerca de ...
void __fastcall TTablaASCIIForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Tabla ASCII");
   delete AcercaDeForm;
}

