//---------------------------------------------------------------------------
#ifndef CagendaH
#define CagendaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TCapturaAgenda : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *Aceptar;
   TPageControl *PageControl1;
   TTabSheet *Agenda;
   TTabSheet *Notas;
   TDateTimePicker *Edit1;
   TDateTimePicker *Edit2;
   TEdit *Edit3;
   TEdit *Edit4;
   TMemo *Memo1;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TPopupMenu *PopupMenu1;
   TMenuItem *Deshacer1;
   TMenuItem *Cortar1;
   TMenuItem *N1;
   TMenuItem *Copiar1;
   TMenuItem *Pegar1;
   TMenuItem *SeleccionarTodo1;
   void __fastcall FormActivate(TObject *Sender);
   void __fastcall AceptarClick(TObject *Sender);
   void __fastcall EditKeyPress(TObject *Sender, char &Key);
   void __fastcall Deshacer1Click(TObject *Sender);
   void __fastcall Cortar1Click(TObject *Sender);
   void __fastcall Copiar1Click(TObject *Sender);
   void __fastcall Pegar1Click(TObject *Sender);
   void __fastcall SeleccionarTodo1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    bool Estado;
   __fastcall TCapturaAgenda(TComponent* Owner);
};
#endif

