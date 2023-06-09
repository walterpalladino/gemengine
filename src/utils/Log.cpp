
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "utils/StringUtils.h"
#include "utils/Log.h"

#include <iostream> // Standard in/out header
#include <fstream>	// File io header

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
	/*
		// find out current date
	__time64_t	long_time ;
	errno_t		err ;
	struct tm	currentdate ;

		//	Get time as 64 bit integer
		_time64( &long_time ) ;
		//	Convert to localtime
		err	= localtime_s ( &currentdate, &long_time );
		if (err)
			;
	*/
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

	//	fLog	= fopen ( "log.txt", "at") ;
	fileLog.open("log.txt", ios::app);
	//	fprintf( fLog, "[%02d/%02d/%4d %02d:%02d:%02d] [%s]%s\n", day, month, year, hour, minute, second, moduleName, logData ) ;
	fileLog << StringPrintf("[%02d/%02d/%4d %02d:%02d:%02d] [%s]%s\n", day, month, year, hour, minute, second, moduleName, logData);
	//	fclose( fLog ) ;
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
