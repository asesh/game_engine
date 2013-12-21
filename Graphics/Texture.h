// Texture.h: Interface of texture class
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#ifndef TEXTURE_H
#define TEXTURE_H

// Forward declarations
//class CShader;

// CTexture2D class
class CTexture2D
{
public:
	CTexture2D(DWORD dwNumberOfTextures = 1); // Default contructor
	CTexture2D(std::wstring oTexturePathString); // Constructor to create texture from a file
	CTexture2D(std::wstring oTexturePathString, D3DX11_IMAGE_LOAD_INFO *pD3DXImageLoadInfo); // Constructor to load texture from a file
	CTexture2D(void *pMemoryLocation, SIZE_T stSizeOfMemory); // Constructor to create texture from memory
	virtual ~CTexture2D(); // Destructor

	// Load methods
	virtual HRESULT load(std::wstring oTexturePathString); // Load texture from a file
	virtual HRESULT load(std::wstring oTexturePathString, D3DX11_IMAGE_LOAD_INFO *pD3DXImageLoadInfo); // Load texture from a file
	virtual HRESULT load(void *pMemoryLocation, SIZE_T stSizeOfMemory); // Load texture from memory

	// Get methods
	virtual DWORD getNumberOfTextures() const; // Get the number of textures
	virtual ID3D11ShaderResourceView **get(UINT uiShaderResourceViewIndex = 0) const; // Get the texture

	// Set methods
	//virtual HRESULT set(CShader *pShader); // Set the texture in an effect
	//virtual HRESULT set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXEffectShaderResourceVariable); // Set the texture in an effect

	virtual ID3D11ShaderResourceView *operator[](DWORD dwIndex) const; // Index into the shader resource view

	virtual bool isValid() const; // Will return a boolean value indicating whether the textures was successfully loaded or not
	virtual bool isNotValid() const; // Will return a boolean value indicating whether the textures was successfully loaded or not

protected:
	std::vector<ID3D11ShaderResourceView *> m_oShaderResourceView; // Texture array

	HRESULT m_hResult; // It will be used for testing errors
};

// CTexture2DArray class
class CTexture2DArray : public CTexture2D
{
public:
	CTexture2DArray(); // Default constructor
	CTexture2DArray(std::wstring *pTexturePathArrayString, DWORD dwNumberOfTextures); // Constructor to load an array of textures
	virtual ~CTexture2DArray(); // Destructor

	// Get methods
	//virtual ID3D11ShaderResourceView **get(UINT uiShaderResourceViewIndex = 0) const; // Get the texture array

	virtual HRESULT load(std::wstring *pTexturePathArrayString, DWORD dwNumberOfTextures); // Load an array of textures

	// Set methods
	//virtual HRESULT set(CShader *pShader); // Set an array of textures
	//virtual HRESULT set(CShader *pShader, UINT uiOffset, UINT uiShaderResourceVariableCount); // Set an array of textures
	//virtual HRESULT set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXShaderResourceVariable); // Set an array of textures to the specified shader resource variable
	//virtual HRESULT set(CShader *pShader, ID3DX11EffectShaderResourceVariable *pD3DXShaderResourceVariable, UINT uiOffset, UINT uiShaderResourceVariableCount); // Set an array of textures

};

// CTexture3D class
class CTexture3D
{
public:
	CTexture3D(); // Default constructor
	virtual ~CTexture3D(); // Destructor
};

// CTextureCube class
class CTextureCube
{
public:
	CTextureCube(); // Default constructor
	virtual ~CTextureCube(); // Destructor

protected:
};

// CTextureCubeArray class
class CTextureCubeArray : public CTextureCube
{
public:
	CTextureCubeArray(); // Default constructor
	virtual ~CTextureCubeArray(); // Destructor
};

#endif // TEXTURE_H