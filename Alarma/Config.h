//---------------------------------------------------------------------------
#ifndef ConfigH
#define ConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TConfigurarForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *btAceptar;
        TFontDialog *FontDialog;
        TColorDialog *ColorDialog;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TButton *btTipoLetra;
        TButton *btColorFondo;
        TButton *btColorTexto;
        TPanel *Panel1;
        TLabel *Label1;
        void __fastcall btAceptarClick(TObject *Sender);
        void __fastcall btTipoLetraClick(TObject *Sender);
        void __fastcall btColorTextoClick(TObject *Sender);
        void __fastcall btColorFondoClick(TObject *Sender);
        
        
        
private:	// User declarations
public:		// User declarations
        bool st;
        void       Abrir(const TColor txt, const TColor fdo, TFont *fnt);
        
        __fastcall TConfigurarForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigurarForm *ConfigurarForm;
//---------------------------------------------------------------------------
#endif
