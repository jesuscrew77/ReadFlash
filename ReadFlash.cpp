//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
USEFORM("UnitMain.cpp", MainForm);
USEFORM("UnitGraph\UnitGraphOrient.cpp", FormGraphOrient);
USEFORM("UnitGraph\UnitAnimateSetting.cpp", FormAnimateSetting);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
	{
		FormatSettings.DecimalSeparator='.';
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
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
