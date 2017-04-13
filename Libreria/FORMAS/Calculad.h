// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef CalculadH
#define CalculadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TCalculadoraForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TEdit *Captura;
        TLabel *Label1;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Edicin1;
        TMenuItem *Salir1;
        TMenuItem *Ultimaexpresin1;
        TMenuItem *Eliminaexpresin1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TMenuItem *FuncionesValidas1;
        TMenuItem *Copiaabufer1;
        TMenuItem *Pegar1;
        TMenuItem *Seleccionatodo1;
        TMenuItem *N1;
        TMenuItem *Cortar1;
        void __fastcall CapturaKeyPress(TObject *Sender, char &Key);
        
        void __fastcall Ultimaexpresin1Click(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Eliminaexpresin1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall FuncionesValidas1Click(TObject *Sender);
        void __fastcall Copiaabufer1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        
        void __fastcall Seleccionatodo1Click(TObject *Sender);
        void __fastcall Cortar1Click(TObject *Sender);
private:	// User declarations
        char exp_cap[1000];
public:		// User declarations
        __fastcall TCalculadoraForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCalculadoraForm *CalculadoraForm;
//---------------------------------------------------------------------------
#endif
