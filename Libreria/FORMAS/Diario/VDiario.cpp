//---------------------------------------------------------------------------
#include <vcl.h>
#include "d:\Libreria\Formas\Diario\VDiario.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\man_arch.hpp"
#include "d:\libreria\fechora.hpp"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TDiarioForm *DiarioForm;
//---------------------------------------------------------------------------
__fastcall TDiarioForm::TDiarioForm(TComponent* Owner) : TForm(Owner)
{
}

// Al crear la forma
void __fastcall TDiarioForm::FormCreate(TObject *Sender)
{
   Table1->Open();
   SeleccionDia->Date = FechaTrabajo.CurrentDate();
   Editor->Clear();
   SeleccionDiaChange(Sender);
} 


// Al destruir la forma
void __fastcall TDiarioForm::FormDestroy(TObject *Sender)
{
   Table1->Close();   
}

// Antes de cerra la forma
void __fastcall TDiarioForm::FormCloseQuery(TObject *Sender,  bool &CanClose)
{
   TLocateOptions options;
   options << loCaseInsensitive;

   if (Editor->Lines->Count > 0) {
      if (Table1->Locate("FECHA",FechaTrabajo.DateString().c_str(),options)) {  
         Table1->Edit();
         Table1->Fields->Fields[1]->Assign(Editor->Lines);
         Table1->Post();
       } else {
         Table1->Append();
         Table1->Fields->Fields[0]->Value = FechaTrabajo.DateString().c_str();
         Table1->Fields->Fields[1]->Assign(Editor->Lines);
         Table1->Post();
      }
   }
   CanClose = true;
}

// Salir
void __fastcall TDiarioForm::Salir1Click(TObject *Sender)
{
   Close();
}

// Acerca de ...
void __fastcall TDiarioForm::acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Diario");
   delete AcercaDeForm;
}

// Icono de Editar
void __fastcall TDiarioForm::IcEditarClick(TObject *Sender)
{
   Editor->ReadOnly = false;
}

// Al cambiar de dia
void __fastcall TDiarioForm::SeleccionDiaChange(TObject *Sender)
{
   TLocateOptions options;
   options << loCaseInsensitive;
   if (Editor->Lines->Count > 0) {
      if (Table1->Locate("FECHA",FechaTrabajo.DateString().c_str(),options)) {
         Table1->Edit();
         Table1->Fields->Fields[1]->Assign(Editor->Lines);
         Table1->Post();
       } else {
         Table1->Append();
         Table1->Fields->Fields[0]->Value = FechaTrabajo.DateString().c_str();
         Table1->Fields->Fields[1]->Assign(Editor->Lines);
         Table1->Post();
      }
   }
   TDateTime fech = SeleccionDia->Date;
   FechaTrabajo = fech;
   Editor->Clear();
   if (Table1->Locate("FECHA",FechaTrabajo.DateString().c_str(),options)) {  
      Editor->Lines->Assign(Table1->Fields->Fields[1]);
   }
   Editor->ReadOnly = true;
}

// Deshacer cambios
void __fastcall TDiarioForm::DeshacerClick(TObject *Sender)
{
   SendMessage(Editor->Handle,WM_UNDO,0,0);           
}

// Selecciona todo el texto
void __fastcall TDiarioForm::Selecciona1Click(TObject *Sender)
{
   Editor->SelectAll();        
}

// Cortar
void __fastcall TDiarioForm::Corta1Click(TObject *Sender)
{
   Editor->CutToClipboard();        
}

// Copiar
void __fastcall TDiarioForm::Copia1Click(TObject *Sender)
{
   Editor->CutToClipboard();        
}

// Pegar
void __fastcall TDiarioForm::Pegar1Click(TObject *Sender)
{
   Editor->PasteFromClipboard();       
}

// Insertar fecha
void __fastcall TDiarioForm::Insertarfecha2Click(TObject *Sender)
{
   char fecha[20], fec_esc[50];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Fecha_hoy(fecha);
   fh.Fecha_escrita(fecha, fec_esc, 1, 1);
   ma.Convierte_linea(fec_esc);
   Editor->SetSelTextBuf(fec_esc);
}

// Insertar hora
void __fastcall TDiarioForm::Insertarhora2Click(TObject *Sender)
{
   char tiempo[20];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Hora_actual(tiempo, 1, 1);
   fh.Trim(tiempo);
   ma.Convierte_linea(tiempo);
   Editor->SetSelTextBuf(tiempo);
}

// Insertar fecha y hora
void __fastcall TDiarioForm::Insertarfechayhora2Click(TObject *Sender)
{
   char xcad[100];
   Manipulador_archivos ma;
   Fechas_Horas fh;
   
   fh.Fecha_y_hora(xcad, 1, 1);
   ma.Convierte_linea(xcad);
   Editor->SetSelTextBuf(xcad);
}

