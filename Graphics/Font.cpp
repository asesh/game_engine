// Font.cpp : Implementation of CFont class for creating and displaying text
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "D2DGraphics.h"
#include "Font.h"

//---------------------------------------------------------------------------
// Name: CFont
// Desc: Default constructor
//---------------------------------------------------------------------------
CFont::CFont()
{
	m_pDWriteTextFormat = nullptr;

	m_fDefaultFontSize = 15.0f; // Set default font size

	m_pszLocaleName = L"en-us"; // English
}

//---------------------------------------------------------------------------
// Name: CFont
// Desc: Parameterized constructor
//---------------------------------------------------------------------------
CFont::CFont(const std::wstring oFontNameString)
{
	m_pDWriteTextFormat = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CFont
// Desc: Destructor
//---------------------------------------------------------------------------
CFont::~CFont()
{
	FREE_COM(m_pDWriteTextFormat);
}

//---------------------------------------------------------------------------
// Name: init
// Desc: Initialize the font system
//---------------------------------------------------------------------------
HRESULT CFont::init()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create
//---------------------------------------------------------------------------
HRESULT CFont::create()
{
	// Create a text format for text layout
	CHECK_COM(g_pD2DGraphics->getDWriteFactory()->CreateTextFormat(L"Verdana", // Font name
		NULL, // Font collection
		DWRITE_FONT_WEIGHT_THIN, // Thin font weight
		DWRITE_FONT_STYLE_NORMAL, // Normal font style
		DWRITE_FONT_STRETCH_NORMAL, // Normal font stretch
		m_fDefaultFontSize, // Default font size
		m_pszLocaleName, // US locale
		&m_pDWriteTextFormat));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create
//---------------------------------------------------------------------------
HRESULT CFont::create(const std::wstring &rFontNameString)
{
	// Create a text format for text layout
	CHECK_COM(g_pD2DGraphics->getDWriteFactory()->CreateTextFormat(rFontNameString.data(), // Font name
		NULL, // Font collection
		DWRITE_FONT_WEIGHT_THIN, // Thin font weight
		DWRITE_FONT_STYLE_NORMAL, // Normal font style
		DWRITE_FONT_STRETCH_NORMAL, // Normal font stretch
		m_fDefaultFontSize, // Default font size
		m_pszLocaleName, // US locale
		&m_pDWriteTextFormat));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a specified font
//---------------------------------------------------------------------------
HRESULT CFont::create(const std::wstring &rFontNameString, float fFontSize)
{
	m_fSpecifiedFontSize = fFontSize; // The specified font size by the user

	// Create a text format for text layout
	CHECK_COM(g_pD2DGraphics->getDWriteFactory()->CreateTextFormat(rFontNameString.data(), // Font name
		NULL, // Font collection
		DWRITE_FONT_WEIGHT_THIN, // Thin font weight
		DWRITE_FONT_STYLE_NORMAL,  // Normal font style
		DWRITE_FONT_STRETCH_NORMAL, // Normal font stretch
		m_fSpecifiedFontSize, // Font size
		m_pszLocaleName, // US locale
		&m_pDWriteTextFormat));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: change
// Desc: Change the current font with a new one
//---------------------------------------------------------------------------
HRESULT CFont::change(const std::wstring &rFontNameString)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: drawText
// Desc: Draw the text onto the window
//---------------------------------------------------------------------------
HRESULT CFont::drawText(const std::wstring &rFontNameString, float fXCoord, float fYCoord)
{
	// Adjust the position of the area in the which the text is drawn
	//g_pD2DGraphics->m_oD2DAreaRect.left = fXCoord; // X coordinate
	//g_pD2DGraphics->m_oD2DAreaRect.top = fYCoord; // Y coordinate

	// Adjust the size of the pixel in which the text is drawn
	//g_pD2DGraphics->m_oD2DAreaRect.right = rFontNameString.length() * m_fSpecifiedFontSize;

	g_pD2DGraphics->getRenderTarget()->DrawText(rFontNameString.data(), // String to draw
		static_cast<UINT>(rFontNameString.length()),  // String length
		m_pDWriteTextFormat, // Text format
		D2D1::RectF(10.0f, 10.0f, 250.0f, 40.0f), // Rectangle holding the size and position of the area in which the text is drawn
		g_pD2DGraphics->getDefSolidColorBrush(), // Default solid color brush
		D2D1_DRAW_TEXT_OPTIONS_CLIP,  // Clip text to the layout rect
		DWRITE_MEASURING_MODE_NATURAL); // 

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//CFont g_oFont;
//CFont *g_pFont = &g_oFont;