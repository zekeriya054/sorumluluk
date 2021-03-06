//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("anaform.cpp", AnaEkran);
USEFORM("hakkinda.cpp", Form1);
USEFORM("sinav_programi.cpp", sinav_programi_f);
USEFORM("ogretmen_program.cpp", ogretmen_rapor_f);
USEFORM("devam_devamsizlik.cpp", devam_devamsizlik_f);
USEFORM("ayrintili_program2.cpp", ayrintili_program_f);
USEFORM("ucret_onayi.cpp", ucret_onay_f);
USEFORM("numara_tekrari.cpp", numara_tekrar_f);
USEFORM("devam_devamsizlik2.cpp", devam_devamsizlik2_f);
USEFORM("ogrenci_sayisi.cpp", ogrenci_sayisi_f);
USEFORM("alanform.cpp", alanf);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TAnaEkran), &AnaEkran);
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(Tsinav_programi_f), &sinav_programi_f);
                 Application->CreateForm(__classid(Togretmen_rapor_f), &ogretmen_rapor_f);
                 Application->CreateForm(__classid(Tdevam_devamsizlik_f), &devam_devamsizlik_f);
                 Application->CreateForm(__classid(Tayrintili_program_f), &ayrintili_program_f);
                 Application->CreateForm(__classid(Tucret_onay_f), &ucret_onay_f);
                 Application->CreateForm(__classid(Tnumara_tekrar_f), &numara_tekrar_f);
                 Application->CreateForm(__classid(Tdevam_devamsizlik2_f), &devam_devamsizlik2_f);
                 Application->CreateForm(__classid(Togrenci_sayisi_f), &ogrenci_sayisi_f);
                 Application->CreateForm(__classid(Talanf), &alanf);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
