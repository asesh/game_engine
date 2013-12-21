// HUD.cpp: Implementation of heads-up display
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "HUD.h"

//------------------------------------------------------------------
// Name: CHUD
// Desc: Default constructor
//------------------------------------------------------------------
CHUD::CHUD()
{
	m_bShowOptions = FALSE; // Set show options dialog box to false
}

//------------------------------------------------------------------
// Name: ~CHUD
// Desc: Destructor
//------------------------------------------------------------------
CHUD::~CHUD()
{
}

//------------------------------------------------------------------
// Name: showSettingsMenu
// Desc: Show the game engine settings menu
//------------------------------------------------------------------
void CHUD::showSettingsMenu(float fSeconds)
{
	// Check to see if the user has initiated to show the settings window
	if(m_bShowOptions)
	{
	}

	//static float fTimer, fScaleX, fScaleY; // Timer and scaling values
	//static BOOL bMenuAnimationEnded = TRUE, bShowOptions, bInitMenuOption = TRUE, bCloseMenuOption, bSubMenuActive; // Signals
	//static DWORD dwActiveTextColor; // Active text color of the menu

	//RECT oScreenRect;
	//RECT oTextMenuClientRect = {250, 100, 600, 200};
	//D3DXVECTOR3 oD3DXVecCenter(256.0f, 256.0f, 0.0f);

	//// Retrieve the input command from the user for displaying/hiding option menu
	//SHORT sKeyState = ::GetKeyState(VK_F2);
	//if(sKeyState & 0x80)
	//{
	//	// It has been commanded to show the option menu
	//	if(bInitMenuOption == TRUE && bMenuAnimationEnded == TRUE)
	//	{
	//		bMenuAnimationEnded = FALSE; // Signal that the animation has not yet completed
	//		bShowOptions = TRUE;
	//	}

	//	// It has been commanded to close the option menu
	//	else if(bMenuAnimationEnded == TRUE && bInitMenuOption == FALSE)
	//	{
	//		bCloseMenuOption = TRUE; // Signal to close the option window
	//		bMenuAnimationEnded = FALSE; // Signal that the animation has not yet completed
	//	}
	//}

	//// Set identity matrix to the world transformation matrix
	//::D3DXMatrixIdentity(&m_oD3DXWorldMat);

	//// Animate the menu on initialization
	//// Check if the menu has not been completely initialized and the animation has ended
	//if(bInitMenuOption == TRUE && bMenuAnimationEnded == FALSE)
	//{
	//	fTimer += fSeconds; // Increment timer

	//	// Increase the size of the menu
	//	if(fScaleX >= 0.0f && fScaleX < 1.0f)
	//	{
	//		// Check to see if 10 milliseconds have elapsed
	//		if(fTimer >= 0.01f)
	//		{
	//			fScaleX = fScaleY += 0.1f; // Increment the X and Y scaling value
	//			m_oD3DXWorldMat._11 = fScaleX; m_oD3DXWorldMat._22 = fScaleY; // Assign the incremented values to world matrix
	//			fTimer = 0.0f; // Reset timer to 0
	//		}
	//	}

	//	// If the maximum size of the menu has reached then end the animation
	//	if(fScaleX >= 1.0f)
	//	{
	//		bMenuAnimationEnded = TRUE; // Signal that the animation has completed
	//		bInitMenuOption = FALSE; // Signal that the menu has been completely initialized
	//		fScaleX = fScaleY = 1.0f; // Set the X and Y scaling values to 1--original size of texture
	//		fTimer = 0.0f; // Reset timer to 0
	//	}
	//}

	//// Animate the menu on closing
	//else if(bCloseMenuOption == TRUE && bMenuAnimationEnded == FALSE)
	//{
	//	fTimer += fSeconds; // Increment timer

	//	// Scale down the menu
	//	if(fScaleX > 0.0f)
	//	{
	//		// Check to see if 10 milliseconds have elapsed
	//		if(fTimer >= 0.01f)
	//		{
	//			fScaleY = fScaleX -= 0.1f; // Decrement the X and Y scaling values
	//			m_oD3DXWorldMat._11 = fScaleX; m_oD3DXWorldMat._22 = fScaleY; // Assign the decremented values to world matrix
	//			fTimer = 0.0f; // Reset timer to 0
	//		}
	//	}

	//	// If the minimum size of the menu has reached then end the animation
	//	if(fScaleX <= 0.0f)
	//	{
	//		bMenuAnimationEnded = bInitMenuOption = TRUE; // Signal that the animation has completed
	//		bShowOptions = FALSE; // Signal not to show the options anymore
	//		fScaleX = fScaleY = 0.0f; // Set the X and Y scaling values to 0
	//		fTimer = 0.0f; // Reset timer to 0
	//	}
	//}

	//// Display the options
	//if(bShowOptions)
	//{
	//	// If the menu has already been completely initialized and animation completed then display the contents
	//	if(bInitMenuOption == FALSE && bMenuAnimationEnded == TRUE)
	//	{
	//		/*m_pD3DXSmallFont->DrawText(m_pD3DXSprite, L"Aseshsoft Game Engine Menu", -1, &oTextMenuClientRect, 0, 0xFFFF0000);

	//		// Display the other contents in the menu
	//		::SetRect(&oTextMenuClientRect, oTextMenuClientRect.left -= 10, oTextMenuClientRect.top += 30, oTextMenuClientRect.right, oTextMenuClientRect.bottom += 30);
	//		m_pD3DXSmallFont->DrawText(m_pD3DXSprite, L"Lighting Effects", -1, &oTextMenuClientRect, 0, 0xFFFFFF00);
	//		::SetRect(&oTextMenuClientRect, oTextMenuClientRect.left, oTextMenuClientRect.top + 30, oTextMenuClientRect.right, oTextMenuClientRect.bottom += 30);
	//		m_pD3DXSmallFont->DrawText(m_pD3DXSprite, L"Fill Modes", -1, &oTextMenuClientRect, 0, 0xFFFFFF00);
	//		::SetRect(&oTextMenuClientRect, oTextMenuClientRect.left, oTextMenuClientRect.top += 30, oTextMenuClientRect.right, oTextMenuClientRect.bottom += 30);
	//		m_pD3DXSmallFont->DrawText(m_pD3DXSprite, L"Virtual World Mode", -1, &oTextMenuClientRect, 0, 0xFFFFFF00);
	//		::SetRect(&oTextMenuClientRect, oTextMenuClientRect.left, oTextMenuClientRect.top += 30, oTextMenuClientRect.right, oTextMenuClientRect.bottom += 30);
	//		m_pD3DXSmallFont->DrawText(m_pD3DXSprite, L"Cheat Modes", -1, &oTextMenuClientRect, 0, 0xFFFFFF00);*/
	//	}

	//	// World transformation for the game engine menu
	//	m_oD3DXWorldMat._41 = 400.0f; m_oD3DXWorldMat._42 = 300.0f; // Translation
	//	m_pD3DXSprite->SetTransform(&m_oD3DXWorldMat);

	//	// Render the menu texture
	//	//m_pD3DXSprite->Draw(m_pD3DEngineMenuTexture, NULL, &oD3DXVecCenter, NULL, 0xFFFFFFFF);

	//	// Reset sprite transformation matrix because it will affect the upcoming list of batched sprites
	//	::D3DXMatrixIdentity(&m_oD3DXWorldMat);
	//	m_pD3DXSprite->SetTransform(&m_oD3DXWorldMat);
	//}
}