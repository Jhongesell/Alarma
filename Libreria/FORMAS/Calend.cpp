// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdio.h>
#include "d:\libreria\formas\Calend.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ccalendr"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TCalendarioForm::TCalendarioForm(TComponent* Owner) : TForm(Owner)
{
}

// Al crear la forma inicializa el calendario
void __fastcall TCalendarioForm::FormCreate(TObject *Sender)
{
   Inicializa_calendario();
}


// Inicializa el calendario
void TCalendarioForm::Inicializa_calendario(void)
{
   char xfecha[20];
   Fechas f;
   
   f.Fecha_hoy(dia,mes,ano);
   f.Fecha_hoy(xfecha);
   f.Fecha_escrita(xfecha, xcad, 1, 1);
   DiaActual->Caption = xcad;
   Actualiza_datos();
}


// Actualiza datos
void TCalendarioForm::Actualiza_datos(void)
{
   Fechas f;

   f.Mes_letra(mes, xmes, 1);
   nmdia = f.Numero_max_dias_mes(mes,ano);
   if (dia < nmdia) nmdia = dia;
   CCalendar->Day = 1;
   CCalendar->Year = ano;
   CCalendar->Month = mes;
   CCalendar->Day = nmdia;
   sprintf(xcad,"%s DE %d",xmes,ano);
   MesAnoCalendario->Caption = xcad;
}

// Mes siguiente
void __fastcall TCalendarioForm::SiguenteClick(TObject *Sender)
{
   mes ++;
   if(mes >12) mes = 1, ano ++;
   Actualiza_datos();
}

// Mes anterior
void __fastcall TCalendarioForm::AnteriorClick(TObject *Sender)
{
   if(mes == 1) mes = 12, ano --;
    else mes --;
   Actualiza_datos(); 
}

// Termina la ventana del calendario
void __fastcall TCalendarioForm::Salir1Click(TObject *Sender)
{
   Close();        
}

// Pone el calendario en el mes actual
void __fastcall TCalendarioForm::Mesactual1Click(TObject *Sender)
{
   Inicializa_calendario();        
}

void __fastcall TCalendarioForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("CALENDARIO");        
   delete AcercaDeForm;

}

