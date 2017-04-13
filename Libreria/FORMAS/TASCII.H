// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef TASCIIH
#define TASCIIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTablaASCIIForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Editor;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Configurar1;
        TMenuItem *Tipodeletra1;
        TFontDialog *FontDialog;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Tipodeletra1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
private:	// User declarations
        void Visualiza_titulo(void);
public:		// User declarations
        __fastcall TTablaASCIIForm(TComponent* Owner);
};
#endif
