// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef CpendienH
#define CpendienH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TCPendiente : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BAceptar;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TMemo *Memo1;
        TDateTimePicker *Edit1;
        TEdit *Edit2;
        TComboBox *Edit4;
        TEdit *Edit3;
        TLabel *TFecha;
        TLabel *TCategoria;
        TLabel *TPrioridad;
        TLabel *TPendiente;
        TLabel *TNotas;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer;
        TMenuItem *Corta1;
        TMenuItem *Copia1;
        TMenuItem *Pegar1;
        TMenuItem *Selecciona1;
        TMenuItem *N1;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BAceptarClick(TObject *Sender);
        void __fastcall DeshacerClick(TObject *Sender);
        void __fastcall Corta1Click(TObject *Sender);
        void __fastcall Copia1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        void __fastcall Selecciona1Click(TObject *Sender);
        
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        
private:	// User declarations
public:		// User declarations
    bool Estado;
        __fastcall TCPendiente(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCPendiente *CPendiente;
//---------------------------------------------------------------------------
#endif
