// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef VdirectH
#define VdirectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TVDirectorioForm : public TForm
{
__published:	// IDE-managed Components
        TTable *Table1;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Ayuda1;
        TMenuItem *Acercade1;
        TMenuItem *Directorio1;
        TMenuItem *Adicionar1;
        TMenuItem *Editar1;
        TMenuItem *Borrar1;
        TMenuItem *Visualizar1;
        TMenuItem *Buscar1;
        TMenuItem *Nombre1;
        TMenuItem *apellido1;
        TMenuItem *Categoria1;
        TMenuItem *Compaia1;
        TMenuItem *Filtro1;
        TMenuItem *Categoria2;
        TMenuItem *Compaia2;
        TMenuItem *Sinfiltro1;
        TPanel *Panel1;
        TSpeedButton *IcAdicionar;
        TSpeedButton *IcEditar;
        TSpeedButton *IcVisualizar;
        TSpeedButton *IcBorrar;
        TSpeedButton *IcBuscar;
   TSpeedButton *BReporte;
   TMenuItem *Reportes1;
   TMenuItem *Corto1;
   TMenuItem *Largo1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BAdicionarClick(TObject *Sender);
        void __fastcall BEditarClick(TObject *Sender);
        void __fastcall BBorrarClick(TObject *Sender);
        
        void __fastcall FormDestroy(TObject *Sender);
        
        void __fastcall BVisualizarClick(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall DBGrid1TitleClick(TColumn *Column);
        
        
        void __fastcall Nombre1Click(TObject *Sender);
        void __fastcall apellido1Click(TObject *Sender);
        void __fastcall Categoria1Click(TObject *Sender);
        void __fastcall Compaia1Click(TObject *Sender);
        
        void __fastcall Categoria2Click(TObject *Sender);
        void __fastcall Compaia2Click(TObject *Sender);
        void __fastcall Sinfiltro1Click(TObject *Sender);
   void __fastcall BReporteClick(TObject *Sender);
private:	// User declarations
        void Buscar(const int tp);
public:		// User declarations
        __fastcall TVDirectorioForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TVDirectorioForm *VDirectorioForm;
//---------------------------------------------------------------------------
#endif
