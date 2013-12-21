// InputLayout.cpp : Implementation of input elements and their corresponding data
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "InputLayout.h"

//---------------------------------------------------------------------------
// Name: CInputLayout
// Desc: Default constructor
//---------------------------------------------------------------------------
CInputLayout::CInputLayout()
{
	m_pD3DPosInputLayout = m_pD3DPosInstInputLayout = m_pD3DPosNormInputLayout = m_pD3DPosNormInstInputLayout = \
		m_pD3DPosTexInputLayout = m_pD3DPosTexInstInputLayout = m_pD3DPosNormTexInputLayout = m_pD3DPosNormTexInstInputLayout = \
		m_pD3DPosColInputLayout = m_pD3DPosColInstInputLayout = m_pD3DPosNormCubeTexInputLayout = m_pD3DPosNormVolTexInputLayout = m_pD3DPosNormTexBinormTangentLayout = nullptr;

	m_hResult = S_OK; // HRESULT
}

//---------------------------------------------------------------------------
// Name: ~CInputLayout
// Desc: Destructor
//---------------------------------------------------------------------------
CInputLayout::~CInputLayout()
{
	FREE_COM(m_pD3DPosInputLayout);
	FREE_COM(m_pD3DPosInstInputLayout);
	FREE_COM(m_pD3DPosNormInputLayout);
	FREE_COM(m_pD3DPosNormInstInputLayout);
	FREE_COM(m_pD3DPosTexInputLayout);
	FREE_COM(m_pD3DPosTexInstInputLayout);
	FREE_COM(m_pD3DPosNormTexInputLayout);
	FREE_COM(m_pD3DPosNormTexInstInputLayout);
	FREE_COM(m_pD3DPosColInputLayout);
	FREE_COM(m_pD3DPosColInstInputLayout);
	FREE_COM(m_pD3DPosNormCubeTexInputLayout);
	FREE_COM(m_pD3DPosNormVolTexInputLayout);
	FREE_COM(m_pD3DPosNormTexBinormTangentLayout);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create input layouts
//---------------------------------------------------------------------------
HRESULT CInputLayout::create(ID3D11Device *pD3DDevice, CShader *pShader)
{
	// WORKING CODE

	//BYTE *pbInputSignature; // Will hold the input signature

	//SIZE_T stInputSignatureSize; // Will hold the size of the input signature

	//// Vertex element with position
	//D3D11_INPUT_ELEMENT_DESC oD3DPosInputElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//};

	//// Vertex element with position and color
	//D3D11_INPUT_ELEMENT_DESC oD3DPosColorElement[] =
	//{
	//	{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Color
	//};

	//// Vertex element with position and 2D texture coordinates
	//D3D11_INPUT_ELEMENT_DESC oD3DPos2DTexElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//};

	//// Vertex element with position, 3D normal and 2D texture coordinates
	//D3D11_INPUT_ELEMENT_DESC oD3DPosNorm2DTexElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//};

	//// Vertex element with position, 3D normal, 2D texture coordinates and color
	//D3D11_INPUT_ELEMENT_DESC oD3DPosNorm2DTexColElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//	{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	//};

	//// Per-instance data
	//D3D11_INPUT_ELEMENT_DESC oD3DInstanceElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//	{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	//	{"InstancePosition", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 1
	//	//{"mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 2
	//	///{"mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 3
	//	//{"mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 4
	//};

	//pbInputSignature = pShader->getInputSignature(stInputSignatureSize); // Get the input signature from diffuse lighting effect

	//// Create input layout with position, normal, texture and color
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPosNorm2DTexColElement, 
	//	ARRAY_SIZE(oD3DPosNorm2DTexColElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosNormTexInputLayout));

	//pbInputSignature = g_pInstanceShader->getInputSignature(stInputSignatureSize); // Get the input signature from instancing effect

	//// Create input layout with position, normal, texture and instancing
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DInstanceElement,
	//	ARRAY_SIZE(oD3DInstanceElement, D3D11_INPUT_ELEMENT_DESC),
	//	pbInputSignature,
	//	stInputSignatureSize,
	//	&m_pD3DPosNormTexInstInputLayout));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create input layouts
//---------------------------------------------------------------------------
HRESULT CInputLayout::create(ID3D11Device *pD3DDevice, BYTE *pbtInputSignature, SIZE_T stInputSignatureSize)
{
	// Vertex element with 3D position
	/*D3D11_INPUT_ELEMENT_DESC oD3D3DPosInputElement[] =
	{
		{"SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	};

	// Vertex element with 3D position and 2D texture coordinates
	D3D11_INPUT_ELEMENT_DESC oD3D3DPos2DTexElement[] =
	{
		{"SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
		{"Texture", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	};*/

	// Vertex element with 3D position, 3D normal and 2D texture coordinates
	D3D11_INPUT_ELEMENT_DESC oD3DPosNorm2DTexElement[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
		{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	};

	//D3D11_INPUT_ELEMENT_DESC oD3D3DPos3DNorm2DTex

	//UINT uiNumOfElements;

	//uiNumOfElements = ARRAY_SIZE(oD3D3DPosInputElement, D3D11_INPUT_ELEMENT_DESC);
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3D3DPosInputElement, uiNumOfElements, NULL, 0, &m_pD3DPosInputLayout));

	//uiNumOfElements = ARRAY_SIZE(oD3D3DPos2DTexElement, D3D11_INPUT_ELEMENT_DESC);
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3D3DPos2DTexElement, uiNumOfElements, NULL, 0, &m_pD3DPosTexInputLayout));

	//uiNumOfElements = ARRAY_SIZE(oD3D3DPos3DNorm2DTexElement, D3D11_INPUT_ELEMENT_DESC);
	CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPosNorm2DTexElement, 
		ARRAY_SIZE(oD3DPosNorm2DTexElement, D3D11_INPUT_ELEMENT_DESC), 
		pbtInputSignature, 
		stInputSignatureSize, 
		&m_pD3DPosNormTexInputLayout));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create input layouts
//---------------------------------------------------------------------------
HRESULT CInputLayout::create(D3D11_INPUT_ELEMENT_DESC *&rD3DInputElementDesc, UINT uiNumOfInputElements, ID3D11InputLayout *pD3DInputLayout, CShader *pEffect)
{
	SIZE_T stInputSignatureSize;

	BYTE *pbInputSignature = pEffect->getInputSignature(stInputSignatureSize);

	CHECK_COM(D3D_DEVICE->CreateInputLayout(rD3DInputElementDesc, 
		uiNumOfInputElements, 
		pbInputSignature, 
		stInputSignatureSize, 
		&m_pD3DPosNormTexInputLayout));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: init
// Desc: Initialize the input layouts
//---------------------------------------------------------------------------
HRESULT CInputLayout::init(ID3D11Device *pD3DDevice)
{
	BYTE *pbInputSignature; // Will hold the input signature

	SIZE_T stInputSignatureSize; // Will hold the size of the input signature

	// Vertex element with position
	//D3D11_INPUT_ELEMENT_DESC oD3DPosInputElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//};

	//// Get the input signature from the effect
	//pbInputSignature = g_pNormalShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal and texture
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPosInputElement, 
	//	ARRAY_SIZE(oD3DPosInputElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosInputLayout));

	//// Vertex element with position and color
	//D3D11_INPUT_ELEMENT_DESC oD3DPosColorElement[] =
	//{
	//	{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Color
	//};

	//// Get the input signature from the diffuse lighting effect
	//pbInputSignature = g_pDiffuseLightingShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal and texture
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPosColorElement, 
	//	ARRAY_SIZE(oD3DPosColorElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosColInputLayout));

	//// Vertex element with position and 2D texture coordinates
	//D3D11_INPUT_ELEMENT_DESC oD3DPos2DTexElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"Texture", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//};

	//// Get the input signature from the diffuse lighting effect
	//pbInputSignature = g_pDiffuseLightingShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal and texture
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPos2DTexElement, 
	//	ARRAY_SIZE(oD3DPos2DTexElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosNormTexInputLayout));

	// Vertex element with position, normal and 2D texture coordinates
	//D3D11_INPUT_ELEMENT_DESC oD3DPositionNormalTextureElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//	//{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Ambient color
	//	//{"COLOR", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	//};

	//// Get the input signature from the diffuse lighting effect
	//pbInputSignature = g_pDiffuseLightingShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal and texture data
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPositionNormalTextureElement, 
	//	ARRAY_SIZE(oD3DPositionNormalTextureElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosNormTexInputLayout));

	// Vertex element with position, normal, texture, color and per-instance data
	//D3D11_INPUT_ELEMENT_DESC oD3DPositionNormalTextureColorInstanceElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//	//{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Diffuse color
	//	{"InstancePosition", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Positionof instance
	//	//{"mTransform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 2
	//	//{"mTransform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 3
	//	//{"mTransform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // Matrix row 4
	//};

	//// Get the input signature from the instancing effect
	//pbInputSignature = g_pInstanceShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal, texture, color and instancing data
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPositionNormalTextureColorInstanceElement, 
	//	ARRAY_SIZE(oD3DPositionNormalTextureColorInstanceElement, D3D11_INPUT_ELEMENT_DESC), 
	//	pbInputSignature, 
	//	stInputSignatureSize, 
	//	&m_pD3DPosNormTexInstInputLayout));

	// Vertex element with position, normal, 2D texture coordinates, binormal and tangent
	//D3D11_INPUT_ELEMENT_DESC oD3DPositionNormalTextureTangentBinormalElement[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Position
	//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Normal
	//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Texture
	//	{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Tangent
	//	{"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, // Binormal
	//};

	//// Get the input signature from the normal mapping effect
	//pbInputSignature = g_pNormalMapShader->getInputSignature(stInputSignatureSize);

	//// Create input layout with position, normal, texture, tangent and binormal
	//CHECK_COM(pD3DDevice->CreateInputLayout(oD3DPositionNormalTextureTangentBinormalElement,
	//	ARRAY_SIZE(oD3DPositionNormalTextureTangentBinormalElement, D3D11_INPUT_ELEMENT_DESC),
	//	pbInputSignature,
	//	stInputSignatureSize,
	//	&m_pD3DPosNormTexBinormTangentLayout));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getPos
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPos() const
{
	return m_pD3DPosInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosInstanced
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosInstanced() const
{
	return m_pD3DPosInstInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosNorm
// Desc: Get the position and normal input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosNorm() const
{
	return m_pD3DPosNormInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosNormInstanced
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosNormInstanced() const
{
	return m_pD3DPosNormInstInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosTex
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosTex() const
{
	return m_pD3DPosTexInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosTexInstanced
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosTexInstanced() const
{
	return m_pD3DPosTexInstInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosNormTex
// Desc: Get the position, normal and texture input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosNormTex() const
{
	return m_pD3DPosNormTexInputLayout;
}

//---------------------------------------------------------------------------
// Name: getPosNormTexInstanced
// Desc: Get the position input layout
//---------------------------------------------------------------------------
ID3D11InputLayout *CInputLayout::getPosNormTexInstanced() const
{
	return m_pD3DPosNormTexInstInputLayout;
}

//---------------------------------------------------------------------------
// Name: setPos
// Desc: Set the position input layout
//---------------------------------------------------------------------------
void CInputLayout::setPos(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosInstanced
// Desc: Set the position, texture and instancing input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosInstanced(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosInstInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosNorm
// Desc: Set the position and normal input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosNorm(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosNormInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosNormInstanced
// Desc: Set the position, texture and instancing input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosNormInstanced(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosNormInstInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosTex
// Desc: Set the position and texture input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosTex(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosTexInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosTexInstanced
// Desc: Set the position, texture and instancing input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosTexInstanced(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosTexInstInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosNormTex
// Desc: Set the position, normal and texture input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosNormTex(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosNormTexInputLayout);
}

//---------------------------------------------------------------------------
// Name: setPosNormTexInstanced
// Desc: Set the position, normal, texture and instancing input layout
//---------------------------------------------------------------------------
void CInputLayout::setPosNormTexInstanced(ID3D11DeviceContext *pD3DDevContext)
{
	pD3DDevContext->IASetInputLayout(m_pD3DPosNormTexInstInputLayout);
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Test if the two objects are equal
//---------------------------------------------------------------------------
bool CInputLayout::operator==(CInputLayout &rInputLayout) const
{
	return true;
}

//---------------------------------------------------------------------------
// Name: operator!
// Desc: Test if an error occurred while creating input layouts
//---------------------------------------------------------------------------
bool CInputLayout::operator!() const
{
	return (FAILED(m_hResult) ? true : false); // Return true if failed else return false
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

CInputLayout g_oInputLayout;
CInputLayout *g_pInputLayout = &g_oInputLayout;