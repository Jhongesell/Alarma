// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

            
#include <vcl.h>
#include <stdio.h>
#include "D:\Libreria\Formas\2d\VGrafica.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

const char *VG_TITULO  = "Ventana de graficación";
const char *VG_TXT01   = "Arrastre el mouse para seleccionar el área";

__fastcall TVVisualizacion::TVVisualizacion(TComponent* Owner): TForm(Owner)
{
   // Define el VG_TITULO de la ventana
   Caption = VG_TITULO;
   // Color de la ventana de graficacion por omision (blanco)
   Color_ventana = clWhite;
   Color_grafico = clBlue;
   Color = Color_ventana;
   // Inicializa el indicador de recuadro
   Sw_Dibuja_rectangulo = false;
   Ventana_seleccionada = false;
   Revisualizar = false; 
   // Se deshabilito la seleccion del recuadro
   Sw_Recuadro_activo = false;
}

// Cierra la ventana de graficación
void __fastcall TVVisualizacion::Salir1Click(TObject *Sender)
{
   Close();        
}

// Cuando la forma cambia de tamaño
void __fastcall TVVisualizacion::FormResize(TObject *Sender)
{
   Limpiar_vantana();
   Calcula_escala();
   Revisualizar = true;
}

// Cuando se requiere redibujar la forma
void __fastcall TVVisualizacion::FormPaint(TObject *Sender)
{
   Revisualizar = true;
}

// Graba la ventana grafica
void __fastcall TVVisualizacion::GrabarClick(TObject *Sender)
{
//   Visualizacion->SaveToFile("c:\\temp\\test.bmp");        
}

// Lee una imagen grabada a la ventana grafica
void __fastcall TVVisualizacion::LeerClick(TObject *Sender)
{
//   Visualizacion->LoadFromFile("C:\\temp\\test.bmp");
}

// Imprime la ventana grafica
void __fastcall TVVisualizacion::Imprimir1Click(TObject *Sender)
{
   Print();
}

// Limpia la ventana grafica
void __fastcall TVVisualizacion::Limpiar1Click(TObject *Sender)
{
   Limpiar_vantana();
}

// Muestra la ventana acerca de ...
void __fastcall TVVisualizacion::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Gráfica 2D");
   delete AcercaDeForm;
}

// Muestra un mensaje dentro de la barra de estado
void TVVisualizacion::Muestra_mensaje(const char *msg)
{
   StatusBar->SimpleText = (AnsiString) msg;
}

// Limpia la ventana de graficacion
void TVVisualizacion::Limpiar_vantana(void)
{
   Color = Color_ventana;
   Visualizacion->Canvas->Pen->Color = Color_ventana;
   Visualizacion->Canvas->Rectangle(0, 0, Visualizacion->Width, Visualizacion->Height);
}



//////////////////////////////////////////////////////////////////////////////
// Aqui empiezan las rutinas que controlan y visualizan una region de la 
// ventana seleccionada por el usuario
//////////////////////////////////////////////////////////////////////////////

// Controla cuando el mouse se presiona
void __fastcall TVVisualizacion::VisualizacionMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         Vt2.Xf = Vt1.Xf = Vt2.Xi = Vt1.Xi = X;
         Vt2.Yf = Vt1.Yf = Vt2.Yi = Vt1.Yi = Y;
         Sw_Dibuja_rectangulo = true;
         Sw_Dibuja_rectangulo_ant = false;
         Ventana_seleccionada = false;
      }
   }
}

// Controla cuando el mouse esta presionado y en movimiento
void __fastcall TVVisualizacion::VisualizacionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Sw_Dibuja_rectangulo) {
         TPenMode mode;

         mode = Visualizacion->Canvas->Pen->Mode;
         Visualizacion->Canvas->Pen->Mode = pmNot;
      
         if(Sw_Dibuja_rectangulo_ant) {
            Visualizacion->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            Visualizacion->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
            Visualizacion->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            Visualizacion->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            Visualizacion->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            Visualizacion->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            Visualizacion->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            Visualizacion->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         }

         Visualizacion->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         Visualizacion->Canvas->LineTo(X,Vt1.Yi);
         Visualizacion->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         Visualizacion->Canvas->LineTo(Vt1.Xi,Y);
         Visualizacion->Canvas->MoveTo(X,Y);
         Visualizacion->Canvas->LineTo(Vt1.Xi,Y);
         Visualizacion->Canvas->MoveTo(X,Y);
         Visualizacion->Canvas->LineTo(X,Vt1.Yi);
      
         Vt2.Xf = X;
         Vt2.Yf = Y;
         Visualizacion->Canvas->Pen->Mode = mode;
         Sw_Dibuja_rectangulo_ant = true;

         // Ajusta a que xVt tenga el inicio y el final de la ventana
         xVt.Xi = Vt1.Xi, xVt.Xf = Vt2.Xf, xVt.Yi = Vt1.Yi, xVt.Yf = Vt2.Yf;
         int  xtmp;
         if (xVt.Xi > xVt.Xf) xtmp = xVt.Xi, xVt.Xi = xVt.Xf, xVt.Xf = xtmp;
         if (xVt.Yi > xVt.Yf) xtmp = xVt.Yi, xVt.Yi = xVt.Yf, xVt.Yf = xtmp;
         // Ajusta los valores a la longitud de la ventana
         if (xVt.Xi < 0) xVt.Xi = 0;
         if (xVt.Yi < 0) xVt.Yi = 0;
         if (xVt.Xf > Visualizacion->Width) xVt.Xf = Visualizacion->Width;
         if (xVt.Yf > Visualizacion->Height) xVt.Yf = Visualizacion->Height;
   //      // Visualiza las coordenadas de la region seleccionada
   //      sprintf(xc,"%s: %d, %d, %d, %d",VG_TXT01,xVt.Xi,xVt.Yi,xVt.Xf,xVt.Yf);
         // Visualiza los valores de la region seleccionada segun la dimención de la ventana
         Vs.Xi = xVt.Xi / Escala.X + Vtn.Xi;
         Vs.Yi = (-(xVt.Yi - Visualizacion->Height) / Escala.Y) + Vtn.Yi;
         Vs.Xf = xVt.Xf / Escala.X + Vtn.Xi;
         Vs.Yf = (-(xVt.Yf - Visualizacion->Height) / Escala.Y) + Vtn.Yi;
         sprintf(xcad,"%s: %3.5Lf, %3.5Lf, %3.5Lf, %3.5Lf",VG_TXT01,Vs.Xi,Vs.Yf,Vs.Xf,Vs.Yi);
         Muestra_mensaje(xcad);
      }     
   }
}

// Controla cuando el mouse es soltado
void __fastcall TVVisualizacion::VisualizacionMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         TPenMode mode;
         mode = Visualizacion->Canvas->Pen->Mode;
         Visualizacion->Canvas->Pen->Mode = pmNot;
         Visualizacion->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         Visualizacion->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         Visualizacion->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         Visualizacion->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         Visualizacion->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         Visualizacion->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         Visualizacion->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         Visualizacion->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         Visualizacion->Canvas->Pen->Mode = mode;
         Vt1.Xf = X;
         Vt1.Xf = Y;
         Sw_Dibuja_rectangulo = false;
         Sw_Dibuja_rectangulo_ant = false;
         Muestra_mensaje("");
         Ventana_seleccionada = true;
      }
   }
}
//////////////////////////////////////////////////////////////////////////////
// Aqui termina las rutinas que controlan y visualizan una region de la 
// ventana seleccionada por el usuario
//////////////////////////////////////////////////////////////////////////////


// Configura las dimenciones de la ventana grafica
void TVVisualizacion::Configura(const Dimencion_Ventana vtn)
{
   Vtn = vtn;
   Calcula_escala();
}


// Calcula la escala de la ventana
void TVVisualizacion::Calcula_escala(void)
{
   Escala.X = Visualizacion->Width / (long double) (Vtn.Xf - Vtn.Xi);
   Escala.Y = Visualizacion->Height / (long double) (Vtn.Yf - Vtn.Yi);
}

// Dibuja un punto sobre la ventana grafica
void TVVisualizacion::Dibuja_punto(C3D pto)
{
   if (pto.X >= Vtn.Xi && pto.X <= Vtn.Xf && pto.Y >= Vtn.Yi && pto.Y <= Vtn.Yf) {
      x = (pto.X - Vtn.Xi) * Escala.X;
      y = Visualizacion->Height - ((pto.Y - Vtn.Yi) * Escala.Y) -1;
      Visualizacion->Canvas->Pixels[x][y] = Color_grafico;
   }
}   

