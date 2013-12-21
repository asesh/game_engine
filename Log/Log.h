// Log.h: Implementation of logger
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef LOG_H
#define LOG_H

// Forward declarations
enum class ELogType;

// CLog class
class CLog final
{
public:
	CLog(); // Default constructor
	~CLog(); // Destructor

	static bool start(); // Start the logging process
	static bool stop(); // Stop error logging
	static bool clear(); // Clear the log file
	static bool log(std::wstring oStringToWriteToLogFile); // Write the specified data to the log file
	static void insertLineFeed(); // Write line feed
	static void insertCarriageReturn(); // Write carriage return
	static bool execute(); // Show the log file in an external application
	static bool isNotValid(); // The log file is not valid

private:
	static std::wfstream m_fStream; // File stream handle

	//time_t m_tTime;

	static SYSTEMTIME m_oLocalTime; // Will hold the system time
};

//extern CLog *g_pLog;

// ELogType
enum class ELogType
{
	eMinimum,
	eVerbose,
};

#endif // LOG_H