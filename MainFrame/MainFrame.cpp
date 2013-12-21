// MainFrame.cpp: Implementation of CMainFrame class
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\App\App.h"
#include "MainFrame.h"
#include "..\Input\Input.h"

//---------------------------------------------------------------------------
// Name: CMainFrame
// Desc: Default constructor
//---------------------------------------------------------------------------
CMainFrame::CMainFrame()
{
	// Set window width to 720p HD
	m_nWindowHeight = 720; // Intial height of the window
	m_nWindowWidth = 1280; // Initial width of the window

	m_bOnFocus = false; // Initially set the window as not active/focused
}

//---------------------------------------------------------------------------
// Name: ~CMainFrame
// Desc: Destructor
//---------------------------------------------------------------------------
CMainFrame::~CMainFrame()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create the main window
//---------------------------------------------------------------------------
BOOL CMainFrame::create()
{
	RECT oScreenRect, oClientRect = {0};

	WNDCLASSEX oWndClassEx = {0};
	oWndClassEx.cbSize = sizeof(WNDCLASSEX);
	oWndClassEx.hInstance = g_pApp->getInstance();
	oWndClassEx.lpszClassName = g_szClassName;
	oWndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	oWndClassEx.hIcon = reinterpret_cast<HICON>(::LoadImage(g_pApp->getInstance(), 
		MAKEINTRESOURCE(IDI_MAIN_WINDOW_ICON), 
		IMAGE_ICON, 
		::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 
		LR_SHARED));
	//oWndClassEx.hIconSm = (HICON) ::LoadImage(NULL,
	oWndClassEx.hCursor = reinterpret_cast<HCURSOR>(::LoadImage(NULL, 
		IDC_ARROW, 
		IMAGE_CURSOR, 
		::GetSystemMetrics(SM_CXCURSOR), ::GetSystemMetrics(SM_CYCURSOR), 
		LR_SHARED));
	oWndClassEx.lpfnWndProc = wndProc;
	if(!::RegisterClassEx(&oWndClassEx))
		return FALSE;

	// Get the work area
	::SystemParametersInfo(SPI_GETWORKAREA, 0, reinterpret_cast<void *>(&oScreenRect), 0);

	oClientRect.right = m_nWindowWidth; // Assign the width of the window
	oClientRect.bottom = m_nWindowHeight; // Assign the height of the window

	// Adjust the window rectangle to accomodate the desired client area
	::AdjustWindowRectEx(&oClientRect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	// Create the main window
	m_hWnd = ::CreateWindowEx(0,
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPEDWINDOW,
		(oScreenRect.right - m_nWindowWidth) / 2,
		(oScreenRect.bottom - m_nWindowHeight) / 2,
		oClientRect.right - oClientRect.left,
		oClientRect.bottom - oClientRect.top,
		NULL,
		NULL,
		g_pApp->getInstance(),
		NULL);
	if(m_hWnd == NULL)
		return FALSE;

	return TRUE;
}

//---------------------------------------------------------------------------
// Name: close
// Desc: Close the main window
//---------------------------------------------------------------------------
void CMainFrame::close()
{
	::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
}

//---------------------------------------------------------------------------
// Name: show
// Desc: Show the main window
//---------------------------------------------------------------------------
void CMainFrame::show() const
{
	::ShowWindow(m_hWnd, SW_SHOW);
}

//---------------------------------------------------------------------------
// Name: onSetFocus
// Desc: Handle WM_SETFOCUS message
//---------------------------------------------------------------------------
void CMainFrame::onSetFocus()
{
	m_bOnFocus = true; // Signal that the window is on focus
}

//---------------------------------------------------------------------------
// Name: onKillFocus
// Desc: Handle WM_KILLFOCUS message
//---------------------------------------------------------------------------
void CMainFrame::onKillFocus()
{
	m_bOnFocus = false; // Signal that the window is out of focus
}

//---------------------------------------------------------------------------
// Name: onInput
// Desc: Handle WM_INPUT message
//---------------------------------------------------------------------------
void CMainFrame::onInput(WPARAM wpParam, LPARAM lpParam)
{
	g_pInput->getRawInput(wpParam, reinterpret_cast<HRAWINPUT>(lpParam)); // Get raw input data from the input devices
}

//---------------------------------------------------------------------------
// Name: onClose
// Desc: Handle WM_CLOSE message
//---------------------------------------------------------------------------
void CMainFrame::onClose()
{
	::DestroyWindow(m_hWnd); // Destroy the main window
}

//---------------------------------------------------------------------------
// Name: onDestroy
// Desc: Handle WM_DESTROY message
//---------------------------------------------------------------------------
void CMainFrame::onDestroy()
{
	::PostQuitMessage(0);
}

//---------------------------------------------------------------------------
// Name: getWindowHeight
// Desc: Return the main window height
//---------------------------------------------------------------------------
int CMainFrame::getWindowHeight() const
{
	return m_nWindowHeight; // Returnt the height of the window
}

//---------------------------------------------------------------------------
// Name: getWindowWidth
// Desc: Return the main window width
//---------------------------------------------------------------------------
int CMainFrame::getWindowWidth() const
{
	return m_nWindowWidth; // Return the width of the window
}

//---------------------------------------------------------------------------
// Name: getWindowHandle
// Desc: Return the main window handle
//---------------------------------------------------------------------------
HWND CMainFrame::getWindowHandle() const
{
	return m_hWnd; // Return the application window handle
}

//---------------------------------------------------------------------------
// Name: isWindowOnFocus
// Desc: Will return a boolean value indicating if the window is on focus or
//		 not
//---------------------------------------------------------------------------
bool CMainFrame::isWindowOnFocus() const
{
	return m_bOnFocus == true; // Signal that the main window is on focus or out of focus
}

CMainFrame g_oMainFrame;
CMainFrame *g_pMainFrame = &g_oMainFrame;

//---------------------------------------------------------------------------
// Name: wndProc
// Desc: Main window procedure
//---------------------------------------------------------------------------
LRESULT CALLBACK wndProc(HWND hWnd, UINT uiMsg, WPARAM wpParam, LPARAM lpParam)
{
	switch(uiMsg)
	{
	case WM_SETFOCUS: // The window is on focus
		g_pMainFrame->onSetFocus();
		break;

	case WM_KILLFOCUS: // The window is out of focus
		g_pMainFrame->onKillFocus();
		break;

	case WM_INPUT: // Raw input
		g_pMainFrame->onInput(wpParam, lpParam);
		break;

	case WM_CLOSE:
		g_pMainFrame->onClose(); // Close the window
		break;

	case WM_DESTROY:
		g_pMainFrame->onDestroy(); // Destroy the main window
		break;

	default:
		return ::DefWindowProc(hWnd, uiMsg, wpParam, lpParam); // Default window procedure
	}

	return 0;
}
