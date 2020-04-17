//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ucret_onayi.h"
#include "anaform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tucret_onay_f *ucret_onay_f;
//---------------------------------------------------------------------------
__fastcall Tucret_onay_f::Tucret_onay_f(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tucret_onay_f::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
  // ShowMessage(IBQuery1->FieldByName("ad_soyad")->AsString);
   IBQuery2->Active=false;
   IBQuery2->ParamByName("ad_soyad")->AsString=IBQuery1->FieldByName("ad_soyad")->AsString;
   IBQuery2->Active=true;
  // ks->Caption=IBQuery2->FieldByName("ks")->AsString;
   IBQuery3->Active=false;
   IBQuery3->ParamByName("ad_soyad")->AsString=IBQuery1->FieldByName("ad_soyad")->AsString;
   IBQuery3->Active=true;
  // gs->Caption=IBQuery3->FieldByName("gs")->AsString;


}
//---------------------------------------------------------------------------
void __fastcall Tucret_onay_f::FormShow(TObject *Sender)
{
  IBQuery1->Active=false;
  IBQuery1->Active=true;
}
//---------------------------------------------------------------------------

