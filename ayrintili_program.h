//---------------------------------------------------------------------------

#ifndef ayrintili_programH
#define ayrintili_programH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
#include <QRExport.hpp>
//---------------------------------------------------------------------------
class Tdevam_devamsizlik_f : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *ayrintili_program;
        TIBQuery *IBQuery1;
        TIBQuery *IBQuery2;
        TQRBand *QRBand1;
        TQRDBText *QRDBText1;
        TQRSubDetail *QRSubDetail1;
        TQRDBText *QRDBText2;
        TIBQuery *IBQuery3;
        TQRSubDetail *QRSubDetail2;
        TQRDBText *QRDBText3;
        TQRLabel *QRLabel2;
        TQRShape *QRShape1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRMemo *QRMemo1;
        TQRDBText *QRDBText4;
        TQRMemo *QRMemo2;
        TQRLabel *QRLabel5;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRShape *QRShape6;
        TQRShape *QRShape7;
        TQRShape *QRShape8;
        TQRShape *QRShape9;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape14;
        TQRShape *QRShape15;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRShape *QRShape18;
        TQRShape *QRShape20;
        TQRLabel *QRLabel1;
        TQRShape *QRShape19;
        TQRBand *QRBand2;
        TQRShape *QRShape21;
        TQRLabel *QRLabel6;
        TQRShape *QRShape22;
        TQRShape *QRShape23;
        TQRShape *QRShape24;
        TQRDBText *QRDBText5;
        TQRCSVFilter *QRCSVFilter1;
        TQRBand *QRBand3;
        TQRLabel *QRLabel7;
        TQRDBText *QRDBText6;
        void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
        void __fastcall ayrintili_programBeforePrint(
          TCustomQuickRep *Sender, bool &PrintReport);
        void __fastcall QRSubDetail1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
        void __fastcall QRChildBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
        void __fastcall QRSubDetail1AfterPrint(TQRCustomBand *Sender,
          bool BandPrinted);
private:	// User declarations
   AnsiString ders_kodu,saat,tarih;


public:		// User declarations
        __fastcall Tdevam_devamsizlik_f(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdevam_devamsizlik_f *devam_devamsizlik_f;
//---------------------------------------------------------------------------
#endif
