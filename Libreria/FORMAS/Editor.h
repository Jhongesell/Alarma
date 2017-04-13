// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A




#ifndef EditorH
#define EditorH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <vcl\Clipbrd.hpp>
#include "d:\libreria\Fechora.hpp"

//---------------------------------------------------------------------------
class TEditorForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MenuPrincipal;
        TMenuItem *Archivo;
        TMenuItem *Exit1;
   TMenuItem *Separador;
        TMenuItem *ConfiguraImpresora;
        TMenuItem *Imprime;
        TMenuItem *N2;
        TMenuItem *Grabacomo;
        TMenuItem *Graba;
        TMenuItem *Open1;
        TMenuItem *New1;
        TMenuItem *Edicion;
        TMenuItem *Remplazar;
        TMenuItem *Buscar;
        TMenuItem *N5;
        TMenuItem *Paste1;
        TMenuItem *Copy1;
        TMenuItem *Cut1;
        TMenuItem *N6;
        TMenuItem *Deshacer1;
        TMenuItem *Ayuda;
        TMenuItem *About1;
        TPanel *BarraDeHerramientas;
        TSpeedButton *Abrir;
        TSpeedButton *Grabar;
        TSaveDialog *SaveDialog;
        TOpenDialog *OpenDialog;
        TPrintDialog *PrintDialog;
        TMenuItem *Selecciona;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer;
        TMenuItem *Corta1;
        TMenuItem *Copia1;
        TMenuItem *Pegar1;
        TMenuItem *Selecciona1;
        TSpeedButton *Corta;
        TSpeedButton *Copia;
        TSpeedButton *Pegar;
        TSpeedButton *DeshaserB;
        TSpeedButton *SpeedButton1;
        TStatusBar *BarraDeEstados;
        TMenuItem *Otros1;
        TMenuItem *N7;
        TMenuItem *ConvertirMayusculas1;
        TMenuItem *Convertiraminusculas1;
        TMenuItem *Configurar1;
        TMenuItem *Tipodeletra1;
        TFontDialog *FontDialog;
        TMenuItem *Longituddeedicionfija1;
        TMenuItem *Leerbloque;
        TMenuItem *Grabarbloque;
        TMenuItem *Imprimirbloque;
        TMenuItem *N4;
        TMenuItem *Insertarfecha1;
        TMenuItem *Insertarhora1;
        TMenuItem *Insertarfechayhora1;
        TMenuItem *N3;
        TMenuItem *Insertarfecha2;
        TMenuItem *Insertarhora2;
        TMenuItem *Insertarfechayhora2;
        TSpeedButton *BInsertaFecha;
        TSpeedButton *BInsertaHora;
        TSpeedButton *BInsertaFechaHora;
        TMenuItem *N8;
        TRichEdit *Editor;
        TFindDialog *FindDialog;
        TSpeedButton *SpeedButton2;
        TOpenDialog *OpenDialog1;
        TReplaceDialog *ReplaceDialog;
   TColorDialog *ColorDialog;
   TMenuItem *Colordelaventana1;
   TMenuItem *N9;
   TMenuItem *Arch1;
   TMenuItem *Arch2;
   TMenuItem *Arch3;
   TMenuItem *Arch4;
        TMenuItem *Copiartodo1;
        TMenuItem *Copiartodo2;
        void __fastcall NuevoArchivo(TObject *Sender);
        
        void __fastcall GrabaArchivo(TObject *Sender);
        void __fastcall AbrirArchivo(TObject *Sender);
        void __fastcall GrabaComoArchivo(TObject *Sender);
        
        void __fastcall DeshaseCambios(TObject *Sender);
        void __fastcall SeleccionaTexto(TObject *Sender);
        void __fastcall CortaTexto(TObject *Sender);
        void __fastcall CopiaTexto(TObject *Sender);
        void __fastcall PegarTexto(TObject *Sender);
        void __fastcall SalirEditor(TObject *Sender);
        
        void __fastcall LongitudFija(TObject *Sender);
        void __fastcall AcercaDe(TObject *Sender);
        void __fastcall ImprimeClick(TObject *Sender);
        
        void __fastcall ConfiguraPRN(TObject *Sender);
        void __fastcall Insertafecha1Click(TObject *Sender);
        void __fastcall Insertahora1Click(TObject *Sender);
        void __fastcall Insertafechayhora1Click(TObject *Sender);
        void __fastcall ConvertirMayusculas1Click(TObject *Sender);
        void __fastcall Convertiraminusculas1Click(TObject *Sender);
        void __fastcall Tipodeletra1Click(TObject *Sender);
        void __fastcall LeerbloqueClick(TObject *Sender);
        
        void __fastcall FindDialogFind(TObject *Sender);
        void __fastcall BuscarClick(TObject *Sender);
        void __fastcall ReplaceDialogReplace(TObject *Sender);
        void __fastcall RemplazarClick(TObject *Sender);
        
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall Colordelaventana1Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall Arch1Click(TObject *Sender);
   void __fastcall Arch2Click(TObject *Sender);
   void __fastcall Arch3Click(TObject *Sender);
   void __fastcall Arch4Click(TObject *Sender);
        void __fastcall Copiartodo1Click(TObject *Sender);
private:	// User declarations
        char        *ARCHIVO;
        char         TITULO[200];
        bool         st_solo_lectura;
        int          PtrEditor;

              // El editor estara en modo de solo lectura
        void  Editor_solo_lectura(bool st);
              // Muestra el titulo de la aplicación
        void  Titulo(void);
              //Actualiza lista de archivos
        void  Actualiza_lista(void);


        void  __fastcall OnHint(TObject *Sender);
        void  __fastcall OnIdle(TObject *Sender, bool &Done);
        
public:		// User declarations

              // Abre el archivo por omision
        void  Abrir_archivo(char *arch, bool st_edicion, const int ptr);
              // Abre el archivo indicado
        void  Abrir_archivo_lista(const char *arch);
        
        __fastcall TEditorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TEditorForm *EditorForm;
//---------------------------------------------------------------------------
#endif
