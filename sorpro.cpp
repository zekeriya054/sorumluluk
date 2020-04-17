//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("anaform.cpp", AnaEkran);
USEFORM("hakkinda.cpp", Form1);
USEFORM("ogretmen_program.cpp", ogretmen_rapor);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{

		Application->Initialize();
		Application->CreateForm(__classid(TAnaEkran), &AnaEkran);
		Application->CreateForm(__classid(Togretmen_rapor), &ogretmen_rapor);
		Application->CreateForm(__classid(TForm1), &Form1);
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
