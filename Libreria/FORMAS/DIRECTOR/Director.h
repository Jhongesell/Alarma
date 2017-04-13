// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef DirectorH
#define DirectorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TCapturadireccion : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TLabel *TNotas;
        TLabel *TNombre;
        TLabel *TApellidos;
        TLabel *TTitulo;
        TLabel *TCompania;
        TLabel *TTrabajo;
        TLabel *TCasa;
        TLabel *TFax;
        TLabel *TOtro;
        TLabel *TEmail;
        TLabel *TCategoria;
        TLabel *TDireccion;
        TLabel *TCiudad;
        TLabel *TEstado;
        TLabel *TCP;
        TLabel *TPais;
        TBitBtn *Aceptar;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TMemo *Memo1;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit14;
        TEdit *Edit15;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer;
        TMenuItem *Corta1;
        TMenuItem *Copia1;
        TMenuItem *Pegar1;
        TMenuItem *Selecciona1;
        TMenuItem *N1;
        void __fastcall AceptarClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall DeshacerClick(TObject *Sender);
        void __fastcall Corta1Click(TObject *Sender);
        void __fastcall Copia1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        void __fastcall Selecciona1Click(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    bool Estado;

        __fastcall TCapturadireccion(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCapturadireccion *Capturadireccion;
//---------------------------------------------------------------------------
#endif
