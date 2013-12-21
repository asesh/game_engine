// NormalMapShader.cpp: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "NormalMapShader.h"

//---------------------------------------------------------------------------
// Name: CNormalMapShader
// Desc: Default constructor
//---------------------------------------------------------------------------
CNormalMapShader::CNormalMapShader()
{
	m_pD3DXEffectNormalMapSRV = nullptr;

	m_pTextureArray = nullptr;
	//m_pPrimitiveTexture = m_pNormalMapTexture = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CNormalMapShader
// Desc: Destructor
//---------------------------------------------------------------------------
CNormalMapShader::~CNormalMapShader()
{
	DELETE_FREE(m_pTextureArray);
	//DELETE_FREE(m_pPrimitiveTexture);
	//DELETE_FREE(m_pNormalMapTexture);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a normal mapping shader
//---------------------------------------------------------------------------
HRESULT CNormalMapShader::create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, const std::wstring oPrimitiveTexture, const std::wstring oNormalMapTexture, ID3D11Device *pD3DDevice)
{
	SIZE_T stInputSignatureSize;

	// Create normal mapping shader
	CHECK_COM(CShader::create(oVertexShaderFile, oGeometryShaderFile, oPixelShaderFile, pD3DDevice));

	// Vertex element for normal mapping
	D3D11_INPUT_ELEMENT_DESC oD3DNormalMapElement[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Tangent
		{"BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Bitangent
		//{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	};

	// Get the input signature from the normal mapping shader
	//BYTE *pbInputSignature = getInputSignature(stInputSignatureSize);

	// Create an input layout for normal mapping
	CHECK_COM(pD3DDevice->CreateInputLayout(oD3DNormalMapElement, 
		ARRAY_SIZE(oD3DNormalMapElement, D3D11_INPUT_ELEMENT_DESC), 
		m_pD3DCompiledVertexShaderBlob->GetBufferPointer(), 
		m_pD3DCompiledVertexShaderBlob->GetBufferSize(), 
		&m_pD3DInputLayout));

	FREE_COM(m_pD3DCompiledVertexShaderBlob);

	// Load the given textures if both the primitive texture and normal map texture are given
	if(!oPrimitiveTexture.empty() && !oNormalMapTexture.empty()) // The path of the both textures are specified
	{
		std::wstring oTextureArray[] = {oPrimitiveTexture, oNormalMapTexture}; // Create an array which holds both the primitive texture and it's corresponding normal map

		// Load the textures
		CHECK_VALIDATION((m_pTextureArray = new CTexture2DArray(oTextureArray, ARRAY_SIZE(oTextureArray, std::wstring))));
		//CHECK_VALIDATION((m_pPrimitiveTexture = new CTexture2D(oPrimitiveTexture)));
		//CHECK_VALIDATION((m_pNormalMapTexture = new CTexture2D(oNormalMapTexture)));
		//CHECK_COM(m_pTextureArray->set(this)); // Bind the textures in the shader

		// Retrieve a handle to texture primitive variable
		//m_pD3DXEffectNormalMapSRV = m_pD3DXEffect->GetVariableByName("g_texNormalMap")->AsShaderResource();
		//if(!m_pD3DXEffectNormalMapSRV->IsValid()) // Is not valid
		//	return E_FAIL;
		//m_pD3DXEffectPrimitiveSRV = m_pD3DXEffect->GetVariableByName("g_texPrimitive")->AsShaderResource();
		//if(!m_pD3DXEffectPrimitiveSRV->IsValid()) // Is not valid
		//	return E_FAIL;

		// Retrieve a handle to the sampler variable
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
HRESULT CNormalMapShader::updateConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: set
// Desc: Set/bind the shader and it's corresponding resources
//---------------------------------------------------------------------------
HRESULT CNormalMapShader::set(ID3D11DeviceContext *pD3DDeviceContext)
{
	//CHECK_COM(m_pTextureArray->set(this, m_pD3DXEffectNormalMapSRV)); // Set the texture array
	//CHECK_COM(setShaderResourceVariableArray(m_pD3DXEffectNormalMapSRV, m_pTextureArray->get(), 0, m_pTextureArray->getNumberOfTextures()));

	//if(m_pPrimitiveTexture && m_pNormalMapTexture)
	if(m_pTextureArray)
	{
		//CHECK_COM(m_pD3DXEffectNormalMapSRV->SetResourceArray(m_pPrimitiveTexture->get(), 0, 1)); // Bind texture array
		//CHECK_COM(m_pD3DXEffectPrimitiveSRV->SetResource(m_pPrimitiveTexture->get()[0])); // Bind primitive texture
		//CHECK_COM(m_pD3DXEffectNormalMapSRV->SetResource(m_pNormalMapTexture->get()[0])); // Bind normal map texture

		pD3DDeviceContext->PSSetShaderResources(0, m_pTextureArray->getNumberOfTextures(), m_pTextureArray->get()); // Set shader resources
	}

	setInputLayout(pD3DDeviceContext); // Set input layout

	//pD3DDeviceContext->VSSetConstantBuffers(0, 1, 
	updateEveryFrameConstantBuffer(pD3DDeviceContext); // Update every frame constant buffers
	pD3DDeviceContext->VSSetShader(m_pD3DVertexShader, nullptr, 0); // Set vertex shader
	pD3DDeviceContext->GSSetShader(m_pD3DGeometryShader, nullptr, 0); // Set geometry shader
	pD3DDeviceContext->PSSetSamplers(0, 1, &m_pD3DSamplerState); // Set samplers
	pD3DDeviceContext->PSSetShader(m_pD3DPixelShader, nullptr, 0); // Set pixel shader
	pD3DDeviceContext->HSSetShader(nullptr, nullptr, 0); // No hull shader
	//pD3DDeviceContext->PSSetShaderResources(0, m_pTextureArray->getNumberOfTextures(), m_pTextureArray->get());

	return S_OK;
}

CNormalMapShader g_oNormalMapShader;
CNormalMapShader *g_pNormalMapShader = &g_oNormalMapShader;