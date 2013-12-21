// Logger.cpp: Implementation of logger
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "Log.h"

std::wfstream CLog::m_fStream;
SYSTEMTIME CLog::m_oLocalTime;

//---------------------------------------------------------------------------
// Name: CLog
// Desc: Default constructor
//---------------------------------------------------------------------------
CLog::CLog()
{
}


//---------------------------------------------------------------------------
// Name: ~CLog
// Desc: Destructor
//---------------------------------------------------------------------------
CLog::~CLog()
{
}

//---------------------------------------------------------------------------
// Name: start
// Desc: Start logging
//---------------------------------------------------------------------------
bool CLog::start()
{
	m_fStream = std::wfstream(L"log.txt", std::ios::out | std::ios::trunc);
	if(m_fStream.bad()) // Error creating log file
		return false;

	return true;
}

//---------------------------------------------------------------------------
// Name: stop
// Desc: Stop logging
//---------------------------------------------------------------------------
bool CLog::stop()
{
	if(!m_fStream.bad())
	{
		m_fStream.close(); // Close the file
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------
// Name: clear
// Desc: Clear the log
//---------------------------------------------------------------------------
bool CLog::clear()
{
	//m_fStream.clear(

	return true;
}

//---------------------------------------------------------------------------
// Name: log
// Desc: Write the specified data to the log file
//---------------------------------------------------------------------------
bool CLog::log(std::wstring oStringToWriteToLogFile)
{
	/*::time(&m_tTime);
	m_fStream<<ctime_s(&m_tTime)<<" "<<oStringToWriteToLogFile;*/

	//WCHAR szSystemTime[60];

	// Check if the file stream is valid
	if(m_fStream.bad()) // File stream is invalid
		return false; // So return false w/o logging anything

	::GetLocalTime(&m_oLocalTime); // Get the current system time

	// Write the date data and the specified data to the log file
	m_fStream<<m_oLocalTime.wMonth<<"/"<<m_oLocalTime.wDay<<"/"<<m_oLocalTime.wYear<<" "<<m_oLocalTime.wHour<<":"<<m_oLocalTime.wMinute<<":"<<m_oLocalTime.wSecond<<"- "<<oStringToWriteToLogFile<<"\n";

	return true;
}

//---------------------------------------------------------------------------
// Name: insertLineFeed
// Desc: Write line feed 
//---------------------------------------------------------------------------
void CLog::insertLineFeed()
{
	m_fStream<<"\n";
}

//---------------------------------------------------------------------------
// Name: insertCarriageReturn
// Desc: Write carriage return
//---------------------------------------------------------------------------
void CLog::insertCarriageReturn()
{
	m_fStream<<"\r";
}

//---------------------------------------------------------------------------
// Name: execute
// Desc: Show the log file in an external application
//---------------------------------------------------------------------------
bool CLog::execute()
{
	if(SUCCEEDED(::ShellExecute(NULL, L"open", L"log.txt", NULL, NULL, SW_SHOW))) // The log was successfully executed
		return true;
	
	return false; // Error executing the log file
}

//---------------------------------------------------------------------------
// Name: isNotValid
// Desc: Returns true if the fstream object is not valid
//---------------------------------------------------------------------------
bool CLog::isNotValid()
{
	return m_fStream.bad() ? true : false;
}

//CLog g_oLog;
//CLog *g_pLog = &g_oLog;