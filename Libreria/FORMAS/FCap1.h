//---------------------------------------------------------------------------
#ifndef FCap1H
#define FCap1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TCaptura1Form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TEdit *Edit1;
        TLabel *Label1;
        TStatusBar *StatusBar;
        void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        bool st;
        __fastcall TCaptura1Form(TComponent* Owner);

        void Abrir(const char *tit, const char *eti, const char *txt, const char *hlp);
};
#endif
