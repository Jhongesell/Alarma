// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdio.h>
#include <dir.h>
#include "d:\Libreria\Evaexpc.hpp"
#include "d:\Libreria\Formas\Calculad.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\Formas\Ayuda.h"
#include "d:\libreria\man_arch.hpp"
#pragma hdrstop

extern char *TRAYECTORIA_ARCHIVOS;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TCalculadoraForm::TCalculadoraForm(TComponent* Owner) : TForm(Owner)
{
   exp_cap[0] = 0;
}


// Acepta la cadena y evalua la expresion
void __fastcall TCalculadoraForm::CapturaKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      char res[1000];
      char exp[1000];
      Evalua_expresion_cadena eval;
      strcpy(exp_cap,Captura->Text.c_str());
      sprintf(exp,"X=%s",Captura->Text.c_str());
      eval.Evalua_expresion(exp,res);
      Captura->Text = (AnsiString) res;
      Key = 0;
   }
}

// Retorna la ultima expresion capturada
void __fastcall TCalculadoraForm::Ultimaexpresin1Click(TObject *Sender)
{
   Captura->Text = (AnsiString) exp_cap;
}


// Termina la calculadora
void __fastcall TCalculadoraForm::Salir1Click(TObject *Sender)
{
   Close();     
}

// Elimina la expresion capturada
void __fastcall TCalculadoraForm::Eliminaexpresin1Click(TObject *Sender)
{
   Captura->Text = (AnsiString) "";
}

// Muestra la ventana de acerca de ...
void __fastcall TCalculadoraForm::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("CALCULADORA");
   delete AcercaDeForm;
}

// Muestra el archivo de ayuda de las funciones validas
void __fastcall TCalculadoraForm::FuncionesValidas1Click(TObject *Sender)
{
   char arch[MAXPATH];
   Manipulador_archivos ma;
   TAyudaForm *ayuda = new TAyudaForm(this);
   
   ma.Construye_trayectoria(TRAYECTORIA_ARCHIVOS,"FUNCION.DAT", arch);
   ayuda->Abrir_archivo("Funciones validas",arch);
   ayuda->ShowModal();
   delete ayuda;
}

// Copia el texto seleccinado al bufer
void __fastcall TCalculadoraForm::Copiaabufer1Click(TObject *Sender)
{
   Captura->CopyToClipboard();
}

// Copia el contenido del bufer a la cadena
void __fastcall TCalculadoraForm::Pegar1Click(TObject *Sender)
{
   Captura->PasteFromClipboard();
}

// Selecciona todo el texto del campo de captura
void __fastcall TCalculadoraForm::Seleccionatodo1Click(TObject *Sender)
{
   Captura->SelectAll();
}

// Corta el texto seleccionado
void __fastcall TCalculadoraForm::Cortar1Click(TObject *Sender)
{
   Captura->CutToClipboard();        
}

