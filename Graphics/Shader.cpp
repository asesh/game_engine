// Shader.cpp: Implementation of shader interfaces
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"

#include <D3Dcompiler.h> // Direct3D compiler

#include "..\..\common\Effects11\Inc\d3dx11effect.h" // Effects 11

#include "Shader.h"

//---------------------------------------------------------------------------
// Name: CShader
// Desc: Default constructor
//---------------------------------------------------------------------------
CShader::CShader()
{
	//DELETE_FREE(m_pPrimitiveTexture);

	m_pD3DInputLayout = nullptr;

	m_pD3DVertexShader = nullptr;
	m_pD3DPixelShader = nullptr;
	m_pD3DGeometryShader = nullptr;

	m_pD3DXEffect = nullptr;

	m_pD3DXEffectWorldMatVariable = m_pD3DXEffectInverseTransposeWorldMatVariable = nullptr;
	m_pD3DXEffectViewMatVariable = m_pD3DXEffectProjMatVariable = m_pD3DXEffectViewProjMatVariable = m_pD3DXEffectHomoMatVariable = nullptr;

	m_pD3DXEffectSamplerVariable = nullptr;

	m_pD3DXEffectShaderResourceVariable = nullptr;

	m_pD3DXEffectTechnique = nullptr;
	m_pD3DXEffectPass = nullptr;

	m_pD3DStaticConstBuffer = m_pD3DChangesEveryFrameConstBuffer = m_pD3DMaterialConstbuffer = nullptr;

	m_pD3DCompiledShaderBlob = m_pD3DErrorBlob = m_pD3DCompiledVertexShaderBlob = nullptr; // Blobs

#ifdef _DEBUG // Debug version

	m_dwShaderCompileFlags = D3DCOMPILE_DEBUG; // Compile with debug information

#else // Release versions

	m_dwShaderCompileFlags = 0;

#endif // _DEBUG

	m_hResult = S_OK; // HRESULT
}

//---------------------------------------------------------------------------
// Name: CShader
// Desc: Create shader from a file
//---------------------------------------------------------------------------
CShader::CShader(const std::wstring oShaderFilePathString, ID3D11Device *pD3DDevice)
{
	m_pD3DInputLayout = nullptr;

	m_pD3DXEffect = nullptr;

	m_pD3DXEffectWorldMatVariable = m_pD3DXEffectViewMatVariable = m_pD3DXEffectProjMatVariable = m_pD3DXEffectViewProjMatVariable = m_pD3DXEffectHomoMatVariable = nullptr;

	m_pD3DXEffectSamplerVariable = nullptr;

	m_pD3DXEffectShaderResourceVariable = nullptr;

	m_pD3DXEffectTechnique = nullptr;
	m_pD3DXEffectPass = nullptr;

	m_pD3DStaticConstBuffer = m_pD3DChangesEveryFrameConstBuffer = m_pD3DMaterialConstbuffer = nullptr;

	m_pD3DCompiledShaderBlob = m_pD3DErrorBlob = m_pD3DCompiledVertexShaderBlob = nullptr; // Blobs

	//m_pPrimitiveTexture = NULL;

	m_hResult = S_OK; // HRESULT

	ASSIGN_COM(create(oShaderFilePathString, pD3DDevice));
}

//---------------------------------------------------------------------------
// Name: CShader
// Desc: Create shader from memory location
//---------------------------------------------------------------------------
CShader::CShader(void *pMemLocation, SIZE_T stSize, ID3D11Device *pD3DDevice)
{
	m_pD3DInputLayout = nullptr;

	m_pD3DXEffect = nullptr;

	m_pD3DXEffectWorldMatVariable = m_pD3DXEffectProjMatVariable = m_pD3DXEffectViewMatVariable = m_pD3DXEffectViewProjMatVariable = m_pD3DXEffectHomoMatVariable = nullptr;

	m_pD3DXEffectSamplerVariable = nullptr;

	m_pD3DXEffectShaderResourceVariable = nullptr;

	m_pD3DXEffectTechnique = nullptr;
	m_pD3DXEffectPass = nullptr;

	m_pD3DStaticConstBuffer = m_pD3DChangesEveryFrameConstBuffer = m_pD3DMaterialConstbuffer = nullptr;

	m_pD3DCompiledShaderBlob = m_pD3DErrorBlob = m_pD3DCompiledVertexShaderBlob = nullptr; // Blobs

	//m_pPrimitiveTexture = NULL;

	m_hResult = S_OK; // HRESULT

	ASSIGN_COM(create(pMemLocation, stSize, pD3DDevice));
}

//---------------------------------------------------------------------------
// Name: ~CShader
// Desc: Destructor
//---------------------------------------------------------------------------
CShader::~CShader()
{
	//DELETE_FREE(m_pPrimitiveTexture);

	FREE_COM(m_pD3DMaterialConstbuffer);
	FREE_COM(m_pD3DStaticConstBuffer);
	FREE_COM(m_pD3DChangesEveryFrameConstBuffer);

	FREE_COM(m_pD3DCompiledVertexShaderBlob);
	FREE_COM(m_pD3DCompiledShaderBlob);
	FREE_COM(m_pD3DErrorBlob);

	FREE_COM(m_pD3DXEffect);

	FREE_COM(m_pD3DGeometryShader);
	FREE_COM(m_pD3DVertexShader);
	FREE_COM(m_pD3DPixelShader);

	FREE_COM(m_pD3DInputLayout);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create shader from the specified file
//---------------------------------------------------------------------------
HRESULT CShader::create(const std::wstring oShaderFilePath, EShaderType oShaderType, ID3D11Device *pD3DDevice)
{
	std::string oShaderTarget;

	switch(oShaderType)
	{
	case EShaderType::eVertexShader: // Vertex shader
		oShaderTarget = "vs_5_0";
		break;

	case EShaderType::ePixelShader: // Pixel shader
		oShaderTarget = "ps_5_0";
		break;

	case EShaderType::eGeometryShader: // Geometry shader
		oShaderTarget = "gs_5_0";
		break;

	case EShaderType::eHullShader: // Hull shader
		oShaderTarget = "hs_5_0";
		break;

	case EShaderType::eDomainShader: // Domain shader
		oShaderTarget = "ds_5_0";
		break;
	}

	// Compile the shader and get the blob data from it
	//m_hResult = ::D3DCompileFromFile(oShaderFilePath.data(), NULL, NULL, NULL, oShaderTarget.data(), dwShaderFlags, NULL, &m_pD3DCompiledShaderBlob, &m_pD3DErrorBlob);
	if(FAILED(m_hResult))
	{
#ifdef _DEBUG // Debug version

		if(m_pD3DErrorBlob)
			::OutputDebugStringA(reinterpret_cast<char *>(m_pD3DErrorBlob->GetBufferPointer()));

#endif // _DEBUG

		return E_INVALIDARG;
	}

	return E_FAIL; // This method is incomplete that's why :)

	CHECK_COM(createConstantBuffers(pD3DDevice)); // Create constant buffers

	//
	// Create constant buffers

	// Retrieve the handles to the constant buffers
	//
	m_pD3DXEffectEveryFrameConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBEveryFrame"); // Constant buffer that changes every frame
	if(!m_pD3DXEffectEveryFrameConstBuffer->IsValid())
		return E_FAIL;
	m_pD3DXEffectStaticConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBStatic"); // Constant buffer that never changes
	if(!m_pD3DXEffectStaticConstBuffer->IsValid())
		return E_FAIL;
	m_pD3DXEffectMaterialConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBDiffuseMaterial"); // Constant buffer holding materials
	if(!m_pD3DXEffectMaterialConstBuffer->IsValid())
		return E_FAIL;

	//m_pD3DXEffectEveryFrameConstBuffer->SetConstantBuffer(m_pD3DChangesEveryFrameConstBuffer);
	//m_pD3DXEffectStaticConstBuffer->SetConstantBuffer(m_pD3DStaticConstBuffer);

	return S_OK;
}

//---------------------------------------------------------------------------
//Name: create
//Desc: Create vertex and pixel shader from the specified files
//---------------------------------------------------------------------------
HRESULT CShader::create(const std::wstring oVertexShaderFile, const std::wstring oGeometryShaderFile, const std::wstring oPixelShaderFile, ID3D11Device *pD3DDevice)
{
	DWORD dwShaderFlags; // Holds shader compile flags

	ID3DBlob *pD3DCompiledShaderBlob, *pD3DErrorBlob; // Will hold the compiled shader and error data

#ifdef _DEBUG // Debug version

	dwShaderFlags = D3DCOMPILE_DEBUG; // 

#else // Release versions

	dwShaderFlags = 0;

#endif // _DEBUG

	std::string oShaderProfiles[] = {"vs_5_0", "gs_5_0", "ps_5_0"}; // Shader profiles
	std::wstring oShaders[] = {oVertexShaderFile, oGeometryShaderFile, oPixelShaderFile}; // Vertex, geometry and pixel shader file paths

	DWORD dwShaderProfileIndex = 0; // Shader profile index which will index into the shader profiles

	// Iterate through the shader paths and create them
	for(std::wstring oShaderFilePath : oShaders)
	{
		// Check if the shader file path is specified
		if(oShaderFilePath.empty()) // Shader file path is empty
		{
			dwShaderProfileIndex++; // Increment shader profile index since this shader file path is empty

			continue; // Next shader
		}

		// Compile the shader and get the blob data from it
		m_hResult = ::D3DCompileFromFile(oShaderFilePath.data(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", oShaderProfiles[dwShaderProfileIndex].data(), dwShaderFlags, NULL, &pD3DCompiledShaderBlob, &pD3DErrorBlob);
		if(FAILED(m_hResult))
		{
#ifdef _DEBUG // Debug version

			if(m_pD3DErrorBlob)
				::OutputDebugStringA(reinterpret_cast<char *>(m_pD3DErrorBlob->GetBufferPointer()));

#endif // _DEBUG

			return E_INVALIDARG;
		}

		switch(dwShaderProfileIndex)
		{
		case 0: // Vertex shader
			m_pD3DCompiledVertexShaderBlob = pD3DCompiledShaderBlob; // Assign the compiled shader blob
			CHECK_COM(pD3DDevice->CreateVertexShader(m_pD3DCompiledVertexShaderBlob->GetBufferPointer(), m_pD3DCompiledVertexShaderBlob->GetBufferSize(), nullptr, &m_pD3DVertexShader)); // Create vertex shader
			dwShaderProfileIndex++; // Next shader
			continue;
			break;

		case 1: // Geometry shader
			CHECK_COM(pD3DDevice->CreateGeometryShader(pD3DCompiledShaderBlob->GetBufferPointer(), pD3DCompiledShaderBlob->GetBufferSize(), nullptr, &m_pD3DGeometryShader)); // Create geometry shader
			break;

		case 2: // Pixel shader
			CHECK_COM(pD3DDevice->CreatePixelShader(pD3DCompiledShaderBlob->GetBufferPointer(), pD3DCompiledShaderBlob->GetBufferSize(), nullptr, &m_pD3DPixelShader)); // Create pixel shader
			break;
		}

		dwShaderProfileIndex++; // Next shader

		RELEASE_COM(pD3DCompiledShaderBlob); // Compiled shader blob
		RELEASE_COM(pD3DErrorBlob); // Error blob
	}

	CHECK_COM(createConstantBuffers(pD3DDevice)); // Create constant buffers

	// Retrieve the handles to the constant buffers
	//
	//m_pD3DXEffectEveryFrameConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBEveryFrame"); // Constant buffer that changes every frame
	//if(!m_pD3DXEffectEveryFrameConstBuffer->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectStaticConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBStatic"); // Constant buffer that never changes
	//if(!m_pD3DXEffectStaticConstBuffer->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectMaterialConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBDiffuseMaterial"); // Constant buffer holding materials
	//if(!m_pD3DXEffectMaterialConstBuffer->IsValid())
	//	return E_FAIL;

	//m_pD3DXEffectEveryFrameConstBuffer->SetConstantBuffer(m_pD3DChangesEveryFrameConstBuffer);
	//m_pD3DXEffectStaticConstBuffer->SetConstantBuffer(m_pD3DStaticConstBuffer);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create shader from the specified file
//---------------------------------------------------------------------------
HRESULT CShader::create(const std::wstring oShaderFilePathString, ID3D11Device *pD3DDevice)
{
	DWORD dwShaderFlags;

#ifdef _DEBUG // Debug version

	dwShaderFlags = D3DCOMPILE_DEBUG; // 

#else // Release versions

	dwShaderFlags = 0;

#endif // _DEBUG

	// Compile the shader and get the blob data from it
	m_hResult = ::D3DX11CompileFromFile(oShaderFilePathString.data(), nullptr, nullptr, nullptr, "fx_5_0", dwShaderFlags, NULL, nullptr, &m_pD3DCompiledShaderBlob, &m_pD3DErrorBlob, nullptr);
	if(FAILED(m_hResult))
	{
#ifdef _DEBUG // Debug version

		if(m_pD3DErrorBlob)
			::OutputDebugStringA(reinterpret_cast<char *>(m_pD3DErrorBlob->GetBufferPointer()));

#endif // _DEBUG

		return E_INVALIDARG;
	}

	// Create shader from the compiled blob data
	CHECK_COM(::D3DX11CreateEffectFromMemory(m_pD3DCompiledShaderBlob->GetBufferPointer(), m_pD3DCompiledShaderBlob->GetBufferSize(), NULL, pD3DDevice, &m_pD3DXEffect));

	// Get the shader description
	CHECK_COM(m_pD3DXEffect->GetDesc(&m_oD3DXEffectDesc));

	// Get the technique description
	CHECK_COM(m_pD3DXEffect->GetTechniqueByIndex(0)->GetDesc(&m_oD3DXTechniqueDesc));

	// Get the variable handles from the shader
	//m_pD3DXEffectWorldMatVariable = m_pD3DXEffect->GetVariableByName("m_matWorld")->AsMatrix(); // World matrix
	//if(!m_pD3DXEffectWorldMatVariable->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectInverseTransposeWorldMatVariable = m_pD3DXEffect->GetVariableByName("m_matInverseTransposeWorld")->AsMatrix(); // Inverse transpose of world matrix
	//if(!m_pD3DXEffectWorldMatVariable->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectViewMatVariable = m_pD3DXEffect->GetVariableByName("m_matView")->AsMatrix(); // View matrix
	//if(!m_pD3DXEffectViewMatVariable->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectViewProjMatVariable = m_pD3DXEffect->GetVariableByName("m_matViewProjection")->AsMatrix(); // View-projection matrix
	//if(!m_pD3DXEffectViewProjMatVariable->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectHomoMatVariable = m_pD3DXEffect->GetVariableByName("m_matHomogeneous")->AsMatrix(); // Homogeneous matrix
	//if(!m_pD3DXEffectHomoMatVariable->IsValid())
	//	return E_FAIL;
	//m_pD3DXEffectShaderResourceVariable = m_pD3DXEffect->GetVariableByName("g_texPrimitive")->AsShaderResource();
	//if(!m_pD3DXEffectShaderResourceVariable->IsValid())
	//	return E_FAIL;

	CHECK_COM(createConstantBuffers(pD3DDevice)); // Create constant buffers

	// Retrieve the handles to the constant buffers
	//
	m_pD3DXEffectEveryFrameConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBEveryFrame"); // Constant buffer that changes every frame
	if(!m_pD3DXEffectEveryFrameConstBuffer->IsValid())
		return E_FAIL;
	m_pD3DXEffectStaticConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBStatic"); // Constant buffer that never changes
	if(!m_pD3DXEffectStaticConstBuffer->IsValid())
		return E_FAIL;
	m_pD3DXEffectMaterialConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBDiffuseMaterial"); // Constant buffer holding materials
	if(!m_pD3DXEffectMaterialConstBuffer->IsValid())
		return E_FAIL;

	//m_pD3DXEffectEveryFrameConstBuffer->SetConstantBuffer(m_pD3DChangesEveryFrameConstBuffer);
	//m_pD3DXEffectStaticConstBuffer->SetConstantBuffer(m_pD3DStaticConstBuffer);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create shader from memory
//---------------------------------------------------------------------------
HRESULT CShader::create(void *pMemoryLocation, SIZE_T stSize, ID3D11Device *pD3DDevice)
{
	D3D11_BUFFER_DESC oD3DBufferDesc = {0}; // Will hold constant buffer description

	CHECK_COM(::D3DX11CreateEffectFromMemory(pMemoryLocation, stSize, NULL, pD3DDevice, &m_pD3DXEffect));

	CHECK_COM(m_pD3DXEffect->GetDesc(&m_oD3DXEffectDesc)); // Get the shader description

	CHECK_COM(m_pD3DXEffect->GetTechniqueByIndex(0)->GetDesc(&m_oD3DXTechniqueDesc)); // Get the technique description

	// Get the variable handles from the shader
	m_pD3DXEffectWorldMatVariable = m_pD3DXEffect->GetVariableByName("m_matWorld")->AsMatrix(); // World matrix
	if(!m_pD3DXEffectWorldMatVariable->IsValid()) // Is not valid
		return E_FAIL;
	m_pD3DXEffectViewMatVariable = m_pD3DXEffect->GetVariableByName("m_matView")->AsMatrix(); // View matrix
	if(!m_pD3DXEffectViewMatVariable->IsValid()) // Is not valid
		return E_FAIL;
	m_pD3DXEffectViewProjMatVariable = m_pD3DXEffect->GetVariableByName("m_matViewProjection")->AsMatrix(); // View-projection matrix
	if(!m_pD3DXEffectViewProjMatVariable->IsValid())
		return E_FAIL;
	m_pD3DXEffectHomoMatVariable = m_pD3DXEffect->GetVariableByName("m_matHomogeneous")->AsMatrix(); // Homogeneous matrix
	if(!m_pD3DXEffectHomoMatVariable->IsValid()) // Is not valid
		return E_FAIL;
	m_pD3DXEffectShaderResourceVariable = m_pD3DXEffect->GetVariableByName("g_texPrimitive")->AsShaderResource(); // Shader resource
	if(!m_pD3DXEffectShaderResourceVariable->IsValid()) // Is not valid
		return E_FAIL;
	m_pD3DXEffectSamplerVariable = m_pD3DXEffect->GetVariableByName("g_samType")->AsSampler(); // Sampler variable
	if(!m_pD3DXEffectSamplerVariable->IsValid()) // Is not valid
		return E_FAIL;

	// Create constant buffers
	//

	// Constant buffer that changes every frame
	oD3DBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Bind constant buffer
	oD3DBufferDesc.ByteWidth = sizeof(SChangesEveryFrameConstantBuffer);
	oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DBufferDesc, nullptr, &m_pD3DChangesEveryFrameConstBuffer)); // Create a constant buffer that changes every frame
	
	// Constant buffer that never changes
	oD3DBufferDesc.ByteWidth = sizeof(SStaticConstantBuffer);

	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DBufferDesc, nullptr, &m_pD3DStaticConstBuffer)); // Constant buffer that never changes

	//
	// Create constant buffers

	// Retrieve a handle to the constant buffers
	m_pD3DXEffectEveryFrameConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBEveryFrame"); // Constant buffer that changes every frame
	if(!m_pD3DXEffectEveryFrameConstBuffer->IsValid())
		return E_FAIL;
	m_pD3DXEffectStaticConstBuffer = m_pD3DXEffect->GetConstantBufferByName("CBStatic"); // Constant buffer that's static
	if(!m_pD3DXEffectStaticConstBuffer->IsValid())
		return E_FAIL;

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: operator!
// Desc: Will return a boolean value signaling if the shader has been
//		 successfully created or not
//---------------------------------------------------------------------------
bool CShader::operator!() const
{
	return (FAILED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Will return a boolean vlaue if the two objects are equal
//---------------------------------------------------------------------------
bool CShader::operator==(CShader *pShader) const
{
	// Compare the compiled shader blobs
	if(m_pD3DCompiledShaderBlob == pShader->m_pD3DCompiledShaderBlob) // The compiled shader blobs are equal
		return false;

	return false; // The two objects are not equal
}

//---------------------------------------------------------------------------
// Name: isValid
// Desc: Will return a boolean value signaling if an error has occured or not
//---------------------------------------------------------------------------
bool CShader::isValid() const
{
	return (SUCCEEDED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: isNotValid
// Desc: Will return a boolean value signaling if an error has occured or not
//---------------------------------------------------------------------------
bool CShader::isNotValid() const
{
	return (FAILED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: getBufferPointer
// Desc: Get the blob of the compiled shader data
//---------------------------------------------------------------------------
void *CShader::getBlobData() const
{
	return m_pD3DCompiledShaderBlob->GetBufferPointer();
}

//---------------------------------------------------------------------------
// Name: getBlobSize
// Desc: Get the size of the compiled blob
//---------------------------------------------------------------------------
SIZE_T CShader::getBlobSize() const
{
	return m_pD3DCompiledShaderBlob->GetBufferSize(); // Get the compiled shader blob size
}

//---------------------------------------------------------------------------
// Name: getInputSignature
// Desc: Get the input signature from the shader
//---------------------------------------------------------------------------
BYTE *CShader::getInputSignature(SIZE_T &rstInputSignatureSize) const
{
	D3DX11_PASS_DESC oD3DXPassDesc; // Will hold pass description

	m_pD3DXEffect->GetTechniqueByIndex(0)->GetPassByIndex(0)->GetDesc(&oD3DXPassDesc); // Get the description of the pass

	rstInputSignatureSize = oD3DXPassDesc.IAInputSignatureSize; // Assign the size of the input signature

	return oD3DXPassDesc.pIAInputSignature; // Return the input signature
}

//---------------------------------------------------------------------------
// Name: getTechniqueByIndex
// Desc: Get a technique by index
//---------------------------------------------------------------------------
ID3DX11EffectTechnique *CShader::getTechniqueByIndex(UINT uiTechniqueIndex) const
{
	return NULL;
}

//---------------------------------------------------------------------------
// Name: getVariableByIndex
// Desc: Get a variable from the shader
//---------------------------------------------------------------------------
ID3DX11EffectVariable *CShader::getVariableByIndex(void *pVariable) const
{
	return NULL;
}

//---------------------------------------------------------------------------
// Name: getVariableByName
// Desc: Get a variable from the shader
//---------------------------------------------------------------------------
ID3DX11EffectVariable *CShader::getVariableByName(void *pVariable) const
{
	return NULL;
}

//---------------------------------------------------------------------------
// Name: getMatrixVariableByIndex
// Desc: Get matrix variable by index from the shader
//---------------------------------------------------------------------------
ID3DX11EffectMatrixVariable *CShader::getMatrixVariableByIndex(UINT uiIndex) const
{
	return m_pD3DXEffect->GetVariableByIndex(uiIndex)->AsMatrix(); // Return the handle of the specified matrix variable
}

//---------------------------------------------------------------------------
// Name: getMatrixVariableByName
// Desc: Get a matrix variable by name
//---------------------------------------------------------------------------
ID3DX11EffectMatrixVariable *CShader::getMatrixVariableByName(std::string oVariableName) const
{
	return m_pD3DXEffect->GetVariableByName(oVariableName.data())->AsMatrix(); // Return the handle of the specified matrix variable
}

//---------------------------------------------------------------------------
// Name: getMatrices
// Desc: Get the matrices from the shader
//---------------------------------------------------------------------------
HRESULT CShader::getMatrices()
{
	if(m_pD3DXEffectWorldMatVariable)
		m_pD3DXEffectWorldMatVariable->GetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oWorldMatrix)); // Retrieve world matrix
	if(m_pD3DXEffectViewMatVariable)
		m_pD3DXEffectViewMatVariable->GetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oViewMatrix)); // Retrieve view matrix
	if(m_pD3DXEffectProjMatVariable)
		m_pD3DXEffectProjMatVariable->GetMatrix(reinterpret_cast<float *>(&g_pStaticConstBuffer->m_oProjectionMatrix)); // Retrieve projection matrix
	if(m_pD3DXEffectHomoMatVariable)
		m_pD3DXEffectHomoMatVariable->GetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix)); // Retrieve homogeneous matrix

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getNumOfPasses
// Desc: Get the number of passes in the technique
//---------------------------------------------------------------------------
UINT CShader::getNumOfPasses() const
{
	return m_oD3DXTechniqueDesc.Passes;
}

//---------------------------------------------------------------------------
// Name: getInputLayout
// Desc: Get the input layout associated with this shader
//---------------------------------------------------------------------------
ID3D11InputLayout *CShader::getInputLayout() const
{
	return m_pD3DInputLayout;
}

//---------------------------------------------------------------------------
// Name: setMatrixVariable
// Desc: Set the matrix variable in the shader
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixVariable(ID3DX11EffectMatrixVariable *pD3DXSourceEffectMatrixVariable, CMatrix4x4 &rDestMatrix)
{
	return pD3DXSourceEffectMatrixVariable->SetMatrix(reinterpret_cast<float *>(&rDestMatrix));
}

//---------------------------------------------------------------------------
// Name: setMatrixVariableByName
// Desc: Set the matrix variable in the shader by it's name
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixVariableByName(std::string oDestMatrixVarNameString, CMatrix4x4 &rDestMatrix)
{
	return m_pD3DXEffect->GetVariableByName(oDestMatrixVarNameString.data())->AsMatrix()->SetMatrix(reinterpret_cast<float *>(&rDestMatrix));
}

//---------------------------------------------------------------------------
// Name: setMatrixVariable
// Desc: Set the matrix variable in the shader
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixVariableByIndex(UINT uiIndex, CMatrix4x4 &rDestMatrix)
{
	return m_pD3DXEffect->GetVariableByIndex(uiIndex)->AsMatrix()->SetMatrix(reinterpret_cast<float *>(&rDestMatrix));
}

//---------------------------------------------------------------------------
// Name: setMatrixArrayVariable
// Desc: Set the matrix array variable in the shader
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixArrayVariable(ID3DX11EffectMatrixVariable *pD3DXSourceFffectMatrixVariable, UINT uiNumOfMatrixElements, CMatrix4x4 *pMatrices)
{
	return pD3DXSourceFffectMatrixVariable->SetMatrixArray(reinterpret_cast<float *>(pMatrices), 0, uiNumOfMatrixElements);
}

//---------------------------------------------------------------------------
// Name: setMatrixArrayVariableByName
// Desc: Set the matrix array variable in the shader
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixArrayVariableByName(std::string oDestMatrixArrayVarNameString, UINT uiNumOfMatrixElements, CMatrix4x4 *pMatrices)
{
	return m_pD3DXEffect->GetVariableByName(oDestMatrixArrayVarNameString.data())->AsMatrix()->SetMatrixArray(reinterpret_cast<float *>(pMatrices), 0, uiNumOfMatrixElements);
}

//---------------------------------------------------------------------------
// Name: setMatrixArrayVariableByIndex
// Desc: Set the matrix array variable in the shader
//---------------------------------------------------------------------------
HRESULT CShader::setMatrixArrayVariableByIndex(UINT uiIndex, UINT uiNumOfMatrixElements, CMatrix4x4 *pMatrices)
{
	return m_pD3DXEffect->GetVariableByIndex(uiIndex)->AsMatrix()->SetMatrixArray(reinterpret_cast<float *>(pMatrices), 0, uiNumOfMatrixElements);
}

//---------------------------------------------------------------------------
// Name: setWorldMatrixVariable
// Desc: Set world transformation matrix
//---------------------------------------------------------------------------
HRESULT CShader::setWorldMatrixVariable(CMatrix4x4 &rWorldMatrix)
{
	return m_pD3DXEffectWorldMatVariable->SetMatrix(reinterpret_cast<float *>(&rWorldMatrix));
}

//---------------------------------------------------------------------------
// Name: setViewMatrixVariable
// Desc: Set view transformation matrix
//---------------------------------------------------------------------------
HRESULT CShader::setViewMatrixVariable(CMatrix4x4 &rViewMatrix)
{
	return m_pD3DXEffectViewMatVariable->SetMatrix(reinterpret_cast<float *>(&rViewMatrix));
}

//---------------------------------------------------------------------------
// Name: setProjMatrixVariable
// Desc: Set projection transformation matrix
//---------------------------------------------------------------------------
HRESULT CShader::setProjMatrixVariable(CMatrix4x4 &rProjMatrix)
{
	return m_pD3DXEffectProjMatVariable->SetMatrix(reinterpret_cast<float *>(&rProjMatrix));
}

//---------------------------------------------------------------------------
// Name: setHomoMatrixVariable
// Desc: Set homogenenous transformation matrix
//---------------------------------------------------------------------------
HRESULT CShader::setHomoMatrixVariable(CMatrix4x4 &rHomoMatrix)
{
	return m_pD3DXEffectHomoMatVariable->SetMatrix(reinterpret_cast<float *>(&rHomoMatrix));
}

//---------------------------------------------------------------------------
// Name: setShaderResourceVariable
// Desc: Set the specified shader resource variable
//---------------------------------------------------------------------------
//HRESULT CShader::setShaderResourceVariable(ID3D11ShaderResourceView *pD3DShaderResourceView)
//{
//	return m_pD3DXEffectShaderResourceVariable->SetResource(pD3DShaderResourceView);
//}
//
////---------------------------------------------------------------------------
//// Name: setShaderResourceVariable
//// Desc: Set the specified shader resource variable
////---------------------------------------------------------------------------
//HRESULT CShader::setShaderResourceVariable(ID3DX11EffectShaderResourceVariable *pD3DXEffectShaderResourceVariable, ID3D11ShaderResourceView *pD3DShaderResourceView)
//{
//	return pD3DXEffectShaderResourceVariable->SetResource(pD3DShaderResourceView);
//}
//
////---------------------------------------------------------------------------
//// Name: setShaderResourceVariable
//// Desc: Set the specified shader resource variable array
////---------------------------------------------------------------------------
//HRESULT CShader::setShaderResourceVariableArray(ID3D11ShaderResourceView **ppD3DShaderResourceView, UINT uiOffset, UINT uiShaderResourceVariableCount)
//{
//	return m_pD3DXEffectShaderResourceVariable->SetResourceArray(ppD3DShaderResourceView, uiOffset, uiShaderResourceVariableCount);
//}
//
////---------------------------------------------------------------------------
//// Name: setShaderResourceVariable
//// Desc: Set the specified shader resource variable array
////---------------------------------------------------------------------------
//HRESULT CShader::setShaderResourceVariableArray(ID3DX11EffectShaderResourceVariable *pD3DXEffectShaderResourceVariable, ID3D11ShaderResourceView **ppD3DShaderResourceView, UINT uiOffset, UINT uiShaderResourceVariableCount)
//{
//	return pD3DXEffectShaderResourceVariable->SetResourceArray(ppD3DShaderResourceView, uiOffset, uiShaderResourceVariableCount);
//}

//---------------------------------------------------------------------------
// Name: setSamplerVariable
// Desc: Set the sampler state variable
//---------------------------------------------------------------------------
void CShader::setSamplerVariable(ID3D11SamplerState *pD3DSamplerState)
{
	//return m_pD3DXEffectSamplerVariable->SetSampler(0, pD3DSamplerState);
	m_pD3DSamplerState = pD3DSamplerState; // Assign sampler state
}

//---------------------------------------------------------------------------
// Name: setInputLayout
// Desc: Bind input layout to the input-assembler stage
//---------------------------------------------------------------------------
void CShader::setInputLayout(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->IASetInputLayout(m_pD3DInputLayout);
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update constant buffers that never changes in the  shader
//---------------------------------------------------------------------------
HRESULT CShader::updateConstantBuffer(SStaticConstantBuffer *pStaticConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	CHECK_COM(pD3DDeviceContext->Map(m_pD3DStaticConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource)); // Get a pointer to the data in the constant buffer

	::memcpy(oD3DMappedSubresource.pData, pStaticConstantBuffer, sizeof(g_pStaticConstBuffer)); // Copy the constant buffers

	pD3DDeviceContext->Unmap(m_pD3DStaticConstBuffer, 0);

	//pD3DDeviceContext->UpdateSubresource(m_pD3DStaticConstBuffer, 0, NULL, reinterpret_cast<void *>(pNeverChangesConstantBuffer), 0, 0); // Update subresource

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update constant buffers that change every frame in the shader
//---------------------------------------------------------------------------
HRESULT CShader::updateConstantBuffer(SChangesEveryFrameConstantBuffer *pChangesEveryFrameConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	CHECK_COM(pD3DDeviceContext->Map(m_pD3DChangesEveryFrameConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource)); // Get a pointer to the data in the constant buffer

	::memcpy(oD3DMappedSubresource.pData, pChangesEveryFrameConstantBuffer, sizeof(SChangesEveryFrameConstantBuffer)); // Copy the constant buffers

	pD3DDeviceContext->Unmap(m_pD3DChangesEveryFrameConstBuffer, 0);

	//pD3DDeviceContext->UpdateSubresource(m_pD3DChangesEveryFrameConstBuffer, 0, NULL, reinterpret_cast<void *>(pChangesEveryFrameConstantBuffer), 0, 0); // Update subresource

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update constant buffers used for materials in the shader
//---------------------------------------------------------------------------
HRESULT CShader::updateConstantBuffer(SMaterialConstantBuffer *pMaterialConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	CHECK_COM(pD3DDeviceContext->Map(m_pD3DMaterialConstbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource)); // Get a pointer to the data in the constant buffer

	::memcpy(oD3DMappedSubresource.pData, pMaterialConstantBuffer, sizeof(SMaterialConstantBuffer)); // Copy the constant buffers

	pD3DDeviceContext->Unmap(m_pD3DMaterialConstbuffer, 0);

	CHECK_COM(m_pD3DXEffectMaterialConstBuffer->SetConstantBuffer(m_pD3DMaterialConstbuffer)); // Set material constant buffer in the shader

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffer
// Desc: Update arbitrary constant buffers
//---------------------------------------------------------------------------
HRESULT CShader::updateConstantBuffer(void *pBuffer, ID3D11DeviceContext *pD3DDeviceContext)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateEveryFrameConstantBuffer
// Desc: Update constant buffers that change every frame
//---------------------------------------------------------------------------
HRESULT CShader::updateEveryFrameConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext)
{
	g_pChangesEveryFrameConstBuffer->buildTransformationMatrices(); // Build the transformation matrices

	//m_pD3DXEffectWorldMatVariable->SetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oWorldMatrix)); // World matrix
	//m_pD3DXEffectInverseTransposeWorldMatVariable->SetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oInverseTransposeWorldMatrix)); // Inverse transpose of world matrix
	//m_pD3DXEffectViewMatVariable->SetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oViewMatrix)); // View matrix
	//m_pD3DXEffectViewProjMatVariable->SetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oViewProjectionMatrix)); // View-projection matrix
	//m_pD3DXEffectHomoMatVariable->SetMatrix(reinterpret_cast<float *>(&g_pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix)); // Homogeneous matrix

	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	// Get a pointer to the data that contains HLSL constant buffers
	CHECK_COM(pD3DDeviceContext->Map(m_pD3DChangesEveryFrameConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource));

	//SChangesEveryFrameConstantBuffer *pChangesEveryFrameConstBuffer = static_cast<SChangesEveryFrameConstantBuffer *>(oD3DMappedSubresource.pData);

	//pChangesEveryFrameConstBuffer->m_oInverseTransposeWorldMatrix = g_pChangesEveryFrameConstBuffer->m_oInverseTransposeWorldMatrix;
	//pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix = g_pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix;

	// Update the constant buffer data that changes every frame
	::memcpy(oD3DMappedSubresource.pData, g_pChangesEveryFrameConstBuffer, sizeof(SChangesEveryFrameConstantBuffer));

	//pChangesEveryFrameConstBuffer->m_oWorldMatrix = g_pChangesEveryFrameConstBuffer->m_oWorldMatrix;
	//pChangesEveryFrameConstBuffer->m_oViewMatrix = g_pChangesEveryFrameConstBuffer->m_oViewMatrix;
	//pChangesEveryFrameConstBuffer->m_oViewProjectionMatrix = g_pChangesEveryFrameConstBuffer->m_oViewProjectionMatrix;
	//pChangesEveryFrameConstBuffer->m_oInverseTransposeWorldMatrix = g_pChangesEveryFrameConstBuffer->m_oInverseTransposeWorldMatrix;
	//pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix = g_pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix;

	pD3DDeviceContext->Unmap(m_pD3DChangesEveryFrameConstBuffer, 0); // Unmap the pointer to the data

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &m_pD3DChangesEveryFrameConstBuffer); // Set constant buffer that changes every frame
	//CHECK_COM(m_pD3DXEffectEveryFrameConstBuffer->SetConstantBuffer(m_pD3DChangesEveryFrameConstBuffer)); // Set a constant buffer that changes every frame in the shader

	//pD3DDeviceContext->UpdateSubresource(m_pD3DChangesEveryFrameConstBuffer, 0, NULL, reinterpret_cast<void *>(g_pChangesEveryFrameConstBuffer), 0, 0); // Update subresource

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateStaticConstantBuffer
// Desc: Update static constant buffers
//---------------------------------------------------------------------------
HRESULT CShader::updateStaticConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->UpdateSubresource(m_pD3DStaticConstBuffer, 0, nullptr, reinterpret_cast<void *>(g_pStaticConstBuffer), 0, 0); // Update constant buffer data

	pD3DDeviceContext->VSSetConstantBuffers(0, 0, &m_pD3DStaticConstBuffer); // Set status constant buffer
	//CHECK_COM(m_pD3DXEffectStaticConstBuffer->SetConstantBuffer(m_pD3DStaticConstBuffer)); // Set constant buffer that never changes in the shader

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateMaterialConstantBuffer
// Desc: Update constant buffers for materials
//---------------------------------------------------------------------------
HRESULT CShader::updateMaterialConstantBuffer(ID3D11DeviceContext *pD3DDeviceContext)
{
	//pD3DDeviceContext->UpdateSubresource(m_pD3DMaterialConstbuffer, 0, NULL, reinterpret_cast<void *>(g_pMatLightConstBuffer), 0, 0); // Update subresource

	D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	// Get a pointer to the data that contains HLSL constant buffers
	CHECK_COM(pD3DDeviceContext->Map(m_pD3DChangesEveryFrameConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource));

	//::memcpy(oD3DMappedSubresource.pData, &m_o

	pD3DDeviceContext->Unmap(m_pD3DChangesEveryFrameConstBuffer, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: apply
// Desc: Apply the specified pass based on it's index
//---------------------------------------------------------------------------
HRESULT CShader::apply(UINT uiPassIndex, ID3D11DeviceContext *pD3DDeviceContext)
{
	return m_pD3DXEffect->GetTechniqueByIndex(0)->GetPassByIndex(uiPassIndex)->Apply(0, pD3DDeviceContext); // Apply pass
}

//---------------------------------------------------------------------------
// Name: apply
// Desc: Apply the specified pass based on it's index
//---------------------------------------------------------------------------
HRESULT CShader::apply(UINT uiTechniqueIndex, UINT uiPassIndex, ID3D11DeviceContext *pD3DDeviceContext)
{
	return m_pD3DXEffect->GetTechniqueByIndex(uiTechniqueIndex)->GetPassByIndex(uiPassIndex)->Apply(0, pD3DDeviceContext); // Apply pass
}

//---------------------------------------------------------------------------
// Name: applyAllPasses
// Desc: Apply all the passes in the specified technique; this method will
//		 return true if there are more passes left else false if all the
//		 passes have been applied
//---------------------------------------------------------------------------
bool CShader::applyAllPasses(ID3D11DeviceContext *pD3DDeviceContext)
{
	static UINT uiPassCount; // Will hold a value of the current pass count

	// Make sure all the passes are applied
	if(uiPassCount < m_oD3DXTechniqueDesc.Passes) // Passes are left to be applied
	{
		m_pD3DXEffect->GetTechniqueByIndex(0)->GetPassByIndex(uiPassCount)->Apply(NULL, pD3DDeviceContext); // Apply the specified pass

		uiPassCount++; // Since a pass has been applied increment the pass counter

		return true; // Signal to specify there are more passes left
	}
	else // All the passes have been applied
	{
		uiPassCount = 0; // Reset the pass counter

		return false; // Signal to specify that all the passes have been applied or nil pass applied
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: applyAllTechniquesAndPasses
// Desc: Apply all the techniques and passes
//---------------------------------------------------------------------------
bool CShader::applyAllTechniquesAndPasses(ID3D11DeviceContext *pD3DDeviceContext)
{
	// Iterate through all the techniqes
	for(DWORD dwCount = 0; dwCount < m_oD3DXEffectDesc.Techniques; dwCount++)
	{
		applyAllPasses(pD3DDeviceContext); // Apply all the passes
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: createConstantBuffers
// Desc: Create constant buffers
//---------------------------------------------------------------------------
HRESULT CShader::createConstantBuffers(ID3D11Device *pD3DDevice)
{
	// Create constant buffers
	//

	D3D11_BUFFER_DESC oD3DBufferDesc = {0};
	oD3DBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Bind constant buffer

	// Constant buffer that's static
	oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // GPU read/write
	oD3DBufferDesc.ByteWidth = sizeof(SStaticConstantBuffer);
	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DBufferDesc, nullptr, &m_pD3DStaticConstBuffer));

	oD3DBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // GPU read only; CPU write only permissions
	oD3DBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU can change it's contents

	// Constant buffer that changes every frame
	oD3DBufferDesc.ByteWidth = sizeof(SChangesEveryFrameConstantBuffer);
	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DBufferDesc, nullptr, &m_pD3DChangesEveryFrameConstBuffer));
	
	// Constant buffer for materials
	oD3DBufferDesc.ByteWidth = sizeof(SMaterialConstantBuffer);
	CHECK_COM(pD3DDevice->CreateBuffer(&oD3DBufferDesc, nullptr, &m_pD3DMaterialConstbuffer));

	//
	// Create constant buffers

	return S_OK;
}

//CShader g_oGlobalLightingShader;
//CShader *g_pGlobalLightingShader = &g_oGlobalLightingShader;
//
//CShader g_oPhongLightingShader;
//CShader *g_pPhongLightingShader = &g_oPhongLightingShader;
//
//CShader g_oMotionBlurShader;
//CShader *g_pMotionBlurEffect = &g_oMotionBlurShader;
//
//CShader g_oScreenAlignedQuadShader;
//CShader *g_pScreenAlignedQuadShader = &g_oScreenAlignedQuadShader;
//
//CShader g_oNormalShader;
//CShader *g_pNormalShader = &g_oNormalShader;

SStaticConstantBuffer g_oStaticConstantBuffer;
SStaticConstantBuffer *g_pStaticConstBuffer = &g_oStaticConstantBuffer;

SChangesEveryFrameConstantBuffer g_oChangesEveryFrameConstantBuffer;
SChangesEveryFrameConstantBuffer *g_pChangesEveryFrameConstBuffer = &g_oChangesEveryFrameConstantBuffer;