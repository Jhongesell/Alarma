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
class TCapturaPaswordForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TBitBtn *BitBtn1;
        void __fastcall BitBtn1Click(TObject *Sender);
        
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        
private:	// User declarations
public:		// User declarations
        bool Estado;
        __fastcall TCapturaPaswordForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TCapturaPaswordForm *CapturaPaswordForm;
//---------------------------------------------------------------------------
#endif
