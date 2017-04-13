// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

#include <vcl.h>
#include <fstream.h>
#include <stdio.h>
#include <io.h>
#include <dir.h>
#include <dos.h>
#include "Princip.h"
#include "trayec.h"
#include "Config.h"
#include "Ayuda.h"
#include "d:\libreria\formas\Alarma\AlarmVis.h"
#include "d:\libreria\man_arch.hpp"
#include "d:\libreria\ClavSeg.hpp"
#include "d:\libreria\Formas\Editor.h"
#include "d:\libreria\formas\Notas.h"
#include "D:\Libreria\Formas\ArbMemo\ArbMemo.h"
#include "d:\libreria\nucleo.hpp"
#pragma hdrstop
 

#pragma package(smart_init)
#pragma resource "*.dfm"

// Objetos globales
Nucleo NCO;
char        *TRAYECTORIA_ARCHIVOS = "C:\\CLOCK";
char        *ARCH_BITACORA = "C:\\CLOCK\\BITACORA.DAT";
char        *TITULO_APLICACION = "Alarma y Utilerias Varias";

// Objetos Globales a Este Modulo
static char *TXT01 = "Alarma";
static char  Usuario[12], Clave[12];
static char *DRIVE_RESPALDO = "A:";
static int   NUMERO_ARCHIVOS = 13;
static char *ARCHIVOS[] = {"ALARMAS.DAT","DIRECTOR.DBF","DIRECTOR.DBT","DIRECTOR.MDX","PENDIENT.DBF","PENDIENT.DBT","PENDIENT.MDX","AGENDA.DBF","AGENDA.DBT","AGENDA.MDX","DIARIO.DBF","DIARIO.DBT","DIARIO.MDX"};
static char *OMISION   = "C:\\CLOCK\\ARCHIVOS\\OMISION";
static char *TRABAJO   = "C:\\CLOCK\\ARCHIVOS";
static char *ORIGINAL  = "C:\\CLOCK\\ARCHIVOS\\ORIGINAL";
static char  USUARIO[100];

TAlarmaForm      *AlarmaForm;


#define RESPALDA_USUARIO    1
#define RESTAURA_USUARIO    2
#define RESTAURA_GENERAL    3
#define RESPALDA_GENERAL    4
#define CERRAR_USUARIO      5
#define ABRIR_USUARIO       6
#define NUEVO_USUARIO       7
#define BORRA_USUARIO       8
#define RESPALDA_DATOS      9
#define RESTAURA_DATOS      10
#define BORRA_AREA_TRABAJO  11



     
__fastcall TAlarmaForm::TAlarmaForm(TComponent* Owner): TForm(Owner)
{
}

// Al crear la forma
void __fastcall TAlarmaForm::FormCreate(TObject *Sender)
{
   // Configuracion para el manejo de la fecha
   ShortDateFormat = "dd/mm/yyyy";
   DateSeparator = '/';
   // Configuracion para el manejo de la hora
   TDateTime a;
   TimeSeparator   = ':';
   TimeAMString    = "A.M.";
   TimePMString    = "P.M.";
   LongTimeFormat = "hh:mm:ss ampm";

   // Manejo del alias dentro de la base de datos
   Session->DeleteAlias("Trabajo");
   Session->AddStandardAlias("Trabajo", "C:\\CLOCK\\ARCHIVOS", "DBASE");

   // Control de la aplicacion
   Application->HintHidePause = 10000;
   Application->Icon->LoadFromFile("C:\\CLOCK\\ALARMA.ICO");
   
   // No hay usuario definido
   Usuario_activo = false;
   strcpy(Usuario,"");
   strcpy(Clave,"");
   Administrador_usuarios(BORRA_AREA_TRABAJO);
   // Lee la configuracion de la ventana
   Configuracion_ventana(1);
   // Sonido de iniciacion del programa
   NCO.Activa_Sonido(INICIO_PROGRAMA);
   Pendientes      = NULL;
   Directorio      = NULL;
   Agenda          = NULL;
   Diario          = NULL;
   CalculadoraForm = NULL;
   Grafica2D       = NULL;
   CronometroForm  = NULL;
   CalendarioForm  = NULL;
   Tabla_ASCII     = NULL;
   Conversiones    = NULL;
   
   // Restaura la configuracion del sistema
   Administrador_archivo_datos(RESTAURA_GENERAL);
   Manipulando_archivos = false;
   // Control de bitacora
   NCO.Revisa_llenado_bitacora();
   NCO.Bitacora("Inicio programa","","");
   // Genera el mensaje a usar en el Hint
   Timer3Timer(Sender);
}

// Indica que termine el programa
void __fastcall TAlarmaForm::Terminarprograma1Click(TObject *Sender)
{
   Close();
}

// Revisa si desea el usuario terminar el programa
void __fastcall TAlarmaForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   if (MessageBox(Handle,"¿Desea terminar el programa?",TXT01,MB_YESNO + MB_ICONQUESTION)  == IDYES) CanClose = true;
    else CanClose = false;
}

// Al cerrar la forma ...
void __fastcall TAlarmaForm::FormClose(TObject *Sender, TCloseAction &Action)
{   
      Manipulando_archivos = true;
      // Graba la configuracion de la ventana
      Configuracion_ventana(0);
      // Cierra sesion de usuario
      Administrador_usuarios(CERRAR_USUARIO);
      // Sonido de terminacion del programa
      NCO.Activa_Sonido(TERMINO_PROGRAMA);
      _sleep(1);

      if (CalculadoraForm) delete CalculadoraForm;
      if (Grafica2D)       delete Grafica2D;
      if (CronometroForm)  delete CronometroForm;
      if (CalendarioForm)  delete CalendarioForm;
      if (Tabla_ASCII)     delete Tabla_ASCII;
      if (Conversiones)    delete Conversiones;
      if (Pendientes)      delete Pendientes;
      if (Directorio)      delete Directorio;
      if (Agenda)          delete Agenda;
      if (Diario)          delete Diario;

      Manipulando_archivos = false;
      NCO.Bitacora("Fin programa",Usuario,"");
      // Borra las ventanas lanzadas dinamicamente
      NCO.Borrar_forma();
      Action = caFree;
}


// Al cambiar de longitud la ventana ajusta el tamaño de la letra visualizada
void __fastcall TAlarmaForm::FormResize(TObject *Sender)
{
   if (!Rescalar_activo) return;
   int lg = (Label1->ClientHeight/1.9) > (Label1->ClientWidth / 13) ? (Label1->ClientWidth / 13) : (Label1->ClientHeight/1.9);
   Label1->Font->Size = lg * 1.3;
}


// Carga la ventana de acerca de ...
void __fastcall TAlarmaForm::Acercade1Click(TObject *Sender)
{
   NCO.Bitacora("Acerca de...","","");
   TAcercaDeForm *AcercaDeForm = new TAcercaDeForm(this);
   if (AcercaDeForm) {
       AcercaDeForm->Muestra_ventana_AcercaDe(TITULO_APLICACION);
       delete AcercaDeForm;
   }
}


// Mostrar la ventana de captura de alarmas
void __fastcall TAlarmaForm::AlarmasClick(TObject *Sender)
{                               
   NCO.Bitacora("Manipulador de alarmas",Usuario,"");
   AlarmaVis->Carga_alarmas_visualizador();
   AlarmaVis->ShowModal();
}

// Carga el editor de notas
void __fastcall TAlarmaForm::Notas1Click(TObject *Sender)
{
   NCO.Bitacora("Editor de notas",Usuario,"");
   TNotasForm *notas = new TNotasForm(this);
   int ptr;
   if (notas) {
      NCO.Adiciona_forma(notas, ptr,2);
      notas->Abre_Notas(ptr);
   }
}

// Carga el editor 
void __fastcall TAlarmaForm::EditorClick(TObject *Sender)
{
   NCO.Bitacora("Editor de texto ASCII",Usuario,"");
   TEditorForm *editor = new TEditorForm(this);
   int ptr;
   if (editor) {
      NCO.Adiciona_forma(editor, ptr,1);
      editor->Abrir_archivo("", false, ptr);
   }
}

// Arbol de edición
void __fastcall TAlarmaForm::OutLineClick(TObject *Sender)
{
   NCO.Bitacora("Arbol de edición",Usuario,"");
   TArbolMemoForm *Arbolmemo = new TArbolMemoForm(this);
   int ptr;
   if (Arbolmemo) {
      NCO.Adiciona_forma(Arbolmemo, ptr,3);
      Arbolmemo->Abrir("",ptr);
   }   
}


// Visualiza el archivo de pendientes
void __fastcall TAlarmaForm::MPendientesClick(TObject *Sender)
{
   NCO.Bitacora("Pendientes",Usuario,"");
   if (!Pendientes) Pendientes = new TPendienteForm(this);
   if (Pendientes) Pendientes->Show();
}

// Visualiza el archivo del directorio
void __fastcall TAlarmaForm::MDirectorioClick(TObject *Sender)
{
   NCO.Bitacora("Directorio",Usuario,"");
   if (!Directorio) Directorio = new TVDirectorioForm(this);
   if (Directorio) Directorio->Show();
}

// Muestra la Agenda
void __fastcall TAlarmaForm::MAgendaClick(TObject *Sender)
{
   NCO.Bitacora("Agenda",Usuario,"");
   if (!Agenda) Agenda = new TVAgendaForm(this);
   if (Agenda) Agenda->Show();
}

// Mustra el diario
void __fastcall TAlarmaForm::Diario1Click(TObject *Sender)
{
   NCO.Bitacora("Diario",Usuario,"");
   if (!Diario) Diario = new TDiarioForm(this);
   if (Diario) Diario->Show();
}


// Muestra la calculadora
void __fastcall TAlarmaForm::CalculadoraClick(TObject *Sender)
{
   NCO.Bitacora("Calculadora",Usuario,"");
   if (!CalculadoraForm) CalculadoraForm = new TCalculadoraForm(this);
   if (CalculadoraForm) CalculadoraForm->Show();
}

// Grafica una funcion en 2D
void __fastcall TAlarmaForm::Graficaen2D1Click(TObject *Sender)
{
   NCO.Bitacora("Graficadora en 2D",Usuario,"");
   if (!Grafica2D) Grafica2D = new TGrafica2D(this);
   if (Grafica2D) Grafica2D->Show();
}

// Muestra el calendario perpetuo
void __fastcall TAlarmaForm::CalendarioClick(TObject *Sender)
{
   NCO.Bitacora("Calendario",Usuario,"");
   if (!CalendarioForm) CalendarioForm = new TCalendarioForm(this);
   if (CalendarioForm) CalendarioForm->Show();    
}

// Muestra el cronometro
void __fastcall TAlarmaForm::CronometroClick(TObject *Sender)
{
   NCO.Bitacora("Cronómetro",Usuario,"");
   if (!CronometroForm) CronometroForm = new TCronometroForm(this);
   if (CronometroForm) CronometroForm->Show();
}

//Visualiza la table de conversiones
void __fastcall TAlarmaForm::Conversiones1Click(TObject *Sender)
{
   NCO.Bitacora("Tabla de conversiones",Usuario,"");
   if (!Conversiones) {
      char arch[MAXPATH];
      Manipulador_archivos ma;
   
      Conversiones = new TAyudaForm(this);
      ma.Construye_trayectoria(TRAYECTORIA_ARCHIVOS,"CONVERSI.DAT", arch);
      Conversiones->Abrir_archivo("Tabla de conversiones",arch);
   }
   if (Conversiones) Conversiones->Show();
}

// Visualiza la tabla ASCII
void __fastcall TAlarmaForm::TablaASCIIClick(TObject *Sender)
{
   NCO.Bitacora("Tabla ASCII",Usuario,"");
   if (!Tabla_ASCII) Tabla_ASCII = new TTablaASCIIForm(this);
   if (Tabla_ASCII) Tabla_ASCII->Show();
}


// Respalda todos los archivos del sistema        
void __fastcall TAlarmaForm::Respalda1Click(TObject *Sender)
{
   NCO.Bitacora("Respalda",Usuario,"");
   Manipulando_archivos = true;
   if (MessageBox(Handle,"¿Desea respaldar los archivos de datos (Alarma, Pendientes, Directorio, Agenda y Diario)?",TXT01,MB_YESNO + MB_ICONQUESTION)  == IDYES) Administrador_archivo_datos(RESPALDA_DATOS);
   Manipulando_archivos = false;
}

// Restaura todos los archivos del sistema        
void __fastcall TAlarmaForm::Restaurar1Click(TObject *Sender)
{
   NCO.Bitacora("Restaura",Usuario,"");
   Manipulando_archivos = true;
   if (MessageBox(Handle,"¿Desea restaurar los archivos de datos (Alarma, Pendientes, Directorio, Agenda y Diario)?",TXT01,MB_YESNO + MB_ICONQUESTION)  == IDYES) Administrador_archivo_datos(RESTAURA_DATOS);
   Manipulando_archivos = false;
}

// Inicializa todos los archivos del sistema        // Generacion y seleccion del usuario
void __fastcall TAlarmaForm::AbrirUsuarioClick(TObject *Sender)
{
   NCO.Bitacora("Abrir usuario",Usuario,"");
   Manipulando_archivos = true;
   TCapturaPaswordForm *cpasd = new TCapturaPaswordForm(this);
   cpasd->ShowModal();
   if (cpasd->Estado) {
       Administrador_usuarios(CERRAR_USUARIO);

       strcpy(Usuario,cpasd->Edit1->Text.c_str());
       strcpy(Clave,cpasd->Edit2->Text.c_str());
       delete cpasd;
       NCO.Bitacora("usuario",Usuario,"");

       char xcad[100];
       sprintf(USUARIO,"%s\\%s",TRABAJO,Usuario);
       sprintf(xcad,"%s\\%s.CFG",USUARIO,Usuario);
       {
         // Lee la configuracion del usuario
         Manipulador_archivos ma;
         ma.Parametros(xcad,LEE_ARCHIVO,95);
         // Revisa que pueda abrir correctamente el archivo
         if (ma.Retorna_estado()) {
             MessageBox(Handle,"Error el usuario no existe",TXT01,MB_OK + MB_ICONEXCLAMATION);
             Manipulando_archivos = false;
             return;
         }
         // Lee la clave del usuario
         ma.Lee_linea(xcad);
       }
       Clave_seguridad cs;
       if (cs.Compara(Clave,cs.Desencripta(xcad))) Administrador_usuarios(ABRIR_USUARIO);
        else MessageBox(Handle,"Error en la clave del usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
   } else delete cpasd;
   Manipulando_archivos = false;
}

// Cerrar secion de usuario
void __fastcall TAlarmaForm::CerrarUsuarioClick(TObject *Sender)
{
   NCO.Bitacora("Cerrar usuario",Usuario,"");
   Manipulando_archivos = true;
   Administrador_usuarios(CERRAR_USUARIO);
   Manipulando_archivos = false;
}

// Genera un nuevo usuario del sistema
void __fastcall TAlarmaForm::NuevoUsuarioClick(TObject *Sender)
{
   NCO.Bitacora("Nuevo usuario",Usuario,"");
   char xu[100], xp1[100], xp2[100];
   unsigned int st;
   TNuevoUsuarioForm *cpasd = new TNuevoUsuarioForm(this);
   cpasd->ShowModal();
   strcpy(xu,cpasd->Edit1->Text.c_str());
   strcpy(xp1,cpasd->Edit2->Text.c_str());
   strcpy(xp2,cpasd->Edit3->Text.c_str());
   st = cpasd->Estado;
   delete cpasd;

   Manipulando_archivos = true;
   Clave_seguridad cs;
   if (st) {
      Administrador_usuarios(CERRAR_USUARIO);
      if (cs.Compara(xp1,xp2)) {
         if (!cs.Compara(xp1,cs.Desencripta(cs.Encripta(xp1)))) {
            MessageBox(Handle,"Error, no es posible usar esa clave",TXT01,MB_OK + MB_ICONEXCLAMATION);
            Manipulando_archivos = false;
            return;
         }
         strcpy(Usuario,xu);
         strcpy(Clave,xp1);
         sprintf(USUARIO,"%s\\%s",TRABAJO,Usuario);
         
         if (!mkdir(USUARIO)) {
            char xcad[100];
            sprintf(xcad,"%s\\%s.CFG",USUARIO,Usuario);
            {
              // Graba la configuracion del usuario
              Manipulador_archivos ma;
              ma.Parametros(xcad,GRABA_ARCHIVO,95);
              // Revisa que pueda abrir correctamente el archivo
              if (ma.Retorna_estado()) {
                 MessageBox(Handle,"Error, no pudo ser generado el usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
                 Manipulando_archivos = false;
                 return;
              }
              // Graba clave del usuario
              ma.Graba_linea(cs.Encripta(Clave));
            }
            Administrador_usuarios(NUEVO_USUARIO);
            Administrador_usuarios(ABRIR_USUARIO);
         } else MessageBox(Handle,"Error, no pudo ser generado el usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
      } else MessageBox(Handle,"Error, no concuerdan las claves",TXT01,MB_OK + MB_ICONEXCLAMATION);
   } 
   Manipulando_archivos = false;
}

// Permite cambiar clave del usuario
void __fastcall TAlarmaForm::Cambiarclave1Click(TObject *Sender)
{
   NCO.Bitacora("Cambiar clave usuario",Usuario,"");
   if (!Usuario_activo) {
      MessageBox(Handle,"Error, no hay usuario definido",TXT01,MB_OK + MB_ICONEXCLAMATION);
      return;
   }   
   Manipulando_archivos = true;
   Clave_seguridad cs;
   TNuevoUsuarioForm *cpasd = new TNuevoUsuarioForm(this);
   cpasd->ShowModal();
   if (cpasd->Estado) {
      char xuser[100], xpas1[100], xpas2[100];
      strcpy(xuser,cpasd->Edit1->Text.c_str());
      strcpy(xpas1,cpasd->Edit2->Text.c_str());
      strcpy(xpas2,cpasd->Edit3->Text.c_str());
      delete cpasd;
      Cadenas s;
      if (s.Compara(xuser,Usuario)) {
         if (!s.Compara(xpas1,xpas2)) {
            strcpy(Clave,xpas2);
            char xcad[100];
            sprintf(xcad,"%s\\%s.CFG",USUARIO,Usuario);
            {
              // Graba la configuracion del usuario
              Manipulador_archivos ma;
              ma.Parametros(xcad,GRABA_ARCHIVO,95);
              // Revisa que pueda abrir correctamente el archivo
              if (ma.Retorna_estado()) {
                  MessageBox(Handle,"Error, no pudo ser cambiada la clave del usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
                  Manipulando_archivos = false;
                  return;
              }
              // Graba clave del usuario
              ma.Graba_linea(cs.Encripta(Clave));
            }
         } else MessageBox(Handle,"Error, la clave es la misma",TXT01,MB_OK + MB_ICONEXCLAMATION);
      } else MessageBox(Handle,"Error, el usuario no coincide",TXT01,MB_OK + MB_ICONEXCLAMATION);
   }
   Manipulando_archivos = false;
}

// Borra un usuario
void __fastcall TAlarmaForm::Borrar1Click(TObject *Sender)
{
   NCO.Bitacora("Borra usuario",Usuario,"");
   Manipulando_archivos = true;
   if (MessageBox(Handle,"¿Desea borrar los archivos de un usuario?",TXT01,MB_YESNO + MB_ICONQUESTION) == IDYES) {
      TCapturaPaswordForm *cpasd = new TCapturaPaswordForm(this);
      cpasd->ShowModal();
      if (cpasd->Estado) {
         strcpy(Usuario,cpasd->Edit1->Text.c_str());
         strcpy(Clave,cpasd->Edit2->Text.c_str());
         sprintf(USUARIO,"%s\\%s",TRABAJO,Usuario);
         delete cpasd;

         char xcad[100];
         sprintf(xcad,"%s\\%s.CFG",USUARIO,Usuario);
         if (access(xcad, 0) == 0) {
            Administrador_usuarios(BORRA_USUARIO);
            Manipulador_archivos ma;
            ma.Remueve_archivo(xcad,0);
            rmdir(USUARIO);
         } else MessageBox(Handle,"Error, se puede borrar el usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
       } else {
         MessageBox(Handle,"Error, no existe el usuario",TXT01,MB_OK + MB_ICONEXCLAMATION);
         delete cpasd;
      }
   }     
   Manipulando_archivos = false;
}

// Administrador de usuarios
void TAlarmaForm::Administrador_usuarios(const int st)
{
   switch (st) {
      case ABRIR_USUARIO:
         Usuario_activo = true;
         Administrador_archivo_datos(RESPALDA_GENERAL);
         Administrador_archivo_datos(RESTAURA_USUARIO);
         break;
      case CERRAR_USUARIO:
         if (Usuario_activo) {
            Usuario_activo = false;
            Administrador_archivo_datos(RESPALDA_USUARIO);
            Administrador_archivo_datos(RESTAURA_GENERAL);
         } else Administrador_archivo_datos(RESPALDA_GENERAL);
         break;
      case NUEVO_USUARIO:
         Administrador_archivo_datos(NUEVO_USUARIO);
         break;
      case BORRA_USUARIO:
         Administrador_usuarios(CERRAR_USUARIO);
         Administrador_archivo_datos(BORRA_USUARIO);
         break;
      case BORRA_AREA_TRABAJO:
         Administrador_archivo_datos(BORRA_AREA_TRABAJO);
   }
}


// Administrador de archivos
void TAlarmaForm::Administrador_archivo_datos(const int st)
{
   bool sw_ini = false;

   // Genera el nombre de subdirectorio de trabajo del usuario
   sprintf(USUARIO,"%s\\%s",TRABAJO,Usuario);

   // Titulo de la aplicación
   if (Usuario_activo) {
      char xcad[100];
      sprintf(xcad,"%s (%s)",TXT01,Usuario);
      Caption = xcad;
    } else {
      Caption = TXT01;
   }
   
   if (Pendientes) {
       delete Pendientes;
       Pendientes = NULL;
   }
   if (Directorio) {
       delete Directorio;
       Directorio = NULL;
   }
   if (Agenda) {
       delete Agenda;
       Agenda = NULL;
   }
   if (Diario) {
       delete Diario;
       Diario = NULL;
   }
   
                                         
   Manipulador_archivos ma;
   char archf[100];
   char archo[100];
   int i;

   switch (st) {
      case RESPALDA_USUARIO:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",USUARIO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         break;
      case RESTAURA_USUARIO:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",USUARIO,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         sw_ini = true;
         break;
      case RESPALDA_GENERAL:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",OMISION,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         break;
      case RESTAURA_GENERAL:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",OMISION,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         sw_ini = true;
         break;
      case RESPALDA_DATOS:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",DRIVE_RESPALDO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         break;
      case RESTAURA_DATOS:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",DRIVE_RESPALDO,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         sw_ini = true;
         break;
      case NUEVO_USUARIO:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",ORIGINAL,ARCHIVOS[i]);
             sprintf(archo,"%s\\%s",USUARIO,ARCHIVOS[i]);
             ma.Copia_archivo(archf,archo);
         }
         break;
      case BORRA_USUARIO:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",USUARIO,ARCHIVOS[i]);
             ma.Remueve_archivo(archf,0);
         }
         break;
      case BORRA_AREA_TRABAJO:
         for (i = 0; i < NUMERO_ARCHIVOS; i++) {
             sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
             ma.Remueve_archivo(archf,0);
         }
         break;
   }
   if (sw_ini) {
      // Carga las alarmas a memoria
      if (AlarmaVis) AlarmaVis->Lee_archivo_alarmas();   
   }
}
                                                   
// Cada segundo activa el cambio de hora
void __fastcall TAlarmaForm::Timer1Timer(TObject *Sender)
{
    Fechas_Horas fh;
    fh.Hora_actual(Hora_Visualizar,1,1);
    Label1->Caption = Hora_Visualizar;

//////////////////////////////////////////////////////////////////    
//    if (WindowState != wsNormal) Application->Title = xcad;
// Ver como puedo mostrar la hora cuando este la ventana minimizada
//////////////////////////////////////////////////////////////////    
}


// Configura al sistema
void __fastcall TAlarmaForm::Configurar1Click(TObject *Sender)
{
   NCO.Bitacora("Configura ventana",Usuario,"");
   ConfigurarForm->Abrir(Label1->Font->Color, Label1->Color, Label1->Font);
   if (!ConfigurarForm->st) return;
   Rescalar_activo = false;
   Label1->Font    = ConfigurarForm->Label1->Font;
   Label1->Color   = ConfigurarForm->Label1->Color;
   ClientHeight          = Label1->Font->Size * 3;
   ClientWidth           = Label1->Font->Size * 11;
   Rescalar_activo = true;
}


// Graba o lee la configuracion de la ventana
void TAlarmaForm::Configuracion_ventana(const bool st)
{
   int xIzq, xArr, xLar, xAnc, siz, st1 = 0, st2 = 0, st3 = 0, st4 = 0, xtit = 1;
   char fnt[100];
   TColor            Color_fondo;
   TColor            Color_texto;

   if (st) {
      // Valores de configuracion por omision
      xIzq = 10, xArr = 50, xLar = 23, xAnc = 118;
      Color_fondo = Label1->Color;
      Color_texto = Label1->Font->Color;
      strcpy(fnt,Label1->Font->Name.c_str());
      siz = Label1->Font->Size;
      Rescalar_activo  = false;
      // lee la configuracion de la ventana
      ifstream lee(CONFIGURACION,ios::binary);
      if (lee) {
         lee.read((char *)&xIzq,sizeof(xIzq));
         lee.read((char *)&xArr,sizeof(xArr));
         lee.read((char *)&xLar,sizeof(xLar));
         lee.read((char *)&xAnc,sizeof(xAnc));
         lee.read((char *)&Color_fondo,sizeof(TColor));
         lee.read((char *)&Color_texto,sizeof(TColor));
         lee.read((char *)&siz,sizeof(siz));
         lee.read((char *)fnt,100);
         lee.read((char *)&st1,sizeof(st1));
         lee.read((char *)&st2,sizeof(st2));
         lee.read((char *)&st3,sizeof(st3));
         lee.read((char *)&st4,sizeof(st4));
         lee.read((char *)&xtit,sizeof(xtit));
         lee.close();
      }
      // Modificar configuracion de ventana
      Rescalar_activo  = false;
      Label1->Color = Color_fondo;
      Label1->Font->Color = Color_texto;
      Label1->Font->Name = fnt;
      Label1->Font->Size = siz;
      TFontStyles st;
      if (st1) st << fsBold;
      if (st2) st << fsItalic;
      if (st3) st << fsUnderline;
      if (st4) st << fsStrikeOut;
      Label1->Font->Style = st;
      Left = xIzq;
      Top = xArr;
      ClientHeight = xLar;
      ClientWidth = xAnc;
      MuestraTitulo = xtit;
      Rescalar_activo = true;
      CtrlMuestraTitulo();      
    } else {
      // Graba la configuracion de la ventana
      ofstream grab(CONFIGURACION,ios::binary);
      if (grab) {
         Color_fondo = Label1->Color;
         Color_texto = Label1->Font->Color;
         siz         = Label1->Font->Size;
         xtit        = MuestraTitulo;
         xLar        = ClientHeight;
         xAnc        = ClientWidth;
         if (Label1->Font->Style.Contains(fsBold)) st1 = 1;
         if (Label1->Font->Style.Contains(fsItalic)) st2 = 1;
         if (Label1->Font->Style.Contains(fsUnderline)) st3 = 1;
         if (Label1->Font->Style.Contains(fsStrikeOut)) st4 = 1;
         grab.write((char *)&Left,sizeof(Left));
         grab.write((char *)&Top,sizeof(Top));
         grab.write((char *)&xLar,sizeof(xLar));
         grab.write((char *)&xAnc,sizeof(xAnc));
         grab.write((char *)&Color_fondo,sizeof(TColor));
         grab.write((char *)&Color_texto,sizeof(TColor));
         grab.write((char *)&siz,sizeof(siz));
         grab.write((char *)Label1->Font->Name.c_str(),100);
         grab.write((char *)&st1,sizeof(st1));
         grab.write((char *)&st2,sizeof(st2));
         grab.write((char *)&st3,sizeof(st3));
         grab.write((char *)&st4,sizeof(st4));
         grab.write((char *)&xtit,sizeof(xtit));
         grab.close();
      }                                                        
   }
   
}


// Respalda cada 5 minutos todos los datos del usuario activo
void __fastcall TAlarmaForm::Timer2Timer(TObject *Sender)
{
   // No hace el respaldo si se estan manipulando los archivos
   if (Manipulando_archivos) return;
   Manipulador_archivos ma;
   char archf[100];
   char archo[100];
   int i;
   if (Usuario_activo) {
      for (i = 0; i < NUMERO_ARCHIVOS; i++) {
          sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
          sprintf(archo,"%s\\%s",USUARIO,ARCHIVOS[i]);
          ma.Copia_archivo(archf,archo);
      }
    } else {
      for (i = 0; i < NUMERO_ARCHIVOS; i++) {
          sprintf(archf,"%s\\%s",TRABAJO,ARCHIVOS[i]);
          sprintf(archo,"%s\\%s",OMISION,ARCHIVOS[i]);
          ma.Copia_archivo(archf,archo);
      }
   }
}


// Se activa cada minuto
void __fastcall TAlarmaForm::Timer3Timer(TObject *Sender)
{
   char xcad[50], xfech[20];
   Fechas_Horas fh;
   // Genera mensaje para visualizar como Hint
   fh.Fecha_hoy(xfech);
   fh.Fecha_escrita(xfech, xcad, 1, 1);
   Hint = xcad;
   // Borra las ventanas lanzadas dinamicamente
   NCO.Borrar_forma();
}

// Mostrar o no el titulo de la aplicacion
void __fastcall TAlarmaForm::Titulo1Click(TObject *Sender)
{
  if (MuestraTitulo) MuestraTitulo = 0;
   else MuestraTitulo = 1;
  CtrlMuestraTitulo(); 
}

// Controla el mostrar o no el titulo de la aplicacion
void TAlarmaForm::CtrlMuestraTitulo(void)
{
  Rescalar_activo  = false;
  if (!MuestraTitulo) {
     Titulo1->Checked = false;
     BorderStyle = bsNone;
     Height = ClientHeight - 27;
     Width  = ClientWidth  -  8;
   } else {
     Titulo1->Checked = true;
     Height = ClientHeight + 27;
     Width  = ClientWidth  +  8;
     BorderStyle = bsSizeable;
  }
  Rescalar_activo  = true;
}

