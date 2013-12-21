// NormalMapShader.h: Interface of normal mapping
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef NORMALMAPSHADER_H
#define NORMALMAPSHADER_H

#include "Shader.h"

// CNormalMapShader class
class CNormalMapShader : public CShader
{
public:
	CNormalMapShader(); // Default constructor
	virtual ~CNormalMapShader(); // Destructor

	virtual HRESULT create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, const std::wstring oPrimitiveTexture, const std::wstring oNormalMapTexture, ID3D11Device *pD3DDevice); // Create a normal map shader from the specified file

	virtual HRESULT updateConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext);

	virtual HRESULT set(ID3D11DeviceContext *pD3DDeviceContext); // Set/bind the shader and it's corresponding resources

private:
	ID3DX11EffectShaderResourceVariable *m_pD3DXEffectNormalMapSRV; // Normal map shader resource variable

	//CTexture2D *m_pPrimitiveTexture, *m_pNormalMapTexture; // Primitive's texture and it's corresponding normal map
	CTexture2DArray *m_pTextureArray; // Primitive's texture and it's corresponding normal map
};

extern CNormalMapShader *g_pNormalMapShader;

#endif // NORMALMAPSHADER_H