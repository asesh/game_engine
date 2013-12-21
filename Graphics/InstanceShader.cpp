// InstanceShader.cpp: Implementation for geometry instancing
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "Shader.h"
#include "Texture.h"
#include "InstanceShader.h"

//---------------------------------------------------------------------------
// Name: CInstanceShader
// Desc: Default constructor
//---------------------------------------------------------------------------
CInstanceShader::CInstanceShader()
{
	m_pD3DInstanceConstBuffer = nullptr;

	m_pPrimitiveTexture = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CInstanceShader
// Desc: Destructor
//---------------------------------------------------------------------------
CInstanceShader::~CInstanceShader()
{
	FREE_COM(m_pD3DInstanceConstBuffer);

	DELETE_FREE(m_pPrimitiveTexture);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a shader from the specified file
//---------------------------------------------------------------------------
HRESULT CInstanceShader::create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, UINT uiConstantBufferByteWidth, std::wstring oPrimitiveTexture, ID3D11Device *pD3DDevice)
{
	SIZE_T stInputSignatureSize;

	CHECK_COM(CShader::create(oVertexShaderFile, oGeometryShaderFile, oPixelShaderFile, pD3DDevice)); // Create the specified instancing shader

	// Vertex element with position, normal, texture, color and per-instance data
	D3D11_INPUT_ELEMENT_DESC oD3DPositionNormalTextureColorInstanceElement[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
		//{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
		{"InstancePosition", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Position of instance
		//{"mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 2
		//{"mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 3
		//{"mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 4
	};

	// Get the input signature from the instancing effect
	//BYTE *pbInputSignature = getInputSignature(stInputSignatureSize);

	// Create input layout with position, normal, texture, color and instancing data
	CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPositionNormalTextureColorInstanceElement, 
		ARRAY_SIZE(oD3DPositionNormalTextureColorInstanceElement, D3D11_INPUT_ELEMENT_DESC), 
		m_pD3DCompiledVertexShaderBlob->GetBufferPointer(), // pbInputSignature, 
		m_pD3DCompiledVertexShaderBlob->GetBufferSize(), // stInputSignatureSize, 
		&m_pD3DInputLayout));

	// Create constant buffers
	D3D11_BUFFER_DESC oD3DConstantBufferDesc = {0};
	oD3DConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Bind constant buffer
	oD3DConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU writable
	oD3DConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Dynamic usage
	oD3DConstantBufferDesc.ByteWidth = m_uiInstanceConstantBufferDataByteWidth = uiConstantBufferByteWidth; // Size of constant buffer
	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DConstantBufferDesc, nullptr, &m_pD3DInstanceConstBuffer));

	// Retrieve the handles to the constant buffers
	//m_pD3DXEffectMaterialConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBInstancePosition"); // Constant buffer holding instances' position
	//if(!m_pD3DXEffectMaterialConstBuffer->IsValid())
	//	return E_FAIL;

	// Check if texture has been specified
	if(!oPrimitiveTexture.empty()) // Texture has been specified
	{
		CHECK_VALIDATION((m_pPrimitiveTexture = new CTexture2D(oPrimitiveTexture))); // Load the primitive's texture

		// Retrieve a handle to texture primitive variable
		//m_pD3DXShaderResourceVariable = m_pD3DXEffect->GetVariableByName("g_texPrimitive")->AsShaderResource();
		//if(!m_pD3DXShaderResourceVariable->IsValid()) // Is not valid
		//	return E_FAIL;

		//// Retrieve a handle to the sampler variable
		//m_pD3DXEffectSamplerVariable = m_pD3DXEffect->GetVariableByName("g_samPrimitiveTexture")->AsSampler();
		//if(!m_pD3DXEffectSamplerVariable->IsValid())
		//	return E_FAIL;
	}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getInstanceBuffer
// Desc: Get the instance buffer
//---------------------------------------------------------------------------
ID3D11Buffer *CInstanceShader::getInstanceBuffer() const
{
	return m_pD3DInstanceConstBuffer;
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update the specified instance's constant buffers
//---------------------------------------------------------------------------
HRESULT CInstanceShader::updateConstantBuffer(void *pInstanceConstantBufferData, ID3D11DeviceContext *pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	CHECK_COM(pD3DDeviceContext->Map(m_pD3DInstanceConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource)); // Get a pointer to the data in the constant buffer

	::memcpy(oD3DMappedSubresource.pData, pInstanceConstantBufferData, m_uiInstanceConstantBufferDataByteWidth); // Copy the constant buffers

	pD3DDeviceContext->Unmap(m_pD3DInstanceConstBuffer, 0); // Free the pointer

	//pD3DDeviceContext->UpdateSubresource(m_pD3DInstanceConstBuffer, 0, NULL, reinterpret_cast<void *>(pInstanceConstantBuffer), 0, 0);

	//CHECK_COM(m_pD3DXEffectMaterialConstBuffer->SetConstantBuffer(m_pD3DInstanceConstBuffer)); // Set a instance's constant buffer

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update the specified instance's constant buffers
//---------------------------------------------------------------------------
HRESULT CInstanceShader::updateConstantBuffer(void *pInstanceConstantBufferData, UINT uiInstanceConstantBufferDataByteWidth, ID3D11DeviceContext *pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	CHECK_COM(pD3DDeviceContext->Map(m_pD3DInstanceConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource)); // Get a pointer to the data in the constant buffer

	::memcpy(oD3DMappedSubresource.pData, pInstanceConstantBufferData, uiInstanceConstantBufferDataByteWidth); // Copy the constant buffers

	pD3DDeviceContext->Unmap(m_pD3DInstanceConstBuffer, 0); // Free the pointer

	//pD3DDeviceContext->UpdateSubresource(m_pD3DInstanceConstBuffer, 0, NULL, reinterpret_cast<void *>(pInstanceConstantBuffer), 0, 0);

	//CHECK_COM(m_pD3DXEffectMaterialConstBuffer->SetConstantBuffer(m_pD3DInstanceConstBuffer)); // Set a instance's constant buffer

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateInstanceConstantBuffer
// Desc: Update instances' constant buffers
//---------------------------------------------------------------------------
HRESULT CInstanceShader::updateInstanceConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->UpdateSubresource(m_pD3DInstanceConstBuffer, 0, nullptr, reinterpret_cast<void *>(g_pInstanceConstBuffer), 0, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: set
// Desc: Set/bind the shader and it's corresponding resources
//---------------------------------------------------------------------------
HRESULT CInstanceShader::set(ID3D11DeviceContext *pD3DDeviceContext)
{
	if(m_pPrimitiveTexture)
		pD3DDeviceContext->PSSetShaderResources(0, m_pPrimitiveTexture->getNumberOfTextures(), m_pPrimitiveTexture->get());
		//CHECK_COM(m_pD3DXShaderResourceVariable->SetResource(m_pPrimitiveTexture->get()[0])); // Set the texture

	setInputLayout(pD3DDeviceContext); // Set input layout

	//pD3DDeviceContext->VSSetConstantBuffers(0, 1, &m_pD3DInstanceConstBuffer); // Set instance constant buffers
	updateEveryFrameConstantBuffer(pD3DDeviceContext); // Update every frame constant buffers
	pD3DDeviceContext->VSSetShader(m_pD3DVertexShader, nullptr, 0); // Set vertex shader
	pD3DDeviceContext->GSSetShader(m_pD3DGeometryShader, nullptr, 0); // Set geometry shader
	pD3DDeviceContext->PSSetSamplers(0, 1, &m_pD3DSamplerState); // Set samplers
	pD3DDeviceContext->PSSetShader(m_pD3DPixelShader, nullptr, 0); // Set pixel shader

	return S_OK;
}

CInstanceShader g_oInstanceShader;
CInstanceShader *g_pInstanceShader = &g_oInstanceShader;

SInstanceConstantBuffer g_oInstanceConstantBuffer;
SInstanceConstantBuffer *g_pInstanceConstBuffer = &g_oInstanceConstantBuffer;