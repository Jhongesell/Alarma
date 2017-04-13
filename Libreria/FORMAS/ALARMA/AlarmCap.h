// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef AlarmCapH
#define AlarmCapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCapturaAlarma : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TComboBox *Tipo;
        TEdit *Mensaje;
        TBitBtn *BitBtn1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *Dia;
        TDateTimePicker *Fecha;
        TDateTimePicker *Hora;
        TEdit *CadaCuanto;
        TLabel *Label6;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall HoraKeyPress(TObject *Sender, char &Key);
        void __fastcall TipoChange(TObject *Sender);
        
        
private:	// User declarations
public:		// User declarations
        bool Captura;
        __fastcall TCapturaAlarma(TComponent* Owner);
};
#endif
