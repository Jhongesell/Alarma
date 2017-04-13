// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef LMensajeH
#define LMensajeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLMensajeForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TBitBtn *BitBtn1;
    TMemo *Editor;
private:	// User declarations
public:		// User declarations
    __fastcall TLMensajeForm(TComponent* Owner);
};
#endif
