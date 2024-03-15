
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
// #include <format>

#include "utils/StringUtils.h"
#include "utils/Log.h"

#include <iostream> // Standard in/out header
#include <fstream>	// File io header
#include <pwd.h>
using namespace std;

Log::Log()
{
	logLevel = LOG_LEVEL_INFO;
}

void Log::Write(const char *moduleName, const char *logData)
{
	// FILE	*fLog ;
	std::ofstream fileLog;

	int day,
		month,
		year,
		hour,
		minute,
		second;

	time_t rawtime;
	struct tm *currentdate;

	time(&rawtime);
	currentdate = localtime(&rawtime);

	day = currentdate->tm_mday;
	month = currentdate->tm_mon + 1;
	year = currentdate->tm_year + 1900;

	hour = currentdate->tm_hour;
	minute = currentdate->tm_min;
	second = currentdate->tm_sec;

	//	cout << "current_path().parent_path() : " << std::filesystem::current_path().parent_path() << endl;
	// cout << "current_path() : " << std::filesystem::current_path() << endl;

#if defined(__APPLE__) && defined(__MACH__)

	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		// cout << "HOME not set" << endl;
	}
	// cout << "homedir : " << homedir << endl;

	//	string logFileFolder = StringPrintf("/Library/Application Support/GemEngine");
	//	string logFileFolder = StringPrintf("/Users/walterpalladino/Library/Application Support/GemEngine");
	string logFileFolder = string(homedir) + "/Library/Application Support/GemEngine";
	// string logFileFolder = std::filesystem::current_path().u8string() + "/GemEngine";
	//  logFileFolder = "/Users/walterpalladino/prg/sdl2-ws/gemengine/GemEngine";
	string logFileName = logFileFolder + "/log.txt";
#else
	string logFileFolder = "GemEngine";
	string logFileName = logFileFolder + "/log.txt";
#endif

	// Create log file inside User Home folder on Mac
	if (!std::filesystem::exists(logFileFolder))
	{
		std::filesystem::create_directory(logFileFolder);
	}

	try
	{
		fileLog.open(logFileName, ios::app);
		fileLog << StringPrintf("[%02d/%02d/%4d %02d:%02d:%02d] [%s]%s\n", day, month, year, hour, minute, second, moduleName, logData);
		// fileLog << format("[{:02d}/{:02d}/{:04d} {:02d}:{:02d}:{:02d}] [{:s}]{:s}\n", day, month, year, hour, minute, second, moduleName, logData);
	}
	catch (std::ofstream::failure e)
	{
		cout << "Exception opening file " << logFileName << endl
			 << e.what() << endl;
	}

	fileLog.close();
}

void Log::Info(const char *moduleName, const char *text, ...)
{
	char logData[LOG_MESSAGE_SIZE];

	if (logLevel < LOG_LEVEL_INFO)
		return;

	// Compile string to output
	va_list argList;
	va_start(argList, text);
	vsprintf(logData, text, argList);

	Write(moduleName, logData);

	va_end(argList);
}

void Log::Error(const char *moduleName, const char *text, ...)
{
	char logData[LOG_MESSAGE_SIZE];

	// Compile string to output
	va_list argList;
	va_start(argList, text);
	vsprintf(logData, text, argList);

	Write(moduleName, logData);

	va_end(argList);
}

void Log::Debug(const char *moduleName, const char *text, ...)
{
	char logData[LOG_MESSAGE_SIZE];

	if (logLevel < LOG_LEVEL_DEBUG)
		return;

	// Compile string to output
	va_list argList;
	va_start(argList, text);
	vsprintf(logData, text, argList);

	Write(moduleName, logData);

	va_end(argList);
}

void Log::SetLogLevel(LogLevel pLogLevel)
{
	if ((pLogLevel < LOG_LEVEL_ERROR) ||
		(pLogLevel > LOG_LEVEL_DEBUG))
		return;
	logLevel = pLogLevel;
}
