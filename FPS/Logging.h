#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <mutex>
//#pragma once

namespace Logging
{
	class Writter
	{
		BOOL debug = TRUE;
		std::string logLoc = "OFO.log";
		std::ofstream logFile;
		std::mutex _logMutex;

	public: void Write(const std::string &message);

	public: void Clear();
	};
};