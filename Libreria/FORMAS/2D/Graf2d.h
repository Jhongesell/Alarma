// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef Graf2DH
#define Graf2DH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "d:\libreria\definic.hpp"
#include <Dialogs.hpp>

#include "D:\Libreria\Formas\2d\VGrafica.h"
//---------------------------------------------------------------------------
class TGrafica2D : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *archivo1;
        TMenuItem *Salir1;
        TMenuItem *ecuacin1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BGrafica;
        TMenuItem *Dimenciones1;
        TEdit *Captura;
        TLabel *Label1;
        TMenuItem *Colores1;
        TMenuItem *ColorGrafica;
        TMenuItem *ColorFondo;
        TMenuItem *Edicion1;


        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TMenuItem *Funcionesvalidas1;
        TMenuItem *Copiar1;
        TMenuItem *Pegar1;
        TMenuItem *Ultimaexpresin1;
        TMenuItem *Eliminaexpresin1;
        TMenuItem *Ventana1;
        TMenuItem *Limpiar1;
        TMenuItem *Grabar1;
        TMenuItem *Imprimir1;
        TMenuItem *Seleccionatodo1;
        TMenuItem *N2;
        TMenuItem *Cortar1;
        TTimer *Timer1;
        TMenuItem *Puntosavisualizar1;
        TColorDialog *ColorDialog;
   TBitBtn *BDetener;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall BGraficaClick(TObject *Sender);
        void __fastcall Copiar1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        void __fastcall Ultimaexpresin1Click(TObject *Sender);
        void __fastcall Eliminaexpresin1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Funcionesvalidas1Click(TObject *Sender);
        void __fastcall Limpiar1Click(TObject *Sender);
        void __fastcall CapturaKeyPress(TObject *Sender, char &Key);
        void __fastcall Seleccionatodo1Click(TObject *Sender);
        void __fastcall Cortar1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Dimenciones1Click(TObject *Sender);
        
        void __fastcall Puntosavisualizar1Click(TObject *Sender);
        
        void __fastcall ColorGraficaClick(TObject *Sender);
        void __fastcall ColorFondoClick(TObject *Sender);
   void __fastcall BDetenerClick(TObject *Sender);
private:	// User declarations

        char              exp_cap[210];
        TVVisualizacion  *vgraficacion;
        int               NUMERO_PUNTOS;
        Dimencion_Ventana Vtn;
        bool              Suspender_Calculo;
        bool              Valida_revisualizacion;

        void Grafica_funcion(const char *exp);
        
public:		// User declarations

        __fastcall TGrafica2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TGrafica2D *Grafica2D;
//---------------------------------------------------------------------------
#endif
