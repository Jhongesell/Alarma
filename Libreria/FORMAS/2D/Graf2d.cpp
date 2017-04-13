// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dir.h>
#include "d:\libreria\Cadenas.hpp"
#include "d:\libreria\formas\2d\Graf2D.h"
#include "D:\Libreria\Formas\2d\VGrafica.h"
#include "d:\libreria\Formas\2D\CDim2D.h"
#include "d:\Libreria\Formas\Acercade.h"
#include "d:\libreria\Formas\Ayuda.h"
#include "d:\libreria\formas\LMensaje.h"
#include "d:\Libreria\Evaexpc.hpp"
#include "d:\libreria\calnpol.hpp"
#include "d:\libreria\formas\FCap1.h"
#include "d:\libreria\man_arch.hpp"
#include "d:\libreria\nucleo.hpp"

#pragma hdrstop


// Objeto global
extern Nucleo NCO;
extern char *TRAYECTORIA_ARCHIVOS;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

//static char exp_cap[210];


__fastcall TGrafica2D::TGrafica2D(TComponent* Owner): TForm(Owner)
{
}


void __fastcall TGrafica2D::FormCreate(TObject *Sender)
{
   exp_cap[0] = 0;
   NUMERO_PUNTOS = 3000;
   Vtn.Xi = Vtn.Yi = -10.0;
   Vtn.Xf = Vtn.Yf =  10.0;
   vgraficacion = new TVVisualizacion(this);
   vgraficacion->Configura(Vtn);
   vgraficacion->Show();
}


void __fastcall TGrafica2D::FormDestroy(TObject *Sender)
{
   delete vgraficacion;
   vgraficacion = NULL;
}

// Termina el programa
void __fastcall TGrafica2D::Salir1Click(TObject *Sender)
{
   Close();        
}

// Copia el texto seleccionado
void __fastcall TGrafica2D::Copiar1Click(TObject *Sender)
{
   Captura->CopyToClipboard();        
}

// Pega el contenido de bufer
void __fastcall TGrafica2D::Pegar1Click(TObject *Sender)
{
   Captura->PasteFromClipboard();        
}

// Retorna la ultima expresion capturada
void __fastcall TGrafica2D::Ultimaexpresin1Click(TObject *Sender)
{
   Captura->Text = (AnsiString) exp_cap;        
}

// Elimina la expresion actual
void __fastcall TGrafica2D::Eliminaexpresin1Click(TObject *Sender)
{
   Captura->Text = (AnsiString) "";
        
}

// Acerca de ...
void __fastcall TGrafica2D::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Gaficadora en 2D");
   delete AcercaDeForm;
}

// Funciones validas
void __fastcall TGrafica2D::Funcionesvalidas1Click(TObject *Sender)
{
   char arch[MAXPATH];
   Manipulador_archivos ma;
   TAyudaForm *ayuda = new TAyudaForm(this);

   ma.Construye_trayectoria(TRAYECTORIA_ARCHIVOS,"FUNCION.DAT", arch);
   ayuda->Abrir_archivo("Funciones validas",arch);
   ayuda->ShowModal();
   delete ayuda;
}


// Grafica la expresion
void __fastcall TGrafica2D::BGraficaClick(TObject *Sender)
{
   strcpy(exp_cap,Captura->Text.c_str());
   if (!(exp_cap[0] == 'F' && exp_cap[1] == '(' && (exp_cap[2] == 'x' || exp_cap[2] == 'y') && exp_cap[3] == ')' && exp_cap[4] == '=')) {
      MessageBox(Handle,"La función se define como F(x)=... o F(y)=...","Graficadora en 2D",MB_OK + MB_ICONINFORMATION);
      return;
   }
   Valida_revisualizacion = true;
   Grafica_funcion(exp_cap);
}


void TGrafica2D::Grafica_funcion(const char *exp)
{
   if (!exp[0]) return;
   Suspender_Calculo = false;
   NCO.Bitacora("Grafica función",exp,"");
   
   unsigned int pos;
   char xcad[200], cad[200], xexp[200];
   char *xcad1, *xcad2, *xcad3;
   C3D c_ini, a_coord; 
   double inc;
   long n_iter = 0;

   Cadenas c;
   Calculadora_notacion_polaca cnp;
   

   vgraficacion->Show();
   vgraficacion->Muestra_mensaje("Graficando...");

   // Realiza el analisis sintactico de la expresion
   Analizador_sintactico *As = new Analizador_sintactico;
   strcpy(xexp,exp);
   // Cambia el F(x)= por X=
   xexp[0] = xexp[1] = xexp[2] = 32, xexp[3] = 'X';
   
   // Valida la expresion
   As->Crea_arbol(xexp);
   if(!As->Numero_errores()) {
      // Obtiene la expresion en notacion polaca
      As->Retorna_expresion(xcad,POSTORDEN);
      Cadenas ca;
      xcad1 = ca.Asigna_puntero(200);
      xcad2 = ca.Asigna_puntero(200);
      xcad3 = ca.Asigna_puntero(200);
/////////////////////////////////////////////////////////////////////////////      
// Si existen parametros remplaza el valor de los parametros en la ecuacion
//      if(Numero_parametros[Sistema_actual]) {
//         for(i = 0; i < Numero_parametros[Sistema_actual]; i++) {
//            sprintf(xcad3,"|%s|",Nombre_parametro[Sistema_actual][i]);
//            while(Busca_cadena(xcad,xcad3,pos)) {
//               s_substr(xcad,0,pos,xcad1);
//               s_substr(xcad,pos+3,200,xcad2);
//               sprintf(xcad,"%s|%f|%s",xcad1,_P[Sistema_actual][i],xcad2);
//            }
//         }
//      }
//////////////////////////////////////////////////////////////////////////////
      // Inicializa variables
      c_ini.X = 0.0;
      c_ini.Y = 0.0;
      c_ini.Z = 0.0;
      // Revisa sobre que eje se hara la graficacion
      switch(exp[2]) {
         case 'y': // Graficacion sobre el eje X
            // Remplaza la variable por su valor
            strcpy(cad,xcad);
            while(c.Busca_cadena(cad,"|y|",pos)) {
               c.Substr(cad,0,pos,xcad1);
               c.Substr(cad,pos+3,200,xcad2);
               sprintf(cad,"%s|M01|%s",xcad1,xcad2);
            }
            inc = (Vtn.Yf - Vtn.Yi) / NUMERO_PUNTOS;
            for(c_ini.Y = Vtn.Yi; c_ini.Y <= Vtn.Yf; c_ini.Y += inc) {
               a_coord = c_ini;
               // Actualiza el valor a calcular
               cnp.Asigna_valor(0,c_ini.Y);
               // Evalua la expresion en notacion polaca
               c_ini.X = cnp.Evalua(cad);
/////////////////////////////////////////////////////////////////
// Poder graficar con puntos o con lineas
//               if(!Grafica_puntos[Sistema_actual]) Dibuja_linea_ventana(a_coord,c_ini,3,Color_grafica_aux[Sistema_actual],1);
//                else Dibuja_punto_ventana(c_ini,3,Color_grafica_aux[Sistema_actual],1);
/////////////////////////////////////////////////////////////////
               // Dibuja la grafica (punto)
               vgraficacion->Dibuja_punto(c_ini);
               // Procesa mensajes pendientes
               n_iter ++;
               if (!(n_iter % 1000l)) Application->ProcessMessages();
               // Revisa si es necesario suspender el calculo
               if (Suspender_Calculo) break;
            }                
            break;
         case 'x': // Graficacion sobre el eje Y
            // Remplaza la variable por su valor
            strcpy(cad,xcad);
            while(c.Busca_cadena(cad,"|x|",pos)) {
               c.Substr(cad,0,pos,xcad1);
               c.Substr(cad,pos+3,200,xcad2);
               sprintf(cad,"%s|M01|%s",xcad1,xcad2);
            }
            inc = (Vtn.Xf - Vtn.Xi) / NUMERO_PUNTOS;
            for(c_ini.X = Vtn.Xi; c_ini.X <= Vtn.Xf; c_ini.X += inc) {
               a_coord = c_ini;
               // Actualiza el valor a calcular
               cnp.Asigna_valor(0,c_ini.X);
               // Evalua la expresion en notacion polaca
               c_ini.Y = cnp.Evalua(cad);
/////////////////////////////////////////////////////////////////
// Poder graficar con puntos o con lineas
//               if(!Grafica_puntos[Sistema_actual]) Dibuja_linea_ventana(a_coord,c_ini,3,Color_grafica_aux[Sistema_actual],1);
//                else Dibuja_punto_ventana(c_ini,3,Color_grafica_aux[Sistema_actual],1);
/////////////////////////////////////////////////////////////////
               // Dibuja la grafica (punto)
               vgraficacion->Dibuja_punto(c_ini);
               // Procesa mensajes pendientes
               n_iter ++;
               if (!(n_iter % 1000l)) Application->ProcessMessages();
               // Revisa si es necesario suspender el calculo
               if (Suspender_Calculo) break;
            }
            break;
      }
      delete []xcad1;
      delete []xcad2;
      delete []xcad3;
   } else {
      TLMensajeForm *vtn = new TLMensajeForm(this);
      // Introduce la expresión a graficar
      vtn->Editor->Lines->Add(exp);
      // Introduce los errores encontrados en la expresión a graficar
      for (int i = 0; i < As->Numero_errores(); i++) vtn->Editor->Lines->Add(As->Retorna_error(i));
      exp_cap[0] = 0;
      vgraficacion->Revisualizar = false;
      vtn->ShowModal();
      delete vtn;
   }
   vgraficacion->Muestra_mensaje("");
   delete As;
}

// Limpia la venta de trabajo
void __fastcall TGrafica2D::Limpiar1Click(TObject *Sender)
{
   Valida_revisualizacion = false;
   vgraficacion->Limpiar_vantana();
}

// Grafica cuando se presiona la tecla ENTER
void __fastcall TGrafica2D::CapturaKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      BGraficaClick(Sender);
   }
}

// Selecciona todo el texto del campo de captura
void __fastcall TGrafica2D::Seleccionatodo1Click(TObject *Sender)
{
   Captura->SelectAll();
}

// Corta el texto seleccionado
void __fastcall TGrafica2D::Cortar1Click(TObject *Sender)
{
   Captura->CutToClipboard();        
}

// Controla la revisualizacion de la ventana
void __fastcall TGrafica2D::Timer1Timer(TObject *Sender)
{
   if (vgraficacion->Revisualizar) {
      vgraficacion->Revisualizar = false;
      if (Valida_revisualizacion) Grafica_funcion(exp_cap);
   }
}

// Cambia la dimension de la ventana de visualizacion
void __fastcall TGrafica2D::Dimenciones1Click(TObject *Sender)
{
   char tmp[30];
   TCDim2DForm *captura = new TCDim2DForm(this);
   gcvt(Vtn.Xi,10,tmp);
   captura->Edit1->Text = tmp;
   gcvt(Vtn.Xf,10,tmp);
   captura->Edit2->Text = tmp;
   gcvt(Vtn.Yi,10,tmp);
   captura->Edit3->Text = tmp;
   gcvt(Vtn.Yf,10,tmp);
   captura->Edit4->Text = tmp;
   captura->ShowModal();
   if (captura->Estado) {
      Vtn.Xi = captura->Edit1->Text.ToDouble();
      Vtn.Xf = captura->Edit2->Text.ToDouble();
      Vtn.Yi = captura->Edit3->Text.ToDouble();
      Vtn.Yf = captura->Edit4->Text.ToDouble();
      vgraficacion->Configura(Vtn);
      vgraficacion->Limpiar_vantana();
      Grafica_funcion(exp_cap);
   }
   delete captura;
}

// Captura los puntos a visualizar
void __fastcall TGrafica2D::Puntosavisualizar1Click(TObject *Sender)
{
   char tmp[30];
   TCaptura1Form *cn = new TCaptura1Form(this);
   gcvt(NUMERO_PUNTOS,10,tmp);
   cn->Abrir("Grafica en 2D","Puntos a visualizar:", tmp,"Escriba los puntos a visualizar en la ventana");
   if (cn->st) {
      NUMERO_PUNTOS = cn->Edit1->Text.ToDouble();
   }
   delete cn;
}

// Selecciona el color de la grafica
void __fastcall TGrafica2D::ColorGraficaClick(TObject *Sender)
{
   ColorDialog->Color = vgraficacion->Color_grafico;
   if (ColorDialog->Execute()) {
      vgraficacion->Color_grafico = ColorDialog->Color;
      vgraficacion->Limpiar_vantana();
   }
}

// Selecciona el color del fondo
void __fastcall TGrafica2D::ColorFondoClick(TObject *Sender)
{
   ColorDialog->Color = vgraficacion->Color_ventana;
   if (ColorDialog->Execute()) {
      vgraficacion->Color_ventana = ColorDialog->Color;
      vgraficacion->Limpiar_vantana();
   }
}

// Detiene el calculo de la función
void __fastcall TGrafica2D::BDetenerClick(TObject *Sender)
{
   Suspender_Calculo = true;
}

