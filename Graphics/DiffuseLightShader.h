// DiffuseLightShader.h: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef DIFFUSELIGHTSHADER_H
#define DIFFUSELIGHTSHADER_H

#include "Shader.h"

// CDiffuseLightShader class
class CDiffuseLightShader : public CShader
{
public:
	CDiffuseLightShader(); // Default constructor
	virtual ~CDiffuseLightShader(); // Destructor

	virtual HRESULT create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, const std::wstring oPrimitiveTexture, ID3D11Device *pD3DDevice); // Create a diffuse lighting shader from the specified file

	virtual HRESULT updateConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext);

	virtual HRESULT set(ID3D11DeviceContext *pD3DDeviceContext); // Set/bind the shader and it's corresponding resources

private:
	ID3D11Buffer *m_pD3DDiffuseLightingConstBuffer; // Diffuse lighting constant buffer

	ID3DX11EffectShaderResourceVariable *m_pD3DXShaderResourceVariable; // SRV

	CTexture2D *m_pPrimitiveTexture; // Primitive's texture
};

extern CDiffuseLightShader *g_pDiffuseLightShader;

#endif // DIFFUSELIGHTSHADER_H