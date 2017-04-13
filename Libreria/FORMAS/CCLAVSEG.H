//---------------------------------------------------------------------------
#ifndef CPaswordH
#define CPaswordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCapturaClaveSeguridadForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TEdit *Edit1;
        TLabel *Label1;
        TBitBtn *BitBtn1;
        void __fastcall BitBtn1Click(TObject *Sender);
        
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        
private:	// User declarations
public:		// User declarations
        bool Estado;
        __fastcall TCapturaClaveSeguridadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCapturaPaswordForm *CapturaPaswordForm;
//---------------------------------------------------------------------------
#endif
