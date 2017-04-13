// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef CalendH
#define CalendH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ccalendr.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include "d:\libreria\fechas.hpp"
#include "CCALENDR.h"
//---------------------------------------------------------------------------
class TCalendarioForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TPanel *PanelCalendario;
        TCCalendar *CCalendar;
        TLabel *DiaActual;
        TLabel *MesAnoCalendario;
        TSpeedButton *Anterior;
        TSpeedButton *Siguente;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Calendario1;
        TMenuItem *Siguientemes1;
        TMenuItem *Mesanterior1;
        TMenuItem *Mesactual1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SiguenteClick(TObject *Sender);
        void __fastcall AnteriorClick(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        
        void __fastcall Mesactual1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
private:	// User declarations
        char         xmes[50];
        char         xcad[50];
        unsigned int dia;
        unsigned int mes;
        unsigned int ano;
        unsigned int nmdia;
        
        void Actualiza_datos(void);
public:		// User declarations
        // Inicializa el calendario
        void Inicializa_calendario(void);
        __fastcall TCalendarioForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCalendarioForm *CalendarioForm;
//---------------------------------------------------------------------------
#endif
