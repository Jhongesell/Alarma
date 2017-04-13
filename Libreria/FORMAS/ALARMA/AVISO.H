// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef avisoH
#define avisoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAvisoAlarma : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Hora;
        TBitBtn *BitBtn1;
        TLabel *Mensaje;
        TStaticText *StaticText1;
private:	// User declarations
public:		// User declarations
    __fastcall TAvisoAlarma(TComponent* Owner);
};
#endif
