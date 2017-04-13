//---------------------------------------------------------------------------
#ifndef Cfg_repH
#define Cfg_repH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "D:\libreria\gen_rep.hpp"
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class TConfiguraReporteForm :  public TForm
{
__published:	// IDE-managed Components
   TRadioGroup *RadioGroup1;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   TRadioButton *RadioButton3;
   TBitBtn *BitBtn1;
   TSaveDialog *SaveDialog;
   void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:	// User declarations
//   Ctrl_reporte *cr;
   unsigned int Tipo_reporte;
   char       Archivo[MAXPATH];
   void       Configura_reporte(unsigned int &trep, char *arch);
   void       Visualiza_Imprime(void);
   __fastcall TConfiguraReporteForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TConfiguraReporteForm *ConfiguraReporteForm;
//---------------------------------------------------------------------------
#endif

