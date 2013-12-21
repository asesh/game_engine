// D2DGraphics.cpp: Implementation of CD2DGraphics class
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "../MainFrame/MainFrame.h"
#include "ConstantBuffer.h"

#include <d2d1.h> // Direct2D

#include <DWrite.h> // DirectWrite

#include "Font.h"
#include "D2DGraphics.h"

//---------------------------------------------------------------------------
// Name: CD2DGraphics
// Desc: Default constructor
//---------------------------------------------------------------------------
CD2DGraphics::CD2DGraphics()
{
	m_pDXGISharedSurface = nullptr;

	m_pDXGIScreenAlignedQuadKeyedMutex = nullptr;

	m_pD3DDevice = nullptr;

	m_pD3DSharedTexture = nullptr;

	m_pD2DFactory = nullptr;

	m_pD2DRT = nullptr;

	m_pD2DDefSolidColorBrush = m_pD2DBlackColorBrush = m_pD2DRedColorBrush = nullptr;

	m_pD2DRectGeometry = nullptr;
	m_pD2DRoundedRectGeometry = nullptr;

	m_pDWriteFactory = nullptr;

	m_pVerdanaFont = nullptr;

	m_pD2DScreenAlignedQuad = nullptr;

	::memset(&m_oD2DDrawingAreaColor, 0, sizeof(D2D1_COLOR_F)); // Set drawing area color to black
}

//---------------------------------------------------------------------------
// Name: ~CD2DGraphics
// Desc: Destructor
//---------------------------------------------------------------------------
CD2DGraphics::~CD2DGraphics()
{
	DELETE_FREE(m_pVerdanaFont);

	DELETE_FREE(m_pD2DScreenAlignedQuad);

	FREE_COM(m_pDWriteFactory);

	FREE_COM(m_pD2DRectGeometry);
	FREE_COM(m_pD2DRoundedRectGeometry);

	FREE_COM(m_pD2DDefSolidColorBrush);
	FREE_COM(m_pD2DBlackColorBrush);
	FREE_COM(m_pD2DRedColorBrush);

	FREE_COM(m_pD2DRT);

	FREE_COM(m_pD2DFactory);

	FREE_COM(m_pDXGIScreenAlignedQuadKeyedMutex);

	FREE_COM(m_pDXGISharedSurface);
}

//---------------------------------------------------------------------------
// Name: createDevice
// Desc: Create device
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::createDevice()
{
	UINT uiDeviceCreationFlag;
	//ID3D11Texture2D *pOffscreenTexture;

#ifdef _DEBUG // Debug version

	uiDeviceCreationFlag = D3D10_CREATE_DEVICE_DEBUG | D3D10_CREATE_DEVICE_BGRA_SUPPORT;

#else // Release version

	uiDeviceCreationFlag = D3D10_CREATE_DEVICE_BGRA_SUPPORT;

#endif // _DEBUG

	// Create a Direct3D 10.1 device for Direct2D interop
	CHECK_COM(::D3D10CreateDevice1(g_pD3DGraphics->getAdapter(), 
		D3D10_DRIVER_TYPE_HARDWARE, 
		NULL, 
		uiDeviceCreationFlag, 
		D3D10_FEATURE_LEVEL_10_1, 
		D3D10_1_SDK_VERSION, 
		&m_pD3DDevice));

	//m_pD3DDevice->OMSetRenderTargets(0, NULL, NULL); // Don't bind any views to the pipeline
	m_pD3DDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Direct3D shared texture description
	D3D11_TEXTURE2D_DESC oD3DSharedTextureDesc = {0};
	oD3DSharedTextureDesc.ArraySize = 1;
	oD3DSharedTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // 
	oD3DSharedTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 
	oD3DSharedTextureDesc.Height = g_pMainFrame->getWindowHeight(); // Height
	oD3DSharedTextureDesc.Width = g_pMainFrame->getWindowWidth(); // Width
	oD3DSharedTextureDesc.MipLevels = 1; // 
	oD3DSharedTextureDesc.SampleDesc.Count = 1; // 
	oD3DSharedTextureDesc.Usage = D3D11_USAGE_DEFAULT; // R/W by the GPU
	oD3DSharedTextureDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX; // Allow synchronization

	// Create an offscreen D3D surface for D2D to render the 2D content onto
	CHECK_COM(D3D_DEVICE->CreateTexture2D(&oD3DSharedTextureDesc, NULL, &m_pD3DSharedTexture));

	// Retrieve a handle to an IDXGIKeyedMutex for the shared texture
	CHECK_COM(m_pD3DSharedTexture->QueryInterface(GUID(IDXGIKeyedMutex), reinterpret_cast<void **>(&m_pDXGIScreenAlignedQuadKeyedMutex)));

	// Use the texture to obtain a DXGI surface
	CHECK_COM(m_pD3DSharedTexture->QueryInterface(&m_pDXGISharedSurface));

	// Open a shared resource created from the Direct3D 11 device
	CHECK_COM(m_pD3DDevice->OpenSharedResource(g_pD3DGraphics->getSharedResourceHandle(), GUID(IDXGISurface1), reinterpret_cast<void **>(&m_pDXGISharedSurface)));

	// Retrieve a handle to an IDXGIKeyedMutex interface
	CHECK_COM(m_pDXGISharedSurface->QueryInterface(GUID(IDXGIKeyedMutex), reinterpret_cast<void **>(&m_pDXGIScreenAlignedQuadKeyedMutex)));

	// Use the texture to obtain DXGI surface interface
	//CHECK_COM(m_pDXGISharedSurface->QueryInterface(&m_pDXGISurface));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createRenderTarget
// Desc: Create render target
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::createRenderTarget()
{
	float fDPIX, fDPIY; // Will hold desktop DPI

	D2D1_SIZE_U oD2DRTSize; // Will hold the size of the render target in pixels
	oD2DRTSize.height = g_pMainFrame->getWindowHeight();
	oD2DRTSize.width = g_pMainFrame->getWindowWidth();

	// Create a DWrite factory
	CHECK_COM(::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, GUID(IDWriteFactory), reinterpret_cast<IUnknown **>(&m_pDWriteFactory)));

	D2D1_FACTORY_OPTIONS oD2DFactoryOptions;
	::memset(&oD2DFactoryOptions, 0, sizeof(D2D1_FACTORY_OPTIONS));

#ifdef _DEBUG // Debug version

	oD2DFactoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

#endif // _DEBUG

	// Create a D2D factory object
	CHECK_COM(::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, GUID(ID2D1Factory), &oD2DFactoryOptions, reinterpret_cast<void **>(&m_pD2DFactory)));

	// Retrieve the current desktop DPI
	m_pD2DFactory->GetDesktopDpi(&fDPIX, &fDPIY);

	// Render target properties
	D2D1_RENDER_TARGET_PROPERTIES oD2DRTProps;
	::memset(&oD2DRTProps, 0, sizeof(D2D1_RENDER_TARGET_PROPERTIES));
	oD2DRTProps.type = D2D1_RENDER_TARGET_TYPE_HARDWARE; // Hardware rendering
	oD2DRTProps.pixelFormat.format = DXGI_FORMAT_UNKNOWN; // Use the DXGI render target surface format
	oD2DRTProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED; // Alpha value premultiplied
	oD2DRTProps.usage = D2D1_RENDER_TARGET_USAGE_NONE; // 
	oD2DRTProps.minLevel = D2D1_FEATURE_LEVEL_10; // DX10 video card required
	oD2DRTProps.dpiX = fDPIX; // Horizontal DPI of the desktop
	oD2DRTProps.dpiY = fDPIY; // Vertical DPI of the desktop

	// Create a render target that draws to a DXGI surface
	CHECK_COM(m_pD2DFactory->CreateDxgiSurfaceRenderTarget(m_pDXGISharedSurface, oD2DRTProps, &m_pD2DRT));

	SAFE_FREE_COM(m_pDXGISharedSurface); // Don't need it anymore

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createSolidColorBrushes
// Desc: Create solid color brushes
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::createSolidColorBrushes()
{
	//D2D1_COLOR_F oD2DBrushColor = {1.0f, 1.0f, 1.0f, 1.0f}; // White color

	CHECK_COM(m_pD2DRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &m_pD2DDefSolidColorBrush)); // Default red solid color brush
	CHECK_COM(m_pD2DRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &m_pD2DBlackColorBrush)); // Black solid color brush

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createFonts
// Desc: Create all the required fonts
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::createFonts()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createGeometries
// Desc: Create geometries
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::createGeometries()
{
	D2D1_RECT_F oD2DRect;
	D2D1_ROUNDED_RECT oD2DRoundedRect;

	CHECK_COM(m_pD2DFactory->CreateRectangleGeometry(oD2DRect, &m_pD2DRectGeometry));
	CHECK_COM(m_pD2DFactory->CreateRoundedRectangleGeometry(oD2DRoundedRect, &m_pD2DRoundedRectGeometry));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getRenderingSurface
// Desc: Returns a reference to the rendering surface
//---------------------------------------------------------------------------
IDXGISurface1 *&CD2DGraphics::getRenderingSurface()
{
	return m_pDXGISharedSurface;
}

//---------------------------------------------------------------------------
// Name: getRenderTarget
// Desc: Returns a handle to the D2D render target
//---------------------------------------------------------------------------
ID2D1RenderTarget *CD2DGraphics::getRenderTarget() const
{
	return m_pD2DRT;
}

//---------------------------------------------------------------------------
// Name: getDWriteFactory
// Desc: Returns a handle to the DirectWrite factory
//---------------------------------------------------------------------------
IDWriteFactory *CD2DGraphics::getDWriteFactory() const
{
	return m_pDWriteFactory;
}

//---------------------------------------------------------------------------
// Name: getDefSolidColorBrush
// Desc: Returns a handle to the default solid color brush
//---------------------------------------------------------------------------
ID2D1SolidColorBrush *CD2DGraphics::getDefSolidColorBrush() const
{
	return m_pD2DDefSolidColorBrush;
}

//---------------------------------------------------------------------------
// Name: initCoreEngine
// Desc: Initialize the core graphics engine
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::initCoreEngine()
{
	CHECK_COM(createDevice());
	CHECK_COM(createRenderTarget());
	CHECK_COM(createGeometries());
	CHECK_COM(createSolidColorBrushes());

	// Create a font which will be used to write data onto the screen
	//m_pVerdanaFont = new CFont();
	//CHECK_COM(m_pVerdanaFont->create(L"Verdana"));

	// Fullscreen quad where all the 2D will be rendered onto
	m_pD2DScreenAlignedQuad = new CPlanePrimitive();
	CHECK_COM(m_pD2DScreenAlignedQuad->create(1, 1));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: initGameEngine
// Desc: Intialize the core game engine graphics
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::initGameEngine()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: render
// Desc: Render 2D graphics
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::render()
{
	// Acquire exclusive rendering access to the texture
	if(FAILED(m_pDXGIScreenAlignedQuadKeyedMutex->AcquireSync(0, 5))) // Wait for about at most 50ms
		return E_FAIL; // The shared resource couldn't be exclusively acquired

	m_pD2DRT->BeginDraw(); // Begin D2D drawing operations

	m_pD2DRT->Clear(D2D1::ColorF(D2D1::ColorF::Black)); // Clear the drawing area to the specified color

	m_pD2DRT->SetTransform(D2D1::Matrix3x2F::Identity()); // Set identity matrix

	g_pD3DGraphics->setSpriteBlendState(IMM_DEV_CONTEXT); // Enable blending for drawing sprites

	//m_pVerdanaFont->drawText(g_pMath->getFPSData(), 10.0f, 10.0f); // Draw FPS data

	// Disable depth buffering so that the screen aligned quad where all the 2D stuff are rendered onto stays screen aligned
	//g_pD3DGraphics->setDisabledDBDSState(IMM_DEV_CONTEXT);

	// Draw 2D plane where all the 2D stuff are drawn
	//g_pTransformMatrices->translateIdentity();
	//g_pTransformMatrices->scaleIdentity();
	//g_pTransformMatrices->rotateIdentity();
	g_pChangesEveryFrameConstBuffer->m_oWorldMatrix.setIdentity();// =  g_pTransformMatrices->calculateWorldTransform(); // Combine world transformation matrices
	//m_pD2DScreenAlignedQuad->draw(g_pGlobalLightingShader, IMM_DEV_CONTEXT);

	// Re-enable default depth-stencil state
	//g_pD3DGraphics->setDefaultDSState(IMM_DEV_CONTEXT);

	g_pD3DGraphics->setDefaultBlendState(IMM_DEV_CONTEXT); // Disable blending

	m_hResult = m_pD2DRT->EndDraw(); // End D2D drawing operations

	m_pDXGIScreenAlignedQuadKeyedMutex->ReleaseSync(0); // Release exclusive access to the texture

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: renderMenu
// Desc: Render the menu
//---------------------------------------------------------------------------
HRESULT CD2DGraphics::renderMenu()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: present
// Desc: Present the back buffer onto the screen
//---------------------------------------------------------------------------
void CD2DGraphics::present()
{
	//m_pD2DScreenAlignedQuad->draw(g_pScreenAlignedQuadShader, IMM_DEV_CONTEXT);
	//m_pDXGISwapChain->Present(0, 0);
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

CD2DGraphics m_oD2DGraphics;
CD2DGraphics *g_pD2DGraphics = &m_oD2DGraphics;