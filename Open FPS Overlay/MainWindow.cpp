#include "MainWindow.h"



using namespace System;
using namespace System::Windows::Forms;
using namespace OpenFPSOverlay;


DWORD WINAPI HotKeys(LPVOID lpParam)
{
	if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x55))
	{
		std::cout << "Hotkey CTRL+U registered" << std::endl;
	}
	else
	{
		std::cout << "Hotkey fail!" << std::endl;
	}

	MSG msg = {0};
	MainWindow mw;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			mw.Inject();
		}
	}
	return 0;
}

[STAThreadAttribute]
int main(array<String^>^ args)
{

	HANDLE HotKeyThreadHandle = 0;
	LPDWORD tid = 0;
	int HotKeyThreadData = 1;

	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	HotKeyThreadHandle = CreateThread(nullptr, 0, HotKeys, &HotKeyThreadData, 0, tid);
	if (HotKeyThreadHandle == NULL)
	{
		ExitProcess(HotKeyThreadData);
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OpenFPSOverlay::MainWindow form;
	Application::Run(%form);


	return 0;

}