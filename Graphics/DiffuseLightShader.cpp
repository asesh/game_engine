// DiffuseLightShader.cpp: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "DiffuseLightShader.h"

//---------------------------------------------------------------------------
// Name: CDiffuseLightShader
// Desc: Default constructor
//---------------------------------------------------------------------------
CDiffuseLightShader::CDiffuseLightShader()
{
	m_pPrimitiveTexture = nullptr;

	m_pD3DXShaderResourceVariable = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CDiffuseLightShader
// Desc: Destructor
//---------------------------------------------------------------------------
CDiffuseLightShader::~CDiffuseLightShader()
{
	DELETE_FREE(m_pPrimitiveTexture);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a diffuse lighting shader from the specified file
//---------------------------------------------------------------------------
HRESULT CDiffuseLightShader::create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, const std::wstring oPrimitiveTexture, ID3D11Device *pD3DDevice)
{
	SIZE_T stInputSignatureSize;

	// Create normal mapping shader
	CHECK_COM(CShader::create(oVertexShaderFile, oGeometryShaderFile, oPixelShaderFile, pD3DDevice));

	// Vertex element with position, normal and 2D texture coordinates
	D3D11_INPUT_ELEMENT_DESC oD3DPositionNormalTextureElement[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
		//{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Ambient color
		//{"COLOR", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	};

	// Get the input signature from the diffuse lighting effect
	//BYTE *pbInputSignature = getInputSignature(stInputSignatureSize);

	// Create input layout with position, normal and texture data
	CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPositionNormalTextureElement, 
		ARRAY_SIZE(oD3DPositionNormalTextureElement, D3D11_INPUT_ELEMENT_DESC), 
		m_pD3DCompiledVertexShaderBlob->GetBufferPointer(), //pbInputSignature, 
		m_pD3DCompiledVertexShaderBlob->GetBufferSize(), //stInputSignatureSize, 
		&m_pD3DInputLayout));

	FREE_COM(m_pD3DCompiledVertexShaderBlob);

	// Load the given textures if both the primitive texture and normal map texture are given
	if(!oPrimitiveTexture.empty())
	{
		// Primitive texture
		CHECK_VALIDATION((m_pPrimitiveTexture = new CTexture2D(oPrimitiveTexture)));
		//CHECK_COM(m_pPrimitiveTexture->set(this));

		// Retrieve handle to texture primitive variable
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
// Name: updateConstantBuffers
// Desc: 
//---------------------------------------------------------------------------
HRESULT CDiffuseLightShader::updateConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: set
// Desc: Set/bind the shader and it's corresponding resources
//---------------------------------------------------------------------------
HRESULT CDiffuseLightShader::set(ID3D11DeviceContext *pD3DDeviceContext)
{
	if(m_pPrimitiveTexture)
		pD3DDeviceContext->PSSetShaderResources(0, m_pPrimitiveTexture->getNumberOfTextures(), m_pPrimitiveTexture->get());
		//CHECK_COM(m_pD3DXShaderResourceVariable->SetResource(*m_pPrimitiveTexture->get())); // Bind texture

	setInputLayout(pD3DDeviceContext); // Set input layout

	updateEveryFrameConstantBuffer(pD3DDeviceContext); // Update every frame constant buffers
	pD3DDeviceContext->VSSetShader(m_pD3DVertexShader, nullptr, 0); // Set vertex shader
	pD3DDeviceContext->GSSetShader(m_pD3DGeometryShader, nullptr, 0); // Set geometry shader
	pD3DDeviceContext->PSSetSamplers(0, 1, &m_pD3DSamplerState); // Set samplers
	pD3DDeviceContext->PSSetShader(m_pD3DPixelShader, nullptr, 0); // Set pixel shader

	return S_OK;
}

CDiffuseLightShader g_oDiffuseLightShader;
CDiffuseLightShader *g_pDiffuseLightShader = &g_oDiffuseLightShader;