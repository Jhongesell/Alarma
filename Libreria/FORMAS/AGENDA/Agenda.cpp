//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include "d:\libreria\fechora.hpp"
#include "d:\libreria\formas\agenda\Agenda.h"
#include "d:\libreria\formas\agenda\Cagenda.h"
#include "d:\libreria\formas\agenda\RepAgen.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\FCap1.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

__fastcall TVAgendaForm::TVAgendaForm(TComponent* Owner) : TForm(Owner)
{
}

// Al crear la forma
void __fastcall TVAgendaForm::FormCreate(TObject *Sender)
{
   Table1->Open();
   TDateTime ti;
   SeleccionDia->Date = ti.CurrentDate();
   Tipo_filtro = true;
   strcpy(C_Agrupador,"");
   SeleccionDiaChange(Sender);
}

// Al destruir la forma
void __fastcall TVAgendaForm::FormDestroy(TObject *Sender)
{
   Table1->Close();   
}

// Al salir
void __fastcall TVAgendaForm::Salir1Click(TObject *Sender)
{
   Close();   
}

// Edita un nuevo registro
void __fastcall TVAgendaForm::Nuevo1Click(TObject *Sender)
{
   char xcad[30], xxcad[30], xhora[30];
   Fechas_Horas fh;
   TDateTime ti;

   int lg, st = 0;
   strcpy(xhora,ti.TimeString().c_str());
   lg = strlen(xhora);
   if (xhora[lg-1] != '.') MessageBox(Handle,"Defina en configuración regional la hora con formato HH:MM:SS [A.M.|P.M.]","Alarma",MB_OK + MB_ICONINFORMATION);
   if (isupper(xhora[lg-2])) st = 1;

   TCapturaAgenda *cage = new TCapturaAgenda(this);
   cage->Caption = "Nueva actividad";
   cage->Edit1->Date = SeleccionDia->Date;
   cage->Edit2->Time = ti.CurrentTime();
   cage->ShowModal();
   if (cage->Estado) {
      Table1->Append();
      Table1->Fields->Fields[0]->Value = cage->Edit1->Date;
      ti = cage->Edit2->Time;
      strcpy(xcad,ti.TimeString().c_str());
      if(!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
      if (!st) fh.Convierte_mayusculas(xcad);
      fh.AmPm__hors(xcad,xxcad);
      Table1->Fields->Fields[1]->Text = xxcad;
      Table1->Fields->Fields[2]->Text = cage->Edit3->Text;
      Table1->Fields->Fields[3]->Text = cage->Edit4->Text;
      Table1->Fields->Fields[4]->Assign(cage->Memo1->Lines);
      Table1->Post();
   }
   delete cage;
}

// Visualiza el registro actual
void __fastcall TVAgendaForm::Visualizar1Click(TObject *Sender)
{
   char xxcad[30], xhora[30];
   Fechas_Horas fh;
   TDateTime ti;

   int lg, st = 0;
   strcpy(xhora,ti.TimeString().c_str());
   lg = strlen(xhora);
   if (xhora[lg-1] != '.') MessageBox(Handle,"Defina en configuración regional la hora con formato HH:MM:SS [A.M.|P.M.]","Alarma",MB_OK + MB_ICONINFORMATION);
   if (isupper(xhora[lg-2])) st = 1;

   TCapturaAgenda *cage = new TCapturaAgenda(this);
   cage->Caption = "Visualiza actividad";
   cage->Edit1->Date = Table1->Fields->Fields[0]->Value;
   fh.Hrs__am_pm(Table1->Fields->Fields[1]->Text.c_str(),xxcad);
   if (!st) fh.Convierte_minusculas(xxcad);
   cage->Edit2->Time = TDateTime(xxcad,dtkTime);
   cage->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cage->Edit4->Text = Table1->Fields->Fields[3]->Text;
   cage->Memo1->Lines->Assign(Table1->Fields->Fields[4]);

   cage->Edit1->Enabled = false;
   cage->Edit2->Enabled = false;
   cage->Edit3->ReadOnly = true;
   cage->Memo1->ReadOnly = true;

   cage->ShowModal();
   delete cage;
}

// Edita el  registro actual
void __fastcall TVAgendaForm::Editar1Click(TObject *Sender)
{
   char xcad[30], xxcad[30], xhora[30];
   Fechas_Horas fh;
   TDateTime ti;

   int lg, st = 0;
   strcpy(xhora,ti.TimeString().c_str());
   lg = strlen(xhora);
   if (xhora[lg-1] != '.') MessageBox(Handle,"Defina en configuración regional la hora con formato HH:MM:SS [A.M.|P.M.]","Alarma",MB_OK + MB_ICONINFORMATION);
   if (isupper(xhora[lg-2])) st = 1;

   TCapturaAgenda *cage = new TCapturaAgenda(this);
   cage->Caption = "Edita actividad";
   cage->Edit1->Date = Table1->Fields->Fields[0]->Value;
   fh.Hrs__am_pm(Table1->Fields->Fields[1]->Text.c_str(),xxcad);
   if (!st) fh.Convierte_minusculas(xxcad);
   cage->Edit2->Time = TDateTime(xxcad,dtkTime);
   cage->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cage->Edit4->Text = Table1->Fields->Fields[3]->Text;
   cage->Memo1->Lines->Assign(Table1->Fields->Fields[4]);
   cage->ShowModal();
   if (cage->Estado) {
      Table1->Edit();
      Table1->Fields->Fields[0]->Value = cage->Edit1->Date;
      ti = cage->Edit2->Time;
      strcpy(xcad,ti.TimeString().c_str());
      if(!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
      if (!st) fh.Convierte_mayusculas(xcad);
      fh.AmPm__hors(xcad,xxcad);
      Table1->Fields->Fields[1]->Text = xxcad;
      Table1->Fields->Fields[2]->Text = cage->Edit3->Text;
      Table1->Fields->Fields[3]->Text = cage->Edit4->Text;
      Table1->Fields->Fields[4]->Assign(cage->Memo1->Lines);
      Table1->Post();
   }
   delete cage;
}

// Borra el registro actual
void __fastcall TVAgendaForm::Borrar1Click(TObject *Sender)
{
   if (MessageBox(Handle,"¿Desea borrar este registro?","Agenda",MB_YESNO + MB_ICONQUESTION)  == IDYES) Table1->Delete();        
}

// Filtra por agrupador
void __fastcall TVAgendaForm::Agrupador(TObject *Sender)
{
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Filtrar","Agrupador:","","Escriba el filtro (puede usar *)");
   if (cn->st) {
      strcpy(C_Agrupador,cn->Edit1->Text.c_str());
      Tipo_filtro = false;
   }
   delete cn;
   SeleccionDiaChange(Sender);
}

// Sin filtro alguno
void __fastcall TVAgendaForm::Sinfiltro1Click(TObject *Sender)
{
   Tipo_filtro = true;
   SeleccionDiaChange(Sender);
}

// Muestra la ventana de Acerca de ...
void __fastcall TVAgendaForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Agenda");
   delete AcercaDeForm;
}

// Al cambiar de dia ...
void __fastcall TVAgendaForm::SeleccionDiaChange(TObject *Sender)
{
   char xcad[15], cad[100];
   Fechas fe;
   TDateTime fech = SeleccionDia->Date;
   
   strcpy(xcad,fech.DateString().c_str());
   if (!fe.Es_caracter_digito(xcad[1])) fe.Inserta_caracter(xcad,0,'0');
   if (xcad[8] == 0) {
    xcad[8] = xcad[6];
    xcad[9] = xcad[7];
    xcad[10] = 0;
    if(xcad[8] < '8') xcad[6] = '2', xcad[7] = '0';
     else xcad[6] = '1', xcad[7] = '9';
   }    
   // Selecciona el filtro activo
   if (Tipo_filtro) sprintf(cad,"FECHA = '%s'",xcad);
    else sprintf(cad,"FECHA = '%s' and AGRUPADOR = '%s'",xcad,C_Agrupador);
   Table1->Filter = cad;
   Table1->Filtered = true;
   Table1->Refresh();
}


// Si se presiona en el titulo cambia de indice
void __fastcall TVAgendaForm::DBGrid1TitleClick(TColumn *Column)
{
   if (Column->Field->Index != 3) Table1->IndexName = Column->FieldName;
}

// Actualiza datos
//void TVAgendaForm::Actualiza_datos(void)
//{
//   Fechas f;

//   f.Mes_letra(mes, xmes, 1);
//   nmdia = f.Numero_max_dias_mes(mes,ano);
//   if (dia < nmdia) nmdia = dia;
//   CCalendar->Day = 1;
//   CCalendar->Year = ano;
//   CCalendar->Month = mes;
//   CCalendar->Day = nmdia;
//   sprintf(xcad,"%s DE %d",xmes,ano);
//   MesAnoCalendario->Caption = xcad;
//}

// Impresión de la Agenda
void __fastcall TVAgendaForm::BImpresionClick(TObject *Sender)
{
   TReporteAgenda *reppen = new TReporteAgenda(this);
   if (reppen) {
      reppen->Table1->Filter = Table1->Filter;
      reppen->Table1->Filtered = Table1->Filtered;
      reppen->Table1->IndexName = Table1->IndexName;
      reppen->Preview();
      delete reppen;
   }
}
//---------------------------------------------------------------------------



