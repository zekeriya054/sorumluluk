//---------------------------------------------------------------------------

#ifndef anaformH
#define anaformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "IBDatabase.hpp"
#include <DB.hpp>
#include "IBCustomDataSet.hpp"
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include "IBStoredProc.hpp"
#include "IBQuery.hpp"
#include "IBSQL.hpp"
//#include "frxClass.hpp"
//#include "frxDBSet.hpp"
//#include "frxDCtrl.hpp"
//#include "frxRich.hpp"
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
//---------------------------------------------------------------------------
class TAnaEkran : public TForm
{
__published:	// IDE-managed Components
	TIBDatabase *veriler;
	TIBTransaction *IBTransaction1;
	TIBDataSet *ogrenciler;
	TDataSource *ogrenciDS;
	TDataSource *derslerDS;
	TIBDataSet *dersler;
	TIBDataSet *snv_tarihleri;
	TDataSource *snv_tarihleriDS;
	TDataSource *snv_programiDS;
	TIBDataSet *snv_programi;
	TPageControl *ana_sayfa;
	TTabSheet *ogr_kayit;
	TDBGrid *DBGrid1;
	TDBEdit *DBEdit2;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TTabSheet *ders_kayit;
	TDBGrid *DBGrid2;
	TDBNavigator *DBNavigator2;
	TStaticText *StaticText5;
	TDBEdit *DBEdit5;
	TStaticText *StaticText6;
	TDBEdit *DBEdit6;
	TStaticText *StaticText7;
	TDBEdit *DBEdit7;
	TStaticText *StaticText8;
	TDBEdit *DBEdit8;
	TTabSheet *sinav_tarihleri;
	TDBGrid *DBGrid3;
	TStaticText *StaticText9;
	TStaticText *StaticText10;
	TStaticText *StaticText11;
	TDBEdit *DBEdit9;
	TDBEdit *DBEdit10;
	TDBEdit *DBEdit11;
	TDBNavigator *DBNavigator3;
	TTabSheet *sinav_programi;
	TDBGrid *DBGrid4;
	TDataSource *snv_dersleriDS;
	TIBDataSet *snv_dersleri;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TListView *dh;
	TStaticText *StaticText13;
	TStaticText *StaticText14;
	TRadioGroup *r1;
	TListView *odh;
	TIBDataSet *sinava_girecekler;
	TIBQuery *dersler2;
	TIBStoredProc *sp1;
	TSpeedButton *SpeedButton6;
	TIBQuery *kalan_dersler;
	TSpeedButton *bitir;
	TSpeedButton *SpeedButton1;
	TIBStoredProc *sp2;
	TIBStoredProc *sp3;
	TIBStoredProc *sp4;
	TGroupBox *GroupBox1;
	TDBGrid *DBGrid5;
	TDataSource *kalan_derslerDS;
	TStaticText *StaticText12;
	TEdit *Edit1;
	TLabel *Label1;
	TTabSheet *ogretmenler;
	TGroupBox *GroupBox2;
	TDataSource *ogretmenDS;
	TDBGrid *DBGrid6;
	TDBNavigator *DBNavigator4;
	TGroupBox *GroupBox3;
	TListView *gdh;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton7;
	TGroupBox *GroupBox4;
	TSpeedButton *SpeedButton9;
	TListView *ogrdh;
	TRadioGroup *r2;
	TIBDataSet *ogretmen_programi;
	TSpeedButton *SpeedButton8;
	TIBStoredProc *sp5;
	TIBStoredProc *sp6;
	TIBStoredProc *sp7;
	TIBDataSet *ogretmen_programi2;
	TGroupBox *GroupBox5;
	TDataSource *ogretmen_programi2DS;
	TDBGrid *DBGrid7;
	TSpeedButton *SpeedButton11;
	TSpeedButton *SpeedButton12;
	TSpeedButton *SpeedButton13;
	TSpeedButton *SpeedButton14;
	TIBQuery *ogretmen_rapor;
	TIBQuery *sinav_programi_rap;
	TIBQuery *sinav_programi_rapor;
	TGroupBox *GroupBox7;
	TListView *l2;
	TGroupBox *GroupBox6;
	TListView *l1;
	TIBQuery *sinava_girenler;
	TSpeedButton *SpeedButton15;
	TSpeedButton *SpeedButton16;
	TSpeedButton *SpeedButton17;
	TSpeedButton *SpeedButton18;
	TIBStoredProc *sp8;
	TIBStoredProc *sp9;
	TSpeedButton *SpeedButton19;
	TRadioGroup *r3;
	TStaticText *StaticText15;
	TStaticText *os;
	TOpenDialog *dosya_ac;
	TADOConnection *con1;
        TADOTable *t111;
	TDataSource *t1DS;
	TADOTable *kaynak_dersler;
	TTabSheet *TabSheet1;
	TDataSource *ontanimli_sinavlarDS;
	TDBGrid *DBGrid8;
	TIBDataSet *ontanimli_sinavlar;
	TIBStoredProc *sp10;
	TStaticText *StaticText16;
	TStaticText *StaticText17;
	TDBGrid *DBGrid9;
	TSpeedButton *SpeedButton21;
	TEdit *Tarih;
	TEdit *Saat;
	TDBNavigator *DBNavigator5;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox8;
	TCheckBox *c1;
	TCheckBox *c2;
	TCheckBox *c3;
	TCheckBox *c4;
	TCheckBox *c5;
	TCheckBox *c6;
	TSpeedButton *SpeedButton22;
	TIBStoredProc *spsil;
	TCheckBox *c7;
	TCheckBox *c8;
	TTabSheet *TabSheet3;
	TIBDataSet *rapor_bilgileri;
	TDataSource *rapor_bilgileriDS;
	TEdit *ogr_no;
	TDBNavigator *DBNavigator1;
	TMemo *Memo1;
	TGroupBox *GroupBox25;
	TSpeedButton *SpeedButton20;
	TCheckBox *ac1;
	TADOQuery *t2;
	TADOQuery *t3;
	TCheckBox *ac2;
	TADOQuery *t4;
	TLabel *Label4;
	TMemo *Memo4;
	TIBQuery *ogretmen_rapor2;
	TIBQuery *genel_pro_sorgu;
	TSpeedButton *SpeedButton68;
	TStaticText *StaticText64;
	TDBEdit *DBEdit39;
	TRadioGroup *r7;
	TIBDatabase *kaynakf;
	TIBQuery *kaynaks;
	TIBTransaction *IBTransaction2;
	TIBQuery *kaynakd;
	TCheckBox *ac3;
        TSpeedButton *SpeedButton69;
        TADOQuery *t1;
        TGroupBox *GroupBox26;
        TEdit *Edit8;
        TEdit *Edit9;
        TLabel *Label5;
        TLabel *Label6;
        TSpeedButton *SpeedButton70;
        TSpeedButton *SpeedButton71;
        TRadioGroup *rr7;
        TCheckBox *c17;
        TComboBox *alan;
        TStaticText *StaticText65;
        TIBDataSet *alanlar;
        TIBDataSet *ogretmen;
        TIBDataSet *alanlarr;
        TTabSheet *alantab;
        TDBGrid *DBGrid28;
        TDataSource *alanlards;
        TDBNavigator *DBNavigator16;
        TADOQuery *t5;
        TSpeedButton *SpeedButton43;
        TSpeedButton *SpeedButton10;
        TDBMemo *DBMemo1;
        TStaticText *StaticText37;
        TDBEdit *DBEdit23;
        TDBEdit *DBEdit24;
        TDBEdit *DBEdit22;
        TDBEdit *DBEdit21;
        TStaticText *StaticText36;
        TStaticText *StaticText38;
        TStaticText *StaticText40;
        TStaticText *StaticText39;
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ogrenciDSDataChange(TObject *Sender, TField *Field);
	void __fastcall sp2PostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall ogr_kayitShow(TObject *Sender);
	void __fastcall sinav_programiShow(TObject *Sender);
	void __fastcall bitirClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ogretmenlerShow(TObject *Sender);
	void __fastcall SpeedButton9Click(TObject *Sender);
	void __fastcall SpeedButton8Click(TObject *Sender);
	void __fastcall snv_programiDSDataChange(TObject *Sender, TField *Field);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall sp7DeleteError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
	void __fastcall ogretmenDSDataChange(TObject *Sender, TField *Field);
	void __fastcall SpeedButton11Click(TObject *Sender);
	void __fastcall SpeedButton12Click(TObject *Sender);
	void __fastcall SpeedButton13Click(TObject *Sender);
	void __fastcall SpeedButton14Click(TObject *Sender);
	void __fastcall ders_kayitShow(TObject *Sender);
	void __fastcall derslerDSDataChange(TObject *Sender, TField *Field);
	void __fastcall SpeedButton15Click(TObject *Sender);
	void __fastcall SpeedButton17Click(TObject *Sender);
	void __fastcall SpeedButton16Click(TObject *Sender);
	void __fastcall SpeedButton18Click(TObject *Sender);
	void __fastcall SpeedButton19Click(TObject *Sender);
	void __fastcall SpeedButton20Click(TObject *Sender);
	void __fastcall TabSheet1Show(TObject *Sender);
	void __fastcall SpeedButton21Click(TObject *Sender);
	void __fastcall SpeedButton22Click(TObject *Sender);
	void __fastcall SpeedButton66Click(TObject *Sender);
	void __fastcall ogr_noChange(TObject *Sender);
	void __fastcall ogr_noKeyPress(TObject *Sender, char &Key);
	void __fastcall ogrencilerBeforePost(TDataSet *DataSet);
	void __fastcall ogrencilerBeforeInsert(TDataSet *DataSet);
	void __fastcall ogrencilerAfterPost(TDataSet *DataSet);
	void __fastcall sinav_tarihleriShow(TObject *Sender);
	void __fastcall TabSheet18Show(TObject *Sender);
	void __fastcall derslerPostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
	void __fastcall TabSheet2Show(TObject *Sender);
	void __fastcall SpeedButton68Click(TObject *Sender);
        void __fastcall SpeedButton69Click(TObject *Sender);
        void __fastcall SpeedButton70Click(TObject *Sender);
        void __fastcall SpeedButton71Click(TObject *Sender);
        void __fastcall alanChange(TObject *Sender);
        void __fastcall alantabShow(TObject *Sender);
        void __fastcall SpeedButton10Click(TObject *Sender);
private:	// User declarations
   AnsiString yol;
   int hata1,gorev_sil_hata;
   TDate tarih,tarih2;
   AnsiString saat,saat2,ders_kodu,ders_adi,sorgu,asil_sorgu,sinif;
   int sinav_sayisi,onaylanmayan,n,devam,toplu_kayit;
public:		// User declarations
	__fastcall TAnaEkran(TComponent* Owner);
	void __fastcall OgrenciDersleriniHazirla(void);
	void __fastcall OgretmenGorevleriniHazirla(void);
	void __fastcall SinavaGirecekleriHazirla(void);
	void __fastcall SorguyuHazirla(void);
        void __fastcall OgretmenleriHazirla(AnsiString s);
        void __fastcall AlanlariHazirla(void);
	AnsiString __fastcall cevir(AnsiString str);
};
//---------------------------------------------------------------------------
extern PACKAGE TAnaEkran *AnaEkran;
//---------------------------------------------------------------------------
#endif
