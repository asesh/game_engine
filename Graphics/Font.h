// Font.h: 
// Copyright (C) 2010-2011 Asesh Shrestha. All rights reserved

#ifndef FONT_H
#define FONT_H

// CFont class
class CFont
{
public:
	CFont(); // Default constructor
	CFont(const std::wstring oFontNameString); // Constructor
	~CFont(); // Destructor

	HRESULT init(); // Initialize the font system

	// Font creation methods
	//
	HRESULT create();
	HRESULT create(const std::wstring &rFontNameString); // 
	HRESULT create(const std::wstring &rFontNameString, float fFontSize); // 
	HRESULT change(const std::wstring &rFontNameString); // Change the font
	//
	// End font creation methods

	HRESULT drawText(const std::wstring &rFontNameString, float fXCoord, float fYCoord); // Writes data onto the screen

private:
	IDWriteTextFormat *m_pDWriteTextFormat; // DirectWrite text format

	D2D1_RECT_F m_oLayoutRectF;

	float m_fDefaultFontSize, m_fSpecifiedFontSize; // Will hold the default font size

	WCHAR *m_pszLocaleName; // Locale name

	HRESULT m_hResult; // Will be used for checking errors
};

//extern CFont *g_pFont; // Externed class pointer

#endif // FONT_H