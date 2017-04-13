//---------------------------------------------------------------------------
#include <vcl.h>
#include "D:\libreria\formas\Cfg_rep.h"
#include "d:\libreria\Formas\Ayuda.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TConfiguraReporteForm::TConfiguraReporteForm(TComponent* Owner) : TForm(Owner)
{
   Tipo_reporte = CANCELADO;
}

// Configura el tipo de reporte que el usuario quiere
void TConfiguraReporteForm::Configura_reporte(unsigned int &trep,char *arch)
{
    ShowModal();
    strcpy(arch,Archivo);
    trep = Tipo_reporte;
}


// El boton de aceptar se presiona
void __fastcall TConfiguraReporteForm::BitBtn1Click(TObject *Sender)
{
   if (RadioButton1->Checked) {
      SaveDialog->FileName = "";
      if (SaveDialog->Execute()) {
          Tipo_reporte = REPORTE_GRABADO;
          strcpy(Archivo,SaveDialog->FileName.c_str());
      }   
   }
   if (RadioButton2->Checked) {
      Tipo_reporte = REPORTE_VISUALIZADO;
      strcpy(Archivo,"c:\\temp\\rep_vis.tmp");
   }
   if (RadioButton3->Checked) {
      Tipo_reporte = REPORTE_IMPRESO;
      strcpy(Archivo,"c:\\temp\\rep_imp.tmp");
   }
   Close();
}

// Controla la visualizacion o impresion del reporte
void TConfiguraReporteForm::Visualiza_Imprime(void)
{
   // Visualizacion del reporte
   if (Tipo_reporte == REPORTE_VISUALIZADO) {
      TAyudaForm *vis = new TAyudaForm(this);
      if (vis) {
         vis->Abrir_archivo("Visualización del reporte",Archivo);
         vis->ShowModal();
         delete vis;
      }
   }
   // Impresion del reporte
   if (Tipo_reporte == REPORTE_IMPRESO) ShellExecute(Handle,"print",Archivo,NULL,NULL,SW_HIDE);
}

