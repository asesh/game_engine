// RenderToTexture.cpp: Implementation of render-to-texture
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "RenderToTexture.h"

//---------------------------------------------------------------------------
// Name: CRenderToTexture
// Desc: Default constructor
//---------------------------------------------------------------------------
CRenderToTexture::CRenderToTexture()
{
	m_pD3DRenderTargetTexture = nullptr;

	m_pD3DShaderResourceView = nullptr;

	m_pD3DRenderTargetView = nullptr;

	m_pFullscreeenQuad = nullptr;

	m_hResult = S_OK;
}

//---------------------------------------------------------------------------
// Name: CRenderToTexture
// Desc: Constructor
//---------------------------------------------------------------------------
CRenderToTexture::CRenderToTexture(UINT unTextureWidth, UINT unTextureHeight, DXGI_FORMAT oDXGITextureFormat)
{
	ASSIGN_COM(create(unTextureWidth, unTextureHeight, oDXGITextureFormat));
}

//---------------------------------------------------------------------------
// Name: ~CRenderToTexture
// Desc: Destructor
//---------------------------------------------------------------------------
CRenderToTexture::~CRenderToTexture()
{
	DELETE_FREE(m_pFullscreeenQuad);

	FREE_COM(m_pD3DRenderTargetTexture);

	FREE_COM(m_pD3DShaderResourceView);

	FREE_COM(m_pD3DRenderTargetView);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a render texture that by default matches client area's width 
//		 and height
//---------------------------------------------------------------------------
HRESULT CRenderToTexture::create()
{
	RETURN_COM(create(g_pMainFrame->getWindowWidth(), g_pMainFrame->getWindowHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT));
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a render texture
//---------------------------------------------------------------------------
HRESULT CRenderToTexture::create(UINT unTextureWidth, UINT unTextureHeight, DXGI_FORMAT oDXGITextureFormat)
{
	D3D11_TEXTURE2D_DESC oRenderTargetTexture = {0};
	oRenderTargetTexture.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // Bind flags
	oRenderTargetTexture.Format = oDXGITextureFormat; // Texture format
	oRenderTargetTexture.Height = unTextureHeight; // Texture height
	oRenderTargetTexture.Width = unTextureWidth; // Texture width
	oRenderTargetTexture.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU
	oRenderTargetTexture.MipLevels = 1;
	oRenderTargetTexture.ArraySize = 1;
	oRenderTargetTexture.SampleDesc.Count = 1;

	// Create the render texture
	CHECK_COM(D3D_DEVICE->CreateTexture2D(&oRenderTargetTexture, nullptr, &m_pD3DRenderTargetTexture));

	// Render-target view description
	D3D11_RENDER_TARGET_VIEW_DESC oD3DRenderTargetViewDesc;
	::memset(&oD3DRenderTargetViewDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	oD3DRenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D texture
	oD3DRenderTargetViewDesc.Format = oDXGITextureFormat; // Texture format

	// Create the render-target view
	CHECK_COM(D3D_DEVICE->CreateRenderTargetView(m_pD3DRenderTargetTexture, &oD3DRenderTargetViewDesc, &m_pD3DRenderTargetView));

	// Shader resource view description
	D3D11_SHADER_RESOURCE_VIEW_DESC oD3DShaderResourceViewDesc;
	::memset(&oD3DShaderResourceViewDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	oD3DShaderResourceViewDesc.Format = oDXGITextureFormat; // Texture format
	oD3DShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	oD3DShaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view
	CHECK_COM(D3D_DEVICE->CreateShaderResourceView(m_pD3DRenderTargetTexture, &oD3DShaderResourceViewDesc, &m_pD3DShaderResourceView));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: get
// Desc: Get the shader resource view of this render texture
//---------------------------------------------------------------------------
ID3D11ShaderResourceView *CRenderToTexture::get() const
{
	return m_pD3DShaderResourceView;
}

//---------------------------------------------------------------------------
// Name: clear
// Desc: Clear the render texture
//---------------------------------------------------------------------------
HRESULT CRenderToTexture::clear(ID3D11DeviceContext *pD3DDeviceContext, ID3D11DepthStencilView *pD3DDepthStencilView, float fRenderTargetClearColor[4])
{
	pD3DDeviceContext->ClearRenderTargetView(m_pD3DRenderTargetView, fRenderTargetClearColor); // Clear render target
	pD3DDeviceContext->ClearDepthStencilView(pD3DDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0); // Clear depth-stencil

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setRenderTarget
// Desc: Set the render texture as the current render target
//---------------------------------------------------------------------------
HRESULT CRenderToTexture::setRenderTarget(ID3D11DeviceContext *pD3DDeviceContext, ID3D11DepthStencilView *pD3DDepthStencilView)
{
	pD3DDeviceContext->OMSetRenderTargets(1, &m_pD3DRenderTargetView, nullptr);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: render
// Desc: Render the texture
//---------------------------------------------------------------------------
HRESULT CRenderToTexture::render(int nXPosition, int nYPosition)
{
	return S_OK;
}