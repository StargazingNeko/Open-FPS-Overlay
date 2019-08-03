#include "MainWindow.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OpenFPSOverlay::MainWindow form;
	Application::Run(%form);
	
	return 0;
}