// Input.h : Declaration of CInput class
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#ifndef INPUT_H
#define INPUT_H

#define WALK_SPEED 20.0f // Walk units
#define RUN_SPEED 40.0f // Run units
#define STRAFE_SPEED 10.0f // Strafe speed
#define YAW_SPEED 1.0f // Yaw speed
#define PITCH_SPEED 1.0f // Pitch speed

// CInput class
class CInput
{
public:
	CInput(); // Constructor
	~CInput(); // Destructor

	BOOL init(); // Initialize the raw input devices

	BOOL getRawInput(WPARAM &wpInputCode, HRAWINPUT oHRawInput); // Get raw input
	BOOL getRawInputData(); // Get raw input data
	BOOL getRawBufferedData(); // Get raw buffered data
	HRESULT getKeyboardData(float fDeltaTime); // Retrieve the data from the keyboard device
	HRESULT getMouseData(float fDeltaTime); // Retrieve the data from the mouse device

	void toggleDataModes(BOOL bImmediateKeyboardData, BOOL bImmediateMouseData); // Toggle input data modes

	void centerCursor(HWND hWnd); // Center the cursor to the client area
	void showCursor(BOOL bShowCursor); // Show/hide cursor

	BOOL disableAllInputs(BOOL bDisableAllInputs); // Disable all the inputs
	BOOL disableKeyboardInput(BOOL bDisableKeyboardInput); // Disable keyboard input
	BOOL disableMouseInput(BOOL bDisableMouseInput); // Disable mouse input

private: // Private methods

	// Mouse activities
	//
	void onMouseLeftButtonDown(); // Left button down
	void onMouseLeftButtonUp(); // Left button up
	void onMouseRightButtonDown(); // Right button down
	void onMouseRightButtonUp(); // Right button up
	void onMouseMiddleButtonDown(); // Middle button down
	void onMouseWheel(short sWheelDelta); // Mouse wheel
	void onMouseMove(LONG lLastX, LONG lLastY); // Move move

	void onMouseAttributesChanged(); // Mouse attributes changed
	void onMouseMovementRelative(); // Mouse movement data is relative to the last mouse position
	void onMouseMovementAbsolute(); // Mouse movement data is based on absolute position
	//
	// Mouse activities

	// Key up/down activities
	//
	void onEscapeKeyDown(); // Escape key down
	void onEscapeKeyUp(); // Escape key up

	void onPauseKeyDown(); // Pause key down
	//void onPauseKeyUp(); // Pause key up

	void onPrintKeyDown(); // Print screen key down
	void onPrintKeyUp(); // Print screen key up

	void onShiftKeyDown(); // Shift key is down
	void onShiftKeyUp(); // Shift key is up
	void onLeftShiftKeyDown(); // Left shift key down
	void onLeftShiftKeyUp(); // Left shift key up
	void onRightShiftKeyDown(); // Right shift key down

	void onControlKeyDown(); // Control key is down
	void onControlKeyUp(); // Control key is up
	void onLeftControlKeyDown(); // L control key down
	void onRightControlKeyDown(); // R control key down

	void onUpKeyDown(); // Up key down

	void onDownKeyDown(); // Down key down

	void onLeftKeyDown(); // Left key down

	void onRightKeyDown(); // Right key down

	void onEnterKeyDown(); // Enter key down

	void on1KeyDown(); // 1 key down

	void on2KeyDown(); // 2 key down

	void on3KeyDown(); // 3 key down

	void on4KeyDown(); // 4 key down
	//
	// End key up/down activities

private: // Private attributes

	RAWINPUT m_oRawInput; // Raw input

	UINT m_uiRawInputSize; // Will hold the size of the raw input structure

	RECT m_oClientRect; // This will hold the coordinates of the client area

	POINT m_oCursorScreenCoord; // This will hold the cursor coordinates

	BOOL m_bBufferedKeyboardData, m_bBufferedMouseData; // Will hold the buffered/unbuffered state of keyboard and mouse

	BOOL m_bDisableKeyboardInput, m_bDisableMouseInput, m_bDisableAllInputs; // 

	bool m_bLeftShiftKeyDown;

	bool m_bMouseRightButtonDown; // 

	USHORT m_usWheelDelta; // Will hold wheel delta value

	HRESULT m_hResult; // It will be used for checking errors
};

extern CInput *g_pInput; // Externed class CInput pointer

#endif // INPUT