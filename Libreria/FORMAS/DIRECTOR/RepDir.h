//----------------------------------------------------------------------------
#ifndef RepDirH
#define RepDirH
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
class TReporteDirectorio : public TQuickRep
{
__published:
   TTable *Table1;
   TQRBand *QRBand1;
   TQRLabel *QRLabel1;
   TQRBand *QRBand2;
   TQRLabel *QRLabel2;
   TQRLabel *QRLabel3;
   TQRLabel *QRLabel4;
   TQRBand *QRBand3;
   TQRDBText *QRDBText1;
   TQRDBText *QRDBText2;
   TQRDBText *QRDBText3;
   TQRDBText *QRDBText4;
   TQRLabel *QRLabel5;
   TQRDBText *QRDBText5;
private:
public:
   __fastcall TReporteDirectorio::TReporteDirectorio(TComponent* Owner);
};
//----------------------------------------------------------------------------
//extern TReporteDirectorio *ReporteDirectorio;
//----------------------------------------------------------------------------
#endif
