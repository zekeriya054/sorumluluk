//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "anaform.h"
#include "hakkinda.h"
#include "ogretmen_program.h"
#include "sinav_programi.h"
#include "devam_devamsizlik.h"
#include "ayrintili_program2.h"
#include "ucret_onayi.h"
#include "devam_devamsizlik2.h"
#include "ogrenci_sayisi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IBDatabase"
#pragma link "IBCustomDataSet"
#pragma link "IBStoredProc"
#pragma link "IBQuery"
#pragma link "IBSQL"
//#pragma link "frxClass"
//#pragma link "frxDBSet"
//#pragma link "frxDCtrl"
//#pragma link "frxRich"
#pragma resource "*.dfm"
TAnaEkran *AnaEkran;
//---------------------------------------------------------------------------
__fastcall TAnaEkran::TAnaEkran(TComponent* Owner)
	: TForm(Owner)
{

  if(veriler->Connected==false) {
	yol=GetCurrentDir();
	veriler->DatabaseName="veriler.gdb";
	veriler->Connected=true;
  } 
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton3Click(TObject *Sender)
{
  // int n=Application->MessageBox("Ýþaretlenen dersler öðrenciye atansýn mý?","Dikkat...!",MB_YESNO+32);
  // if(n==6) {
	int x,j;
	AnsiString sinav_turu;
	sinava_girecekler->Active=true;
	if(r1->ItemIndex==0) sinav_turu="O.Y"; else sinav_turu="SOR." ;
	for(int i=0;i<dh->Items->Count;i++) {
	 if(dh->Items->Item[i]->Checked==true) {
	  sinava_girecekler->Insert();
	  sinava_girecekler->FieldByName("ogr_no")->AsString=Trim(ogr_no->Text);
	  sinava_girecekler->FieldByName("ders_kodu")->AsString=dh->Items->Item[i]->Caption;
		//sinava_girecekler->FieldByName("ders_adi")->AsString=dh->Items->Item[i]->SubItems->operator [](0);
	  // sinava_girecekler->FieldByName("saat")->AsString=dh->Items->Item[i]->SubItems->operator [](2);
	   //	sinava_girecekler->FieldByName("seviye")->AsString=dh->Items->Item[i]->SubItems->operator [](1);
	  sinava_girecekler->FieldByName("sinav_turu")->AsString=sinav_turu;
	  sinava_girecekler->Post();
	  OgrenciDersleriniHazirla();
	 }
   }
// }
}
//---------------------------------------------------------------------------
void __fastcall TAnaEkran::OgrenciDersleriniHazirla(void)
{
 if(ogr_no->Text.Length()>0) {
   int i=0;
   odh->Items->Clear();
   sinava_girecekler->Active=false;
   sinava_girecekler->ParamByName("ogr_no")->AsString=ogrenciler->FieldByName("ogr_no")->AsString;
   sinava_girecekler->Active=true;
   sinava_girecekler->First();
   while(!sinava_girecekler->Eof) {
	dersler2->Active=false;
	dersler2->ParamByName("ders_kodu")->AsString=sinava_girecekler->FieldByName("ders_kodu")->AsString;
	dersler2->Active=true;
	odh->Items->Add();
	odh->Items->Item[i]->Caption=dersler2->FieldByName("ders_kodu")->AsString;
    odh->Items->Item[i]->SubItems->Add(dersler2->FieldByName("ders_adi")->AsString);
	odh->Items->Item[i]->SubItems->Add(sinava_girecekler->FieldByName("sinav_turu")->AsString);
	odh->Items->Item[i]->SubItems->Add(sinava_girecekler->FieldByName("tarih")->AsString);
	odh->Items->Item[i]->SubItems->Add(sinava_girecekler->FieldByName("saat")->AsString);
	odh->Items->Item[i]->SubItems->Add(dersler2->FieldByName("seviye")->AsString);
	odh->Items->Item[i]->SubItems->Add(dersler2->FieldByName("saat")->AsString);
	sinava_girecekler->Next();
   i++;
  }
  }
 }
void __fastcall TAnaEkran::SpeedButton5Click(TObject *Sender)
{
  for(int i=0;i<odh->Items->Count;i++) odh->Items->Item[i]->Checked=true;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton4Click(TObject *Sender)
{
 int n=Application->MessageBox("Öðrenciye ait ders bilgileri silinsin mi?","Dikkat...!",MB_YESNO+32);
 if(n==6) {
  for(int i=0;i<odh->Items->Count;i++)  {
	if(odh->Items->Item[i]->Checked==true) {
		   sp1->ParamByName("ogr_no")->AsString=Trim(ogr_no->Text);
		   sp1->ParamByName("ders_kodu")->AsString=Trim(odh->Items->Item[i]->Caption);
		   sp1->ExecProc();
	}
  }
 odh->Items->Clear();
 OgrenciDersleriniHazirla();
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogrenciDSDataChange(TObject *Sender, TField *Field)
{
 if(ogrenciler->State==dsBrowse) {
  OgrenciDersleriniHazirla();
  ogr_no->Text=IntToStr(ogrenciler->FieldByName("ogr_no")->AsInteger);
 }
}
//---------------------------------------------------------------------------



void __fastcall TAnaEkran::sp2PostError(TDataSet *DataSet, EDatabaseError *E,
      TDataAction &Action)
{
  hata1=0;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton1Click(TObject *Sender)
{
  int n=Application->MessageBox("Yeni Program Oluþturulsun mu ?","Dikkat...!",MB_YESNO+32);
  if(n==6) {
  onaylanmayan=1;
  int durum;
  if(c17->Checked) durum=1; else durum=0;
  sp2->ParamByName("durum")->AsInteger=durum;
  sp2->ExecProc();//Sýnava girilen dersleri bul
  //ontanýmlý sýnavlarý oluþtur

  ontanimli_sinavlar->Active=false;
  ontanimli_sinavlar->Active=true;
  ontanimli_sinavlar->First();
  while(!ontanimli_sinavlar->Eof) {
         ders_kodu=ontanimli_sinavlar->FieldByName("ders_kodu")->AsString;
	 tarih=ontanimli_sinavlar->FieldByName("tarih")->AsDateTime;
	 saat=ontanimli_sinavlar->FieldByName("saat")->AsString;
	 Application->ProcessMessages();
	 sp3->ParamByName("ders_kodu")->AsString=ders_kodu;
	 sp3->ParamByName("tarih")->AsDateTime=tarih;
	 sp3->ParamByName("saat")->AsString=saat;
	 sp3->ExecProc();
	 ontanimli_sinavlar->Next();
  }

//  if(hata1) ShowMessage("Sýnav Dersleri Oluþturuldu...");
//	else  ShowMessage("Sýnav Dersleri Oluþturulamadý");
 
   snv_tarihleri->Active=false;
   snv_tarihleri->Active=true;
   snv_tarihleri->First();
 while(onaylanmayan>0 && !snv_tarihleri->Eof) {
	tarih=snv_tarihleri->FieldByName("tarih")->AsDateTime;
	saat=snv_tarihleri->FieldByName("saat")->AsString;
	sinav_sayisi=snv_tarihleri->FieldByName("sinav_sayisi")->AsInteger;
	snv_dersleri->Active=false;
	snv_dersleri->Active=true;
	snv_dersleri->First();
    Application->ProcessMessages();
	while(!snv_dersleri->Eof && !snv_tarihleri->Eof) {
	Application->ProcessMessages();
	 if(snv_dersleri->FieldByName("onay")->AsInteger!=1) {
	   if(sinav_sayisi>0) {
		ders_kodu=snv_dersleri->FieldByName("ders_kodu")->AsString;
		//Bu dersi alan öðrencilerde çakýþma var mý?
		sp3->ParamByName("ders_kodu")->AsString=ders_kodu;
		sp3->ParamByName("tarih")->AsDateTime=tarih;
		sp3->ParamByName("saat")->AsString=saat;
        	sp3->ExecProc();
		if(sp3->ParamByName("durum")->AsInteger==1) {//Ýþlem baþarýlýysa
                   snv_programi->Active=false;
		   snv_programi->Active=true;
		   kalan_dersler->Active=false;
 		   kalan_dersler->Active=true;
		   sinav_sayisi=sinav_sayisi-1;
		   snv_dersleri->Next();
		 }
		}
		   if(sinav_sayisi==0 && !snv_tarihleri->Eof) { // O saat deki sýnavlar bitmiþse
                          snv_tarihleri->Next();
                          tarih=snv_tarihleri->FieldByName("tarih")->AsDateTime;
			  saat=snv_tarihleri->FieldByName("saat")->AsString;
			  sinav_sayisi=snv_tarihleri->FieldByName("sinav_sayisi")->AsInteger;
  		   }

  }

  snv_dersleri->Next();
 }
  if(onaylanmayan!=-1) {
  sp4->ExecProc();
  onaylanmayan=sp4->ParamByName("kalan")->AsInteger;
  if(onaylanmayan!=-1) Edit1->Text=IntToStr(onaylanmayan);
  Label1->Visible=true;
  Label1->Caption="Lütfen bekleyin iþlem devam ediyor....";
 }
 //if(onceki==onaylanmayan) i++;
 //if(i>1000) { ShowMessage("Program oluþturulamadý");break;}
 if(onaylanmayan==0) {
	ShowMessage("Program baþarýyla oluþturuldu...!");
	bitirClick(Sender);
 }
 snv_tarihleri->Next();

}
 snv_programi->Active=false;
 snv_programi->Active=true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton6Click(TObject *Sender)
{
  for(int i=0;i<dh->Items->Count;i++) dh->Items->Item[i]->Checked=false;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogr_kayitShow(TObject *Sender)
{

 // ogrenciler->Active=false;
 //FormShow(Sender);
 hata1=1;
 int i=0;
 devam=0;
  ogr_no->OnChange=NULL;
  ogrenciDS->OnDataChange=NULL;
  ogrenciler->Active=false;
  ogrenciler->SelectSQL->Clear();
  ogrenciler->SelectSQL->Add("select ogr_no,ad_soyad from ogrenciler \
  where ogr_no=:ogr_no or ogr_no<>:ogr_no order by ogr_no asc");
  ogrenciler->ParamByName("ogr_no")->AsInteger=-1;
  ogrenciler->Active=false;
  ogrenciler->Active=true;
  if(ogrenciler->RecordCount>0)
  ogr_no->Text=IntToStr(ogrenciler->FieldByName("ogr_no")->AsInteger);
  ogr_no->OnChange=ogr_noChange;
  ogrenciDS->OnDataChange=ogrenciDSDataChange;
  dersler->Active=false;
  dersler->Active=true;
  dersler->First();
  dh->Items->Clear();
   while(!dersler->Eof) {
	dh->Items->Add();
	dh->Items->Item[i]->Caption=dersler->FieldByName("ders_kodu")->AsString;
	dh->Items->Item[i]->SubItems->Add(dersler->FieldByName("ders_adi")->AsString);
	dh->Items->Item[i]->SubItems->Add(dersler->FieldByName("seviye")->AsString);
	dh->Items->Item[i]->SubItems->Add(dersler->FieldByName("saat")->AsString);
	dersler->Next();
	i++;
  }
 if(ogrenciler->RecordCount>0) OgrenciDersleriniHazirla();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::sinav_programiShow(TObject *Sender)
{

  gorev_sil_hata=1;

  snv_programi->Active=false;
  snv_programi->Active=true;

  snv_dersleri->Active=false;
  snv_dersleri->Active=true;

  kalan_dersler->Active=false;
  kalan_dersler->Active=true;
  rapor_bilgileri->Active=false;
  rapor_bilgileri->Active=true ;
  AlanlariHazirla();
  OgretmenleriHazirla(alan->Text);

}
void __fastcall TAnaEkran::AlanlariHazirla(void)
{
  alanlar->Active=false;
  alanlar->Active=true;  
  alanlar->First(); 

  alan->Clear();
  alan->Items->Add("Tümü");
  alan->ItemIndex=0;
  while(!alanlar->Eof) {
     alan->Items->Add(alanlar->FieldByName("alan")->AsString);
     alanlar->Next();
  }
}
void __fastcall TAnaEkran::OgretmenleriHazirla(AnsiString s)
{
  int i=0;
  ogretmen->Active=false;
  ogretmen->SelectSQL->Clear();
  if(s=="Tümü")
    ogretmen->SelectSQL->Add("select ad_soyad from ogretmenler order by ad_soyad asc");
  else {
    ogretmen->SelectSQL->Add("select ad_soyad from ogretmenler where alan=:alan order by ad_soyad asc");
    ogretmen->ParamByName("alan")->AsString=s;
  }
  ogretmen->Active=true;
  ogrdh->Items->Clear();
  while(!ogretmen->Eof) {
	ogrdh->Items->Add();
	ogrdh->Items->Item[i]->Caption=ogretmen->FieldByName("ad_soyad")->AsString;
	ogretmen->Next();
	i++;
   }

  OgretmenGorevleriniHazirla();
}

//---------------------------------------------------------------------------


void __fastcall TAnaEkran::bitirClick(TObject *Sender)
{
   onaylanmayan=-1;
   kalan_dersler->Active=false;
   kalan_dersler->Active=true;
   Label1->Caption="Ýþlem tamamlandý...";
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::FormShow(TObject *Sender)
{
   toplu_kayit=0;
   AnsiString gun,ay,yil;
   TDate tarih;
   tarih=Now();
   gun=tarih.DateString();
   ay=yil=gun;
   gun.Delete(3,10);
   ay.Delete(6,10);
   ay.Delete(1,3);
   yil.Delete(1,6);
   //ShowMessage(yil);

   if(/*StrToInt(ay)>11 && */StrToInt(yil)>2012) {
	  // ShowMessage("Programýn kullaným süresi dolmuþtur...!");
  	   exit(0);
   }
}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::FormClose(TObject *Sender, TCloseAction &Action)
{
   
   Form1->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogretmenlerShow(TObject *Sender)
{

  alanlarr->Active=false;
  alanlarr->Active=true;
  alanlarr->First();
  DBGrid6->Columns->Items[1]->PickList->Clear();
  while(!alanlarr->Eof) {
    DBGrid6->Columns->Items[1]->PickList->Add(alanlarr->FieldByName("alan")->AsString);
    alanlarr->Next();
  }
  ogretmen->Active=false;
  ogretmen->SelectSQL->Clear();
  ogretmen->SelectSQL->Add("select * from ogretmenler order by ad_soyad asc");
  ogretmen->Active=true;
  ogretmen_programi2->Active=false;
  ogretmen_programi2->ParamByName("ad_soyad")->AsString=ogretmen->FieldByName("ad_soyad")->AsString;
  ogretmen_programi2->Active=true;
  
}
//---------------------------------------------------------------------------



void __fastcall TAnaEkran::SpeedButton9Click(TObject *Sender)
{
  for (int i=0;i<ogrdh->Items->Count; i++)  ogrdh->Items->Item[i]->Checked=false;

}
//---------------------------------------------------------------------------
void __fastcall TAnaEkran::OgretmenGorevleriniHazirla(void)
{
   int i=0;
   gdh->Items->Clear();
   ogretmen_programi->Active=false;
   ogretmen_programi->ParamByName("ders_kodu")->AsString=snv_programi->FieldByName("ders_kodu")->AsString;
   ogretmen_programi->Active=true;
   ogretmen_programi->First();
   while(!ogretmen_programi->Eof) {
	   gdh->Items->Add();
	   gdh->Items->Item[i]->Caption=ogretmen_programi->FieldByName("ad_soyad")->AsString;
       gdh->Items->Item[i]->SubItems->Add(ogretmen_programi->FieldByName("gorev")->AsString);
	   ogretmen_programi->Next();
	   i++;
   }

}
void __fastcall TAnaEkran::SpeedButton8Click(TObject *Sender)
{
  AnsiString gorev;
  AnsiString s,ad;
  int x;
  ogretmen_programi->Active=false;
  ogretmen_programi->Active=true;
  int n=Application->MessageBox("Ýþaretlenen öðretmenler bu sýnava atansýn mý?","Dikkat...!",MB_YESNO+32);
   if(n==6) {
	 if(r2->ItemIndex==0) gorev="Komisyon"; else gorev="Gözetmen";
	 for(int i=0;i<ogrdh->Items->Count;i++) {
	   if(ogrdh->Items->Item[i]->Checked==true) {
		 s=ogrdh->Items->Item[i]->Caption;
		 sp5->ParamByName("tarih")->AsDateTime=snv_programi->FieldByName("tarih")->AsDateTime;
		 sp5->ParamByName("saat")->AsString=snv_programi->FieldByName("saat")->AsString;
		 sp5->ParamByName("ad_soyad")->AsString=s;
		 sp5->ExecProc();
		 if(sp5->ParamByName("top")->AsInteger>0) {
		   ad=s;
		   ad.Insert(" adlý öðretmenin bu tarih ve saat de sýnavý var...!\nGenede görevi atamak istiyormusunuz ? ",s.Length()+1);
		   x=Application->MessageBox(ad.c_str(),"Dikkat...!",MB_YESNO+32);
		 }
		   if(x==6 || sp5->ParamByName("top")->AsInteger==0) {
			  ogretmen_programi->Insert();
			  ogretmen_programi->FieldByName("ders_kodu")->AsString=snv_programi->FieldByName("ders_kodu")->AsString;
			  ogretmen_programi->FieldByName("ad_soyad")->AsString=s;
			  ogretmen_programi->FieldByName("gorev")->AsString=gorev;
			  ogretmen_programi->FieldByName("tarih")->AsString=snv_programi->FieldByName("tarih")->AsDateTime;
			  ogretmen_programi->FieldByName("saat")->AsString=snv_programi->FieldByName("saat")->AsString;
			  ogretmen_programi->Post();
		 }
	   }
	 }
   OgretmenGorevleriniHazirla();
   }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::snv_programiDSDataChange(TObject *Sender,
      TField *Field)
{
  OgretmenGorevleriniHazirla();	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton2Click(TObject *Sender)
{
  for(int i=0;i<gdh->Items->Count;i++) gdh->Items->Item[i]->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton7Click(TObject *Sender)
{
  int n=Application->MessageBox("Sýnava atanan öðretmen silinsin mi?","Dikkat...!",MB_YESNO+32);
  if(n==6) {
	 for(int i=0;i<gdh->Items->Count;i++) {
         if(gdh->Items->Item[i]->Checked==true) {
			 sp6->ParamByName("ad_soyad")->AsString=gdh->Items->Item[i]->Caption;
			 sp6->ParamByName("ders_kodu")->AsString=snv_programi->FieldByName("ders_kodu")->AsString;
			 sp6->ParamByName("gorev")->AsString=gdh->Items->Item[i]->SubItems->operator [](0);
			 sp6->ExecProc();

         }
	 }
   OgretmenGorevleriniHazirla();
  }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::sp7DeleteError(TDataSet *DataSet, EDatabaseError *E,
      TDataAction &Action)
{
  gorev_sil_hata=0;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogretmenDSDataChange(TObject *Sender, TField *Field)
{
  ogretmen_programi2->Active=false;
  ogretmen_programi2->ParamByName("ad_soyad")->AsString=ogretmen->FieldByName("ad_soyad")->AsString;
  ogretmen_programi2->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton11Click(TObject *Sender)
{
   //  ogretmen_rapor->ShowModal();
  SorguyuHazirla();
  if(n>0) {

/*
  asil_sorgu="select ogretmen_programi.ad_soyad,ogretmen_programi.ders_kodu,ogretmen_programi.gorev,\
			  ogretmen_programi.tarih,ogretmen_programi.saat,\
			  dersler.ders_adi,dersler.seviye from ogretmen_programi,dersler where \
			  dersler.ders_kodu=ogretmen_programi.ders_kodu and \
			  ogretmen_programi.ad_soyad in ";
   asil_sorgu.Insert(sorgu,asil_sorgu.Length()+1);
   asil_sorgu.Insert(" order by ogretmen_programi.ad_soyad asc,ogretmen_programi.tarih asc,ogretmen_programi.saat asc",asil_sorgu.Length()+1);
   */
   asil_sorgu="select ad_soyad from ogretmenler where ad_soyad in ";
   asil_sorgu.Insert(sorgu,asil_sorgu.Length()+1);
   asil_sorgu.Insert(" order by ad_soyad asc",asil_sorgu.Length()+1);
   //ShowMessage(asil_sorgu);
   ogretmen_rapor->Active=false;
   ogretmen_rapor->SQL->Clear();
   ogretmen_rapor->SQL->Add(asil_sorgu);
   ogretmen_rapor->Active=true;
   ogretmen_rapor2->Active=false;
   ogretmen_rapor2->SQL->Clear();
   ogretmen_rapor2->SQL->Add(asil_sorgu);
   ogretmen_rapor2->Active=true;
   ogretmen_rapor_f->ogretmen_programi->Preview();  
  }  else ShowMessage("Öðretmenler arasýndan hiç seçim yapmadýnýz...!");
}
//---------------------------------------------------------------------------
void __fastcall TAnaEkran::SorguyuHazirla(void)
{
	n=0;
	sorgu="";
	int j;
	for(j=0;j<ogrdh->Items->Count;j++) if(ogrdh->Items->Item[j]->Checked==true) n++;
	if(n>0) {
	   if(ogrdh->Items->Count>0) sorgu.Insert("(",sorgu.Length()+1);
	   for(int i=0;i<ogrdh->Items->Count;i++) {
		if(ogrdh->Items->Item[i]->Checked==true) {
			sorgu.Insert("\'",sorgu.Length()+1);
			sorgu.Insert(ogrdh->Items->Item[i]->Caption,sorgu.Length()+1);
			sorgu.Insert("\'",sorgu.Length()+1);
			if(i<ogrdh->Items->Count) sorgu.Insert(",",sorgu.Length()+1);
		}
	   }
     sorgu.Delete(sorgu.Length(),1);
	 if(ogrdh->Items->Count>0) sorgu.Insert(")",sorgu.Length()+1);
	}
}
void __fastcall TAnaEkran::SpeedButton12Click(TObject *Sender)
{
   for (int i=0;i<ogrdh->Items->Count; i++)  ogrdh->Items->Item[i]->Checked=true;

}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::SpeedButton13Click(TObject *Sender)
{
/*
   sinav_programi_rapor->Active=false;
   sinav_programi_rapor->Active=true;
   //sinav_pro->ShowReport(true);*/
   devam_devamsizlik_f->devam_devamsizlik->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton14Click(TObject *Sender)
{
   sinav_programi_f->sinav_programi->Preview();
   //snv_prog_rapor->ShowReport(true);

}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ders_kayitShow(TObject *Sender)
{

   int i=0;
   dersler->Active=false;
   dersler->Active=true;
  if(dersler->RecordCount>0) {
   ogrenciler->Active=false;
   ogrenciler->Active=true;
   l2->Items->Clear();

   while(!ogrenciler->Eof) {
	   l2->Items->Add();
	   l2->Items->Item[i]->Caption=ogrenciler->FieldByName("ogr_no")->AsString;
	  l2->Items->Item[i]->SubItems->Add(ogrenciler->FieldByName("ad_soyad")->AsString);
	 i++;
	ogrenciler->Next();
   }

  SinavaGirecekleriHazirla();
 } 
}
//---------------------------------------------------------------------------
  void __fastcall TAnaEkran::SinavaGirecekleriHazirla(void)
  {
    int i=0;
	l1->Items->Clear();
	sinava_girenler->Active=false;
    sinava_girenler->ParamByName("ders_kodu")->AsString=dersler->FieldByName("ders_kodu")->AsString;
	sinava_girenler->Active=true;
	sinava_girenler->First();
	while(!sinava_girenler->Eof) {
	   l1->Items->Add();
	   l1->Items->Item[i]->Caption=sinava_girenler->FieldByName("ogr_no")->AsString;
	   l1->Items->Item[i]->SubItems->Add(sinava_girenler->FieldByName("ad_soyad")->AsString);
	 i++;
	sinava_girenler->Next();
	}
    os->Caption=IntToStr(l1->Items->Count);	
  }
void __fastcall TAnaEkran::derslerDSDataChange(TObject *Sender, TField *Field)
{
   SinavaGirecekleriHazirla();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton15Click(TObject *Sender)
{
  for(int i=0;i<l1->Items->Count;i++) l1->Items->Item[i]->Checked=true;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton17Click(TObject *Sender)
{
  for(int i=0;i<l1->Items->Count;i++) l1->Items->Item[i]->Checked=false;		
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton16Click(TObject *Sender)
{
 for(int i=0;i<l1->Items->Count;i++) {
   if(l1->Items->Item[i]->Checked==true) {
	  sp8->ParamByName("ogr_no")->AsInteger=StrToInt(l1->Items->Item[i]->Caption);
	  sp8->ParamByName("ders_kodu")->AsString=dersler->FieldByName("ders_kodu")->AsString;
	  sp8->ExecProc(); 
   }
 }
  SinavaGirecekleriHazirla();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton18Click(TObject *Sender)
{
  AnsiString sinav_turu;
  if(r3->ItemIndex==0) sinav_turu="O.Y"; else sinav_turu="SOR." ;
   for(int i=0;i<l2->Items->Count;i++) {
   if(l2->Items->Item[i]->Checked==true) {
	  sp9->ParamByName("ogr_no")->AsInteger=StrToInt(l2->Items->Item[i]->Caption);
	  sp9->ParamByName("ders_kodu")->AsString=dersler->FieldByName("ders_kodu")->AsString;
	  sp9->ParamByName("sinav_turu")->AsString=sinav_turu;
	  sp9->ExecProc();
   }
 }
  SinavaGirecekleriHazirla();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton19Click(TObject *Sender)
{
   for(int i=0;i<l2->Items->Count;i++) l2->Items->Item[i]->Checked=false;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton20Click(TObject *Sender)
{
  AnsiString kaynak,baglanti,ders_k,ders_a,sorgu,ss,ss2,ad,soyad,ad_soyad;
  int pos;
  dosya_ac->Execute();
  kaynak=dosya_ac->FileName;
  if(kaynak.Length()>0) {
   if(r7->ItemIndex==1 || r7->ItemIndex==2) {
	Label4->Visible=true;
        if(r7->ItemIndex==1)
        	baglanti="Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Jet OLEDB:Database Password=MAUEDGSDUUIRTN;Data Source=";
        else baglanti="Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Data Source=";
	baglanti.Insert(kaynak,baglanti.Length()+1);
	con1->ConnectionString=baglanti;
	con1->Connected=true;
   if(ac2->Checked==true) {   //öðrenciler
        t1->Active=false;
        t1->SQL->Clear();
      if(r7->ItemIndex==1) {   //bilsa
         if(rr7->ItemIndex==0) sorgu="select distinct(OgrenciNotlar.N_Ogr_Numarasi),\
          OgrenciMAin.Ogr_Adi,OgrenciMAin.Ogr_Soyadi,OgrenciMAin.Ogr_Sinif \
          from OgrenciNotlar,OgrenciMAin where \
          OgrenciNotlar.N_Ogr_Numarasi=OgrenciMAin.Ogr_Numarasi and OgrenciNotlar.N_Oys_Dilekce='E'";
         else sorgu="select distinct(OgrenciNotlar.N_Ogr_Numarasi),\
          OgrenciMAin.Ogr_Adi,OgrenciMAin.Ogr_Soyadi,OgrenciMAin.Ogr_Sinif \
          from OgrenciNotlar,OgrenciMAin where \
          OgrenciNotlar.N_Ogr_Numarasi=OgrenciMAin.Ogr_Numarasi and (OgrenciNotlar.N_Oys_Dilekce=' E' or OgrenciNotlar.N_Oys_Dilekce='EE')";
     }else { //access
       sorgu="select distinct(veriler.ogr_no),ad_soyad from veriler";
      }
        t1->SQL->Add(sorgu);
	t1->ConnectionString=baglanti;
	t1->Active=true;
	t1->First();
        t1->Next();
	ogrenciler->Active=false;
	ogrenciler->Active=true;
	toplu_kayit=1;
	ogrenciDS->OnDataChange=NULL;
	while(!t1->Eof) {
         ogrenciler->Insert();
         if(r7->ItemIndex==1) { //bilsa
	  ogr_no->Text=Trim(IntToStr(t1->FieldByName("N_Ogr_Numarasi")->AsInteger));
	  //ogrenciler->FieldByName("ogr_no")->AsInteger=t1->FieldByName("N_Ogr_Numarasi")->AsInteger;
	  ogrenciler->FieldByName("ad_soyad")->AsString=t1->FieldByName("Ogr_Adi")->AsString;
//	  ogrenciler->FieldByName("soyad")->AsString=t1->FieldByName("Ogr_Soyadi")->AsString;
	//  ogrenciler->FieldByName("sinif")->AsString=t1->FieldByName("Ogr_Sinif")->AsString;
         } else {
         //ShowMessage("kjkjk");
           //accesss
           ogr_no->Text=Trim(IntToStr(t1->FieldByName("ogr_no")->AsInteger));
           ogrenciler->FieldByName("ad_soyad")->AsString=t1->FieldByName("ad_soyad")->AsString;
          /*
	  ogrenciler->FieldByName("ogr_no")->AsInteger=t1->FieldByName("N_Ogr_Numarasi")->AsInteger;

          ad_soyad=t1->FieldByName("ad_soyad")->AsString;
         // sinif=t1->FieldByName("sinif")->AsString;
         // ShowMessage(sinif);
          pos=ad_soyad.Pos(" ");
          ad=ad_soyad;
          soyad=ad_soyad;
          ad.Delete(pos,ad_soyad.Length()-pos+1);
          soyad.Delete(1,ad.Length()+2);
        //  pos=soyad.Pos(" ");
        //   ShowMessage(soyad);
        //   ShowMessage(IntToStr(pos));
	  ogrenciler->FieldByName("ad")->AsString=ad;
	  ogrenciler->FieldByName("soyad")->AsString=soyad;

          if(sinif.Length()>0) ogrenciler->FieldByName("sinif")->AsString= sinif;
          */
	  //ogrenciler->FieldByName("sinif")->AsString=t1->FieldByName("Ogr_Sinif")->AsString;
         }
	  ogrenciler->Post();
	  t1->Next();
	}
  }
    if(ac3->Checked==true) {
    //  ShowMessage("kljk");
      t5->SQL->Clear();
      t5->SQL->Add("select sira_no,ad_soyad,alan from ogretmenler");
      t5->Active=true;
      t5->First();
      while(!t5->Eof) {
      	ogretmen->Insert();
        ogretmen->FieldByName("sira_no")->AsInteger=t5->FieldByName("sira_no")->AsInteger;
        ogretmen->FieldByName("ad_soyad")->AsString=t5->FieldByName("ad_soyad")->AsString;
        ogretmen->FieldByName("alan")->AsString=t5->FieldByName("alan")->AsString;
	//	ogretmen->FieldByName("sinav_sayisi")->AsInteger=kaynaks->FieldByName("sinav_sayisi")->AsInteger;
        ogretmen->Post();
        t5->Next();
      }
    }

  if(ac1->Checked==true) {
	 t2->ConnectionString=baglanti;
	 t3->ConnectionString=baglanti;
	 t4->ConnectionString=baglanti;
         t2->Active=false;
         t2->SQL->Clear();
       if(r1->ItemIndex==1) {//bilsa
        if(rr7->ItemIndex==0) sorgu="select distinct(N_Derskodu) from OgrenciNotlar where N_Oys_Dilekce='E'";
           else sorgu="select distinct(N_Derskodu) from OgrenciNotlar where (N_Oys_Dilekce=' E' or N_Oys_Dilekce='EE')";
       } else sorgu="select distinct(ders_kodu),ders_adi,seviye from veriler";//access
         t2->SQL->Add(sorgu);
	 t2->Active=true;
	 dersler->Active=false;
	 dersler->Active=true;
	 sinava_girecekler->Active=false;
	 sinava_girecekler->Active=true;
	 t2->First();
         if(r1->ItemIndex==2) t2->Next();
	 while(!t2->Eof) {
                if(Edit8->Text.Length()>0){
                   ders_k=Edit8->Text;
                   if(r1->ItemIndex==1) ders_k.Insert(t2->FieldByName("N_Derskodu")->AsString,ders_k.Length()+1);
                     else ders_k.Insert(t2->FieldByName("ders_kodu")->AsString,ders_k.Length()+1);
                 } else {
                     if(r1->ItemIndex==1)
                       ders_k=t2->FieldByName("N_Derskodu")->AsString;
                     else ders_k=t2->FieldByName("ders_kodu")->AsString;
                 }
                //ShowMessage(t2->FieldByName("N_Dersadi")->AsString);
		dersler->Insert();
             if(r1->ItemIndex==1) {
		dersler->FieldByName("ders_kodu")->AsString=ders_k;//t2->FieldByName("N_Derskodu")->AsString;
		t3->Active=false;
                t3->SQL->Clear();
                t3->Parameters->ParamByName("ders_kodu")->Value=t2->FieldByName("ders_kodu")->AsString;
                t3->Active=true;
                if(Edit9->Text.Length()>0){
                   ders_a=t3->FieldByName("N_Dersadi")->AsString;
                   ders_a.Insert(Edit9->Text,ders_a.Length()+1);
                 }  else ders_a=t3->FieldByName("N_Dersadi")->AsString;

		dersler->FieldByName("ders_adi")->AsString=ders_a;//t3->FieldByName("N_Dersadi")->AsString;
		dersler->FieldByName("saat")->AsInteger=t3->FieldByName("N_Derssaati")->AsInteger;
             } else {
            
                dersler->FieldByName("ders_kodu")->AsString=t2->FieldByName("ders_kodu")->AsString;
                dersler->FieldByName("ders_adi")->AsString=t2->FieldByName("ders_adi")->AsString;
                dersler->FieldByName("seviye")->AsString=t2->FieldByName("seviye")->AsString;
             }
		dersler->Post();
		t4->Active=false;
                t4->SQL->Clear();
                if(r1->ItemIndex==1) {
                 if(rr7->ItemIndex==0) sorgu="select N_Ogr_Numarasi from OgrenciNotlar where N_Derskodu=:ders_kodu and N_Oys_Dilekce='E'";
                  else sorgu="select N_Ogr_Numarasi from OgrenciNotlar where N_Derskodu=:ders_kodu and (N_Oys_Dilekce=' E' or N_Oys_Dilekce='EE')";
                } else {
                   sorgu="select ogr_no,ders_kodu from veriler where ders_kodu=:ders_kodu";
                }
                sorgu.Insert(ss,sorgu.Length()+1);
                t4->SQL->Add(sorgu);
		t4->Parameters->ParamByName("ders_kodu")->Value=t2->FieldByName("ders_kodu")->AsString;
		t4->Active=true;

		while(!t4->Eof){
		  sinava_girecekler->Insert();
                  if(r1->ItemIndex==1){
        	    sinava_girecekler->FieldByName("ogr_no")->AsString=t4->FieldByName("N_Ogr_Numarasi")->AsString;
                    sinava_girecekler->FieldByName("ders_kodu")->AsString=ders_k;
                  } else {
                    sinava_girecekler->FieldByName("ogr_no")->AsString=t4->FieldByName("ogr_no")->AsString;
                    sinava_girecekler->FieldByName("ders_kodu")->AsString=t2->FieldByName("ders_kodu")->AsString;
                  }
		  sinava_girecekler->Post();
		  t4->Next();
		}
               t2->Next();
	 }
  }
   Label4->Visible=false;
   ShowMessage("Otomatik kayýt iþlemi tamamlandý...");

   con1->Connected=false;
  }
  if(r7->ItemIndex==0) {
	  kaynakf->DatabaseName=kaynak;
	  kaynakf->Connected=true;
	  if(ac2->Checked==true) { //öðrenci tablosu
		  kaynaks->SQL->Clear();
		  kaynaks->SQL->Add("select * from ogrenciler");
		  kaynaks->Active=true;
		  kaynaks->First();
		  ogrenciler->Active=true;
		  while(!kaynaks->Eof) {
			  ogrenciler->Insert();
			  ogr_no->Text=Trim(IntToStr(kaynaks->FieldByName("ogr_no")->AsInteger));
			  ogrenciler->FieldByName("ogr_no")->AsInteger=kaynaks->FieldByName("ogr_no")->AsInteger;
			  ogrenciler->FieldByName("ad_soyad")->AsString=kaynaks->FieldByName("ad_soyad")->AsString;
//			  ogrenciler->FieldByName("soyad")->AsString=kaynaks->FieldByName("soyad")->AsString;
			 // ogrenciler->FieldByName("sinif")->AsString=kaynaks->FieldByName("sinif")->AsString;
			  ogrenciler->Post();
			  kaynaks->Next();
                    }

	   }
    if(ac1->Checked==true) {
	   kaynaks->SQL->Clear();
	   kaynaks->SQL->Add("select * from sinava_girecekler");
	   kaynaks->Active=true;
	   kaynaks->First();
       while(!kaynaks->Eof){
		  sinava_girecekler->Insert();
		  sinava_girecekler->FieldByName("ogr_no")->AsString=kaynaks->FieldByName("ogr_no")->AsString;
		  sinava_girecekler->FieldByName("ders_kodu")->AsString=kaynaks->FieldByName("ders_kodu")->AsString;
		  sinava_girecekler->Post();
		  kaynaks->Next();
		}
	   kaynaks->SQL->Clear();
	   kaynaks->SQL->Add("select * from dersler");
	   kaynaks->Active=true;
	   //kaynaks->First;
	   while(!kaynaks->Eof){
                 dersler->Insert();
		 dersler->FieldByName("ders_kodu")->AsString=kaynaks->FieldByName("ders_kodu")->AsString;
		 dersler->FieldByName("ders_adi")->AsString=kaynaks->FieldByName("ders_adi")->AsString;
		 dersler->FieldByName("saat")->AsInteger=kaynaks->FieldByName("saat")->AsInteger;
		 dersler->FieldByName("seviye")->AsString=kaynaks->FieldByName("seviye")->AsString;
		 dersler->Post();
		 kaynaks->Next();
	   }
	 }
	if(ac3->Checked==true) {
           if(r7->ItemIndex==0) {
                kaynaks->SQL->Clear();
//                ogretmen->Active=true
		kaynaks->SQL->Add("select sira_no,ad_soyad,alan from ogretmenler");
		kaynaks->Active=true;
		kaynaks->First();
	   while(!kaynaks->Eof) {
		ogretmen->Insert();
	        ogretmen->FieldByName("sira_no")->AsInteger=kaynaks->FieldByName("sira_no")->AsInteger;
		ogretmen->FieldByName("ad_soyad")->AsString=kaynaks->FieldByName("ad_soyad")->AsString;
                ogretmen->FieldByName("alan")->AsString=kaynaks->FieldByName("alan")->AsString;
	   //	ogretmen->FieldByName("sinav_sayisi")->AsInteger=kaynaks->FieldByName("sinav_sayisi")->AsInteger;
		ogretmen->Post();
                kaynaks->Next();
	   }
       }
     }
  }
   Label4->Visible=false;
   ShowMessage("Otomatik kayýt iþlemi tamamlandý...");
   kaynakf->Connected=false;
 }
  toplu_kayit=0;
  ogrenciDS->OnDataChange=ogrenciDSDataChange;
}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::TabSheet1Show(TObject *Sender)
{
  ontanimli_sinavlar->Active=false;
  ontanimli_sinavlar->Active=true;
  dersler->Active=false;
  dersler->Active=true;
}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::SpeedButton21Click(TObject *Sender)
{
  if(Tarih->Text.Length()==10 && Saat->Text.Length()==5) {
	sp10->ParamByName("ders_kodu")->AsString=dersler->FieldByName("ders_kodu")->AsString;
	sp10->ParamByName("tarih")->AsDateTime=StrToDate(Trim(Tarih->Text));
	sp10->ParamByName("saat")->AsString=Trim(Saat->Text);
	sp10->ExecProc();
	if(sp10->ParamByName("durum")->AsInteger==0) ShowMessage("Bu dersi alan öðrencilerde çakýþma var\nBu tarihe bu sýnav sabitlenemez");
	  else {
		 ontanimli_sinavlar->Insert();
		 ontanimli_sinavlar->FieldByName("ders_kodu")->AsString=dersler->FieldByName("ders_kodu")->AsString;
		 ontanimli_sinavlar->FieldByName("tarih")->AsDateTime=StrToDate(Trim(Tarih->Text));
		 ontanimli_sinavlar->FieldByName("saat")->AsString=Trim(Saat->Text);
		 ontanimli_sinavlar->Post();
		 ontanimli_sinavlar->Active=false;
                 ontanimli_sinavlar->Active=true;
	  }
  } else ShowMessage("Sýnav tarihi veya saatini boþ býrakmayýnýz...!");

 }
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton22Click(TObject *Sender)
{
 if(c1->Checked || c2->Checked || c3->Checked || c4 ->Checked || c5->Checked || c6->Checked || c7->Checked || c8->Checked) {
 int n=Application->MessageBox("Ýþaretlenen Tablolardaki Tüm Verier Silinecek...! \nSilmek istediðinize Eminmisiniz ?","Dikkat...!",MB_YESNO+32);
 if(n==6) {
	if(c1->Checked==true) spsil->ParamByName("ders")->AsInteger=1; else spsil->ParamByName("ders")->AsInteger=0;
	if(c2->Checked==true) spsil->ParamByName("ogr")->AsInteger=1; else spsil->ParamByName("ogr")->AsInteger=0;
	if(c6->Checked==true) spsil->ParamByName("ogretmen")->AsInteger=1; else spsil->ParamByName("ogretmen")->AsInteger=0;
	if(c4->Checked==true) spsil->ParamByName("ontanimli_sinav")->AsInteger=1; else spsil->ParamByName("ontanimli_sinav")->AsInteger=0;
	if(c3->Checked==true) spsil->ParamByName("sinav_tarih")->AsInteger=1; else spsil->ParamByName("sinav_tarih")->AsInteger=0;
	if(c5->Checked==true) spsil->ParamByName("sinav_program")->AsInteger=1; else spsil->ParamByName("sinav_program")->AsInteger=0;
	if(c7->Checked==true) spsil->ParamByName("sinava_girecek")->AsInteger=1; else spsil->ParamByName("sinava_girecek")->AsInteger=0;
	if(c8->Checked==true) spsil->ParamByName("ogretmen_gorevleri")->AsInteger=1; else spsil->ParamByName("ogretmen_gorevleri")->AsInteger=0;
	spsil->ExecProc();
	ShowMessage("Ýþaretlenen tablolardaki veriler silindi...");
 }
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton66Click(TObject *Sender)
{


 /*
  rapor_bilgileri->Active=false;
  rapor_bilgileri->Active=true;
  okul=rapor_bilgileri->FieldByName("baslik")->AsString;
  mudur=rapor_bilgileri->FieldByName("mudur")->AsString;
  rapor_tarihi=rapor_bilgileri->FieldByName("tarih")->AsString;
  sinav_adi=rapor_bilgileri->FieldByName("sinav_adi")->AsString;
  ogretim_yili=rapor_bilgileri->FieldByName("ogretim_yili")->AsString;
   */
}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::ogr_noChange(TObject *Sender)
{
   if(ogrenciler->State==dsBrowse && devam==1) {
	if(ogr_no->Text.Length()>0) {
	  ogr_no->OnChange=NULL;
	  ogrenciDS->OnDataChange=NULL;
	  ogrenciler->Active=false;
	  ogrenciler->SelectSQL->Clear();
	  ogrenciler->SelectSQL->Add("select ogr_no,ad_soyad from ogrenciler where ogr_no=:ogr_no");
	  ogrenciler->ParamByName("ogr_no")->AsInteger=StrToInt(ogr_no->Text);
	  ogrenciler->Active=true;
      odh->Items->Clear();
	  if(ogrenciler->RecordCount>0) OgrenciDersleriniHazirla();
	  ogr_no->OnChange=ogr_noChange;
	  ogrenciDS->OnDataChange=ogrenciDSDataChange;
	  devam=0;
  } else {
	  ogr_no->OnChange=NULL;
	  ogrenciDS->OnDataChange=NULL;
	  ogrenciler->Active=false;
	  ogrenciler->SelectSQL->Clear();
	  ogrenciler->SelectSQL->Add("select ogr_no,ad_soyad from ogrenciler \
		   where ogr_no=:ogr_no or ogr_no<>:ogr_no order by ogr_no asc");
	  ogrenciler->ParamByName("ogr_no")->AsInteger=-1;
	  ogrenciler->Active=true;
	  //ogr_no->Text=IntToStr(ogrenciler->FieldByName("ogr_no")->AsInteger);
     // odh->Items->Clear();
	  ogr_no->OnChange=ogr_noChange;
	  ogrenciDS->OnDataChange=ogrenciDSDataChange;
	  devam=0;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogr_noKeyPress(TObject *Sender, char &Key)
{
  devam=1;
}
//---------------------------------------------------------------------------



void __fastcall TAnaEkran::ogrencilerBeforePost(TDataSet *DataSet)
{
   ogrenciler->FieldByName("ogr_no")->AsInteger=StrToInt(ogr_no->Text);
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogrencilerBeforeInsert(TDataSet *DataSet)
{
   ogr_no->Text="";	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::ogrencilerAfterPost(TDataSet *DataSet)
{
  devam=0;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::sinav_tarihleriShow(TObject *Sender)
{
  snv_tarihleri->Active=false;
  snv_tarihleri->Active=true;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::TabSheet18Show(TObject *Sender)
{
   rapor_bilgileri->Active=false;
   rapor_bilgileri->Active=true;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::derslerPostError(TDataSet *DataSet,
      EDatabaseError *E, TDataAction &Action)
{
//  Label4->Visible=false;	
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::TabSheet2Show(TObject *Sender)
{
  Label4->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TAnaEkran::SpeedButton68Click(TObject *Sender)
{
  //genel_pro_rap->ShowReport(true);
  // ayrintili_program_f->IBQuery1->Active=false;
  // ayrintili_program_f->IBQuery1->Active=true;
   ayrintili_program_f->ayrintili_program->Preview();
}
//---------------------------------------------------------------------------






void __fastcall TAnaEkran::SpeedButton69Click(TObject *Sender)
{
  ucret_onay_f->ucret_onay->Preview();        
}
//---------------------------------------------------------------------------



void __fastcall TAnaEkran::SpeedButton70Click(TObject *Sender)
{
  tarih2=snv_tarihleri->FieldByName("tarih")->AsDateTime;
  saat2=snv_tarihleri->FieldByName("saat")->AsString;
  devam_devamsizlik2_f->IBQuery2->Active=false;
  devam_devamsizlik2_f->IBQuery2->ParamByName("tarih")->AsDateTime=tarih2;
  devam_devamsizlik2_f->IBQuery2->ParamByName("saat")->AsString=saat2;;
  devam_devamsizlik2_f->IBQuery2->Active=true;
  devam_devamsizlik2_f->IBQuery4->Active=false;
  devam_devamsizlik2_f->IBQuery4->ParamByName("tarih")->AsDateTime=tarih2;
  devam_devamsizlik2_f->IBQuery4->ParamByName("saat")->AsString=saat2;;
  devam_devamsizlik2_f->IBQuery4->Active=true;
  devam_devamsizlik2_f->devam_devamsizlik->Preview();
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::SpeedButton71Click(TObject *Sender)
{
  tarih2=snv_tarihleri->FieldByName("tarih")->AsDateTime;
  saat2=snv_tarihleri->FieldByName("saat")->AsString;
  ogrenci_sayisi_f->IBQuery2->Active=false;
  ogrenci_sayisi_f->IBQuery2->ParamByName("tarih")->AsDateTime=tarih2;
  ogrenci_sayisi_f->IBQuery2->ParamByName("saat")->AsString=saat2;;
  ogrenci_sayisi_f->IBQuery2->Active=true;
  ogrenci_sayisi_f->IBQuery4->Active=false;
  ogrenci_sayisi_f->IBQuery4->ParamByName("tarih")->AsDateTime=tarih2;
  ogrenci_sayisi_f->IBQuery4->ParamByName("saat")->AsString=saat2;;
  ogrenci_sayisi_f->IBQuery4->Active=true;
  ogrenci_sayisi_f->devam_devamsizlik->Preview();
}
//---------------------------------------------------------------------------



void __fastcall TAnaEkran::alanChange(TObject *Sender)
{
  OgretmenleriHazirla(alan->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TAnaEkran::alantabShow(TObject *Sender)
{
  alanlarr->Active=false;
  alanlarr->Active=true;        
}
//---------------------------------------------------------------------------





void __fastcall TAnaEkran::SpeedButton10Click(TObject *Sender)
{
  rapor_bilgileri->Edit();
  rapor_bilgileri->Post();
}
//---------------------------------------------------------------------------

