// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef VpendienH
#define VpendienH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPendienteForm : public TForm
{
__published:	// IDE-managed Components
        TTable *Table1;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Pendientes1;
        TMenuItem *Nuevo1;
        TMenuItem *Visualizar1;
        TMenuItem *Editar1;
        TMenuItem *Borrar1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TMenuItem *Filtrar1;
        TMenuItem *Prioridad1;
        TMenuItem *Categoria1;
        TMenuItem *Sinfiltro1;
        TPanel *Panel1;
        TSpeedButton *IcAdicionar;
        TSpeedButton *IcEditar;
        TSpeedButton *IcVisualizar;
        TSpeedButton *IcBorrar;
        TSpeedButton *IcBuscar;
   TSpeedButton *BImpresion;
   TMenuItem *N1;
   TMenuItem *Imprimir1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BBorrarClick(TObject *Sender);
        void __fastcall BAdicionarClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall BVisualizarClick(TObject *Sender);
        void __fastcall BEditarClick(TObject *Sender);
        void __fastcall DBGrid1TitleClick(TColumn *Column);
        
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Prioridad1Click(TObject *Sender);
        void __fastcall Categoria1Click(TObject *Sender);
        void __fastcall Sinfiltro1Click(TObject *Sender);
   void __fastcall BImpresionClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPendienteForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TPendienteForm *PendienteForm;
//---------------------------------------------------------------------------
#endif
