// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



//---------------------------------------------------------------------------
#ifndef PrincipalH
#define PrincipalH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>


#include "d:\libreria\formas\Alarma\AlarmVis.h"
#include "d:\libreria\Formas\Calculad.h"
#include "d:\libreria\Formas\Cronomet.h"
#include "d:\libreria\Formas\Calend.h"
#include "d:\libreria\Formas\TASCII.h"
#include "d:\libreria\Formas\Ayuda.h"
#include "d:\libreria\Formas\AcercaDe.h"
#include "d:\libreria\formas\2d\Graf2D.h"
#include "d:\libreria\formas\director\Vdirect.h"
#include "d:\libreria\formas\pendient\Vpendien.h"
#include "d:\libreria\formas\CPasword.h"
#include "d:\libreria\formas\CNPaswor.h"
#include "d:\libreria\formas\agenda\Agenda.h"
#include "d:\Libreria\Formas\Diario\VDiario.h"

//---------------------------------------------------------------------------


class TAlarmaForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TTimer *Timer1;

        TPopupMenu *PopupMenu1;
        TMenuItem *Alarmas;
        TMenuItem *Acercade1;
        TMenuItem *Editor;
        TMenuItem *Calculadora;
        TMenuItem *Cronometro;
        TMenuItem *Calendario;
        TMenuItem *TablaASCII;
        TMenuItem *MPendientes;
        TMenuItem *MDirectorio;
        TMenuItem *Conversiones1;
        TMenuItem *Graficaen2D1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *Utilerias1;
        TMenuItem *Respalda1;
        TMenuItem *Restaurar1;
        TMenuItem *OutLine;
        TMenuItem *N3;
        TMenuItem *MUsuarios;
        TMenuItem *AbrirUsuario;
        TMenuItem *CerrarUsuario;
        TMenuItem *NuevoUsuario;
        TMenuItem *Borrar1;
        TMenuItem *Cambiarclave1;
        TMenuItem *Terminarprograma1;
        TMenuItem *Configurar1;
        TMenuItem *Notas1;
        TTimer *Timer2;
   TTimer *Timer3;
   TMenuItem *MAgenda;
   TMenuItem *Diario1;
        TMenuItem *Titulo1;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall AlarmasClick(TObject *Sender);
        void __fastcall EditorClick(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall TablaASCIIClick(TObject *Sender);
        void __fastcall MPendientesClick(TObject *Sender);
        void __fastcall MDirectorioClick(TObject *Sender);
        void __fastcall CalendarioClick(TObject *Sender);
        void __fastcall CalculadoraClick(TObject *Sender);
        void __fastcall CronometroClick(TObject *Sender);
        void __fastcall Conversiones1Click(TObject *Sender);
        void __fastcall Graficaen2D1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Respalda1Click(TObject *Sender);
        void __fastcall Restaurar1Click(TObject *Sender);
        void __fastcall OutLineClick(TObject *Sender);
        
        void __fastcall AbrirUsuarioClick(TObject *Sender);
        void __fastcall CerrarUsuarioClick(TObject *Sender);
        void __fastcall NuevoUsuarioClick(TObject *Sender);
        void __fastcall Borrar1Click(TObject *Sender);
        void __fastcall Cambiarclave1Click(TObject *Sender);

        void __fastcall Terminarprograma1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Configurar1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Notas1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
   void __fastcall Timer3Timer(TObject *Sender);
   void __fastcall MAgendaClick(TObject *Sender);
   void __fastcall Diario1Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall Titulo1Click(TObject *Sender);
private:	// User declarations
    TPendienteForm   *Pendientes;
    TVDirectorioForm *Directorio;
    TVAgendaForm     *Agenda;
    TDiarioForm      *Diario;

    TCalculadoraForm *CalculadoraForm;
    TGrafica2D       *Grafica2D;
    TCronometroForm  *CronometroForm;
    TCalendarioForm  *CalendarioForm;
    TTablaASCIIForm  *Tabla_ASCII;
    TAyudaForm       *Conversiones;
    char              Hora_Visualizar[20];
    bool              MuestraTitulo;

    bool Usuario_activo;
    bool Rescalar_activo;
    bool Manipulando_archivos;
    
    void Revisa_activacion_alarma(void);
    void Lee_archivo_alarmas(void);
    void Administrador_usuarios(const int st);
    void Administrador_archivo_datos(const int st);
         // Graba o lee la configuracion de la ventana
    void Configuracion_ventana(const bool st);
         // Controla el mostrar o no el titulo de la aplicacion
    void CtrlMuestraTitulo(void);

public:		// User declarations
    __fastcall TAlarmaForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmaForm *AlarmaForm;
//---------------------------------------------------------------------------
#endif













         
