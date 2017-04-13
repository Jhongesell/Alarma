// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef ArbolMemoH
#define ArbolMemoH
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


class TArbolMemoForm : public TForm
{
__published:	// IDE-managed Components
        TTreeView *Arbol;
        TSplitter *Spliter;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *MSalir;
        TMenuItem *Outline1;

        TMenuItem *AdicionaArriba;
        TMenuItem *AdicionaHijo;
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
        TMenuItem *Edicin1;
        TMenuItem *Deshacer1;
        TMenuItem *N7;
        TMenuItem *Corta1;
        TMenuItem *Copia1;
        TMenuItem *Pegar1;
        TMenuItem *Selecciona1;
        TMenuItem *N8;
        TMenuItem *Busca1;
        TMenuItem *Buscayremplaza1;
        TMenuItem *N9;
        TMenuItem *InsertaFecha;
        TMenuItem *InsertaHora1;
        TMenuItem *Insertafechayhora1;
        TMenuItem *N10;
        TMenuItem *LeeBloque;
        TMenuItem *GrabaBloque;
        TMenuItem *ImplimeBloque;
        TMenuItem *N11;
        TFontDialog *FontDialog;
   TMenuItem *Separador;
        TMenuItem *Nuevo1;
        TMenuItem *Abrir1;
        TMenuItem *Grabar1;
        TMenuItem *Grabarcomo1;
        TMenuItem *N14;
        TMenuItem *Imprimir1;
        TMenuItem *Configurarimpresora1;
        TPanel *Panel1;
        TStatusBar *BarraDeEstados;
        TSpeedButton *Corta;
        TSpeedButton *BInsertaFechaHora;
        TSpeedButton *Copia;
        TSpeedButton *Pegar;
        TSpeedButton *Deshacer;
        TSpeedButton *BInsertaFecha;
        TSpeedButton *BInsertaHora;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer2;
        TMenuItem *Cortar2;
        TMenuItem *Copia2;
        TMenuItem *Pegar2;
        TMenuItem *Selecciona2;
        TMenuItem *MenuItem3;
        TMenuItem *Insertarfecha2;
        TMenuItem *Insertarhora2;
        TMenuItem *Insertarfechayhora2;
        TPrintDialog *PrintDialog;
        TMenuItem *AdicionaAbajo;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TSpeedButton *BAbrir;
        TSpeedButton *BGrabar;
        TSpeedButton *BImprimir;
        TSpeedButton *BInsertaArriba;
        TSpeedButton *BAdicionaAbajo;
        TSpeedButton *BAdicionaHijo;
        TSpeedButton *BEditaTitulo;
        TSpeedButton *BExpandeTodo;
        TSpeedButton *BColapsaTodo;
        TTimer *Timer1;
        TSpeedButton *BBorraNodo;
        TPopupMenu *PopupMenu2;
        TMenuItem *Adicionaarriba1;
        TMenuItem *Adicionaabajo1;
        TMenuItem *Adicionahijo1;
        TMenuItem *N15;
        TMenuItem *Indenta2;
        TMenuItem *Desindenta2;
        TMenuItem *N16;
        TMenuItem *Expande2;
        TMenuItem *Expandetodo2;
        TMenuItem *N17;
        TMenuItem *Colapsa2;
        TMenuItem *Colapsatodo2;
        TMenuItem *N18;
        TMenuItem *Cambiatitulo2;
        TMenuItem *N19;
        TMenuItem *Cortanodo1;
        TMenuItem *Copianodo1;
        TMenuItem *Peganodo1;
        TMenuItem *Borranodo1;
        TRichEdit *Editor;
        TSpeedButton *Buscar;
        TFindDialog *FindDialog;
        TOpenDialog *OpenDialog1;
        TReplaceDialog *ReplaceDialog;
        TMenuItem *N20;
        TMenuItem *Convertiramayusculas1;
        TMenuItem *Convertiraminusculas1;
        TTimer *Timer2;
   TMenuItem *Configurar1;
   TMenuItem *Arbol1;
   TMenuItem *Editor1;
   TMenuItem *Longitudfija1;
   TColorDialog *ColorDialog;
   TMenuItem *Colordelaventanadelrbol1;
   TMenuItem *Colordelaventandeleditor1;
   TMenuItem *N12;
   TMenuItem *N21;
   TMenuItem *Arch1;
   TMenuItem *Arch2;
   TMenuItem *Arch3;
   TMenuItem *Arch4;
   TMenuItem *Copiartodo1;
   TMenuItem *Copiartodo2;
        TMenuItem *N13;
        TMenuItem *Clavedeseguridad1;
        void __fastcall MSalirClick(TObject *Sender);
        
        void __fastcall Tipodeletra1Click(TObject *Sender);
        void __fastcall Tipodeletra2Click(TObject *Sender);
        void __fastcall Sortea1Click(TObject *Sender);
        void __fastcall Deshacer1Click(TObject *Sender);
        void __fastcall Corta1Click(TObject *Sender);
        void __fastcall Copia1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        void __fastcall Selecciona1Click(TObject *Sender);
        void __fastcall InsertaFechaClick(TObject *Sender);
        void __fastcall InsertaHora1Click(TObject *Sender);
        void __fastcall Insertafechayhora1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Configurarimpresora1Click(TObject *Sender);
        void __fastcall Grabar1Click(TObject *Sender);
        void __fastcall AdicionaArribaClick(TObject *Sender);
        void __fastcall Borrarelemento1Click(TObject *Sender);
        void __fastcall Cambiatitulo1Click(TObject *Sender);
        void __fastcall AdicionaHijoClick(TObject *Sender);
        void __fastcall Colapsatodo1Click(TObject *Sender);
        void __fastcall Expandetodo1Click(TObject *Sender);
        void __fastcall Colapsa1Click(TObject *Sender);
        void __fastcall Expande1Click(TObject *Sender);
        void __fastcall AdicionaAbajoClick(TObject *Sender);
        void __fastcall Abrir1Click(TObject *Sender);
        void __fastcall Indenta1Click(TObject *Sender);
        void __fastcall Desindenta1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Longitudfija1Click(TObject *Sender);
        void __fastcall LeeBloqueClick(TObject *Sender);
        
        
        

        void __fastcall ArbolClick(TObject *Sender);

        void __fastcall ArbolKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Cortaelemento1Click(TObject *Sender);
        void __fastcall Pegaelemento1Click(TObject *Sender);
        void __fastcall Copiaelemento1Click(TObject *Sender);
        void __fastcall AutoGraba(TObject *Sender);
        
        void __fastcall FindDialogFind(TObject *Sender);
        void __fastcall BuscarClick(TObject *Sender);
        
        void __fastcall Buscayremplaza1Click(TObject *Sender);
        void __fastcall ReplaceDialogReplace(TObject *Sender);
        void __fastcall Imprimir1Click(TObject *Sender);
        
        
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall Grabarcomo1Click(TObject *Sender);
        void __fastcall Nuevo1Click(TObject *Sender);
        
        
        
        
        
        
        void __fastcall Convertiramayusculas1Click(TObject *Sender);
        void __fastcall Convertiraminusculas1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
   void __fastcall Colordelaventanadelrbol1Click(TObject *Sender);
   void __fastcall Colordelaventandeleditor1Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall Arch1Click(TObject *Sender);
   void __fastcall Arch2Click(TObject *Sender);
   void __fastcall Arch3Click(TObject *Sender);
   void __fastcall Arch4Click(TObject *Sender);
   void __fastcall Copiartodo1Click(TObject *Sender);
        void __fastcall Clavedeseguridad1Click(TObject *Sender);
        
private:	// User declarations

        bool       Modificado;
        bool       Pegar_activo;
        bool       Genera_nuevo_nodo;
        char       Titulo[110];
        char       Encriptado[2];
        char       Password[32];
        char       NombresArchivos[4][MAXPATH];
        TStrings  *Datos;
        TTreeNode *Actual;
        int        PtrArbolEdicion;


              //Actualiza lista de archivos
        void  Actualiza_lista(void);
               // Actualiza el contenido del editor
        void  Actualiza(void);
              // Graba el contenido del arbol de edición
        void  GrabaArbolMemo(void);
              // Lee un archivo al arbol de edición
        void  LeerArbolMemo(const char *arch);
              // destruye el contenido de los nodos
        void  Destruye(void);
              // Graba o lee la configuracion de la ventana
        bool  Configuracion_ventana(const char *arch, const bool st);
              // Borra el nodo indicado y todos los subnodos
        void  TArbolMemoForm::BorraNodo(TTreeNode* TreeNode);

        void  __fastcall OnHint(TObject *Sender);
        void  __fastcall OnIdle(TObject *Sender, bool &Done);

public:		// User declarations

        void  Abrir(const char *arch, const int ptr);
              // Abre el archivo indicado
        void  Abrir_archivo_lista(const char *arch);
                   // Constructor
        __fastcall TArbolMemoForm(TComponent* Owner);
};
#endif
