//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ayrintili_program.h"
#include "anaform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tdevam_devamsizlik_f *devam_devamsizlik_f;
//---------------------------------------------------------------------------
__fastcall Tdevam_devamsizlik_f::Tdevam_devamsizlik_f(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall Tdevam_devamsizlik_f::QRBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{

   IBQuery1->Active=false;
   IBQuery1->SQL->Clear();
   IBQuery1->SQL->Add("select  distinct(sinav_programi.ders_kodu),sinav_programi.tarih,sinav_programi.saat,dersler.ders_adi,dersler.seviye from sinav_programi,dersler where sinav_programi.tarih=:tarih and sinav_programi.ders_kodu=dersler.ders_kodu order by sinav_programi.tarih asc,sinav_programi.saat asc,dersler.ders_adi asc");
   IBQuery1->ParamByName("tarih")->AsDateTime=IBQuery2->FieldByName("tarih")->AsDateTime;
   IBQuery1->Active=true;
 /*
  IBQuery3->Active=false;
  IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;
  IBQuery3->Active=true;*/
}
//---------------------------------------------------------------------------
void __fastcall Tdevam_devamsizlik_f::ayrintili_programBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{

   IBQuery1->Active=false;
   IBQuery1->SQL->Clear();
   IBQuery1->SQL->Add("select  distinct(sinav_programi.ders_kodu),sinav_programi.tarih,sinav_programi.saat,dersler.ders_adi,dersler.seviye from sinav_programi,dersler where sinav_programi.tarih=:tarih and sinav_programi.ders_kodu=dersler.ders_kodu order by sinav_programi.tarih asc,sinav_programi.saat asc,dersler.ders_adi asc");
   
   IBQuery1->ParamByName("tarih")->AsDateTime=IBQuery2->FieldByName("tarih")->AsDateTime;
   IBQuery1->Active=true;
   IBQuery3->Active=false;
   IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery3->Active=true;


}
//---------------------------------------------------------------------------
void __fastcall Tdevam_devamsizlik_f::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{

  IBQuery3->Active=false;
  IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 /*
  IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
  IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;*/
  IBQuery3->Active=true;
}
//---------------------------------------------------------------------------



void __fastcall Tdevam_devamsizlik_f::QRChildBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
/*
  IBQuery3->Active=false;
  IBQuery3->ParamByName("ders_kodu")->AsString=IBQuery1->FieldByName("ders_kodu")->AsString;
 // IBQuery3->ParamByName("tarih")->AsDateTime=IBQuery1->FieldByName("tarih")->AsDateTime;
 // IBQuery3->ParamByName("saat")->AsString=IBQuery1->FieldByName("saat")->AsString;
  IBQuery3->Active=true;*/
}
//---------------------------------------------------------------------------

void __fastcall Tdevam_devamsizlik_f::QRSubDetail1AfterPrint(
      TQRCustomBand *Sender, bool BandPrinted)
{
//  QRSubDetail2->Repaint();        
}
//---------------------------------------------------------------------------


