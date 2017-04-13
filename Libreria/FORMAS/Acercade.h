// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#ifndef AcercaDeH
#define AcercaDeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <NMNNTP.hpp>
#include <Psock.hpp>
#include <NMsmtp.hpp>

//---------------------------------------------------------------------------
class TAcercaDeForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Caratula;
        TBitBtn *BitBtn1;
        TLabel *NombreAplicacion;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label1;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void Muestra_ventana_AcercaDe(char *aplic);
        __fastcall TAcercaDeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TAcercaDeForm *AcercaDeForm;
//---------------------------------------------------------------------------
#endif
