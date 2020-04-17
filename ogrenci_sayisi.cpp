//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ogrenci_sayisi.h"
#include "anaform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Togrenci_sayisi_f *ogrenci_sayisi_f;
//---------------------------------------------------------------------------
__fastcall Togrenci_sayisi_f::Togrenci_sayisi_f(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Togrenci_sayisi_f::devam_devamsizlikBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{

   IBQuery1->Active=false;
   IBQuery1->SQL->Clear();
   IBQuery1->SQL->Add("select  distinct(sinav_programi.ders_kodu),sinav_programi.tarih,sinav_programi.saat,dersler.ders_adi,dersler.seviye from sinav_programi,dersler where sinav_programi.tarih=:tarih and sinav_programi.saat=:saat and sinav_programi.ders_kodu=dersler.ders_kodu order by sinav_programi.tarih asc,sinav_programi.saat asc,dersler.ders_adi asc");
   IBQuery1->ParamByName("tarih")->AsDateTime=IBQuery2->FieldByName("tarih")->AsDateTime;
   IBQuery1->ParamByName("saat")->AsString=IBQuery2->FieldByName("saat")->AsString;
   IBQuery1->Active=true;
   IBQuery3->Active=false;
   IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery3->Active=true;

  IBQuery5->Active=false;
  IBQuery5->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery5->Active=true;     
}
//---------------------------------------------------------------------------
void __fastcall Togrenci_sayisi_f::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
  IBQuery3->Active=false;
  IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery3->Active=true;        

  IBQuery5->Active=false;
  IBQuery5->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery5->Active=true;

}
//---------------------------------------------------------------------------
void __fastcall Togrenci_sayisi_f::QRBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
  static int i=0;i++;
  if(i==1) {
   IBQuery1->Active=false;
   IBQuery1->SQL->Clear();
   IBQuery1->SQL->Add("select  distinct(sinav_programi.ders_kodu),sinav_programi.tarih,sinav_programi.saat,dersler.ders_adi,dersler.seviye from sinav_programi,dersler where sinav_programi.tarih=:tarih and sinav_programi.saat=:saat and sinav_programi.ders_kodu=dersler.ders_kodu order by sinav_programi.tarih asc,sinav_programi.saat asc,dersler.ders_adi asc");
   IBQuery1->ParamByName("tarih")->AsDateTime=IBQuery2->FieldByName("tarih")->AsDateTime;
   IBQuery1->ParamByName("saat")->AsString=IBQuery2->FieldByName("saat")->AsString;
   IBQuery1->Active=true;
  }         
}
//---------------------------------------------------------------------------
