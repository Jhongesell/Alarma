// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef CronometH
#define CronometH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "d:\libreria\fechora.hpp"
//---------------------------------------------------------------------------

class TCronometroForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *Iniciar;
        TBitBtn *Parar;
        TBitBtn *inicializa;
        TPanel *Panel2;
        TLabel *Label1;
        TLabel *TInicio;
        TLabel *Label3;
        TLabel *TFin;
        TLabel *Label5;
        TLabel *TDiferencia;
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Cronometro1;
        TMenuItem *Iniciar1;
        TMenuItem *Parar1;
        TMenuItem *Inicializar1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IniciarClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall inicializaClick(TObject *Sender);
        void __fastcall PararClick(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
private:	// User declarations
        long T_inicio, T_fin, T_diferencia;
        char xcad[30];
        Fechas_Horas t;
        bool Activo;
public:		// User declarations
        __fastcall TCronometroForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCronometroForm *CronometroForm;
//---------------------------------------------------------------------------
#endif
