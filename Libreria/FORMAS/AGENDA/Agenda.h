//---------------------------------------------------------------------------
#ifndef AgendaH
#define AgendaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TVAgendaForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TSpeedButton *IcAdicionar;
   TSpeedButton *IcEditar;
   TSpeedButton *IcVisualizar;
   TSpeedButton *IcBorrar;
   TSpeedButton *IcBuscar;
   TDBGrid *DBGrid1;
   TTable *Table1;
   TDataSource *DataSource1;
   TMainMenu *MainMenu1;
   TMenuItem *Archivo1;
   TMenuItem *Salir1;
   TMenuItem *Pendientes1;
   TMenuItem *Nuevo1;
   TMenuItem *Visualizar1;
   TMenuItem *Editar1;
   TMenuItem *Borrar1;
   TMenuItem *Filtrar1;
   TMenuItem *Prioridad1;
   TMenuItem *Sinfiltro1;
   TMenuItem *Ayuda1;
   TMenuItem *Acercade1;
   TPanel *Panel2;
   TDateTimePicker *SeleccionDia;
   TSpeedButton *BImpresion;
   TMenuItem *N1;
   TMenuItem *Imprimir1;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall Salir1Click(TObject *Sender);
   void __fastcall Nuevo1Click(TObject *Sender);
   void __fastcall Visualizar1Click(TObject *Sender);
   void __fastcall Editar1Click(TObject *Sender);
   void __fastcall Borrar1Click(TObject *Sender);
   void __fastcall Agrupador(TObject *Sender);
   void __fastcall Sinfiltro1Click(TObject *Sender);
   void __fastcall Acercade1Click(TObject *Sender);
   void __fastcall SeleccionDiaChange(TObject *Sender);
   void __fastcall DBGrid1TitleClick(TColumn *Column);
   void __fastcall BImpresionClick(TObject *Sender);
private:	// User declarations
   bool Tipo_filtro;
   char C_Agrupador [40];
   unsigned int dia;
   unsigned int mes;
   unsigned int ano;

//   void Actualiza_datos(void);
public:		// User declarations
   __fastcall TVAgendaForm(TComponent* Owner);
};
#endif

