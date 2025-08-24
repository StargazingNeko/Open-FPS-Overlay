#include <Windows.h>
#include "Logging.h"
#include <iostream>
#include <string>
#include <sstream>
#include <psapi.h>
#include <tchar.h>
#include <fstream>

#include <d3d9.h>
#pragma comment(lib, "d3dx9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
/*#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <d3d11.h>
#include <d3d12.h>*/

DWORD pid = GetCurrentProcessId();
int LogDeletedThisRun = 0;

int ListModules(DWORD ProcId)
{
	Logging::Writter().Write("Info: Searching for DX/OGL\n");
	std::stringstream ss;
	ss << "PID: " << pid;

	HMODULE hModule[1024];
	HANDLE hProc;
	DWORD cbNeeded;
	unsigned int i;

	hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcId);

	if (EnumProcessModulesEx(hProc, hModule, sizeof(hModule), &cbNeeded, LIST_MODULES_ALL)) 
	{
		std::string s;
		std::string render;
		for(i = 0; i < (500); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProc, hModule[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				_tprintf(TEXT("\t%s (0x%08X)\n)"), szModName, i);
				
				s = szModName;
				if (s.find("d3d9") != std::string::npos || s.find("d3d11") != std::string::npos || s.find("d3d12") != std::string::npos)
				{
					//MessageBoxA(0, szModName, "Found!", 0);
					Logging::Writter::Writter().Write("Info: Found " + s + "\n");
					render = s.erase(0,20);
					break;
				}
				else
				{
					if (i >= 499) 
					{
						Logging::Writter().Write("Error: Did not find any DX/OGL modules loaded.\n");
						break;
					}
				}
			}
			else
			{
				std::cout << "Error!" << std::endl;
			}
		}
		
		if(!render.empty())
		{
			Logging::Writter().Write(render + "\n");
		}
	}

	CloseHandle(hProc);
	return 0;
}

DWORD WINAPI MainThread(LPVOID lpParam) 
{
	Logging::Writter().Write("Info: MainThread START\n");
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "Injection Success!" << std::endl;

	ListModules(pid);

	Logging::Writter().Write("Info: MainThread END\n");
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//As of right now this is temporary for testing and learning injection! Will be replaced with overlay drawing which displays FPS in the future.//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	
	//Logging::Writter().Write("-------INIT-------\n\n");
	LPDWORD tid = 0;
	int MainThreadData = 1;
	HANDLE MainThreadHandle = 0;
	
	if (LogDeletedThisRun == 0)
	{
		remove("OFO.log");
		LogDeletedThisRun++;
	}

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Logging::Writter().Write("<-----ATTATCHED----->\n");
		MainThreadHandle = CreateThread(nullptr, 0, MainThread, &MainThreadData, 0, tid);
		if (MainThreadHandle == NULL)
		{
			ExitProcess(MainThreadData);
		}

		MainThread(NULL);

		return TRUE;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

		Logging::Writter().Write("<-----DETATCHED----->");
		if (MainThreadHandle != 0)
		{
			CloseHandle(MainThreadHandle);
		}
		return FALSE;
	}

	return FALSE;
}
