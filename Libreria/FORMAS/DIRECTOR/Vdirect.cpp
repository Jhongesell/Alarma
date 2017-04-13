// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdio.h>
#include "d:\libreria\formas\director\Director.h"
#include "d:\libreria\formas\director\Vdirect.h"
#include "d:\libreria\formas\director\RepDir.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\FCap1.h"
#pragma hdrstop


extern char *TITULO_APLICACION;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TVDirectorioForm::TVDirectorioForm(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TVDirectorioForm::FormCreate(TObject *Sender)
{
   Table1->Open();        
}

// Al destruir la forma cierra la tabla y destruye la pantalla de captura
void __fastcall TVDirectorioForm::FormDestroy(TObject *Sender)
{
   Table1->Close();
}

// Adiciona un nuevo registro a la base de datos
void __fastcall TVDirectorioForm::BAdicionarClick(TObject *Sender)
{
   TCapturadireccion *cdir = new TCapturadireccion(this);
   cdir->Caption = "Adiciona registro";
   cdir->ShowModal();
   if (cdir->Estado) {
      Table1->Append();
      Table1->Fields->Fields[0]->Text = cdir->Edit1->Text;
      Table1->Fields->Fields[1]->Text = cdir->Edit2->Text;
      Table1->Fields->Fields[2]->Text = cdir->Edit3->Text;
      Table1->Fields->Fields[3]->Text = cdir->Edit4->Text;
      Table1->Fields->Fields[4]->Text = cdir->Edit5->Text;
      Table1->Fields->Fields[5]->Text = cdir->Edit6->Text;
      Table1->Fields->Fields[6]->Text = cdir->Edit7->Text;
      Table1->Fields->Fields[7]->Text = cdir->Edit8->Text;
      Table1->Fields->Fields[8]->Text = cdir->Edit9->Text;
      Table1->Fields->Fields[9]->Text = cdir->Edit10->Text;
      Table1->Fields->Fields[10]->Text = cdir->Edit11->Text;
      Table1->Fields->Fields[11]->Text = cdir->Edit12->Text;
      Table1->Fields->Fields[12]->Text = cdir->Edit13->Text;
      Table1->Fields->Fields[13]->Text = cdir->Edit14->Text;
      Table1->Fields->Fields[14]->Text = cdir->Edit15->Text;
      Table1->Fields->Fields[15]->Assign(cdir->Memo1->Lines);
      Table1->Post();
   }
   delete cdir;
}

// Edita el registro de la base de datos
void __fastcall TVDirectorioForm::BEditarClick(TObject *Sender)
{
   TCapturadireccion *cdir = new TCapturadireccion(this);
   cdir->Caption = "Edita registro";
   cdir->Edit1->Text = Table1->Fields->Fields[0]->Text;
   cdir->Edit2->Text = Table1->Fields->Fields[1]->Text;
   cdir->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cdir->Edit4->Text = Table1->Fields->Fields[3]->Text;
   cdir->Edit5->Text = Table1->Fields->Fields[4]->Text;
   cdir->Edit6->Text = Table1->Fields->Fields[5]->Text;
   cdir->Edit7->Text = Table1->Fields->Fields[6]->Text;
   cdir->Edit8->Text = Table1->Fields->Fields[7]->Text;
   cdir->Edit9->Text = Table1->Fields->Fields[8]->Text;
   cdir->Edit10->Text = Table1->Fields->Fields[9]->Text;
   cdir->Edit11->Text = Table1->Fields->Fields[10]->Text;
   cdir->Edit12->Text = Table1->Fields->Fields[11]->Text;
   cdir->Edit13->Text = Table1->Fields->Fields[12]->Text;
   cdir->Edit14->Text = Table1->Fields->Fields[13]->Text;
   cdir->Edit15->Text = Table1->Fields->Fields[14]->Text;
   cdir->Memo1->Lines->Assign(Table1->Fields->Fields[15]);

   cdir->ShowModal();
   if (cdir->Estado) {
      Table1->Edit();
      Table1->Fields->Fields[0]->Text = cdir->Edit1->Text;
      Table1->Fields->Fields[1]->Text = cdir->Edit2->Text;
      Table1->Fields->Fields[2]->Text = cdir->Edit3->Text;
      Table1->Fields->Fields[3]->Text = cdir->Edit4->Text;
      Table1->Fields->Fields[4]->Text = cdir->Edit5->Text;
      Table1->Fields->Fields[5]->Text = cdir->Edit6->Text;
      Table1->Fields->Fields[6]->Text = cdir->Edit7->Text;
      Table1->Fields->Fields[7]->Text = cdir->Edit8->Text;
      Table1->Fields->Fields[8]->Text = cdir->Edit9->Text;
      Table1->Fields->Fields[9]->Text = cdir->Edit10->Text;
      Table1->Fields->Fields[10]->Text = cdir->Edit11->Text;
      Table1->Fields->Fields[11]->Text = cdir->Edit12->Text;
      Table1->Fields->Fields[12]->Text = cdir->Edit13->Text;
      Table1->Fields->Fields[13]->Text = cdir->Edit14->Text;
      Table1->Fields->Fields[14]->Text = cdir->Edit15->Text;
      Table1->Fields->Fields[15]->Assign(cdir->Memo1->Lines);
      Table1->Post();
   }
   delete cdir;
}

// Visualiza el contenido del registro actual
void __fastcall TVDirectorioForm::BVisualizarClick(TObject *Sender)
{
   TCapturadireccion *cdir = new TCapturadireccion(this);
   cdir->Caption = "Visualiza registro";

   cdir->Edit1->Text = Table1->Fields->Fields[0]->Text;
   cdir->Edit2->Text = Table1->Fields->Fields[1]->Text;
   cdir->Edit3->Text = Table1->Fields->Fields[2]->Text;
   cdir->Edit4->Text = Table1->Fields->Fields[3]->Text;
   cdir->Edit5->Text = Table1->Fields->Fields[4]->Text;
   cdir->Edit6->Text = Table1->Fields->Fields[5]->Text;
   cdir->Edit7->Text = Table1->Fields->Fields[6]->Text;
   cdir->Edit8->Text = Table1->Fields->Fields[7]->Text;
   cdir->Edit9->Text = Table1->Fields->Fields[8]->Text;
   cdir->Edit10->Text = Table1->Fields->Fields[9]->Text;
   cdir->Edit11->Text = Table1->Fields->Fields[10]->Text;
   cdir->Edit12->Text = Table1->Fields->Fields[11]->Text;
   cdir->Edit13->Text = Table1->Fields->Fields[12]->Text;
   cdir->Edit14->Text = Table1->Fields->Fields[13]->Text;
   cdir->Edit15->Text = Table1->Fields->Fields[14]->Text;
   cdir->Memo1->Lines->Assign(Table1->Fields->Fields[15]);

   cdir->Edit1->ReadOnly = true;
   cdir->Edit2->ReadOnly = true;
   cdir->Edit3->ReadOnly = true;
   cdir->Edit4->ReadOnly = true;
   cdir->Edit5->ReadOnly = true;
   cdir->Edit6->ReadOnly = true;
   cdir->Edit7->ReadOnly = true;
   cdir->Edit8->ReadOnly = true;
   cdir->Edit9->ReadOnly = true;
   cdir->Edit10->ReadOnly = true;
   cdir->Edit11->ReadOnly = true;
   cdir->Edit12->ReadOnly = true;
   cdir->Edit13->ReadOnly = true;
   cdir->Edit14->ReadOnly = true;
   cdir->Memo1->ReadOnly = true;
   
   cdir->ShowModal();
   delete cdir;
}


// Borra un registro de la base de datos
void __fastcall TVDirectorioForm::BBorrarClick(TObject *Sender)
{
   if (MessageBox(Handle,"¿Desea borrar este registro?","Directorio",MB_YESNO + MB_ICONQUESTION)  == IDYES) Table1->Delete();
}



// Muestra la ventana de acerca de ...
void __fastcall TVDirectorioForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Directorio");
   delete AcercaDeForm;
}

// Cierra la ventana
void __fastcall TVDirectorioForm::Salir1Click(TObject *Sender)
{
   Close();        
}

// Define el indice activo
void __fastcall TVDirectorioForm::DBGrid1TitleClick(TColumn *Column)
{
   switch (Column->Field->Index) {
      case 0:
      case 1:
      case 3:
      case 9:
      Table1->IndexName = Column->FieldName;
      break;
   }
}


void TVDirectorioForm::Buscar(const int tp)
{
   TLocateOptions Options;
   Options << loPartialKey;
   Options << loCaseInsensitive;
   
   char *txt, *clv;
   switch (tp) {
      case 0:
        txt = "Nombre:";
        clv = "NOMBRE";
        break;
      case 1:
        txt = "Apellidos:";
        clv = "APELLIDOS";
        break;
      case 2:
        txt = "Categoría:";
        clv = "CATEGORIA";
        break;
      case 3:
        txt = "Compañía:";
        clv = "COMPANIA";
        break;
   }
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Buscar",txt,"","Escriba el texto a buscar");
   if (cn->st) {
      if (!Table1->Locate(clv,cn->Edit1->Text,Options)) MessageBox(Handle,"No se encontro el registro","Directorio",MB_OK + MB_ICONINFORMATION);
   }
   delete cn;
}

void __fastcall TVDirectorioForm::Nombre1Click(TObject *Sender)
{
   Buscar(0);        
}

void __fastcall TVDirectorioForm::apellido1Click(TObject *Sender)
{
   Buscar(1);        
}

void __fastcall TVDirectorioForm::Categoria1Click(TObject *Sender)
{
   Buscar(2);        
}

void __fastcall TVDirectorioForm::Compaia1Click(TObject *Sender)
{
   Buscar(3);        
}


void __fastcall TVDirectorioForm::Categoria2Click(TObject *Sender)
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

void __fastcall TVDirectorioForm::Compaia2Click(TObject *Sender)
{
   TCaptura1Form *cn = new TCaptura1Form(this);
   cn->Abrir("Filtrar","Compañía:","","Escriba el filtro (puede usar *)");
   if (cn->st) {
      char cad[100];
      sprintf(cad,"COMPANIA = '%s'",cn->Edit1->Text.c_str());
      Table1->Filter = cad;
      Table1->Filtered = true;
   }
   delete cn;
}

void __fastcall TVDirectorioForm::Sinfiltro1Click(TObject *Sender)
{
   Table1->Filter = "";
   Table1->Filtered = true;
}

// Reporte
void __fastcall TVDirectorioForm::BReporteClick(TObject *Sender)
{
   TReporteDirectorio *reppen = new TReporteDirectorio(this);
   if (reppen) {
      reppen->Table1->Filter = Table1->Filter;
      reppen->Table1->Filtered = Table1->Filtered;
      reppen->Table1->IndexName = Table1->IndexName;
      reppen->Preview();
      delete reppen;
   }
}

/*
   TConfiguraReporteForm *cr = new TConfiguraReporteForm(this);
   if (cr) {
     char arch[MAXPATH];
     char xcad[300], tmp1[200];
     unsigned int tp;
     cr->Configura_reporte(tp, arch);
     if (tp == CANCELADO) return;
     Ctrl_reporte *rep = new Ctrl_reporte;
     if (rep) {
        rep->Parametros(0,60,200,REPORTE_GRABADO,0,arch);
        Table1->First();
        rep->Alinea_cadena(TITULO_APLICACION,150,CENTRADA,tmp1);
        rep->Formato_impresion(1, 1, tmp1);
        rep->Alinea_cadena("LISTADO DEL DIRECTORIO CORTO",80,CENTRADA,tmp1);
        rep->Formato_impresion(1, 1, tmp1);
        rep->Formato_impresion(1, 2, " ");
        while (!Table1->Eof) {
           sprintf(xcad,"%s %s ",Table1->Fields->Fields[0]->Text.c_str(),Table1->Fields->Fields[1]->Text.c_str());
           rep->Elimina_espacios_inicesarios(xcad, tmp1);
           rep->Formato_impresion(2, 1, tmp1);
           sprintf(xcad,"Trab: %s,  Casa: %s, Fax: %s, Otros: %s",Table1->Fields->Fields[4]->Text.c_str(),Table1->Fields->Fields[5]->Text.c_str(),Table1->Fields->Fields[6]->Text.c_str(),Table1->Fields->Fields[7]->Text.c_str());
           rep->Elimina_espacios_inicesarios(xcad, tmp1);
           rep->Formato_impresion(45, 0, tmp1);
           Table1->Next();
        }
        delete rep;
        cr->Visualiza_Imprime();
     }
     delete cr;
     Table1->First();
   }
*/   

