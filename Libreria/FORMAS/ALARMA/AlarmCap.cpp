// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CALA-691229-TV5
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

#include <vcl.h>
#include "d:\libreria\formas\Alarma\AlarmCap.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TCapturaAlarma::TCapturaAlarma(TComponent* Owner)
        : TForm(Owner)
{
   Captura = false;
}


void __fastcall TCapturaAlarma::BitBtn1Click(TObject *Sender)
{
   Captura = true;
   Close();
}

void __fastcall TCapturaAlarma::HoraKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
   }
}


void __fastcall TCapturaAlarma::TipoChange(TObject *Sender)
{
   if (Tipo->ItemIndex == 5) {
      Label6->Visible = true;
      CadaCuanto->Visible = true;
    } else {
      Label6->Visible = false;
      CadaCuanto->Visible = false;
   }     
}
//---------------------------------------------------------------------------

