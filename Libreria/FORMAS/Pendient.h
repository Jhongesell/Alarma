// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef PendientH
#define PendientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Grids.hpp>
#include <Outline.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TOutlineForm : public TForm
{
__published:	// IDE-managed Components
        TTreeView *Arbol;
        TSplitter *Spliter;
        TMemo *Editor;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *MSalir;
        TMenuItem *Outline1;

        TMenuItem *Adicionaarriba1;
        TMenuItem *Adicionaabajo1;
        TMenuItem *N1;
        TMenuItem *Indenta1;
        TMenuItem *Desindenta1;
        TMenuItem *N2;
        TMenuItem *Expande1;
        TMenuItem *Expandetodo1;
        TMenuItem *N3;
        TMenuItem *Colapsa1;
        TMenuItem *Colapsatodo1;
        TMenuItem *N4;
        TMenuItem *Cambiatitulo1;
        TMenuItem *N5;
        TMenuItem *Cortaelemento1;
        TMenuItem *Copiaelemento1;
        TMenuItem *Pegaelemento1;
        TMenuItem *Borrarelemento1;
        TMenuItem *N6;
        TMenuItem *Sortea1;
        TMenuItem *Tipodeletra1;
        TMenuItem *Edicin1;
        TMenuItem *Deshacer1;
        TMenuItem *N7;
        TMenuItem *Corta1;
        TMenuItem *Copia1;
        TMenuItem *Pega1;
        TMenuItem *Seleccionatodo1;
        TMenuItem *N8;
        TMenuItem *Busca1;
        TMenuItem *Buscayremplaza1;
        TMenuItem *N9;
        TMenuItem *InsertaFecha;
        TMenuItem *InsertaHora1;
        TMenuItem *Insertafechayhora1;
        TMenuItem *N10;
        TMenuItem *Insertatextodearchivo1;
        TMenuItem *Grabatextoaarchivo1;
        TMenuItem *Imprime1;
        TMenuItem *N11;
        TMenuItem *Tipodeletra2;
        TFontDialog *FontDialog;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *Nuevo1;
        TMenuItem *Abrir1;
        TMenuItem *Grabar1;
        TMenuItem *Grabarcomo1;
        TMenuItem *N14;
        TMenuItem *Imprimir1;
        TMenuItem *Configurarimpresora1;
        TMenuItem *Longitudfija1;
        TPanel *Panel1;
        TStatusBar *BarraDeEstados;
        TSpeedButton *Corta;
        TSpeedButton *BInsertaFechaHora;
        TSpeedButton *Copia;
        TSpeedButton *Pegar;
        TSpeedButton *DeshaserB;
        TSpeedButton *BInsertaFecha;
        TSpeedButton *BInsertaHora;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer;
        TMenuItem *MenuItem1;
        TMenuItem *MenuItem2;
        TMenuItem *Pegar1;
        TMenuItem *Selecciona1;
        TMenuItem *MenuItem3;
        TMenuItem *Insertarfecha2;
        TMenuItem *Insertarhora2;
        TMenuItem *Insertarfechayhora2;
        void __fastcall MSalirClick(TObject *Sender);
        
        void __fastcall Tipodeletra1Click(TObject *Sender);
        void __fastcall Tipodeletra2Click(TObject *Sender);
        void __fastcall Sortea1Click(TObject *Sender);
        void __fastcall Deshacer1Click(TObject *Sender);
        void __fastcall Corta1Click(TObject *Sender);
        void __fastcall Copia1Click(TObject *Sender);
        void __fastcall Pega1Click(TObject *Sender);
        void __fastcall Seleccionatodo1Click(TObject *Sender);
        void __fastcall InsertaFechaClick(TObject *Sender);
        void __fastcall InsertaHora1Click(TObject *Sender);
        void __fastcall Insertafechayhora1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOutlineForm(TComponent* Owner);
};
#endif
