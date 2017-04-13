// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdlib.h>
#include <stdio.h>
#include "d:\libreria\formas\pendient\Vpendien.h"
#include "d:\libreria\formas\pendient\Cpendien.h"
#include "d:\libreria\formas\pendient\RepPend.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\FCap1.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Arreglo de prioridades
char *Array[] = {
   "1",
   "2",
   "3",
   "4",
   "5",
   "6",
   "7",
   "8",
   "9"
};

// Constructor de la clase
__fastcall TPendienteForm::TPendienteForm(TComponent* Owner) : TForm(Owner)
{
}

// Al crear forma abre la base de datos
void __fastcall TPendienteForm::FormCreate(TObject *Sender)
{
   Table1->Open();        
}

// Al destruir la forma borra la base de datos
void __fastcall TPendienteForm::FormDestroy(TObject *Sender)
{
   Table1->Close();        
}

// Borra el registro actual
void __fastcall TPendienteForm::BBorrarClick(TObject *Sender)
{
   if (MessageBox(Handle,"¿Desea borrar este registro?","Directorio",MB_YESNO + MB_ICONQUESTION)  == IDYES) Table1->Delete();        
}

// Adiciona un registro
void __fastcall TPendienteForm::BAdicionarClick(TObject *Sender)
{
   TCPendiente *cpend = new TCPendiente(this);
   cpend->Caption = "Nuevo Pendiente";
   TDateTime dia;
   cpend->Edit1->Date = dia.CurrentDate();
   
   cpend->ShowModal();
   if (cpend->Estado) {
      Table1->Append();
      Table1->Fields->Fields[0]->Value = cpend->Edit1->Date;
      Table1->Fields->Fields[1]->Text = cpend->Edit2->Text;
      Table1->Fields->Fields[2]->Text = cpend->Edit3->Text;
      Table1->Fields->Fields[3]->Text = Array[cpend->Edit4->ItemIndex];
      Table1->Fields->Fields[4]->Assign(cpend->Memo1->Lines);
      Table1->Post();
   }
   delete cpend;
}

// Visualiza un registro
void __fastcall TPendienteForm::BVisualizarClick(TObject *Sender)
{
   TCPendiente *cpend = new TCPendiente(this);
   cpend->Caption = "Visualiza Pendiente";
   cpend->Edit1->Date = Table1->Fields->Fields[0]->Value;
   cpend->Edit2->Text = Table1->Fields->Fields[1]->Text;
   cpend->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cpend->Edit4->ItemIndex = atoi(Table1->Fields->Fields[3]->Text.c_str()) -1;
   cpend->Memo1->Lines->Assign(Table1->Fields->Fields[4]);

   cpend->Edit1->Enabled = false;
   cpend->Edit2->ReadOnly = true;
   cpend->Edit3->ReadOnly = true;
   cpend->Edit4->Enabled = false;
   cpend->Memo1->ReadOnly = true;

   cpend->ShowModal();
   delete cpend;
}

// Edita un registro
void __fastcall TPendienteForm::BEditarClick(TObject *Sender)
{
   TCPendiente *cpend = new TCPendiente(this);
   cpend->Caption = "Edita Pendiente";
   cpend->Edit1->Date = Table1->Fields->Fields[0]->Value;
   cpend->Edit2->Text = Table1->Fields->Fields[1]->Text;
   cpend->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cpend->Edit4->ItemIndex = atoi(Table1->Fields->Fields[3]->Text.c_str()) -1;
   cpend->Memo1->Lines->Assign(Table1->Fields->Fields[4]);

   cpend->ShowModal();
   if (cpend->Estado) {
      Table1->Edit();
      Table1->Fields->Fields[0]->Value = cpend->Edit1->Date;
      Table1->Fields->Fields[1]->Text = cpend->Edit2->Text;
      Table1->Fields->Fields[2]->Text = cpend->Edit3->Text;
      Table1->Fields->Fields[3]->Text = Array[cpend->Edit4->ItemIndex];
      Table1->Fields->Fields[4]->Assign(cpend->Memo1->Lines);
      Table1->Post();
   }

   delete cpend;
}


// Muestra la ventana de acerca de ...
void __fastcall TPendienteForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Pendientes");
   delete AcercaDeForm;
}


// Cierra la ventana
void __fastcall TPendienteForm::Salir1Click(TObject *Sender)
{
   Close();        
}


// Define el indice activo
void __fastcall TPendienteForm::DBGrid1TitleClick(TColumn *Column)
{
   if (Column->Field->Index != 2) Table1->IndexName = Column->FieldName;
}

// Filtro por prioridad
void __fastcall TPendienteForm::Prioridad1Click(TObject *Sender)
{
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Filtrar","Prioridad:","","Escriba el filtro (puede usar *)");
   if (cn->st) {
      char cad[100];
      sprintf(cad,"PRIORIDAD = '%s'",cn->Edit1->Text.c_str());
      Table1->Filter = cad;
      Table1->Filtered = true;
   }
   delete cn;
}

// Filtro por categoria
void __fastcall TPendienteForm::Categoria1Click(TObject *Sender)
{
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Filtrar","Categoría:","","Escriba el filtro (puede usar *)");
   if (cn->st) {
      char cad[100];
      sprintf(cad,"CATEGORIA = '%s'",cn->Edit1->Text.c_str());
      Table1->Filter = cad;
      Table1->Filtered = true;
   }
   delete cn;
}

// Sin filtro alguno
void __fastcall TPendienteForm::Sinfiltro1Click(TObject *Sender)
{
   Table1->Filter = "";
   Table1->Filtered = true;
}

// Reporte de pendientes
void __fastcall TPendienteForm::BImpresionClick(TObject *Sender)
{
   TReportePendientes *reppen = new TReportePendientes(this);
   if (reppen) {
      reppen->Table1->Filter = Table1->Filter;
      reppen->Table1->Filtered = Table1->Filtered;
      reppen->Table1->IndexName = Table1->IndexName;
      reppen->Preview();
      delete reppen;
   }
}


