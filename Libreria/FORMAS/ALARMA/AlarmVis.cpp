// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#include <vcl.h>
#include <stdio.h>
#include "d:\libreria\man_arch.hpp"
#include "d:\libreria\fechora.hpp"
#include "d:\clock\trayec.h"
#include "d:\libreria\formas\Alarma\AlarmVis.h"
#include "d:\libreria\formas\Alarma\AlarmCap.h"
#include "d:\libreria\formas\Alarma\aviso.h"
#include "d:\Libreria\Formas\AcercaDe.h"
#include "d:\libreria\Formas\Ayuda.h"
#include "d:\libreria\nucleo.hpp"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TAlarmaVis       *AlarmaVis;
// Objeto global Nucleo
extern Nucleo NCO;

char *Dias[] = {
   "Lunes",
   "Martes",
   "Miercoles",
   "Jueves",
   "Viernes",
   "Sabado",
   "Domingo"
};


char *Tipo[] = {
   "Unica",
   "Diaria",
   "Semanal",
   "Mensual",
   "Anual",
   "Ciclica",
   "Dia laborable",
   "Fin de semana"
   
};


__fastcall TAlarmaVis::TAlarmaVis(TComponent* Owner): TForm(Owner)
{
}

// Al crear la forma
void __fastcall TAlarmaVis::FormCreate(TObject *Sender)
{
   Lee_archivo_alarmas();
   Alarma_inicializada = true;
}



// Carga las alarmas existentes al visualizador de alarmas
void TAlarmaVis::Carga_alarmas_visualizador(void)
{
   char xcad[300], xhora[30], xc1[20], xc2[20];

   ListaAlarmas->Items->BeginUpdate();
   ListaAlarmas->Items->Clear();
   Fechas_Horas fh;

   for (int i = 0; i < Alarma_numero; i++) {
       fh.Nseg__horas(Alarma_horas[i],xhora);
       fh.Alinea_cadena(Dias[Alarma_dia[i]], 9, CENTRADA, xc1);
       fh.Alinea_cadena(Tipo[Alarma_tipo[i]], 13, CENTRADA, xc2);
       sprintf(xcad,"%s  %s  %s  %s  %s",xhora,Alarma_fecha[i],xc1,xc2,Alarma_mensaje[i]);   
       ListaAlarmas->Items->Add(xcad);
   }
   ListaAlarmas->Items->EndUpdate();

   if (Alarma_numero) Alarma_existe = true;
}


// Genara una nueva alarma
void __fastcall TAlarmaVis::NuevoClick(TObject *Sender)
{
    if ((Alarma_numero + 1) >= NUMA_MAX_ALARMAS)  {
       MessageBox(Handle,"Hay muchas alarmas definidas","Alarma",MB_OK + MB_ICONEXCLAMATION);
       return;
    }
    char xcad[30], xxcad[30];
    char xhora[30];
    int lg, st = 0;
    Fechas_Horas fh;
    TDateTime ti;

    strcpy(xhora,ti.TimeString().c_str());
    lg = strlen(xhora);
    if (xhora[lg-1] != '.') MessageBox(Handle,"Defina en configuración regional la hora con formato HH:MM:SS [A.M.|P.M.]","Alarma",MB_OK + MB_ICONEXCLAMATION);
    if (isupper(xhora[lg-2])) st = 1;
     
    TCapturaAlarma *capalarma = new TCapturaAlarma(this);  
    capalarma->Hora->Time = ti.CurrentTime();
    capalarma->Fecha->Date = ti.CurrentDate();
    capalarma->Dia->ItemIndex = 0;
    capalarma->Tipo->ItemIndex = 0;
    capalarma->CadaCuanto->Text = 10;
    capalarma->ShowModal();
    if (capalarma->Captura) {
       ti = capalarma->Hora->Time;
       strcpy(xcad,ti.TimeString().c_str());
       if(!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
       if (!st) fh.Convierte_mayusculas(xcad);
       fh.AmPm__hors(xcad,xxcad);
       Alarma_horas[Alarma_numero] = fh.Horas__n_seg(xxcad);
       TDateTime fech = capalarma->Fecha->Date;
       strcpy(xcad,fech.DateString().c_str());
       if (!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
       if (xcad[8] == 0) {
          xcad[8] = xcad[6];
          xcad[9] = xcad[7];
          xcad[10] = 0;
          if(xcad[8] < '8') xcad[6] = '2', xcad[7] = '0';
           else xcad[6] = '1', xcad[7] = '9';
       }    
       strcpy(Alarma_fecha[Alarma_numero],xcad);
       Alarma_dia[Alarma_numero] = capalarma->Dia->ItemIndex;
       Alarma_tipo[Alarma_numero] = capalarma->Tipo->ItemIndex;
       Alarma_CadaCuanto[Alarma_numero] = capalarma->CadaCuanto->Text.ToInt();
       strcpy(Alarma_mensaje[Alarma_numero],capalarma->Mensaje->Text.c_str());
       Alarma_borrada[Alarma_numero] = false;
       Alarma_numero++;
       Graba_archivo_alarmas();
       Lee_archivo_alarmas();
       Carga_alarmas_visualizador();
    }
    delete capalarma;
}

// Edita la alarma seleccionada
void __fastcall TAlarmaVis::EditarClick(TObject *Sender)
{
   char xcad[30], xxcad[30];
    char xhora[30];
    int lg, st = 0;
    Fechas_Horas fh;
    TDateTime ti;

    strcpy(xhora,ti.TimeString().c_str());
    lg = strlen(xhora);
    if (xhora[lg-1] != '.') MessageBox(Handle,"Defina en configuración regional la hora con formato HH:MM:SS [A.M.|P.M.]","Alarma",MB_OK + MB_ICONEXCLAMATION);
    if (isupper(xhora[lg-2])) st = 1;

   if (ListaAlarmas->ItemIndex >= 0) {
      TCapturaAlarma *capalarma = new TCapturaAlarma(this);  
      fh.Nseg__horas(Alarma_horas[ListaAlarmas->ItemIndex],xcad);
      fh.Hrs__am_pm(xcad,xxcad);
      if (!st) fh.Convierte_minusculas(xxcad);
      capalarma->Hora->Time = TDateTime(xxcad,dtkTime);
      capalarma->Fecha->Date =  TDateTime(Alarma_fecha[ListaAlarmas->ItemIndex]);
      capalarma->Dia->ItemIndex = Alarma_dia[ListaAlarmas->ItemIndex];
      capalarma->Tipo->ItemIndex = Alarma_tipo[ListaAlarmas->ItemIndex];
      capalarma->CadaCuanto->Text = Alarma_CadaCuanto[ListaAlarmas->ItemIndex];
      capalarma->Mensaje->Text = Alarma_mensaje[ListaAlarmas->ItemIndex];
      if (capalarma->Tipo->ItemIndex == 5) {
         capalarma->Label6->Visible = true;
         capalarma->CadaCuanto->Visible = true;
       } else {
         capalarma->Label6->Visible = false;
         capalarma->CadaCuanto->Visible = false;
      }     
      capalarma->ShowModal();
      if (capalarma->Captura) {
         TDateTime hor = capalarma->Hora->Time;
         strcpy(xcad,hor.TimeString().c_str());
         if(!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
         if (!st) fh.Convierte_mayusculas(xcad);
         fh.AmPm__hors(xcad,xxcad);
         Alarma_horas[ListaAlarmas->ItemIndex] = fh.Horas__n_seg(xxcad);
         TDateTime fech = capalarma->Fecha->Date;
         strcpy(xcad,fech.DateString().c_str());
         if (!fh.Es_caracter_digito(xcad[1])) fh.Inserta_caracter(xcad,0,'0');
         if (xcad[8] == 0) {
            xcad[8] = xcad[6];
            xcad[9] = xcad[7];
            xcad[10] = 0;
            if(xcad[8] < '8') xcad[6] = '2', xcad[7] = '0';
             else xcad[6] = '1', xcad[7] = '9';
         }    
         strcpy(Alarma_fecha[ListaAlarmas->ItemIndex],xcad);
         Alarma_dia[ListaAlarmas->ItemIndex] = capalarma->Dia->ItemIndex;
         Alarma_tipo[ListaAlarmas->ItemIndex] = capalarma->Tipo->ItemIndex;
         Alarma_CadaCuanto[ListaAlarmas->ItemIndex] = capalarma->CadaCuanto->Text.ToInt();
         strcpy(Alarma_mensaje[ListaAlarmas->ItemIndex],capalarma->Mensaje->Text.c_str());
         Alarma_borrada[ListaAlarmas->ItemIndex] = false;
         Graba_archivo_alarmas();
         Lee_archivo_alarmas();
         Carga_alarmas_visualizador();
      }
      delete capalarma;
   }
}

// Borra la alarma seleccionada
void __fastcall TAlarmaVis::BorrarClick(TObject *Sender)
{
   if (ListaAlarmas->ItemIndex >= 0) {
       if (MessageBox(Handle,"¿Desea borrar la alarma?","Alarma",MB_YESNO + MB_ICONQUESTION)  == IDYES) {
           Alarma_borrada[ListaAlarmas->ItemIndex] = true;
           Graba_archivo_alarmas();
           Lee_archivo_alarmas();
           Carga_alarmas_visualizador();
       }
   }
}


// Lectura de las alarmas definidas en el archivo CLOCK.DAT
void TAlarmaVis::Lee_archivo_alarmas(void)
{
   Cargando_alarma = true;
   char xcad[105];
   char i = 0;
   Fechas_Horas fh;
   
   Alarma_existe = false;
   Alarma_numero = 0;

   // Manipulador de archivos
   Manipulador_archivos ma;
   ma.Parametros(ALARMAS,LEE_ARCHIVO,95);
   // Revisa que pueda abrir correctamente el archivo
   if (ma.Retorna_estado()) return;
   // Lee la hora de activacion de la alarma
   ma.Lee_linea(xcad);
   // Controla la lectura de la estructura de la alarma
   while(xcad[0] != '-') {
      // Almacena y comvierte la hora en formato HH:MM:SS a numeros de segundos desde el comienzo del dia
      Alarma_horas[i] = fh.Horas__n_seg(xcad);
      // Lee la fecha 
      ma.Lee_linea(xcad);
      strcpy(Alarma_fecha[i],xcad);
      // Lee el dia de la semana 
      ma.Lee_linea(xcad);
      Alarma_dia[i] = atoi(xcad);
      // Lee el tipo de alarma
      Alarma_tipo[i] = atoi(xcad); 
      ma.Lee_linea(xcad);
      // Almacena el tipo de alarma
      Alarma_tipo[i] = atoi(xcad);
      // Lee cada cuantos minutos se activara la alarma ciclica
      ma.Lee_linea(xcad);
      // Almacena cada cuantos minutos se activara la alarma ciclica
      Alarma_CadaCuanto[i] = atoi(xcad);
      // Lee el texto de la alarma
      ma.Lee_linea(xcad);
      // Almacena el mensaje de la alarma  
      strcpy(Alarma_mensaje[i],xcad);
      // Indica que la alarma no ha sido borrada
      Alarma_borrada[i] = false;
      // Lee la hora de activacion de la alarma
      ma.Lee_linea(xcad);
      i++;
      if (i >= NUMA_MAX_ALARMAS) break;
   }
   Alarma_numero = i;
   if (Alarma_numero) Alarma_existe = true;
   // Analiza las alarmas
   Analiza_alarmas();
   Cargando_alarma = false;
}

//  Graba las alarmas en archivo
void TAlarmaVis::Graba_archivo_alarmas(void)
{
   Cargando_alarma = true;
   char xcad[105];
   int i = 0;
   Fechas_Horas fh;
   
   // Manipulador de archivos
   Manipulador_archivos ma;
   ma.Parametros(ALARMAS,GRABA_ARCHIVO,0);
   // Revisa que pueda abrir correctamente el archivo
   if (ma.Retorna_estado()) return;
   for (i = 0; i < Alarma_numero; i++) {
       if (Alarma_borrada[i]) continue;
       fh.Nseg__horas(Alarma_horas[i], xcad);
       ma.Graba_linea(xcad);
       ma.Graba_linea(Alarma_fecha[i]);
       itoa(Alarma_dia[i],xcad,10);
       ma.Graba_linea(xcad);
       itoa(Alarma_tipo[i],xcad,10);
       ma.Graba_linea(xcad);
       itoa(Alarma_CadaCuanto[i],xcad,10);
       ma.Graba_linea(xcad);
       ma.Graba_linea(Alarma_mensaje[i]);
   }
   // Graba el final del archivo
   ma.Graba_linea("-----------------------");
   Cargando_alarma = false;
}



// Revisa si se activa la alarma y en su caso muestra el mensajo de esta
void TAlarmaVis::Revisa_activacion_alarma(void)
{
   Fechas_Horas fh;
   Cargando_alarma = true;
   ns = fh.Numero_segundos();
   bool st = false;
   
   for (i = 0; i < Alarma_numero; i++) {
      if (Alarma_activa[i] && Alarma_activada[i]) {
         if (ns >= Alarma_horas[i] && ns <= (Alarma_horas[i] + 3)) {
            Alarma_activada[i] = false;
            char xtiempo[40];
            fh.Hora_actual(xtiempo,1,1);
            // Suena la alrma
            if (NCO.Sonidos_alarma) NCO.Activa_Sonido(ALARMA);
            // Muestra el mensaje de la alarma
            TAvisoAlarma *AvisoAlarma = new TAvisoAlarma(this);
            AvisoAlarma->Hora->Caption = xtiempo;    
            AvisoAlarma->Mensaje->Caption = Alarma_mensaje[i];
            // Si la alarma es unica se borrara esta
            if (Alarma_tipo[i] == 0) {
                Alarma_borrada[i] = true;
                st = true;
            }
            // Si la alarma es ciclica actualiza a la proxima 
            if (Alarma_tipo[i] == 5) {
               Alarma_horas[i] = Alarma_horas[i] + (Alarma_CadaCuanto[i] * 60);
               st = true;
            }
            AvisoAlarma->ShowModal();
            delete AvisoAlarma;
         }
      }
   }
   if (st) {
      // Actualiza el archivo de alarmas
      Graba_archivo_alarmas();
      // Lee el archivo de alarmas
      Lee_archivo_alarmas();
      // Actualiza las alarmas cargadas
      Carga_alarmas_visualizador();
   }
   Cargando_alarma = false;
}


// Analiza la activacion de las alarmas
void TAlarmaVis::Analiza_alarmas(void)
{
   int i;
   char fecha[20];
   Fechas_Horas fh;
   
   fh.Fecha_hoy(fecha);
   int dia_sem = fh.Dia_semana(fecha);
   // Transforma el dia de la semana a Lunes (0) ... 
   if (dia_sem > 1 && dia_sem < 7) dia_sem -= 2;
    else if (dia_sem == 1) dia_sem = 5;
         else if (dia_sem == 7) dia_sem = 6;
   for (i = 0; i < Alarma_numero; i++) {
       Alarma_activa[i] = false;
       Alarma_activada[i] = true;
       switch (Alarma_tipo[i]) {
          case 0: // Unica
             if (Alarma_fecha[i][0] == fecha[0] && Alarma_fecha[i][1] == fecha[1] && Alarma_fecha[i][3] == fecha[3] && Alarma_fecha[i][4] == fecha[4] && Alarma_fecha[i][6] == fecha[6] && Alarma_fecha[i][7] == fecha[7] && Alarma_fecha[i][8] == fecha[8] && Alarma_fecha[i][9] == fecha[9]) Alarma_activa[i] = true;
             break;
          case 1: // Diaria
             Alarma_activa[i] = true;
             break;
          case 2: // Semanal
             if (Alarma_dia[i] == dia_sem) Alarma_activa[i] = true;
             break;
          case 3: // Mensual
             if (Alarma_fecha[i][0] == fecha[0] && Alarma_fecha[i][1] == fecha[1]) Alarma_activa[i] = true;
             break;
          case 4: // Anual
             if (Alarma_fecha[i][0] == fecha[0] && Alarma_fecha[i][1] == fecha[1] && Alarma_fecha[i][3] == fecha[3] && Alarma_fecha[i][4] == fecha[4]) Alarma_activa[i] = true;
             break;
          case 5: // Ciclica
             Alarma_activa[i] = true;
             break;
          case 6: // Dia laborable
             if (dia_sem < 5) Alarma_activa[i] = true;
             break;
          case 7: // Fin de semana
             if (dia_sem > 4) Alarma_activa[i] = true;
             break;
       }
   }
}


// Controla la revision de las alarmas
void __fastcall TAlarmaVis::Timer1Timer(TObject *Sender)
{
   if (Cargando_alarma) return;
   if (Alarma_existe) Revisa_activacion_alarma();        
}


void __fastcall TAlarmaVis::Salir1Click(TObject *Sender)
{
   Close();     
}

// Muestra la ventana de acerca de ...
void __fastcall TAlarmaVis::Acercade1Click(TObject *Sender)
{
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   AcercaDeForm->Muestra_ventana_AcercaDe("Alarmas");
   delete AcercaDeForm;
}

// Visualiza informacion sobre los tipos de alarmas
void __fastcall TAlarmaVis::Tiposdealarmas1Click(TObject *Sender)
{
   TAyudaForm *ayuda = new TAyudaForm(this);
   ayuda->Abrir_archivo("Tipos de alarmas",AYUDA_ALARMA);
   ayuda->ShowModal();
   delete ayuda;
}

// Controla la activacion de la camapanada de cada hora y carga de alarmas por nuevo dia
void __fastcall TAlarmaVis::Timer2Timer(TObject *Sender)
{
   Fechas_Horas fh;
   xns = fh.Numero_segundos();

   // Revisa si esta activo el sonido de cada hora
   if (NCO.Sonidos_hora) {
      // Suena una campana cada hora 
      if (!(xns % 3600l)) NCO.Activa_Sonido(CAMPANADA);
   }

   // Al cambiar de dia carga nuevamente las alarmas
   if (Alarma_inicializada && xns < 3) {
      Alarma_inicializada = false;
      Lee_archivo_alarmas();
   } 
   if (xns > 3)Alarma_inicializada = true;
}



