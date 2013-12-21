// Settings.cpp: 
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "Settings.h"

//------------------------------------------------------------------
// Name: CSettings
// Desc: Constuctor
//------------------------------------------------------------------
CSettings::CSettings()
{
	m_pszSaveFileName = L"settings.ini"; // File where the settings will be stored

	// Retrieve the path of the local application data folder where the settings will ba saved
	//CHECK_THROW_COM(::SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, m_szUserAppDataPath));

	::SetCurrentDirectory(m_szUserAppDataPath);

	// Try to open the file and if it doesn't exist then create a new one
	m_hSettingsFile = ::CreateFile(m_pszSaveFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(m_hSettingsFile == INVALID_HANDLE_VALUE)
		throw E_FAIL;

	// Check if the file already exists
	if(::GetLastError() == ERROR_ALREADY_EXISTS) // The file already exists
	{
		// Since the file already exists try to load the settings from the file
		if(load() == false) // The settings failed to load
		{
			// Since the settings failed to load restore default settings and save it
			restoreDefault();
		}
	}
	else // The file didn't exist so a new one was created
	{
		restoreDefault(); // Set default settings in the newly created file
	}
}

//------------------------------------------------------------------
// Name: CSettings
// Desc: Destuctor
//------------------------------------------------------------------
CSettings::~CSettings()
{
	::CloseHandle(m_hSettingsFile);
	m_hSettingsFile = NULL;
}

//------------------------------------------------------------------
// Name: load
// Desc: Load the settings from the file
//------------------------------------------------------------------
BOOL CSettings::load()
{
	return TRUE;
}

//------------------------------------------------------------------
// Name: restoreDefault
// Desc: Restore default settings
//------------------------------------------------------------------
BOOL CSettings::restoreDefault()
{
	return TRUE;
}

//------------------------------------------------------------------
// Name: parse
// Desc: Parse the settings file
//------------------------------------------------------------------
BOOL CSettings::parse()
{
	//WCHAR *pszSettingsData;

	// Retrieve the size of the file
	DWORD dwFileSize = ::GetFileSize(m_hSettingsFile, NULL);

	// if the size of the file is 0 bytes then
	if(dwFileSize == 0)
		return FALSE;

	// Convert the total number of bytes to KB equivalent
	dwFileSize /= 1024;

	// If the size of the file is greater than 1
	if(dwFileSize > 1024)
		return FALSE;

	// Read the bytes from the file
	//::ReadFile(m_hSettingsFile, );

	return TRUE;
}