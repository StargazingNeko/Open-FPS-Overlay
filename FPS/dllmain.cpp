#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <psapi.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <d3d11.h>
#include <d3d12.h>

DWORD pid = GetCurrentProcessId();

int ListModules(DWORD ProcId)
{

	std::stringstream ss;
	ss << "PID: " << pid;

	HMODULE hModule[1024];
	HANDLE hProc;
	DWORD cbNeeded;
	unsigned int i;

	hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcId);

	if (EnumProcessModules(hProc, hModule, sizeof(hModule), &cbNeeded)) 
	{
		for (i = 0; i < (cbNeeded / sizeof(hModule)); i++)
		{
			std::cout << ss.str() << std::endl;
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProc, hModule[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				_tprintf(TEXT("\t%s (0x%08X)\n)"), szModName, hModule[i]);
			}
			else
			{
				std::cout << "Error!" << std::endl;
			}

		}
	}

	CloseHandle(hProc);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) 
	{

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//As of right now this is temporary for testing and learning injection! Will be replaced with overlay drawing which displays FPS in the future.//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		std::cout << "Injection Success!" << std::endl;

		ListModules(pid);

		return TRUE;
	}
	return FALSE;
}