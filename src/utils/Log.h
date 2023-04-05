
#pragma once

#include	<string>

using namespace std ;

enum LogLevel
{
	LOG_LEVEL_ERROR		= 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG
} ;

#define	LOG_MESSAGE_SIZE	16384

class Log
{

private:

	void				Write( const char* moduleName, const char * logData );
	LogLevel			logLevel ;

public:
    Log();
	static Log *	GetInstance()
	{
	    static Log instance ;
		return &instance ;
	};

	void				Info( const char* moduleName, const char* text, ... );
	void				Error( const char* moduleName, const char* text, ... );
	void				Debug( const char* moduleName, const char* text, ... );

	void				SetLogLevel ( LogLevel pLogLevel ) ;
	LogLevel			GetLogLevel ( void ) { return logLevel ; } ;

};


