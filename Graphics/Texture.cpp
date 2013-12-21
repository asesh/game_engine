// Texture.cpp : Implementation of texture management
// Copyright (C) 2007-2013 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "Texture.h"

//---------------------------------------------------------------------------
// Name: CTexture2D
// Desc: Default constructor
//---------------------------------------------------------------------------
CTexture2D::CTexture2D(DWORD dwNumberOfTextures)
{
	m_hResult = S_OK;
}

//---------------------------------------------------------------------------
// Name: CTexture2D
// Desc: Constructor to create texture from a file
//---------------------------------------------------------------------------
CTexture2D::CTexture2D(std::wstring oTexturePathString)
{
	ASSIGN_COM(load(oTexturePathString));
}

//---------------------------------------------------------------------------
// Name: CTexture2D
// Desc: Constructor to create texture from memory
//---------------------------------------------------------------------------
CTexture2D::CTexture2D(void *pMemoryLocation, SIZE_T stSizeOfMemory)
{
	ASSIGN_COM(load(pMemoryLocation, stSizeOfMemory));
}

//---------------------------------------------------------------------------
// Name: ~CTexture2D
// Desc: Destructor
//---------------------------------------------------------------------------
CTexture2D::~CTexture2D()
{
	FREE_CONTAINER_COM(m_oShaderResourceView);
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the texture from a file
//---------------------------------------------------------------------------
HRESULT CTexture2D::load(std::wstring oTexturePathString)
{
	//m_oShaderResourceView.reserve(1); // Allocate space for a single texture

	ID3D11ShaderResourceView *pD3DShaderResourceView;
	CHECK_COM(::D3DX11CreateShaderResourceViewFromFile(g_pD3DGraphics->getDevice(), oTexturePathString.data(), nullptr, nullptr, &pD3DShaderResourceView, nullptr));

	m_oShaderResourceView.push_back(pD3DShaderResourceView); // Save the SRV

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the texture from a file
//---------------------------------------------------------------------------
HRESULT CTexture2D::load(std::wstring oTexturePathString, D3DX11_IMAGE_LOAD_INFO *pD3DXImageLoadInfo)
{
	RETURN_COM(::D3DX11CreateShaderResourceViewFromFile(g_pD3DGraphics->getDevice(), oTexturePathString.data(), pD3DXImageLoadInfo, nullptr, &m_oShaderResourceView[0], nullptr));
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the texture from memory
//---------------------------------------------------------------------------
HRESULT CTexture2D::load(void *pMemoryLocation, SIZE_T stSizeOfMemory)
{
	RETURN_COM(::D3DX11CreateShaderResourceViewFromMemory(g_pD3DGraphics->getDevice(), pMemoryLocation, stSizeOfMemory, nullptr, nullptr, &m_oShaderResourceView[0], nullptr));
}

//---------------------------------------------------------------------------
// Name: getNumberOfTextures
// Desc: Get the number of textures
//---------------------------------------------------------------------------
DWORD CTexture2D::getNumberOfTextures() const
{
	return static_cast<DWORD>(m_oShaderResourceView.size());
}

//---------------------------------------------------------------------------
// Name: get
// Desc: Get the texture
//---------------------------------------------------------------------------
//ID3D11ShaderResourceView *CTexture2D::get(UINT uiShaderResourceViewIndex) const
//{
//	//return m_oShaderResourceView[uiShaderResourceViewIndex > m_oShaderResourceView.size() ? 0 : uiShaderResourceViewIndex];
//	return (*this)[uiShaderResourceViewIndex];
//}
ID3D11ShaderResourceView **CTexture2D::get(UINT uiShaderResourceViewIndex) const
{
	//return m_oShaderResourceView[uiShaderResourceViewIndex > m_oShaderResourceView.size() ? 0 : uiShaderResourceViewIndex];
	return const_cast<ID3D11ShaderResourceView **>(&(m_oShaderResourceView[uiShaderResourceViewIndex]));
}

//---------------------------------------------------------------------------
// Name: set
// Desc: Set the texture in the effect
//---------------------------------------------------------------------------
//HRESULT CTexture2D::set(CShader *pShader)
//{
//	return pShader->setShaderResourceVariable(m_oShaderResourceView[0]);
//}
//
////---------------------------------------------------------------------------
//// Name: set
//// Desc: Set the texture in the effect
////---------------------------------------------------------------------------
//HRESULT CTexture2D::set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXShaderResourceVariable)
//{
//	return pShader->setShaderResourceVariable(pD3DXShaderResourceVariable, m_oShaderResourceView[0]);
//}

//---------------------------------------------------------------------------
// Name: operator[]
// Desc: Index into the specified shader resource view
//---------------------------------------------------------------------------
ID3D11ShaderResourceView *CTexture2D::operator[](DWORD dwIndex) const
{
	return dwIndex > m_oShaderResourceView.size() ? nullptr : m_oShaderResourceView[dwIndex]; // If the index is out of range return NULL else return SRV with the specified index
}

//---------------------------------------------------------------------------
// Name: isValid
// Desc: Returns a boolean value indicating if the texture loading operation
//		 was successful or not
//---------------------------------------------------------------------------
bool CTexture2D::isValid() const
{
	return (SUCCEEDED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: isNotValid
// Desc: Returns a boolean value indicating if the texture loading operation
//		 was successful or not
//---------------------------------------------------------------------------
bool CTexture2D::isNotValid() const
{
	return (FAILED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: CTexture2DArray
// Desc: Default constructor
//---------------------------------------------------------------------------
CTexture2DArray::CTexture2DArray()
{
	//m_ppD3DShaderResourceView = NULL;

	m_hResult = S_OK;
}

//---------------------------------------------------------------------------
// Name: CTexture2DArray
// Desc: Constructor to create texture from a file
//---------------------------------------------------------------------------
CTexture2DArray::CTexture2DArray(std::wstring *pTexturePathArrayString, DWORD dwNumberOfTextures)
{
	//m_ppD3DShaderResourceView = NULL;

	ASSIGN_COM(load(pTexturePathArrayString, dwNumberOfTextures));
}

//---------------------------------------------------------------------------
// Name: CTexture2DArray
// Desc: Constructor to create texture from memory
//---------------------------------------------------------------------------
//CTexture2DArray::CTexture2DArray(void *pMemoryLocation, SIZE_T stSizeOfMemory)
//{
//	m_ppD3DShaderResourceView = NULL;
//
//	ASSIGN_COM(load(pMemoryLocation, stSizeOfMemory));
//}

//---------------------------------------------------------------------------
// Name: ~CTexture2DArray
// Desc: Destructor
//---------------------------------------------------------------------------
CTexture2DArray::~CTexture2DArray()
{
	FREE_CONTAINER_COM(m_oShaderResourceView);
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the texture from a file
//---------------------------------------------------------------------------
HRESULT CTexture2DArray::load(std::wstring *pTexturePathArrayString, DWORD dwNumberOfTextures)
{
	//m_ppD3DShaderResourceView = new ID3D11ShaderResourceView *[2]; // Allocate two SRVs, one for geometry texture and the other for normal map textures
	//m_oShaderResourceView.reserve(dwNumberOfTextures);

	ID3D11ShaderResourceView *pD3DShaderResourceView;

	// Loop to create shader resource views
	for(DWORD dwTextureCount = 0; dwTextureCount < dwNumberOfTextures; dwTextureCount++)
	{
		CHECK_COM(::D3DX11CreateShaderResourceViewFromFile(g_pD3DGraphics->getDevice(), pTexturePathArrayString[dwTextureCount].data(), nullptr, nullptr, &pD3DShaderResourceView, nullptr));
		
		m_oShaderResourceView.push_back(pD3DShaderResourceView); // Save the SRV

		pD3DShaderResourceView = nullptr;
	}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: set
// Desc: Set an array of textures
//---------------------------------------------------------------------------
//HRESULT CTexture2DArray::set(CShader *pShader)
//{
//	return pShader->setShaderResourceVariableArray(&m_oShaderResourceView[0], 0, m_oShaderResourceView.size());
//}
//
////---------------------------------------------------------------------------
//// Name: set
//// Desc: Set an array of textures
////---------------------------------------------------------------------------
//HRESULT CTexture2DArray::set(CShader *pShader, UINT uiOffset, UINT uiShaderResourceVariableCount)
//{
//	return pShader->setShaderResourceVariableArray(&m_oShaderResourceView[0], uiOffset, uiShaderResourceVariableCount);
//}
//
////---------------------------------------------------------------------------
//// Name: set
//// Desc: Set an array of textures to the specified shader resource variable
////---------------------------------------------------------------------------
//HRESULT CTexture2DArray::set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXShaderResourceVariable)
//{
//	return pShader->setShaderResourceVariableArray(pD3DXShaderResourceVariable, &m_oShaderResourceView[0], 0, m_oShaderResourceView.size());
//}
//
////---------------------------------------------------------------------------
//// Name: set
//// Desc: Set an array of textures
////---------------------------------------------------------------------------
//HRESULT CTexture2DArray::set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXShaderResourceVariable, UINT uiOffset, UINT uiShaderResourceVariableCount)
//{
//	return pShader->setShaderResourceVariableArray(pD3DXShaderResourceVariable, &m_oShaderResourceView[0], uiOffset, uiShaderResourceVariableCount);
//}

//---------------------------------------------------------------------------
// Name: CTexture3D
// Desc: Default constructor
//---------------------------------------------------------------------------
CTexture3D::CTexture3D()
{
}

//---------------------------------------------------------------------------
// Name: ~CTexture3D
// Desc: Destructor
//---------------------------------------------------------------------------
CTexture3D::~CTexture3D()
{
}

//---------------------------------------------------------------------------
// Name: CTextureCube
// Desc: Default constructor
//---------------------------------------------------------------------------
CTextureCube::CTextureCube()
{
}

//---------------------------------------------------------------------------
// Name: ~CTextureCube
// Desc: Destructor
//---------------------------------------------------------------------------
CTextureCube::~CTextureCube()
{
}

//---------------------------------------------------------------------------
// Name: CTextureCubeArray
// Desc: Default constructor
//---------------------------------------------------------------------------
CTextureCubeArray::CTextureCubeArray()
{
}

//---------------------------------------------------------------------------
// Name: ~CTextureCubeArray
// Desc: Destructor
//---------------------------------------------------------------------------
CTextureCubeArray::~CTextureCubeArray()
{
}
