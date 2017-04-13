// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef AlarmVisH
#define AlarmVisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <graphsv3.hpp>
#include <OleCtrls.hpp>
#include <vcf1.hpp>
#include <vcfi.hpp>
#include <vcspell3.hpp>
#include <MPlayer.hpp>
#include <checklst.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>

#define NUMA_MAX_ALARMAS 30


class TAlarmaVis : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TListBox *ListaAlarmas;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Alarmas1;
        TMenuItem *Nueva1;
        TMenuItem *Editar1;
        TMenuItem *Borrar1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TMenuItem *Tiposdealarmas1;
        TTimer *Timer2;
        TPanel *Panel2;
        TSpeedButton *IcNueva;
        TSpeedButton *IcEditar;
        TSpeedButton *IcBorrar;
        TSpeedButton *IcAyuda;
        void __fastcall NuevoClick(TObject *Sender);
        void __fastcall EditarClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        
        void __fastcall BorrarClick(TObject *Sender);
        
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Tiposdealarmas1Click(TObject *Sender);
        
        void __fastcall Timer2Timer(TObject *Sender);
        
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
    char  Alarma_numero;
    bool  Alarma_inicializada;
    long  Alarma_horas[NUMA_MAX_ALARMAS];
    char  Alarma_fecha[NUMA_MAX_ALARMAS][12];
    int   Alarma_dia[NUMA_MAX_ALARMAS];
    int   Alarma_tipo[NUMA_MAX_ALARMAS];
    int   Alarma_CadaCuanto[NUMA_MAX_ALARMAS];
    char  Alarma_mensaje[NUMA_MAX_ALARMAS][100];
    bool  Alarma_activada[NUMA_MAX_ALARMAS];
    bool  Alarma_activa[NUMA_MAX_ALARMAS];
    bool  Alarma_borrada[NUMA_MAX_ALARMAS];

    int i;   // Temporal
    long ns;  // Numero de segundos
    long xns; // Numero de segundos

    void Revisa_activacion_alarma(void);
    void Graba_archivo_alarmas(void);
    void Analiza_alarmas(void);

public:		// User declarations

    bool  Alarma_existe;
    bool  Cargando_alarma;

    void Carga_alarmas_visualizador(void);
    void Lee_archivo_alarmas(void);
     
       __fastcall TAlarmaVis(TComponent* Owner);
};

extern PACKAGE TAlarmaVis *AlarmaVis;
#endif
