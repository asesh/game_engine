// Settings.h: 
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#ifndef SETTINGS_H
#define SETTINGS_H

// Forward declarations
struct SGraphicsSettings;
struct SKeyboardSettings;
struct SMouseSettings;

// CSettings class
class CSettings
{
public:
	CSettings() throw(...); // Default constructor
	~CSettings(); // Destructor

	BOOL load(); // Load the settings file
	BOOL restoreDefault(); // Restore default settings

private: // Private methods

	BOOL parse();

private: // Private attributes
	std::vector<WCHAR *> m_oSettingsVec;

public: // Public attributes

	/*struct SProfileSettings
	{
		SGraphicsSettings m_oGraphicsSettings;
		SKeyboardSettings m_oKeyboardSettings;
		SMouseSettings m_oMouseSettings;
	} m_oProfileSettings;*/

private: // Private attributes

	HANDLE m_hSettingsFile; // Handle to the file which will store settings

	WCHAR *m_pszSaveFileName; // Will hold the name of the filename where the settings will be stored
	WCHAR m_szUserAppDataPath[MAX_PATH]; // Will hold the local app. data path where the settings will be stored

	// Structures holding the settings
	//
	// Graphics settings
	struct SGraphicsSettings
	{
		// Screen resolution
		DWORD m_dwScreenWidth, m_dwScreenHeight; // Width and height of the screen resolution
	};

	// keyboard settings
	struct SKeyboardSettings
	{
		// Keys
		USHORT m_sForward, m_sBackward, m_sLeft, m_sRight;
		USHORT m_sJump, m_sCrawl;
	};

	// Mouse settings
	struct SMouseSettings
	{
		short m_sMouseSpeed; // 
	};

	HRESULT m_hResult; // It will be used for checking errors
};

#endif // SETTINGS_H