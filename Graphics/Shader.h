// Shader.h: Implementation of shader interface
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef SHADER_H
#define SHADER_H

#include "ConstantBuffer.h"

// Forward declarations
enum class EShaderType;

class CMatrix4x4;

// CShader class
class CShader
{
public: // Public methods
	CShader(); // Default constructor
	CShader(const std::wstring oEffectFileString, ID3D11Device *pD3DDevice); // Constructor to create effect from the file
	CShader(void *pMemLocation, SIZE_T stSize, ID3D11Device *pD3DDevice); // Constructor to create effect from memory
	virtual ~CShader(); // Destructor

	virtual HRESULT create(const std::wstring oShaderFile, EShaderType oShaderType, ID3D11Device *pD3DDevice); // Create a shader
	virtual HRESULT create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, ID3D11Device *pD3DDevice); // Create vertex and pixel shader
	virtual HRESULT create(const std::wstring oEffectFileString, ID3D11Device *pD3DDevice); // Create effect from a file
	virtual HRESULT create(void *pMemoryLocation, SIZE_T stSize, ID3D11Device *pD3DDevice); // Create effect from memory location

	// Operation overloading
	virtual bool operator!() const; // Effect object validation test
	virtual bool operator==(CShader *pShader) const; // Objects equality test

	virtual bool isValid() const; // Will return a boolean value signaling if an error has occured or not
	virtual bool isNotValid() const; // Will return a boolean value signaling if an error has occured or not

	// Get methods
	virtual void *getBlobData() const; // Get the blob of compiled effect data
	virtual SIZE_T getBlobSize() const; // Get the size of the compiled blob
	virtual BYTE *getInputSignature(SIZE_T &rstInputSignatureSize) const; // Get the input signature
	virtual ID3DX11EffectTechnique *getTechniqueByIndex(UINT uiTechniqueIndex) const; // Get a technique by index
	virtual ID3DX11EffectVariable *getVariableByIndex(void *pVariable) const; // Get Variable by index
	virtual ID3DX11EffectVariable *getVariableByName(void *pVariable) const; // Get Variable by name
	virtual ID3DX11EffectMatrixVariable *getMatrixVariableByIndex(UINT uiMatrixIndex) const; // Get a matrix variable by index
	//CShader getMatrixVariableByIndex(UINT uiMatrixIndex) const; // Get a matrix variable by index
	virtual ID3DX11EffectMatrixVariable *getMatrixVariableByName(std::string oVariableName) const; // Get matrix variable by name
	virtual HRESULT getMatrices(); // Get and store the tranformation matrices
	virtual UINT getNumOfPasses() const; // Get the number of passes in the technique
	virtual ID3D11InputLayout *getInputLayout() const; // Get the input layout associated with this shader

	// Set methods
	//

	virtual HRESULT set(ID3D11DeviceContext *pD3DDeviceContext) = 0; // Set/bind the shader; derived class must implement this method

	// Set matrix methods
	virtual HRESULT setMatrixVariable(ID3DX11EffectMatrixVariable *pD3DXSourceEffectMatrixVariable, CMatrix4x4 &rDestMatrix); // Set the matrix variable
	virtual HRESULT setMatrixVariableByName(std::string oDestMatrixVarNameString, CMatrix4x4 &rDestMatrix); // Set matrix variable by name
	virtual HRESULT setMatrixVariableByIndex(UINT uiIndex, CMatrix4x4 &rDestMatrix); // Set matrix variable by by index
	virtual HRESULT setMatrixArrayVariable(ID3DX11EffectMatrixVariable *pD3DXSourceFffectMatrixVariable, UINT uiNumOfMatrixElements, CMatrix4x4 *pMatrices); // Set the matrix array variable
	virtual HRESULT setMatrixArrayVariableByName(std::string oDestMatrixArrayVarNameString, UINT uiNumOfMatrixElements, CMatrix4x4 *pMatrices); // Set the matrix array variable by name
	virtual HRESULT setMatrixArrayVariableByIndex(UINT uiIndex, UINT uiNumOfMatrixElements, CMatrix4x4 *pXMMatrices); // Set the matrix array variable by index
	virtual HRESULT setWorldMatrixVariable(CMatrix4x4 &rWorldMatrix); // Set world transformation matrix
	virtual HRESULT setViewMatrixVariable(CMatrix4x4 &rViewMatrix); // Set view transformation matrix
	virtual HRESULT setProjMatrixVariable(CMatrix4x4 &rProjMatrix); // Set projection transformation matrix
	virtual HRESULT setHomoMatrixVariable(CMatrix4x4 &rHomoMatrix); // Set homogenenous transformation matrix

	// Set shader resource methods
	//virtual HRESULT setShaderResourceVariable(ID3D11ShaderResourceView *pD3DShaderResourceView); // Set shader resource variable
	//virtual HRESULT setShaderResourceVariable(ID3DX11EffectShaderResourceVariable *pD3DXEffectShaderResourceVariable, ID3D11ShaderResourceView *pD3DShaderResourceView); // Set shader resource variable
	//virtual HRESULT setShaderResourceVariableArray(ID3D11ShaderResourceView **ppD3DShaderResourceView, UINT uiOffset, UINT uiShaderResourceVariableCount); // Set the specified shader resource variable array
	//virtual HRESULT setShaderResourceVariableArray(ID3DX11EffectShaderResourceVariable *pD3DXEffectShaderResourceVariable, ID3D11ShaderResourceView **ppD3DShaderResourceView, UINT uiOffset, UINT uiShaderResourceVariableCount); // Set the specified shader resource variable array

	// Set sampler variable methods
	virtual void setSamplerVariable(ID3D11SamplerState *pD3DSamplerState); // Set the sampler variable

	// Set input layout methods
	virtual void setInputLayout(ID3D11DeviceContext *pD3DDeviceContext); // Bind input layout to the input-assembler stage

	//
	// Set methods
	
	// Update methods
	virtual HRESULT updateConstantBuffer(SStaticConstantBuffer *pStaticConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext); // Update constant buffer that never changes
	virtual HRESULT updateConstantBuffer(SChangesEveryFrameConstantBuffer *pChangesEveryFrameConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext); // Update constant buffers that are updated every frame
	virtual HRESULT updateConstantBuffer(SMaterialConstantBuffer *pMaterialConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext); // Update material constant buffer
	virtual HRESULT updateConstantBuffer(void *pBuffer, ID3D11DeviceContext *pD3DDeviceContext); // Update constant buffer
	virtual HRESULT updateEveryFrameConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext); // Update constant buffer that are updated every frame
	virtual HRESULT updateStaticConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext); // Update constant buffer that's static
	virtual HRESULT updateMaterialConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext); // Update material constant buffer

	// Apply methods
	virtual HRESULT apply(UINT uiPassIndex, ID3D11DeviceContext *pD3DDeviceContext); // Apply the specifed pass by index
	virtual HRESULT apply(UINT uiTechniqueIndex, UINT uiPassIndex, ID3D11DeviceContext *pD3DDeviceContext); // Apply the specifed pass by index
	virtual bool applyAllPasses(ID3D11DeviceContext *pD3DDeviceContext); // Apply all the passes
	virtual bool applyAllTechniquesAndPasses(ID3D11DeviceContext *pD3DDeviceContext); // Apply all the techniqes and passes

private: // Private methods
	HRESULT createConstantBuffers(ID3D11Device *pD3DDevice); // Create constant buffers

protected: // Protected attributes
	ID3D11InputLayout *m_pD3DInputLayout; // Input layout associated with this shader

	ID3D11VertexShader *m_pD3DVertexShader; // Vertex shader
	ID3D11PixelShader *m_pD3DPixelShader; // Pixel shader
	ID3D11GeometryShader *m_pD3DGeometryShader; // Geometry shader
	ID3D11HullShader *m_pD3DHullShader; // Hull shader
	ID3D11DomainShader *m_pD3DDomainShader; // Domain shader

	ID3D11SamplerState *m_pD3DSamplerState; // Sampler state

	ID3DX11Effect *m_pD3DXEffect; // Effect

	ID3DX11EffectVectorVariable *m_pD3DXEffectVectorVariable; // Effect vector variables
	ID3DX11EffectMatrixVariable *m_pD3DXEffectWorldMatVariable, *m_pD3DXEffectInverseTransposeWorldMatVariable;
	ID3DX11EffectMatrixVariable *m_pD3DXEffectViewMatVariable, *m_pD3DXEffectProjMatVariable, *m_pD3DXEffectViewProjMatVariable, *m_pD3DXEffectHomoMatVariable; // Effect matrix variable

	ID3DX11EffectSamplerVariable *m_pD3DXEffectSamplerVariable; // Sampler variables

	ID3DX11EffectShaderResourceVariable *m_pD3DXEffectShaderResourceVariable; // Shader resource variables

	ID3DX11EffectTechnique *m_pD3DXEffectTechnique; // Effect technique
	ID3DX11EffectPass *m_pD3DXEffectPass; // Effect pass

	ID3DX11EffectConstantBuffer *m_pD3DXEffectEveryFrameConstBuffer, *m_pD3DXEffectStaticConstBuffer, *m_pD3DXEffectMaterialConstBuffer; // Effect constant buffers

	D3DX11_EFFECT_DESC m_oD3DXEffectDesc; // Will hold effect description
	D3DX11_TECHNIQUE_DESC m_oD3DXTechniqueDesc; // Will hold technique description

	ID3D11Buffer *m_pD3DStaticConstBuffer, *m_pD3DChangesEveryFrameConstBuffer, *m_pD3DMaterialConstbuffer; // Constant buffers

	ID3DBlob *m_pD3DCompiledShaderBlob, *m_pD3DCompiledVertexShaderBlob, *m_pD3DErrorBlob; // Blobs

	//CTexture2D *m_pPrimitiveTexture; // Primitive's 2D texture

	DWORD m_dwShaderCompileFlags; // Shader compilation flag

	HRESULT m_hResult; // Will be used for checking errors
};

// Shader type
enum class EShaderType
{
	eVertexShader, // Vertex shader
	ePixelShader, // Pixel shader
	eGeometryShader, // Geometry shader
	eHullShader, // Hull shader
	eDomainShader, // Domain shader
};

#endif // SHADER_H