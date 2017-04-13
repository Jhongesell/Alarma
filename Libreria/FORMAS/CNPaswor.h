//---------------------------------------------------------------------------
#ifndef CNPasworH
#define CNPasworH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNuevoUsuarioForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        void __fastcall BitBtn1Click(TObject *Sender);
        
        
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        
        
private:	// User declarations
public:		// User declarations
        bool Estado;
        __fastcall TNuevoUsuarioForm(TComponent* Owner);
};
#endif
