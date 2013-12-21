// RenderToTexture.h: Implementation of render-to-texture
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef RENDERTOTEXTURE_H
#define RENDERTOTEXTURE_H

// CRenderToTexture class
class CRenderToTexture
{
public: // Public methods
	CRenderToTexture(); // Default constructor
	CRenderToTexture(UINT uiTextureWidth, UINT uiTextureHeight, DXGI_FORMAT oDXGITextureFormat); // Constructor
	virtual ~CRenderToTexture(); // Destructor

	virtual HRESULT create(); // Create a render texture that matches the client area's width and height
	virtual HRESULT create(UINT unTextureWidth, UINT unTextureHeight, DXGI_FORMAT oDXGITextureFormat); // Create render texture

	virtual ID3D11ShaderResourceView *get() const; // Get the shader resource view of this render texture

	virtual HRESULT clear(ID3D11DeviceContext *pD3DDeviceContext, ID3D11DepthStencilView *pD3DDepthStencilView, float fRenderTargetClearColor[4]); // Clear the render texture

	virtual HRESULT setRenderTarget(ID3D11DeviceContext *pD3DDeviceContext, ID3D11DepthStencilView *pD3DDepthStencilView); // Set the render texture as the current render target

	virtual HRESULT render(int nXPosition, int nYPosition); // Render the texture

protected: // Protected attributes
	ID3D11Texture2D *m_pD3DRenderTargetTexture; // Texture onto which we will render onto

	ID3D11RenderTargetView *m_pD3DRenderTargetView; // 

	ID3D11ShaderResourceView *m_pD3DShaderResourceView; // 

	CFullscreenQuadPrimitive *m_pFullscreeenQuad; // Quad onto which we will render our texture

	UINT m_unRenderToTextureWidth, m_unRenderToTextureHeight; // Width and height of the current render texture

	DXGI_FORMAT m_oDXGITextureFormat; // Format of the current render texture

	//D3D11_TEXTURE3D_DESC m_oD3DTexture3DDesc;

	HRESULT m_hResult;
};

#endif // RENDERTOTEXTURE_H