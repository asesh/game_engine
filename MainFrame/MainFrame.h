// MainFrame.h: CMainFrame class declaration
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef MAINFRAME_H
#define MAINFRAME_H

// Global variables
const WCHAR g_szClassName[] = L"Asesh";
const WCHAR g_szWindowTitle[] = L"Asesh Game Engine";

// Function prototypes
LRESULT CALLBACK wndProc(HWND hWnd, UINT uiMsg, WPARAM wpParam, LPARAM lpParam);

// CMainFrame class
class CMainFrame final
{
public: // Public methods

	CMainFrame(); // Default constructor
	~CMainFrame(); // Destructor

	BOOL create(); // Create the main window
	void close(); // Close the main window

	void show() const; // Show the main window

	void onSetFocus(); // Handle WM_SETFOCUS message
	void onKillFocus(); // Handle WM_KILLFOCUS message
	void onInput(WPARAM wpParam, LPARAM lpParam); // Handle WM_INPUT message
	void onClose(); // Handle WM_CLOSE message
	void onDestroy(); // Handle WM_DESTROY message

	int getWindowHeight() const; // Get the window height
	int getWindowWidth() const; // Get the window width
	HWND getWindowHandle() const; // Get the window handle

	bool isWindowOnFocus() const; // Determine if the window is on focus or not

private: // Private attributes

	HWND m_hWnd; // Main window handle

	int m_nWindowHeight, m_nWindowWidth; // Height andn width of the window

	RECT m_oClientRect; // Will hold the coordinates of the client area

	bool m_bOnFocus; // Will hold a value if the window is in/out of focus
};

extern CMainFrame *g_pMainFrame;

#endif // MAINFRAME_H