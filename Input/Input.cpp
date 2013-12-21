// Input.cpp : Implementation of CInput class for managing inputs
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "Input.h"

//---------------------------------------------------------------------------
// Name: CInput
// Desc: CInput constructor
//---------------------------------------------------------------------------
CInput::CInput()
{
	m_bBufferedKeyboardData = m_bBufferedMouseData = FALSE; // Specify unbuffered data for both the keyboard and mouse

	m_bDisableKeyboardInput = m_bDisableMouseInput = m_bDisableAllInputs = FALSE; // All inputs are enabled

	m_uiRawInputSize = sizeof(RAWINPUT); // Size of the RAWINPUT structure

	m_hResult = S_OK; // HRESULT
}

//---------------------------------------------------------------------------
// Name ~CInput
// Desc: CInput destructor
//---------------------------------------------------------------------------
CInput::~CInput()
{

}

//---------------------------------------------------------------------------
// Name: init
// Desc: Register and initialize the raw input devices
//---------------------------------------------------------------------------
BOOL CInput::init()
{
	RAWINPUTDEVICE oRawInputDevice[2];
	::memset(oRawInputDevice, 0, sizeof(oRawInputDevice));

	// Register keyboard for raw input
	oRawInputDevice[0].usUsage = 0x6;
	oRawInputDevice[0].usUsagePage = 0x1;
	oRawInputDevice[0].hwndTarget = g_pMainFrame->getWindowHandle();
	oRawInputDevice[0].dwFlags = RIDEV_NOLEGACY;

	// Register mouse for raw input
	oRawInputDevice[1].usUsage = 0x2;
	oRawInputDevice[1].usUsagePage = 0x1;
	oRawInputDevice[1].hwndTarget = g_pMainFrame->getWindowHandle();

	// Register the raw input devices
	CHECK_BOOL(::RegisterRawInputDevices(oRawInputDevice, ARRAY_SIZE(oRawInputDevice, RAWINPUTDEVICE), sizeof(RAWINPUTDEVICE)));

	return TRUE;
}

//---------------------------------------------------------------------------
// Name: getRawInput
// Desc: Get the raw input from the registered devices
//---------------------------------------------------------------------------
BOOL CInput::getRawInput(WPARAM &wpInputCode, HRAWINPUT hRawInput)
{
	// Check to see all the inputs have been disabled
	if(m_bDisableAllInputs)
		return FALSE; // Since all the inputs have been disabled return 'FALSE'

	// If the application is in the foreground and input occurred
	if(wpInputCode == RIM_INPUT)
	{
		// Unbuffered keyboard data
		if(!m_bBufferedKeyboardData)
		{
			// Get the standard/unbuffered raw input data
			if(::GetRawInputData(hRawInput, RID_INPUT, &m_oRawInput, &m_uiRawInputSize, sizeof(RAWINPUTHEADER)) != static_cast<UINT>(-1))
			{
				// Raw input from keyboard
				if(m_oRawInput.header.dwType == RIM_TYPEKEYBOARD)
				{
					switch(m_oRawInput.data.keyboard.Message)
					{
					case WM_KEYDOWN: // Key is down
						switch(m_oRawInput.data.keyboard.VKey) // Virtual key
						{
						case VK_ESCAPE: // Escape key
							onEscapeKeyDown();
							break;

						case VK_PAUSE: // eGame_Mode_Paused key
						case 'p':
						case 'P':
							onPauseKeyDown();
							break;

						case VK_PRINT: // Print key
							onPrintKeyDown();
							break;

						case VK_SHIFT: // Shift key
							onShiftKeyDown();
							break;

						case VK_LCONTROL: // Left-control key
							onLeftControlKeyDown();
							break;

						case VK_RCONTROL: // Right-control key
							onRightControlKeyDown();
							break;

						case VK_UP: // Up key
							onUpKeyDown();
							break;

						case VK_DOWN: // Down key
							onDownKeyDown();
							break;

						case VK_LEFT: // Left key
							onLeftKeyDown();
							break;

						case VK_RIGHT: // Right key
							onRightKeyDown();
							break;

						case VK_RETURN: // Enter key
							onEnterKeyDown();
							break;

						case 'w':
						case 'W':
							onUpKeyDown();
							break;

						case 's':
						case 'S':
							onDownKeyDown();
							break;

						case 'a':
						case 'A':
							onLeftKeyDown();
							break;

						case 'd':
						case 'D':
							onRightKeyDown();
							break;

						case 'f': // Toggle fullscreen state
						case 'F':
							//g_pD3DGraphics->toggleFullscreenState();
							break;

						case 't': // Toggle fill mode
						case 'T':
							g_pD3DGraphics->toggleFillMode(IMM_DEV_CONTEXT);
							break;

						case '1':
							on1KeyDown();
							break;

						case '2':
							on2KeyDown();
							break;

						case '3':
							on3KeyDown();
							break;

						case '4':
							on4KeyDown();
							break;
						}
						break;

					case WM_KEYUP: // Key is up
						switch(m_oRawInput.data.keyboard.VKey)
						{
						case VK_ESCAPE: // Escape key
							onEscapeKeyUp();
							break;

						case VK_SHIFT: // Shift key
							onShiftKeyUp();
							break;

#ifdef _DEBUG // Debug versions

						case 'F':
						case 'f':
							//g_pD3DGraphics->toggleFullscreenState();
							break;

#endif // _DEBUG
						}
						break;
					}
				}

				// Raw input from mouse
				if(m_oRawInput.header.dwType == RIM_TYPEMOUSE)
				{
					// Mouse state
					switch(m_oRawInput.data.mouse.usFlags)
					{
					case MOUSE_ATTRIBUTES_CHANGED: // The mouse attributes has changed
						onMouseAttributesChanged();
						break;

					case MOUSE_MOVE_ABSOLUTE: // Mouse movement data is based on absolute position
						onMouseMovementAbsolute();
						break;

					case MOUSE_MOVE_RELATIVE: // Mouse movement data is relative to the last mouse position
						onMouseMovementRelative();
						break;
					}
				}
			}
		}

		// Buffered data
		else
		{
			// Get the buffered input data
			/*if(::GetRawInputBuffer(&hRawInput, &m_uiRawInputSize, sizeof(RAWINPUTHEADER)) != <static_cast<UINT>(-1))
			{
			}*/
		}
	}

	return TRUE;
}

//---------------------------------------------------------------------------
// Name: toggleDataModes
// Desc: Toggle input data modes
//---------------------------------------------------------------------------
void CInput::toggleDataModes(BOOL bImmediateKeyboardData, BOOL bImmediateMouseData)
{

}

//---------------------------------------------------------------------------
// Name: onMouseLeftButtonDown
// Desc: Mouse left button is down
//---------------------------------------------------------------------------
void CInput::onMouseLeftButtonDown()
{
	// Get the clicked position
	::GetCursorPos(&m_oCursorScreenCoord); // Get the cursor position in screen space
	::ScreenToClient(g_pMainFrame->getWindowHandle(), &m_oCursorScreenCoord); // Convert the screen space coordinate to client coordinates

	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseLeftButtonUp
// Desc: Mouse left button is up
//---------------------------------------------------------------------------
void CInput::onMouseLeftButtonUp()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseRightButtonDown
// Desc: Mouse right button is down
//---------------------------------------------------------------------------
void CInput::onMouseRightButtonDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		m_bMouseRightButtonDown = true; // Signal the right mouse button is down
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseRightButtonUp
// Desc: Mouse right button is up
//---------------------------------------------------------------------------
void CInput::onMouseRightButtonUp()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		m_bMouseRightButtonDown = false; // Signal the right mouse button is up
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseMiddleButtonDown
// Desc: Mouse middle button is down
//---------------------------------------------------------------------------
void CInput::onMouseMiddleButtonDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseWheel
// Desc: Mouse wheel activities
//---------------------------------------------------------------------------
void CInput::onMouseWheel(short sWheelDelta)
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming

		// Check if the user has scrolled the mouse wheen forward or backward
		if(sWheelDelta < 0) // Backwards scrolling
		{
			//g_pCamera->walk(-g_pMath->getTimeDelta());
			onDownKeyDown();
		}
		else // Forward scrolling
		{
			//g_pCamera->walk(g_pMath->getTimeDelta());
			onUpKeyDown();
		}

		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseMove
// Desc: Mouse move
//---------------------------------------------------------------------------
void CInput::onMouseMove(LONG lLastX, LONG lLastY)
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming

		// Check if the mouse has moved or not
		if(lLastX) // Motion of the mouse in the x direction has changed
		{
			g_pCamera->yaw(lLastX * g_pMath->getTimeDelta());
		}
		if(lLastY) // Motion of the mouse in the y direction has changed
		{
			g_pCamera->pitch(lLastY * g_pMath->getTimeDelta());
		}
		break;

	case EGameMode::ePaused: // Paused

		// When the game is paused, all user to rotate the camera by holding the right mouse button
		if(m_bMouseRightButtonDown)
		{
			if(lLastX)
			{
				g_pCamera->yaw(static_cast<float>(lLastX));
			}
			if(lLastY)
			{
				g_pCamera->pitch(static_cast<float>(lLastY));
			}
		}
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onMouseAttributesChanged
// Desc: Mouse attributes changed
//---------------------------------------------------------------------------
void CInput::onMouseAttributesChanged()
{
}

//---------------------------------------------------------------------------
// Name: onMouseMovementRelative
// Desc: Mouse movement data is relative to the last mouse position
//---------------------------------------------------------------------------
void CInput::onMouseMovementRelative()
{
	// Transition state of mouse buttons
	switch(m_oRawInput.data.mouse.usButtonFlags)
	{
	case RI_MOUSE_LEFT_BUTTON_DOWN: // Left button is down
		onMouseLeftButtonDown();
		break;

	case RI_MOUSE_LEFT_BUTTON_UP: // Left button is up
		onMouseLeftButtonUp();
		break;

	case RI_MOUSE_RIGHT_BUTTON_DOWN: // Right button is down
		onMouseRightButtonDown();
		break;

	case RI_MOUSE_RIGHT_BUTTON_UP: // Right button is up
		onMouseRightButtonUp();
		break;

	case RI_MOUSE_MIDDLE_BUTTON_DOWN: // Middle button is down
		onMouseMiddleButtonDown();
		break;

	case RI_MOUSE_MIDDLE_BUTTON_UP: // Middle button is up
		break;

	case RI_MOUSE_WHEEL: // Mouse wheel
		onMouseWheel(static_cast<short>(m_oRawInput.data.mouse.usButtonData));
		break;
	}

	onMouseMove(m_oRawInput.data.mouse.lLastX, m_oRawInput.data.mouse.lLastY);
}

//---------------------------------------------------------------------------
// Name: onMouseMovementAbsolute
// Desc: 
//---------------------------------------------------------------------------
void CInput::onMouseMovementAbsolute()
{
}

//---------------------------------------------------------------------------
// Name: onEscapeKeyDown
// Desc: Escape is down
//---------------------------------------------------------------------------
void CInput::onEscapeKeyDown()
{
	//g_pMainFrame->onClose(); // Close the application

	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onEscapeKeyDown
// Desc: Escape is down
//---------------------------------------------------------------------------
void CInput::onEscapeKeyUp()
{
	g_pMainFrame->onClose(); // Close the application

	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onPauseKeyDown
// Desc: eGame_Mode_Paused key is down
//---------------------------------------------------------------------------
void CInput::onPauseKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		g_pGame->pauseOrResume();
		break;

	case EGameMode::ePaused: // Paused
		g_pGame->pauseOrResume();
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onPrintKeyDown
// Desc: Print screen key is down
//---------------------------------------------------------------------------
void CInput::onPrintKeyDown()
{
	g_pGame->printScreen();
}

//---------------------------------------------------------------------------
// Name: onShiftKeyDown
// Desc: Shift key is down
//---------------------------------------------------------------------------
void CInput::onShiftKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		switch(m_oRawInput.data.keyboard.MakeCode) // Corresponding left/right key down
		{
		case 0x2A: // Left shift key
			onLeftShiftKeyDown();
			break;

		case 0x36: // Right shift key
			break;
		}
	}
}

//---------------------------------------------------------------------------
// Name: onShiftKeyUp
// Desc: Shift key is up
//---------------------------------------------------------------------------
void CInput::onShiftKeyUp()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		switch(m_oRawInput.data.keyboard.MakeCode)
		{
		case 0x2A: // Left shift key
			onLeftShiftKeyUp();
			break;

		case 0x36: // Right shift key
			break;
		}
	}
}

//---------------------------------------------------------------------------
// Name: onLeftShiftKeyDown
// Desc: Left shift key is down
//---------------------------------------------------------------------------
void CInput::onLeftShiftKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		m_bLeftShiftKeyDown = true;
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onLeftShiftKeyUp
// Desc: Left shift key is up
//---------------------------------------------------------------------------
void CInput::onLeftShiftKeyUp()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		m_bLeftShiftKeyDown = false;
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onRightShiftKeyDown
// Desc: Right shift key is down
//---------------------------------------------------------------------------
void CInput::onRightShiftKeyDown()
{
}

//---------------------------------------------------------------------------
// Name: onLeftControlKeyDown
// Desc: Left control key is down
//---------------------------------------------------------------------------
void CInput::onLeftControlKeyDown()
{

}

//---------------------------------------------------------------------------
// Name: onRightControlKeyDown
// Desc: Right control key is down
//---------------------------------------------------------------------------
void CInput::onRightControlKeyDown()
{
}

//---------------------------------------------------------------------------
// Name: onUpKeyDown
// Desc: Up key is down
//---------------------------------------------------------------------------
void CInput::onUpKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		if(m_bLeftShiftKeyDown) // Shift key is down which implies user is running
			g_pCamera->walk(g_pMath->getTimeDelta() * RUN_SPEED);
		else
			g_pCamera->walk(g_pMath->getTimeDelta() * WALK_SPEED);
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onDownKeyDown
// Desc: Down key is down
//---------------------------------------------------------------------------
void CInput::onDownKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		g_pCamera->walk(-g_pMath->getTimeDelta() * WALK_SPEED);
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onLeftKeyDown
// Desc: Left key is down
//---------------------------------------------------------------------------
void CInput::onLeftKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		g_pCamera->strafe(-g_pMath->getTimeDelta() * STRAFE_SPEED);
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onRightKeyDown
// Desc: Right key is down
//---------------------------------------------------------------------------
void CInput::onRightKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		g_pCamera->strafe(g_pMath->getTimeDelta() * STRAFE_SPEED);
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onEnterKeyDown
// Desc: Enter key is down
//---------------------------------------------------------------------------
void CInput::onEnterKeyDown()
{
	switch(g_pGame->getMode())
	{
	case EGameMode::ePlaying: // Gaming
		break;

	case EGameMode::ePaused: // Paused
		break;

	case EGameMode::eMenu: // Menu
		break;
	}
}

//---------------------------------------------------------------------------
// Name: on1KeyDown
// Desc: 1 key is down
//---------------------------------------------------------------------------
void CInput::on1KeyDown()
{
}

//---------------------------------------------------------------------------
// Name: on2KeyDown
// Desc: 2 key is down
//---------------------------------------------------------------------------
void CInput::on2KeyDown()
{
}

//---------------------------------------------------------------------------
// Name: on3KeyDown
// Desc: 3 key is down
//---------------------------------------------------------------------------
void CInput::on3KeyDown()
{
}

//---------------------------------------------------------------------------
// Name: on4KeyDown
// Desc: 4 key is down
//---------------------------------------------------------------------------
void CInput::on4KeyDown()
{
}

//---------------------------------------------------------------------------
// Name: centerCursor
// Desc: Center the cursor to the client area
//---------------------------------------------------------------------------
void CInput::centerCursor(HWND hWnd)
{
	// Get the coordinates of the client area
	::GetClientRect(hWnd, &m_oClientRect);

	m_oCursorScreenCoord.x = m_oClientRect.right / 2;
	m_oCursorScreenCoord.y = m_oClientRect.bottom / 2;

	// Convert client coordinates to screen coordinates
	::ClientToScreen(hWnd, &m_oCursorScreenCoord);

	// Set the cursor position
	::SetCursorPos(m_oCursorScreenCoord.x, m_oCursorScreenCoord.y);
}

//---------------------------------------------------------------------------
// Name: showCursor
// Desc: Show cursor
//---------------------------------------------------------------------------
void CInput::showCursor(BOOL bShowCursor)
{
	::ShowCursor(bShowCursor);
}

//---------------------------------------------------------------------------
// Name: disableAllInputs
// Desc: Disable all the inputs
//---------------------------------------------------------------------------
BOOL CInput::disableAllInputs(BOOL bDisableAllInputs)
{
	if(bDisableAllInputs) // Disable all inputs
		return (m_bDisableAllInputs ? TRUE : FALSE);
	else // Enable all inputs
		return (m_bDisableAllInputs ? FALSE : TRUE);
}

//---------------------------------------------------------------------------
// Name: disableKeyboardInput
// Desc: Disable keyboard input
//---------------------------------------------------------------------------
BOOL CInput::disableKeyboardInput(BOOL bDisableKeyboardInput)
{
	if(bDisableKeyboardInput) // Disable keyboard input
		return (m_bDisableKeyboardInput ? TRUE : FALSE);
	else // Enable keyboard input
		return (m_bDisableKeyboardInput ? FALSE : TRUE);
}

//---------------------------------------------------------------------------
// Name: disableMouseInput
// Desc: Disable mouse input
//---------------------------------------------------------------------------
BOOL CInput::disableMouseInput(BOOL bDisableMouseInput)
{
	if(bDisableMouseInput) // Disable mouse input
		return (m_bDisableMouseInput ? TRUE : FALSE);
	else // Enable mouse input
		return (m_bDisableMouseInput ? FALSE : TRUE);
}

CInput g_oInput;
CInput *g_pInput = &g_oInput;