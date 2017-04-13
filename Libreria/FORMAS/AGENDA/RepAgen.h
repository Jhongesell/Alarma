//----------------------------------------------------------------------------
#ifndef RepAgenH
#define RepAgenH
//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>

//----------------------------------------------------------------------------
class TReporteAgenda : public TQuickRep
{
__published:
   TTable *Table1;
   TQRBand *QRBand1;
   TQRLabel *QRLabel1;
   TQRBand *QRBand2;
   TQRLabel *QRLabel2;
   TQRLabel *QRLabel3;
   TQRLabel *QRLabel4;
   TQRLabel *QRLabel5;
   TQRBand *QRBand3;
   TQRDBText *QRDBText1;
   TQRDBText *QRDBText2;
   TQRDBText *QRDBText3;
   TQRDBText *QRDBText4;
private:
public:
   __fastcall TReporteAgenda::TReporteAgenda(TComponent* Owner);
};
//----------------------------------------------------------------------------
//extern TReporteAgenda *ReporteAgenda;
//----------------------------------------------------------------------------
#endif
