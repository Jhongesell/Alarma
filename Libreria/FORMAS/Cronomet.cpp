// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include "d:\libreria\Formas\Cronomet.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TCronometroForm *CronometroForm;
//---------------------------------------------------------------------------

__fastcall TCronometroForm::TCronometroForm(TComponent* Owner) : TForm(Owner)
{
}




void __fastcall TCronometroForm::FormCreate(TObject *Sender)
{
   T_inicio = T_fin = T_diferencia = 0;
   t.Nseg__horas(0, xcad); 
   TInicio->Caption = xcad;
   TFin->Caption = xcad;
   TDiferencia->Caption = xcad;
   Activo = false;
}

// Iniciliza el cronometro
void __fastcall TCronometroForm::IniciarClick(TObject *Sender)
{
   Activo = true;
   T_inicio = T_fin;
   T_diferencia = 0;
   t.Nseg__horas(T_inicio, xcad); 
   TInicio->Caption = xcad;
   t.Nseg__horas(T_diferencia, xcad); 
   TDiferencia->Caption = xcad;
   
}

// Controla el cambio de segundos
void __fastcall TCronometroForm::Timer1Timer(TObject *Sender)
{       
   if (Activo) {
      T_fin ++;
      T_diferencia = T_fin - T_inicio;
      t.Nseg__horas(T_fin, xcad); 
      TFin->Caption = xcad;
      t.Nseg__horas(T_diferencia, xcad); 
      TDiferencia->Caption = xcad;
   }   
}

// inicializa el cronometro
void __fastcall TCronometroForm::inicializaClick(TObject *Sender)
{
   T_inicio = T_fin = T_diferencia = 0;
   t.Nseg__horas(T_inicio, xcad); 
   TInicio->Caption = xcad;
   t.Nseg__horas(T_fin, xcad); 
   TFin->Caption = xcad;
   t.Nseg__horas(T_diferencia, xcad); 
   TDiferencia->Caption = xcad;
        
}

// Para el cronometro
void __fastcall TCronometroForm::PararClick(TObject *Sender)
{
   Activo = false;        
   t.Nseg__horas(T_inicio, xcad); 
   TInicio->Caption = xcad;
   t.Nseg__horas(T_fin, xcad); 
   TFin->Caption = xcad;
   t.Nseg__horas(T_diferencia, xcad); 
   TDiferencia->Caption = xcad;
}


void __fastcall TCronometroForm::Salir1Click(TObject *Sender)
{
   Close();        
}

void __fastcall TCronometroForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("CRONOMETRO");        
   delete AcercaDeForm;
}

