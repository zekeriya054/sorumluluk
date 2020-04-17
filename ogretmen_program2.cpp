//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ogretmen_program2.h"
#include"anaform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IBCustomDataSet"
#pragma link "IBQuery"
#pragma resource "*.dfm"
Togretmen_rapor_f *ogretmen_rapor_f;
//---------------------------------------------------------------------------
__fastcall Togretmen_rapor_f::Togretmen_rapor_f(TComponent* Owner)
	: TForm(Owner)
{


}
//---------------------------------------------------------------------------

void __fastcall Togretmen_rapor_f::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
  //QRLabel3->Caption=ogretmenler->FieldByName("ders_adi")->AsString;        
}
//---------------------------------------------------------------------------

void __fastcall Togretmen_rapor_f::QRBand2BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{

  ogretmenler->Active=false;
  ogretmenler->SQL->Clear();
  ogretmenler->SQL->Add("select ogretmen_programi.ad_soyad,ogretmen_programi.ders_kodu,ogretmen_programi.gorev\
                         ,ogretmen_programi.tarih,ogretmen_programi.saat,dersler.ders_adi,dersler.seviye from ogretmen_programi,dersler where ad_soyad=:ad_soyad \
                          and ogretmen_programi.ders_kodu=dersler.ders_kodu");
  ogretmenler->ParamByName("ad_soyad")->AsString=AnaEkran->ogretmen_rapor2->FieldByName("ad_soyad")->AsString;
  ogretmenler->Active=true;
  //ShowMessage(AnaEkran->ogretmen_rapor2->FieldByName("ad_soyad")->AsString);
  //QRDBText2->DataSet=ogretmenler;
  //QRDBText2->DataField="DERS_KODU";        
}
//---------------------------------------------------------------------------


void __fastcall Togretmen_rapor_f::ogretmen_programiBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{

  ogretmenler->Active=false;
  ogretmenler->SQL->Clear();
  ogretmenler->SQL->Add("select ogretmen_programi.ad_soyad,ogretmen_programi.ders_kodu,ogretmen_programi.gorev\
                         ,ogretmen_programi.tarih,ogretmen_programi.saat,dersler.ders_adi,dersler.seviye from ogretmen_programi,dersler where ad_soyad=:ad_soyad \
                          and ogretmen_programi.ders_kodu=dersler.ders_kodu");
  ogretmenler->ParamByName("ad_soyad")->AsString=AnaEkran->ogretmen_rapor2->FieldByName("ad_soyad")->AsString;
  ogretmenler->Active=true;        
}
//---------------------------------------------------------------------------




