// App.cpp: 
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "../MainFrame/MainFrame.h"
#include "../Timer/Timer.h"
#include "App.h"

// WinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG // Debug versions

	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); // Perform memory leak check

#endif // _DEBUG

	MSG oMsg = {0};

	CTimer<float> oTimeDeltaTimer;

	// Check if the logger has been successfully initialized
	if(CLog::isNotValid()) // Something's wrong with the logger
		return 1;

	CLog::log(L"Game engine started");

	//LARGE_INTEGER oPerformanceFrequency, oPrevPerformanceCounter, oCurrPerformanceCounter;

	g_pApp->setInstance(hInstance); // Assign the application instance handle

	//
	/*HANDLE hAppMutex = ::CreateMutex(NULL, TRUE, L"Asesh's Game Engine");
	if(hMutex == NULL || ::GetLastError() == ERROR_ALREADY_EXISTS)
		return 1;*/

	// Get the system information
	SYSTEM_INFO oSystemInfo = {0};
	::GetSystemInfo(&oSystemInfo);

	// Retrieve the frequency of the high-resolution performance counter
	//::QueryPerformanceFrequency(&oPerformanceFrequency);

	// Calculate the number of seconds per-count
	//double dSecondsPerCount = 1.0 / oPerformanceFrequency.QuadPart;

	// Create the main window
	if(!g_pMainFrame->create())
		return 1;

	// Initialize the core game engine
	if(FAILED(g_pGame->initCoreEngine()))
	{
		g_pMainFrame->close();
		return 1;
	}

	// Retrieve the current value of the high-resolution performance counter
	//::QueryPerformanceCounter(&oPrevPerformanceCounter);
	oTimeDeltaTimer.start();

	// Initialize and register the raw input devices
	g_pInput->init();

	// Show the main window
	g_pMainFrame->show();

	// Main message loop
	while(oMsg.message != WM_QUIT)
	{
		// Get the message from the queue
		if(::PeekMessage(&oMsg, nullptr, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&oMsg);
			::DispatchMessage(&oMsg);
		}
		else
		{
			// Check to see if the window is in focus or not
			if(g_pMainFrame->isWindowOnFocus()) // The window is on focus so do rendering stuff
			{
				//::QueryPerformanceCounter(&oCurrPerformanceCounter); // Retrieve the current value of the high-resolution performance counter
				oTimeDeltaTimer.end(); // End the timer
				//float fTimeDelta = static_cast<float>((oCurrPerformanceCounter.QuadPart - oPrevPerformanceCounter.QuadPart) * dSecondsPerCount); // Calculate time delta
				g_pGame->display(oTimeDeltaTimer.getElapsedTime()); // Display the game data onto the screen
				oTimeDeltaTimer.reset(); // Reset the timer
				//oPrevPerformanceCounter.QuadPart = oCurrPerformanceCounter.QuadPart; // Swap old and new performance counters
			}
			else // The window is out of focus
			{
				::Sleep(10); // Sleep
				continue;
			}
		}
	}

	//::CloseHandle(hAppMutex); // Close the application mutex handle

	CLog::log(L"Game engine is about to quit");

	CLog::stop(); // Stop logging

	return static_cast<int>(oMsg.wParam);
}


//---------------------------------------------------------------------------
// Name: CApp
// Desc: Default constructor
//---------------------------------------------------------------------------
CApp::CApp()
{
	m_hInstance = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CApp
// Desc: Destructor
//---------------------------------------------------------------------------
CApp::~CApp()
{
}

//---------------------------------------------------------------------------
// Name: setInstance
// Desc: Set the instance of the application
//---------------------------------------------------------------------------
void CApp::setInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

//---------------------------------------------------------------------------
// Name: getInstance
// Desc: Get the instance handle of the application
//---------------------------------------------------------------------------
HINSTANCE CApp::getInstance() const
{
	return m_hInstance;
}

CApp g_oApp;
CApp *g_pApp = &g_oApp;