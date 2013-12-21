// D2DGraphics.h: 
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef D2DGRAPHICS_H
#define D2DGRAPHICS_H

#include <d2d1.h>
#include <dwrite.h>

// Forward declarations
class CFont;
class CPlanePrimitive;

// CD2DGraphics class
class CD2DGraphics
{
public: // Public methods
	CD2DGraphics(); // Default constructor
	~CD2DGraphics(); // Destructor

	HRESULT createDevice(); // Create device
	HRESULT createRenderTarget(); // Create render target
	HRESULT createSolidColorBrushes(); // Create solid color brushes
	HRESULT createFonts(); // Create fonts
	HRESULT createGeometries(); // Create geometries

	IDXGISurface1 *&getRenderingSurface(); // Will return an IDXGISurface as a reference
	ID2D1RenderTarget *getRenderTarget() const; // Returns a handle to the D2D render target
	IDWriteFactory *getDWriteFactory() const; // 
	ID2D1SolidColorBrush *getDefSolidColorBrush() const;

	HRESULT initCoreEngine(); // Initialize core graphics engine
	HRESULT initGameEngine(); // Intialize the game engine

	HRESULT render(); // Render 2D graphics
	HRESULT renderMenu(); // Render menu

	void present(); // Present the back buffer onto the screen

private: // Private attributes
	IDXGISurface1 *m_pDXGISharedSurface;

	IDXGIKeyedMutex *m_pDXGIScreenAlignedQuadKeyedMutex;

	ID3D10Device1 *m_pD3DDevice;

	ID3D11Texture2D *m_pD3DSharedTexture; // Shared texture that Direct3D 10.1 will render onto

	ID3D11ShaderResourceView *m_pD3DScreenAlignedSRV; // SRV 

	ID2D1Factory *m_pD2DFactory; // Factory

	ID2D1RectangleGeometry *m_pD2DRectGeometry; // Rectangle geometry
	ID2D1RoundedRectangleGeometry *m_pD2DRoundedRectGeometry; // Rounded rectangle geometry

	ID2D1RenderTarget *m_pD2DRT; // Render target

	ID2D1Bitmap *m_pD2DBitmap;

	ID2D1SolidColorBrush *m_pD2DDefSolidColorBrush, *m_pD2DBlackColorBrush, *m_pD2DRedColorBrush; // Sold color brushes

	ID2D1BitmapBrush *m_pD2DRockBrush, *m_pD2DWoodBrush; // Bitmap brushes

	IDWriteFactory *m_pDWriteFactory; // DWrite factory

	D2D1_RECT_F m_oD2DAreaRect; // Will hold the size and position of the area in which the text is drawn

	D2D1_SIZE_F m_oD2DRTSize; // Will hold the size of the render target

	D2D1_COLOR_F m_oD2DDrawingAreaColor; // Will hold the drawing area color

	CFont *m_pVerdanaFont;

	CPlanePrimitive *m_pD2DScreenAlignedQuad;

	HRESULT m_hResult;
};

extern CD2DGraphics *g_pD2DGraphics;

#endif // D2DGRAPHICS_H