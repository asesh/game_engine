// InstanceShader.h: Interface for geometry instancing
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef INSTANCESHADER_H
#define INSTANCESHADER_H

#include "Shader.h"

// Forward declarations
//class CShader;

// CInstanceShader class
class CInstanceShader : public CShader
{
public:
	CInstanceShader(); // Default constructor
	virtual ~CInstanceShader(); // Destructor

	virtual HRESULT create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, UINT uiConstantBufferByteWidth, std::wstring oPrimitiveTexture, ID3D11Device *pD3DDevice); // Create a shader from the specified file

	virtual ID3D11Buffer *getInstanceBuffer() const; // Get the instance buffer

	virtual HRESULT updateConstantBuffer(void *pInstanceConstantBufferData, ID3D11DeviceContext *pD3DDeviceContext); // Update instance constant buffer
	virtual HRESULT updateConstantBuffer(void *pInstanceConstantBufferData, UINT uiInstanceConstantBufferDataByteWidth, ID3D11DeviceContext *pD3DDeviceContext); // Update instance constant buffer
	virtual HRESULT updateInstanceConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext); // Update instance constant buffer

	virtual HRESULT set(ID3D11DeviceContext *pD3DDeviceContext); // Set/bind the shader and it's corresponding resources

private:
	ID3D11Buffer *m_pD3DInstanceConstBuffer; // Instance constant buffer

	//ID3DX11EffectConstantBuffer *m_pD3DXInstanceConstantBuffer; // Will hold a handle to the instance constant buffer

	//ID3DX11EffectShaderResourceVariable *m_pD3DXShaderResourceVariable; // SRV

	CTexture2D *m_pPrimitiveTexture; // Primitive's texture

	UINT m_uiInstanceConstantBufferDataByteWidth; // Holds the byte width of the constant buffer data
};

extern CInstanceShader *g_pInstanceShader;

// Contant buffers used for instancing
struct SInstanceConstantBuffer
{
	//CMatrix4x4 m_oXMInstancingMatrix[50];

	CVector4 m_oInstancePositionVector; // Instance's position
};

extern SInstanceConstantBuffer *g_pInstanceConstBuffer;

#endif // INSTANCESHADER_H