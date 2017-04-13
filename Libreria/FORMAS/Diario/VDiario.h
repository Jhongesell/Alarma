//---------------------------------------------------------------------------
#ifndef VDiarioH
#define VDiarioH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDiarioForm : public TForm
{
__published:	// IDE-managed Components
   TDateTimePicker *SeleccionDia;
   TRichEdit *Editor;
   TMainMenu *MainMenu1;
   TMenuItem *Archiivo1;
   TMenuItem *Salir1;
   TMenuItem *Ayuda1;
   TMenuItem *acercade1;
   TPanel *Panel1;
   TSpeedButton *IcEditar;
   TTable *Table1;
   TMenuItem *Edicin1;
   TMenuItem *Ediardiario1;
   TPopupMenu *PopupMenu1;
   TMenuItem *Deshacer;
   TMenuItem *N8;
   TMenuItem *Corta1;
   TMenuItem *Copia1;
   TMenuItem *Pegar1;
   TMenuItem *Selecciona1;
   TMenuItem *N3;
   TMenuItem *Insertarfecha2;
   TMenuItem *Insertarhora2;
   TMenuItem *Insertarfechayhora2;
   TMenuItem *N1;
   TMenuItem *Editardiario1;
   void __fastcall SeleccionDiaChange(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall Salir1Click(TObject *Sender);
   void __fastcall acercade1Click(TObject *Sender);
   void __fastcall IcEditarClick(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall DeshacerClick(TObject *Sender);
   void __fastcall Selecciona1Click(TObject *Sender);
   void __fastcall Corta1Click(TObject *Sender);
   void __fastcall Copia1Click(TObject *Sender);
   void __fastcall Pegar1Click(TObject *Sender);
   void __fastcall Insertarfecha2Click(TObject *Sender);
   void __fastcall Insertarhora2Click(TObject *Sender);
   void __fastcall Insertarfechayhora2Click(TObject *Sender);
private:	// User declarations
   TDateTime FechaTrabajo;
public:		// User declarations
   __fastcall TDiarioForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TDiarioForm *DiarioForm;
//---------------------------------------------------------------------------
#endif

