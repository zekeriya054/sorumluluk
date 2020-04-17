//---------------------------------------------------------------------------

#ifndef ogrenci_sayisiH
#define ogrenci_sayisiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class Togrenci_sayisi_f : public TForm
{
__published:	// IDE-managed Components
        TIBQuery *IBQuery3;
        TIBQuery *IBQuery2;
        TIBQuery *IBQuery1;
        TIBQuery *IBQuery4;
        TIBQuery *IBQuery5;
        TQuickRep *devam_devamsizlik;
        TQRBand *QRBand1;
        TQRDBText *QRDBText1;
        TQRLabel *QRLabel2;
        TQRShape *QRShape1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRMemo *QRMemo1;
        TQRLabel *QRLabel5;
        TQRShape *QRShape5;
        TQRShape *QRShape8;
        TQRShape *QRShape9;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel8;
        TQRDBText *QRDBText4;
        TQRSubDetail *QRSubDetail2;
        TQRDBText *QRDBText3;
        TQRShape *QRShape3;
        TQRShape *QRShape6;
        TQRShape *QRShape15;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRShape *QRShape18;
        TQRShape *QRShape20;
        TQRBand *QRBand2;
        TQRShape *QRShape21;
        TQRBand *QRBand3;
        TQRLabel *QRLabel7;
        TQRDBText *QRDBText6;
        TQRSubDetail *QRSubDetail1;
        TQRShape *QRShape2;
        TQRShape *QRShape4;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape19;
        TQRDBText *QRDBText2;
        TQRDBText *QRDBText5;
        TQRSubDetail *QRSubDetail3;
        TQRDBText *QRDBText7;
        TQRShape *QRShape14;
        TQRShape *QRShape23;
        TQRShape *QRShape22;
        TQRShape *QRShape24;
        TQRShape *QRShape7;
        TQRBand *QRBand4;
        TQRShape *QRShape25;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel10;
        TQRShape *QRShape26;
        TQRShape *QRShape10;
        TQRShape *QRShape27;
        TQRShape *QRShape28;
        TQRShape *QRShape29;
        TQRDBText *QRDBText8;
        TQRLabel *QRLabel6;
        void __fastcall devam_devamsizlikBeforePrint(
          TCustomQuickRep *Sender, bool &PrintReport);
        void __fastcall QRSubDetail1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
        void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
public:		// User declarations
        __fastcall Togrenci_sayisi_f(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Togrenci_sayisi_f *ogrenci_sayisi_f;
//---------------------------------------------------------------------------
#endif
