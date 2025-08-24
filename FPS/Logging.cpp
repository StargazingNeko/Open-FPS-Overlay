#include "Logging.h"

namespace Logging
{
	void Logging::Writter::Write(const std::string &message)
	{
		std::lock_guard<std::mutex> lock(_logMutex);
		switch (debug)
		{
		case true:
		{
			logFile.open(logLoc, std::fstream::app);
			logFile.write(message.c_str(), message.length());// << message;
			logFile.close();
		}
		case false:
		{
			return;
		}
		}
		std::lock_guard<std::mutex> unlock(_logMutex);
	}

	void Logging::Writter::Clear()
	{
		std::lock_guard<std::mutex> lock(_logMutex);

		logFile.open(logLoc, std::fstream::app);
		logFile.clear();
		logFile.close();

		std::lock_guard<std::mutex> unlock(_logMutex);
	}
}