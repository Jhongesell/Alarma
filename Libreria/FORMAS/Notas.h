//---------------------------------------------------------------------------
#ifndef NotasH
#define NotasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

class TNotasForm : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TPopupMenu *PopupMenu1;
        TMenuItem *Deshacer1;
        TMenuItem *Cortar1;
        TMenuItem *Copiar1;
        TMenuItem *Pegar1;
        TMenuItem *Seleccionar1;
        TMenuItem *N3;
        TMenuItem *Insertafecha1;
        TMenuItem *Insertahora1;
        TMenuItem *Insertafechayhora1;
        TFontDialog *FontDialog;
        TColorDialog *ColorDialog;
        TTimer *Timer;
        TPrintDialog *PrintDialog;
        TFindDialog *FindDialog;
        TRichEdit *Editor;
        TMainMenu *MainMenu;
   TMenuItem *Archivo1;
        TMenuItem *Nuevo2;
        TMenuItem *Abrir2;
        TMenuItem *Grabar1;
        TMenuItem *Grabarcomo1;
        TMenuItem *N8;
        TMenuItem *Imprimir2;
        TMenuItem *Configurarimpresora1;
        TMenuItem *N9;
        TMenuItem *Salir1;
        TMenuItem *Edicin1;
        TMenuItem *Deshacer2;
        TMenuItem *N10;
        TMenuItem *Cortar2;
        TMenuItem *Copiar2;
        TMenuItem *Pegar2;
        TMenuItem *Seleccionar2;
        TMenuItem *N11;
        TMenuItem *Buscar2;
        TMenuItem *Buscaryremplazar1;
        TMenuItem *N12;
        TMenuItem *InsertarFecha1;
        TMenuItem *Insertarhora1;
        TMenuItem *Insertarfechayhora1;
        TMenuItem *N14;
        TMenuItem *Leerbloque2;
        TMenuItem *Grabarbloque2;
        TMenuItem *Imprimirbloque2;
        TMenuItem *Configurar1;
        TMenuItem *Tipodeletra1;
        TMenuItem *Longituddeedicinfija1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade2;
        TMenuItem *N1;
        TMenuItem *Color1;
        TReplaceDialog *ReplaceDialog;
        TOpenDialog *OpenDialog1;
        TMenuItem *Efectos1;
        TMenuItem *Negrita1;
        TMenuItem *Italica1;
        TMenuItem *Subrayado1;
        TMenuItem *N2;
        TMenuItem *Tipodeletra2;
        TMenuItem *AlineadoIzquierda1;
        TMenuItem *Alineadoderecha1;
        TMenuItem *Alineadocentrada1;
        TMenuItem *N6;
        TMenuItem *Vietas1;
        TMenuItem *Tachado1;
        TMenuItem *Ventanasiemprevisible1;
        TMenuItem *N4;
        TMenuItem *Convierteamaysculas1;
        TMenuItem *Convierteaminusculas1;
        TMenuItem *N5;
   TMenuItem *Separador;
   TMenuItem *Arch1;
   TMenuItem *Arch2;
   TMenuItem *Arch3;
   TMenuItem *Arch4;
        TMenuItem *Copiartodo1;
        TMenuItem *Copiartodo2;
        TMenuItem *N7;
        TMenuItem *Clavedeseguridad1;
        
        void __fastcall Grabar1Click(TObject *Sender);
        void __fastcall Nuevo1Click(TObject *Sender);
        void __fastcall Deshacer1Click(TObject *Sender);
        void __fastcall Cortar1Click(TObject *Sender);
        void __fastcall Copiar1Click(TObject *Sender);
        void __fastcall Pegar1Click(TObject *Sender);
        void __fastcall Seleccionar1Click(TObject *Sender);
        void __fastcall Insertafecha1Click(TObject *Sender);
        void __fastcall Insertahora1Click(TObject *Sender);
        void __fastcall Insertafechayhora1Click(TObject *Sender);
        void __fastcall Configuracolor1Click(TObject *Sender);
        void __fastcall Configuratipodeletra1Click(TObject *Sender);
        void __fastcall Abrir1Click(TObject *Sender);
        
        void __fastcall Leerbloque1Click(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Imprimir1Click(TObject *Sender);
        void __fastcall Buscar1Click(TObject *Sender);
        
        
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FindDialogFind(TObject *Sender);
        
        void __fastcall Salir1Click(TObject *Sender);
        
        void __fastcall Grabarcomo1Click(TObject *Sender);
        void __fastcall Configurarimpresora1Click(TObject *Sender);
        void __fastcall ReplaceDialogFind(TObject *Sender);
        void __fastcall Buscaryremplazar1Click(TObject *Sender);
        void __fastcall Vietas1Click(TObject *Sender);
        void __fastcall Negrita1Click(TObject *Sender);
        void __fastcall Italica1Click(TObject *Sender);
        void __fastcall Subrayado1Click(TObject *Sender);
        void __fastcall Tipodeletra2Click(TObject *Sender);
        void __fastcall AlineadoIzquierda1Click(TObject *Sender);
        void __fastcall Alineadoderecha1Click(TObject *Sender);
        void __fastcall Alineadocentrada1Click(TObject *Sender);
        void __fastcall Tachado1Click(TObject *Sender);
        void __fastcall Longituddeedicinfija1Click(TObject *Sender);
        void __fastcall Ventanasiemprevisible1Click(TObject *Sender);
        
        
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        
        void __fastcall Convierteamaysculas1Click(TObject *Sender);
        void __fastcall Convierteaminusculas1Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall Arch1Click(TObject *Sender);
   void __fastcall Arch2Click(TObject *Sender);
   void __fastcall Arch3Click(TObject *Sender);
   void __fastcall Arch4Click(TObject *Sender);
        void __fastcall Copiartodo1Click(TObject *Sender);
        void __fastcall Clavedeseguridad1Click(TObject *Sender);
private:	// User declarations

        char       Encriptado[2];
        char       Password[32];
        char       NombresArchivos[4][MAXPATH];
        int        PtrNotas;

             // Graba o recupera la configuracion del sistema
        bool Configuracion_ventana(const char *arch, const bool st);
             // OnIdle
        void __fastcall OnIdle(TObject *Sender, bool &Done);
             //Actualiza lista de archivos
        void Actualiza_lista(void);

public:		// User declarations
        void Abre_Notas(const int ptr)
             {
                PtrNotas = ptr;
                Show();
             }
              // Abre el archivo indicado
        void  Abrir_archivo_lista(const char *arch);

        __fastcall TNotasForm(TComponent* Owner);
};
#endif
