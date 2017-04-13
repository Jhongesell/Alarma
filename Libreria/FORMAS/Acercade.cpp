// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#include <vcl.h>
#include "d:\Libreria\Formas\AcercaDe.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init) 
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TAcercaDeForm::TAcercaDeForm(TComponent* Owner): TForm(Owner)
{
}
                                                       
// Muestra la ventana de Acerca de ...
void TAcercaDeForm::Muestra_ventana_AcercaDe(char *aplic)
{
//   Hide();
   NombreAplicacion->Caption = aplic;
   ShowModal();
}

void __fastcall TAcercaDeForm::BitBtn1Click(TObject *Sender)
{
   Close();      
}
//---------------------------------------------------------------------------

