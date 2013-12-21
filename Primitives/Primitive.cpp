// Primitive.cpp: Methods for loading and manipulating primitives
// Copyright (C) 2010-2013 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "InputLayout.h"
#include "Primitive.h"
#include "AssetLoader.h"

//---------------------------------------------------------------------------
// Name: CBasePrimitive
// Desc: CBasePrimitive
//---------------------------------------------------------------------------
CBasePrimitive::CBasePrimitive()
{
	m_pD3DVertexBuffer = nullptr;
	m_pD3DIndexBuffer = nullptr;

	::memset(&m_oD3DBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	::memset(&m_oD3DSubrsrcData, 0, sizeof(D3D11_SUBRESOURCE_DATA));

	m_uiVertexStride = m_uiOffset = m_uiTotalIndices = m_uiTotalVertices = 0;

	m_oD3DPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

	m_hResult = S_OK;
}

//---------------------------------------------------------------------------
// Name: ~CBasePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CBasePrimitive::~CBasePrimitive()
{
	FREE_COM(m_pD3DIndexBuffer);
	FREE_COM(m_pD3DVertexBuffer);
}

//---------------------------------------------------------------------------
// Name: getPrimitiveTopology
// Desc: Get the primitive topology
//---------------------------------------------------------------------------
D3D_PRIMITIVE_TOPOLOGY CBasePrimitive::getPrimitiveTopology() const
{
	return m_oD3DPrimitiveTopology;
}

//---------------------------------------------------------------------------
// Name: getVertexBuffer
// Desc: Get the vertex buffer
//---------------------------------------------------------------------------
ID3D11Buffer *CBasePrimitive::getVertexBuffer() const
{
	return m_pD3DVertexBuffer;
}

//---------------------------------------------------------------------------
// Name: getIndexBuffer
// Desc: Get the index buffer
//---------------------------------------------------------------------------
ID3D11Buffer *CBasePrimitive::getIndexBuffer() const
{
	return m_pD3DIndexBuffer;
}

//---------------------------------------------------------------------------
// Name: getTotalNumberOfVertices
// Desc: Get the total number of vertices
//---------------------------------------------------------------------------
UINT CBasePrimitive::getTotalNumberOfVertices() const
{
	return m_uiTotalVertices;
}

//---------------------------------------------------------------------------
// Name: getTotalNumberOfIndices
// Desc: Get the total number of indices
//---------------------------------------------------------------------------
UINT CBasePrimitive::getTotalNumberOfIndices() const
{
	return m_uiTotalIndices;
}

//---------------------------------------------------------------------------
// Name: getVertexStride
// Desc: Get the size of the element of vertex buffer
//---------------------------------------------------------------------------
UINT CBasePrimitive::getVertexStride() const
{
	return m_uiVertexStride;
}

//---------------------------------------------------------------------------
// Name: setMaterial
// Desc: Set the material for this primitive
//---------------------------------------------------------------------------
//void CBasePrimitive::setMaterial(SMaterial *pMaterial)
//{
//	m_pMaterial = pMaterial;
//}
//
////---------------------------------------------------------------------------
//// Name: setMaterialAttributes
//// Desc: Get the total number of indices
////---------------------------------------------------------------------------
//void CBasePrimitive::setMaterialAttributes(const SMaterialConstantBuffer *pMaterialConstantBuffer)
//{
//	m_oMaterialConstantBuffer = pMaterialConstantBuffer;
//}
//
////---------------------------------------------------------------------------
//// Name: setDefaultMaterialAttributes
//// Desc: Set the default material attributes
////---------------------------------------------------------------------------
//void CBasePrimitive::setDefaultMaterialAttributes(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
//{
//	pShader->updateConstantBuffer(&m_oMaterialConstantBuffer, pD3DDeviceContext); // Update the material constant buffers
//}
//
////---------------------------------------------------------------------------
//// Name: setMaterialAttributes
//// Desc: Get the total number of indices
////---------------------------------------------------------------------------
//void CBasePrimitive::setMaterialAttributes(const SShinyMaterialConstantBuffer *pMaterialConstantBuffer)
//{
//}
//
////---------------------------------------------------------------------------
//// Name: setMaterialAttributes
//// Desc: Get the total number of indices
////---------------------------------------------------------------------------
//void CBasePrimitive::setMaterialAttributes(CVector4 m_oDiffuseMaterialColor, CVector4 m_oDiffuseLightColor, CVector4 m_oAmbientMaterialColor, CVector4 m_oAmbientLightColor)
//{
//}
//
////---------------------------------------------------------------------------
//// Name: setMaterialAttributes
//// Desc: Get the total number of indices
////---------------------------------------------------------------------------
//void CBasePrimitive::setMaterialAttributes(CVector4 m_oDiffuseMaterialColor, CVector4 m_oDiffuseLightColor, CVector4 m_oAmbientMaterialColor, CVector4 m_oAmbientLightColor, CVector4 m_oSpecularMaterialColor, CVector4 m_oSpecularLightColor, float m_fSpecularPower)
//{
//}

//---------------------------------------------------------------------------
// Name: isValid
// Desc: Determines whther the primitive creation succeeded or not
//---------------------------------------------------------------------------
bool CBasePrimitive::isValid() const
{
	return (SUCCEEDED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: isNotValid
// Desc: Determines whther the primitive creation succeeded or not
//---------------------------------------------------------------------------
bool CBasePrimitive::isNotValid() const
{
	return (FAILED(m_hResult) ? true : false);
}

//---------------------------------------------------------------------------
// Name: CInstanceBasePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CInstanceBasePrimitive::CInstanceBasePrimitive()
{
	m_pD3DInstanceBuffer = nullptr;

	//m_pInstancesMatrix = nullptr;

	// Zero out arrays
	::memset(&m_uiStrideArray, 0, ARRAY_SIZE(m_uiStrideArray, UINT)); // Stride array
	::memset(&m_uiOffsetArray, 0, ARRAY_SIZE(m_uiOffsetArray, UINT)); // Offset array

	::memset(&m_oD3DMappedSubresource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
}

//---------------------------------------------------------------------------
// Name: ~CInstanceBasePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CInstanceBasePrimitive::~CInstanceBasePrimitive()
{
	FREE_COM(m_pD3DInstanceBuffer);

	//DELETE_FREE_ARRAY(m_pInstancesMatrix); // Instances matrix
}

//---------------------------------------------------------------------------
// Name: getNumOfInstances
// Desc: Get the number of instances
//---------------------------------------------------------------------------
UINT CInstanceBasePrimitive::getNumOfInstances() const
{
	return m_uiNumOfInstances;
}

//---------------------------------------------------------------------------
// Name: getInstaceDataBuffer
// Desc: Get the instance data buffer
//---------------------------------------------------------------------------
ID3D11Buffer *CInstanceBasePrimitive::getInstanceDataBuffer() const
{
	return m_pD3DInstanceBuffer;
}

//---------------------------------------------------------------------------
// Name: updateInstanceBuffer
// Desc: Update the instance buffer
//---------------------------------------------------------------------------
HRESULT CInstanceBasePrimitive::updateInstanceBuffer(void *pSourceData, UINT uiSizeOfElement, UINT uiNumOfInstancesToUpdate, ID3D11DeviceContext *pD3DDeviceContext)
{
	//D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	//// Get a pointer to the instance data
	//CHECK_COM(pD3DDeviceContext->Map(m_pD3DInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource));

	//// Copy the data for the instances to the mapped subresource data
	//::memcpy(oD3DMappedSubresource.pData, pSourceData, m_uiNumOfInstances * uiSizeOfElement);

	//pD3DDeviceContext->Unmap(m_pD3DInstanceBuffer, 0);

	pD3DDeviceContext->UpdateSubresource(m_pD3DInstanceBuffer, 0, nullptr, pSourceData, 0, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: updateInstanceBuffer
// Desc: Update the instance buffer
//---------------------------------------------------------------------------
HRESULT CInstanceBasePrimitive::updateInstanceBuffer(ID3D11DeviceContext *pD3DDeviceContext)
{
	//D3D11_MAPPED_SUBRESOURCE oD3DMappedSubresource;

	//// Get a pointer to the matrix instance data
	//CHECK_COM(pD3DDeviceContext->Map(m_pD3DInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &oD3DMappedSubresource));

	//// Copy the matrices for the instances to the mapped subresource data
	//::memcpy(oD3DMappedSubresource.pData, m_pInstancesMatrix, m_uiNumOfInstances * sizeof(CMatrix4x4));

	//pD3DDeviceContext->Unmap(m_pD3DInstanceBuffer, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: CLinePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CLinePrimitive::CLinePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CLinePrimitive
// Desc: Constructor
//---------------------------------------------------------------------------
CLinePrimitive::CLinePrimitive(float fHeight)
{
}

//---------------------------------------------------------------------------
// Name: ~CLinePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CLinePrimitive::~CLinePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a line primitive with the specified height
//---------------------------------------------------------------------------
HRESULT CLinePrimitive::create(float fHeight)
{
	// Line
	SVertexNormalTexture2D oLineVertices[] =
	{
		SVertexNormalTexture2D(CVector3(0.0f, 0.0f, -fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(0.0f, 1.0f)), // Bottom vertex
		SVertexNormalTexture2D(CVector3(0.0f, 0.0f, fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(0.0f, 0.0f)), // Top vertex
	};

	// Indices of the plane
	DWORD dwPlaneIndices[] =
	{
		0, 1, 2, 0, 2, 3,
	};

	m_uiVertexStride = sizeof(SVertexNormalTexture2D); // Stride of vertex format

	m_uiTotalIndices = ARRAY_SIZE(dwPlaneIndices, DWORD);

	m_uiOffset = 0;

	// Vertex buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(SVertexNormalTexture2D) * ARRAY_SIZE(oLineVertices, SVertexNormalTexture2D); // Size of the vertices
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Vertex buffer subresource data
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(oLineVertices); // Vertices

	// Create vertex buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer));

	// Index buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Bind index buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(DWORD) * sizeof(dwPlaneIndices); // Size of the indices
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Index buffer subresource data
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(dwPlaneIndices); // Indices

	// Create index buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DIndexBuffer));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the line primitive
//---------------------------------------------------------------------------
void CLinePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	//g_pInputLayout->setPos(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CCirclePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CCirclePrimitive::CCirclePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CCirclePrimitive
// Desc: Constructor
//---------------------------------------------------------------------------
CCirclePrimitive::CCirclePrimitive(float fRadius, DWORD dwSlices)
{
	ASSIGN_COM(create(fRadius, dwSlices));
}

//---------------------------------------------------------------------------
// Name: ~CCirclePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CCirclePrimitive::~CCirclePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: 
//---------------------------------------------------------------------------
HRESULT CCirclePrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a circle with the specified properties
//---------------------------------------------------------------------------
HRESULT CCirclePrimitive::create(float fRadius, DWORD dwSlices)
{
	float fXCoord, fYCoord;

	// If there are less than 4 slices then return error
	if(dwSlices < 4)
		return E_FAIL;

	DWORD *pdwVertices = new DWORD[dwSlices]; // Allocate memory for the vertices of the circle

	SAFE_DELETE_ARRAY(pdwVertices); // Deallocate memory allocated for the vertices of the circle

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the circle
//---------------------------------------------------------------------------
void CCirclePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	//g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CSpherePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CSpherePrimitive::CSpherePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CSpherePrimitive
// Desc: Create a sphere with the specified properties
//---------------------------------------------------------------------------
CSpherePrimitive::CSpherePrimitive(float fRadius, DWORD dwSlices, DWORD dwStacks)
{
	ASSIGN_COM(create(fRadius, dwSlices, dwStacks));
}

//---------------------------------------------------------------------------
// Name: ~CSpherePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CSpherePrimitive::~CSpherePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: 
//---------------------------------------------------------------------------
HRESULT CSpherePrimitive::create()
{
	CHECK_COM(create(1.0f, 8, 1));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a sphere with the specified properties
//---------------------------------------------------------------------------
HRESULT CSpherePrimitive::create(float fRadius, DWORD dwSlices, DWORD dwStacks)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the sphere
//---------------------------------------------------------------------------
void CSpherePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CCylinderPrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CCylinderPrimitive::CCylinderPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CCylinderPrimitive
// Desc: Parameterized constructor
//---------------------------------------------------------------------------
CCylinderPrimitive::CCylinderPrimitive(float fRadius1, float fRadius2, float fLength, DWORD dwSlices, DWORD dwStacks)
{
	ASSIGN_COM(create(fRadius1, fRadius2, fLength, dwSlices, dwStacks));
}

//---------------------------------------------------------------------------
// Name: ~CCylinderPrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CCylinderPrimitive::~CCylinderPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: 
//---------------------------------------------------------------------------
HRESULT CCylinderPrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a cylinder with the specified properties
//---------------------------------------------------------------------------
HRESULT CCylinderPrimitive::create(float fRadius1, float fRadius2, float fLength, DWORD dwSlices, DWORD dwStacks)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the cylinder
//---------------------------------------------------------------------------
void CCylinderPrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CCubePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CCubePrimitive::CCubePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CCubePrimitive
// Desc: Parameterized constructor
//---------------------------------------------------------------------------
CCubePrimitive::CCubePrimitive(float fWidth, float fHeight, float fDepth)
{
	ASSIGN_COM(create(fWidth, fHeight, fDepth));
}

//---------------------------------------------------------------------------
// Name: ~CCubePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CCubePrimitive::~CCubePrimitive()
{

}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a cube primitive
//---------------------------------------------------------------------------
HRESULT CCubePrimitive::create()
{
	RETURN_COM(create(1.0f, 1.0f, 1.0f));
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a cube primitive
//---------------------------------------------------------------------------
HRESULT CCubePrimitive::create(float fWidth, float fHeight, float fDepth)
{
	// Vertices of the cube
	SVertexNormalTangentBinormalTexture2D oCubeVertices[] =
	{
		// Front part
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, -fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, -fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, -fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, -fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		// Back part
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		// Left part
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, -fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, -fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		// Right part
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, -fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, -fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		// Above part
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, -fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, fHeight, fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, fHeight, -fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		// Below part
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, -fDepth), CVector2(0.0f, 1.0f)), // Lower left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(-fWidth, -fHeight, fDepth), CVector2(0.0f, 0.0f)), // Upper left vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, fDepth), CVector2(1.0f, 0.0f)), // Upper right vertex
		SVertexNormalTangentBinormalTexture2D(CVector3(fWidth, -fHeight, -fDepth), CVector2(1.0f, 1.0f)), // Lower right vertex

		//// Front part
		//SVertexNormalTexture2D(-fWidth, -fHeight, -fDepth, CVector3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(-fWidth, fHeight, -fDepth, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(fWidth, fHeight, -fDepth, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(fWidth, -fHeight, -fDepth, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f), // Lower right vertex

		//// Back part
		//SVertexNormalTexture2D(-fWidth, -fHeight, fDepth, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(-fWidth, fHeight, fDepth, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(fWidth, fHeight, fDepth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(fWidth, -fHeight, fDepth, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), // Lower right vertex

		//// Left part
		//SVertexNormalTexture2D(-fWidth, -fHeight, fDepth, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(-fWidth, fHeight, fDepth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(-fWidth, fHeight, -fDepth, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(-fWidth, -fHeight, -fDepth, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Right part
		//SVertexNormalTexture2D(fWidth, -fHeight, -fDepth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(fWidth, fHeight, -fDepth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(fWidth, fHeight, fDepth, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(fWidth, -fHeight, fDepth, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Above part
		//SVertexNormalTexture2D(-fWidth, fHeight, -fDepth, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(-fWidth, fHeight, fDepth, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(fWidth, fHeight, fDepth, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(fWidth, fHeight, -fDepth, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Below part
		//SVertexNormalTexture2D(-fWidth, -fHeight, -fDepth, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertexNormalTexture2D(-fWidth, -fHeight, fDepth, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertexNormalTexture2D(fWidth, -fHeight, fDepth, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertexNormalTexture2D(fWidth, -fHeight, -fDepth, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		// Front part
		//SVertex(-fWidth, -fHeight, -fDepth, 0.0f, 0.0f, -cosf(45.0f), 0.0f, 1.0f), // Lower left vertex
		//SVertex(-fWidth, fHeight, -fDepth, 0.0f, 0.0f, -cosf(45.0f), 0.0f, 0.0f), // Upper left vertex
		//SVertex(fWidth, fHeight, -fDepth, 0.0f, 0.0f, -cosf(45.0f), 1.0f, 0.0f), // Upper right vertex
		//SVertex(fWidth, -fHeight, -fDepth, 0.0f, 0.0f, -cosf(45.0f), 1.0f, 1.0f), // Lower right vertex

		//// Back part
		//SVertex(-fWidth, -fHeight, fDepth, 0.0f, 0.0f, cosf(45.0f), 0.0f, 1.0f), // Lower left vertex
		//SVertex(-fWidth, fHeight, fDepth, 0.0f, 0.0f, cosf(45.0f), 0.0f, 0.0f), // Upper left vertex
		//SVertex(fWidth, fHeight, fDepth, 0.0f, 0.0f, cosf(45.0f), 1.0f, 0.0f), // Upper right vertex
		//SVertex(fWidth, -fHeight, fDepth, 0.0f, 0.0f, cosf(45.0f), 1.0f, 1.0f), // Lower right vertex

		//// Left part
		//SVertex(-fWidth, -fHeight, fDepth, -cosf(45.0f), 0.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertex(-fWidth, fHeight, fDepth, -cosf(45.0f), 0.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertex(-fWidth, fHeight, -fDepth, -cosf(45.0f), 0.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertex(-fWidth, -fHeight, -fDepth, -cosf(45.0f), 0.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Right part
		//SVertex(fWidth, -fHeight, -fDepth, cosf(45.0f), 0.0f, 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertex(fWidth, fHeight, -fDepth, cosf(45.0f), 0.0f, 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertex(fWidth, fHeight, fDepth, cosf(45.0f), 0.0f, 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertex(fWidth, -fHeight, fDepth, cosf(45.0f), 0.0f, 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Above part
		//SVertex(-fWidth, fHeight, -fDepth, 0.0f, cosf(45.0f), 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertex(-fWidth, fHeight, fDepth, 0.0f, cosf(45.0f), 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertex(fWidth, fHeight, fDepth, 0.0f, cosf(45.0f), 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertex(fWidth, fHeight, -fDepth, 0.0f, cosf(45.0f), 0.0f, 1.0f, 1.0f), // Lower right vertex

		//// Below part
		//SVertex(-fWidth, -fHeight, -fDepth, 0.0f, -cosf(45.0f), 0.0f, 0.0f, 1.0f), // Lower left vertex
		//SVertex(-fWidth, -fHeight, fDepth, 0.0f, -cosf(45.0f), 0.0f, 0.0f, 0.0f), // Upper left vertex
		//SVertex(fWidth, -fHeight, fDepth, 0.0f, -cosf(45.0f), 0.0f, 1.0f, 0.0f), // Upper right vertex
		//SVertex(fWidth, -fHeight, -fDepth, 0.0f, -cosf(45.0f), 0.0f, 1.0f, 1.0f), // Lower right vertex
	};

	// Indices of the box
	DWORD dwIndices[] =
	{
		0, 1, 2, 0, 2, 3, // Front part
		6, 5, 4, 6, 4, 7, // Back part
		8, 9, 10, 8, 10, 11, // Left-side part
		12, 13, 14, 12, 14, 15, // Right-side part
		16, 17, 18, 16, 18, 19, // Top part
		22, 21, 20, 22, 20, 23, // Bottom part
	};

	SVertexTexture2D oGeometryVertex[3];

	CVector3 oVertex, oNormalVector, oTangentVector, oBinormalVector; // Will hold vertex coordinates, normal vector, tangent vector and binormal vector

	DWORD dwFaceCount = ARRAY_SIZE(oCubeVertices, SVertexNormalTangentBinormalTexture2D) / 3; // Calculate the number of faces; offset 4 is for the above and below faces since they have been created via index buffers

	// Iterate through all the faces of this geometry to calculate normal, tangent and binormal vectors
	for(DWORD dwFaceIndex = 0, dwVertexIndex = 0; dwFaceIndex < dwFaceCount; dwFaceIndex++)
	{
		// Get the vertex data of this face including vertices and texture coordinates

		// 1st vertex
		oGeometryVertex[0].m_oVertex = CVector3(oCubeVertices[dwVertexIndex].m_oVertex.x, oCubeVertices[dwVertexIndex].m_oVertex.y, oCubeVertices[dwVertexIndex].m_oVertex.z); // Vertex
		oGeometryVertex[0].m_oUV = CVector2(oCubeVertices[dwVertexIndex].m_oUV.x, oCubeVertices[dwVertexIndex].m_oUV.y); // Texture coordinate

		dwVertexIndex++;

		// 2nd vertex
		oGeometryVertex[1].m_oVertex = CVector3(oCubeVertices[dwVertexIndex].m_oVertex.x, oCubeVertices[dwVertexIndex].m_oVertex.y, oCubeVertices[dwVertexIndex].m_oVertex.z); // Vertex
		oGeometryVertex[1].m_oUV = CVector2(oCubeVertices[dwVertexIndex].m_oUV.x, oCubeVertices[dwVertexIndex].m_oUV.y); // Texture coordinate

		dwVertexIndex++;

		// 3rd vertex
		oGeometryVertex[2].m_oVertex = CVector3(oCubeVertices[dwVertexIndex].m_oVertex.x, oCubeVertices[dwVertexIndex].m_oVertex.y, oCubeVertices[dwVertexIndex].m_oVertex.z); // Vertex
		oGeometryVertex[2].m_oUV = CVector2(oCubeVertices[dwVertexIndex].m_oUV.x, oCubeVertices[dwVertexIndex].m_oUV.y); // Texture coordinate

		dwVertexIndex++;

		// Compute normal, tangent and binormal from the above vertex data
		//CMath::vectorComputeNormalTangentBinormal(oGeometryVertex[0], oGeometryVertex[1], oGeometryVertex[2], oNormalVector, oTangentVector, oBinormalVector);
		CMath::vectorComputeTangentBinormal(oGeometryVertex[0], oGeometryVertex[1], oGeometryVertex[2], oTangentVector, oBinormalVector);
		/*CMath::vectorComputeNormal(CVector3(oGeometryVertex[0].m_oVertex.x, oGeometryVertex[0].m_oVertex.y, oGeometryVertex[0].m_oVertex.z), 
			CVector3(oGeometryVertex[1].m_oVertex.x, oGeometryVertex[1].m_oVertex.y, oGeometryVertex[1].m_oVertex.z), 
			CVector3(oGeometryVertex[2].m_oVertex.x, oGeometryVertex[2].m_oVertex.y, oGeometryVertex[2].m_oVertex.z), 
			oNormalVector);*/
		CMath::vectorComputeNormal(oTangentVector, oBinormalVector, oNormalVector); // Compute normal from tangent and binormal

		// Assign the calculated normal, tangent and binormal in the vertex buffer
		oCubeVertices[dwVertexIndex - 1].m_oNormalVector = oNormalVector;
		oCubeVertices[dwVertexIndex - 1].m_oBinormalVector = oBinormalVector;
		oCubeVertices[dwVertexIndex - 1].m_oTangentVector = oTangentVector;

		oCubeVertices[dwVertexIndex - 2].m_oNormalVector = oNormalVector;
		oCubeVertices[dwVertexIndex - 2].m_oBinormalVector = oBinormalVector;
		oCubeVertices[dwVertexIndex - 2].m_oTangentVector = oTangentVector;

		oCubeVertices[dwVertexIndex - 3].m_oNormalVector = oNormalVector;
		oCubeVertices[dwVertexIndex - 3].m_oBinormalVector = oBinormalVector;
		oCubeVertices[dwVertexIndex - 3].m_oTangentVector = oTangentVector;
	}

	m_uiVertexStride = sizeof(SVertexNormalTangentBinormalTexture2D); // Stride of vertex format

	m_uiTotalIndices = ARRAY_SIZE(dwIndices, DWORD); // Total indices

	// Vertex buffer description
	m_oD3DBufferDesc.ByteWidth = m_uiVertexStride * ARRAY_SIZE(oCubeVertices, SVertexNormalTangentBinormalTexture2D); // Size of the vertex buffer
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Vertex buffer
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// 
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(oCubeVertices); // 

	// Create vertex buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer));

	// Index buffer description
	m_oD3DBufferDesc.ByteWidth = sizeof(DWORD) * sizeof(dwIndices); // Size of the index buffer
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Index buffer
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(dwIndices);

	// Create index buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DIndexBuffer));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the cube
//---------------------------------------------------------------------------
void CCubePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	pShader->updateConstantBuffer(m_pMaterial, pD3DDeviceContext);

	//g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CInstanceCubePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CInstanceCubePrimitive::CInstanceCubePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CInstanceCubePrimitive
// Desc: Parameterized constructor
//---------------------------------------------------------------------------
CInstanceCubePrimitive::CInstanceCubePrimitive(float fWidth, float fHeight, float fDepth, UINT uiNumOfInstances)
{
	ASSIGN_COM(create(fWidth, fHeight, fDepth, uiNumOfInstances));
}

//---------------------------------------------------------------------------
// Name: ~CInstanceCubePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CInstanceCubePrimitive::~CInstanceCubePrimitive()
{

}

//---------------------------------------------------------------------------
// Name: createInstanced
// Desc: Create an instanced cube primitive
//---------------------------------------------------------------------------
HRESULT CInstanceCubePrimitive::create(float fWidth, float fHeight, float fDepth, UINT uiNumOfInstances)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: drawInstanced
// Desc: Render the instanced cube
//---------------------------------------------------------------------------
void CInstanceCubePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
}

//---------------------------------------------------------------------------
// Name: CCapsulePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CCapsulePrimitive::CCapsulePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: ~CCapsulePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CCapsulePrimitive::~CCapsulePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a capsule primitive
//---------------------------------------------------------------------------
HRESULT CCapsulePrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Draw capsule primitive
//---------------------------------------------------------------------------
void CCapsulePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CGridPrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CGridPrimitive::CGridPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CGridPrimitive
// Desc: Constructor
//---------------------------------------------------------------------------
CGridPrimitive::CGridPrimitive(DWORD dwNumOfCellsPerRow, DWORD dwNumOfCellsPerColumn, float fXSpacePerCell, float fZSpacePerCell)
{
	ASSIGN_COM(create(dwNumOfCellsPerRow, dwNumOfCellsPerColumn, fXSpacePerCell, fZSpacePerCell));
}

//---------------------------------------------------------------------------
// Name: ~CGridPrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CGridPrimitive::~CGridPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: 
//---------------------------------------------------------------------------
HRESULT CGridPrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a grid with the specified properties
//---------------------------------------------------------------------------
HRESULT CGridPrimitive::create(DWORD dwNumOfCellsPerRow, DWORD dwNumOfCellsPerColumn, float fXSpacePerCell, float fZSpacePerCell)
{
	DWORD dwNumOfVerticesPerRow, dwNumOfVerticesPerColumn, dwTotalVertices, dwTotalTriangles;

	dwNumOfVerticesPerRow = dwNumOfCellsPerRow + 1; // Number of vertices per-row
	dwNumOfVerticesPerColumn = dwNumOfCellsPerColumn + 1; // Number of vertices per-column

	dwTotalVertices = dwNumOfVerticesPerRow * dwNumOfVerticesPerColumn; // Total number of vertices
	m_uiTotalIndices = dwNumOfCellsPerRow * dwNumOfCellsPerColumn * 6; // Total number of indices
	dwTotalTriangles = dwNumOfCellsPerRow * dwNumOfCellsPerColumn * 2; // Total number of triangles

	// Allocate memory for the vertices of the grid
	SVertex *pGridVertices = new SVertex[dwTotalVertices];

	// Allocate memory for the indices
	DWORD *pdwGridIndices = new DWORD[dwNumOfCellsPerRow * dwNumOfCellsPerColumn * 6];

	// Loop to create vertices for the grid
	for(DWORD dwColumn = 0; dwColumn < dwNumOfCellsPerColumn; dwColumn++) // Column
	{
		// Row
		for(DWORD dwRow = 0; dwRow < dwNumOfCellsPerRow; dwRow++) // Row
		{
			pGridVertices[dwColumn] = SVertexNormalTexture2D(CVector3(static_cast<float>(dwColumn), 0.0f, static_cast<float>(dwRow)), CVector3(0.0f, 1.0f, 0.0f), CVector2(0.5f, 0.5f)); // Construct grid vertex
		}
	}

	// Loop to create indices for the grid
	for(DWORD dwCount = 0; dwCount < dwTotalTriangles; dwCount++)
	{
		pdwGridIndices[dwCount * 3 + 0] = 0; // Index of indices 0, 3, 6...
		pdwGridIndices[dwCount * 3 + 1] = 0; // Index of indices 1, 4, 7...
		pdwGridIndices[dwCount * 3 + 2] = 0; // Index of indices 2, 5, 8...
	}

	m_uiVertexStride = sizeof(SVertexNormalTexture2D); // Stride of vertex format

	m_uiOffset = 0; // Offset

	// Vertex buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(SVertexNormalTexture2D) * dwTotalVertices; // Size of the vertex buffer
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(pGridVertices); // Grid vertices

	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer)); // Create vertex buffer

	// Index buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Bind index buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(DWORD) * m_uiTotalIndices; // Size of the index buffer
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(pdwGridIndices); // Grid indices

	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DIndexBuffer));

	// Deallocate the memory occupied for the grid
	SAFE_DELETE_ARRAY(pGridVertices); // Vertices
	SAFE_DELETE_ARRAY(pdwGridIndices); // Indices

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the grid
//---------------------------------------------------------------------------
void CGridPrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CPlanePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CPlanePrimitive::CPlanePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CPlanePrimitive
// Desc: Constructor to create a plane
//---------------------------------------------------------------------------
CPlanePrimitive::CPlanePrimitive(float fWidth, float fHeight)
{
	ASSIGN_COM(create(fWidth, fHeight));
}

//---------------------------------------------------------------------------
// Name: ~CPlanePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CPlanePrimitive::~CPlanePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a plane
//---------------------------------------------------------------------------
HRESULT CPlanePrimitive::create()
{
	RETURN_COM(create(1.0f, 1.0f));
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a plane with the specified properties
//---------------------------------------------------------------------------
HRESULT CPlanePrimitive::create(float fWidth, float fHeight)
{
	// Plane on the xz plane
	SVertexNormalTexture2D oPlaneVertices[] =
	{
		SVertexNormalTexture2D(CVector3(-fWidth, 0.0f, -fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(0.0f, 1.0f)), // Near-left vertex
		SVertexNormalTexture2D(CVector3(-fWidth, 0.0f, fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(0.0f, 0.0f)), // Far-left vertex
		SVertexNormalTexture2D(CVector3(fWidth, 0.0f, fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(1.0f, 0.0f)), // Far-right vertex
		SVertexNormalTexture2D(CVector3(fWidth, 0.0f, -fHeight), CVector3(0.0f, 1.0f, 0.0f), CVector2(1.0f, 1.0f)), // Near-right vertex
	};

	// Indices of the plane
	DWORD dwPlaneIndices[] =
	{
		0, 1, 2, 0, 2, 3,
	};

	m_uiVertexStride = sizeof(SVertexNormalTexture2D); // Stride of vertex format

	m_uiTotalIndices = ARRAY_SIZE(dwPlaneIndices, DWORD); // Total number of indices

	m_uiOffset = 0;

	// Vertex buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(SVertexNormalTexture2D) * ARRAY_SIZE(oPlaneVertices, SVertexNormalTexture2D); // Size of the vertices
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Vertex buffer subresource data
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(oPlaneVertices); // Vertices

	// Create vertex buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer));

	// Index buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Bind index buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(DWORD) * m_uiTotalIndices; // Size of the indices
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Index buffer subresource data
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(dwPlaneIndices); // Indices

	// Create index buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DIndexBuffer));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the plane
//---------------------------------------------------------------------------
void CPlanePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	//g_pInputLayout->setPosNormTex(pD3DDeviceContext); // Bind input layout
	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBuffer, m_pD3DIndexBuffer, m_uiVertexStride, m_uiOffset, m_uiTotalIndices);
}

//---------------------------------------------------------------------------
// Name: CInstancePlanePrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CInstancePlanePrimitive::CInstancePlanePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CInstancePlanePrimitive
// Desc: Constructor
//---------------------------------------------------------------------------
CInstancePlanePrimitive::CInstancePlanePrimitive(float fWidth, float fHeight, UINT uiNumOfInstances, UINT uiInstanceDataStride, void *pInstantSourceData)
{
	ASSIGN_COM(create(fWidth, fHeight, uiNumOfInstances, uiInstanceDataStride, pInstantSourceData));
}

//---------------------------------------------------------------------------
// Name: ~CInstancePlanePrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CInstancePlanePrimitive::~CInstancePlanePrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create an instanced plane
//---------------------------------------------------------------------------
HRESULT CInstancePlanePrimitive::create()
{
	RETURN_COM(create(1.0f, 1.0f, 1, nullptr));
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create an instanced plane
//---------------------------------------------------------------------------
HRESULT CInstancePlanePrimitive::create(float fWidth, float fHeight, UINT uiNumOfInstances, UINT uiInstanceDataStride, void *pInstanceSourceData)
{
	CHECK_COM(m_oPlane.create(fWidth, fHeight)); // Create a plane

	m_uiTotalVertices = m_oPlane.getTotalNumberOfVertices(); // Total number of vertices
	m_uiTotalIndices = m_oPlane.getTotalNumberOfIndices(); // Total number of indices

	// Instance buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	m_oD3DBufferDesc.ByteWidth = uiNumOfInstances * uiInstanceDataStride;
	//m_oD3DBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU access write
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // GPU read/write

	// Subresource description
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(pInstanceSourceData); // Subresource data

	// Create instanced data buffer
	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DInstanceBuffer));

	m_uiNumOfInstances = uiNumOfInstances; // Assign the number of instances to create

	// Initialize the vertex and instance stride arrays
	m_uiStrideArray[0] = m_oPlane.getVertexStride(); // Stride of vertex data
	m_uiStrideArray[1] = uiInstanceDataStride; // Stride of instance data
	
	// Initialize the offset array
	m_uiOffsetArray[0] = m_uiOffsetArray[1] = 0;

	// Initialize the vertex buffer array
	m_pD3DVertexBufferArray[0] = m_oPlane.getVertexBuffer(); // Vertex buffer
	m_pD3DVertexBufferArray[1] = m_pD3DInstanceBuffer; // Instance buffer

	//m_pD3DIndexBuffer = m_oPlane.getIndexBuffer(); // Assign the index buffer

	//XMMATRIX *pXMMatrices = nullptr; // Will hold the transformation matrices

	//// Get a pointer to the matrix instance data
	//CHECK_COM(IMM_DEV_CONTEXT->Map(m_pD3DInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, nullptr));

	//::memcpy(pXMMatrices, m_pInstancesMatrix, uiNumOfInstances * sizeof(XMMATRIX)); // Copy the matrices

	//// Release the pointer to the matrix instance data
	//IMM_DEV_CONTEXT->Unmap(m_pD3DInstanceBuffer, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create an instanced plane
//---------------------------------------------------------------------------
HRESULT CInstancePlanePrimitive::create(float fWidth, float fHeight, UINT uiNumOfInstances, void *pInstanceSourceData)
{
	CHECK_COM(m_oPlane.create(fWidth, fHeight)); // Create uninstanced plane

	//m_pD3DIndexBuffer = m_oPlane.getIndexBuffer(); // Assign the index buffer

	//XMMATRIX *pXMMatrices = nullptr; // Will hold the transformation matrices

	//// Get a pointer to the matrix instance data
	//CHECK_COM(IMM_DEV_CONTEXT->Map(m_pD3DInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, nullptr));

	//::memcpy(pXMMatrices, m_pInstancesMatrix, uiNumOfInstances * sizeof(XMMATRIX)); // Copy the matrices

	//// Release the pointer to the matrix instance data
	//IMM_DEV_CONTEXT->Unmap(m_pD3DInstanceBuffer, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render an instanced plane
//---------------------------------------------------------------------------
void CInstancePlanePrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	//g_pInputLayout->setPosNormTexInstanced(pD3DDeviceContext); // Set input layout of the instanced primitives
	g_pD3DGraphics->renderIndexedInstancedPrimitive(pD3DDeviceContext, pShader, m_pD3DVertexBufferArray, 2, m_oPlane.getIndexBuffer(), m_uiTotalIndices, m_uiStrideArray, m_uiOffsetArray, m_uiNumOfInstances);
}

//---------------------------------------------------------------------------
// Name: CFullscreenQuadPrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CFullscreenQuadPrimitive::CFullscreenQuadPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: ~CFullscreenQuadPrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CFullscreenQuadPrimitive::~CFullscreenQuadPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a fullscreen quad
//---------------------------------------------------------------------------
HRESULT CFullscreenQuadPrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Draw the fullscreen quad
//---------------------------------------------------------------------------
void CFullscreenQuadPrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
}

//---------------------------------------------------------------------------
// Name: CScreenAlignedQuadPrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CScreenAlignedQuadPrimitive::CScreenAlignedQuadPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: ~CScreenAlignedQuadPrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CScreenAlignedQuadPrimitive::~CScreenAlignedQuadPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a screen aligned quad
//---------------------------------------------------------------------------
HRESULT CScreenAlignedQuadPrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Draw the screen aligned quad
//---------------------------------------------------------------------------
void CScreenAlignedQuadPrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
}

//---------------------------------------------------------------------------
// Name: CPointPrimitive
// Desc: Default constructor
//---------------------------------------------------------------------------
CPointPrimitive::CPointPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: CPointPrimitive
// Desc: Constructor
//---------------------------------------------------------------------------
CPointPrimitive::CPointPrimitive(float fWidth, float fHeight, float fNumOfPointsAlongX, float fNumOfPointsAlongY)
{
	ASSIGN_COM(create(fWidth, fHeight, fNumOfPointsAlongX, fNumOfPointsAlongY));
}

//---------------------------------------------------------------------------
// Name: ~CPointPrimitive
// Desc: Destructor
//---------------------------------------------------------------------------
CPointPrimitive::~CPointPrimitive()
{
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create point primitives
//---------------------------------------------------------------------------
HRESULT CPointPrimitive::create()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create point primitives
//---------------------------------------------------------------------------
HRESULT CPointPrimitive::create(float fWidth, float fHeight, float fNumOfPointsAlongX, float fNumOfPointsAlongY)
{
	DWORD dwTotalPoints = static_cast<DWORD>(fNumOfPointsAlongX * fNumOfPointsAlongY); // Calculate the total number of points

	// Allocate memory for the points
	SVertex *pVertices = new SVertex[dwTotalPoints];

	// Loop to create vertices of the points
	for(DWORD dwColumn = 0; dwColumn < fNumOfPointsAlongX; dwColumn++)
	{
		for(DWORD dwRow = 0; dwRow < dwTotalPoints; dwRow++)
		{
			pVertices[dwRow] = SVertex(CVector3(static_cast<float>(dwColumn), 0.0f, static_cast<float>(dwRow))); // Points' coordinates
		}
	}

	// Vertex buffer description
	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	m_oD3DBufferDesc.ByteWidth = sizeof(SVertex) * dwTotalPoints;
	m_oD3DBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Writeable by CPU
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Dynamic usage

	// Vertex buffer subresource data
	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<void *>(pVertices); // Vertex buffer data

	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer)); // Create vertex buffer

	// Instance buffer description
	m_oD3DBufferDesc.ByteWidth = static_cast<UINT>(fNumOfPointsAlongX * fNumOfPointsAlongY * sizeof(XMMATRIX));
	m_oD3DBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Dynamic usage

	CHECK_COM(D3D_DEVICE->CreateBuffer(&m_oD3DBufferDesc, nullptr, &m_pD3DInstanceBuffer)); // Create instance buffer

	SAFE_DELETE_ARRAY(pVertices); // Deallocate the memory allocated for the points

	m_uiVertexStride = sizeof(SVertex); // Stride of vertex format

	m_uiOffset = 0; // Offset

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Draw the specified geometry
//---------------------------------------------------------------------------
void CPointPrimitive::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pD3DDeviceContext->IASetVertexBuffers(0, 0, &m_pD3DVertexBuffer, &m_uiVertexStride, &m_uiOffset);
}

//---------------------------------------------------------------------------
// Name: CAsset
// Desc: Default constructor
//---------------------------------------------------------------------------
CAsset::CAsset()
{
	//m_ppD3DVertexBufferArray = nullptr;
	//m_ppD3DIndexBufferArray = nullptr;

	//m_pAssetTextures = nullptr;

	//m_punOffset = nullptr;
	//m_punVertexStride = nullptr;
}

//---------------------------------------------------------------------------
// Name: ~CAsset
// Desc: Destructor
//---------------------------------------------------------------------------
CAsset::~CAsset()
{
	//FREE_CONTAINER_ELEMENTS(m_oVertexStrides); // Vertex strides

	//FREE_CONTAINER_ELEMENTS(m_oVertexOffset); // Vertex offsets

	FREE_CONTAINER_COM(m_oVertexBufferArray); // Vertex buffers

	FREE_CONTAINER_COM(m_oIndexBufferArray); // Index buffers

	DELETE_CONTAINER_ELEMENTS(m_oAssetTextures); // Assets' texture

	//DELETE_FREE(m_punOffset);
	//DELETE_FREE(m_punVertexStride);
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the specified asset
//---------------------------------------------------------------------------
HRESULT CAsset::load(std::wstring oAssetFilePath)
{
	std::string oANSIAssetFilePath(oAssetFilePath.begin(), oAssetFilePath.end()); // Convert the asset file path in ANSI format

	std::unique_ptr<CAssetLoader> oAssetLoader(new CAssetLoader()); // Asset loader for loading assets

	CHECK_BOOL_AND_RETURN_COM(oAssetLoader->load(oANSIAssetFilePath)); // Load the specified asset

	// Get the number of meshes
	if(oAssetLoader->getNumberOfMeshes() == 0) // There are no meshes
		return E_FAIL;

	//std::unique_ptr<ID3D11Buffer *> oVertexBuffer(new ID3D11Buffer *[oAssetLoader->getNumberOfMeshes()]); // Allocate vertex buffer for all the meshes
	//std::unique_ptr<ID3D11Buffer *> oIndexBuffer(new ID3D11Buffer *[oAssetLoader->getNumberOfMeshes()]); // Allocate index buffer for all the meshes
	//std::unique_ptr<CVector3 *> oTextureCoordinate(new CVector3[oAssetLoader->

	// Allocate vertex and index buffer containers for all the meshes
	m_oVertexBufferArray.resize(oAssetLoader->getNumberOfMeshes()); // Vertex buffer
	m_oIndexBufferArray.resize(oAssetLoader->getNumberOfMeshes()); // Index buffer

	// Mesh vertex buffer description
	D3D11_BUFFER_DESC oD3DMeshVertexBufferDesc = {0};
	oD3DMeshVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
	oD3DMeshVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Will hold mesh's subresource data
	D3D11_SUBRESOURCE_DATA oD3DMeshSubresourceData = {0};

	// Mesh index buffer description
	D3D11_BUFFER_DESC oD3DMeshIndexBufferDesc = {0};
	oD3DMeshIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Bind index buffer
	oD3DMeshIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	m_unNumberOfMeshes = oAssetLoader->getNumberOfMeshes(); // Assign the number of meshes in this scene

	// Loop to load all the meshes in this scene
	for(UINT unMeshIndex = 0; unMeshIndex < m_unNumberOfMeshes; unMeshIndex++)
	{
		UINT unNumberOfVertices = oAssetLoader->getNumberOfVertices(unMeshIndex); // Assign the number of vertices of this mesh

		UINT unNumberOfFaces = oAssetLoader->getNumberOfFaces(unMeshIndex); // Assign the number of faces of this mesh

		std::unique_ptr<SVertexNormalTangentBitangentTexture2D []> oMeshVertexData(new SVertexNormalTangentBitangentTexture2D[unNumberOfVertices]); // Will hold the vertex data for this mesh

		std::unique_ptr<UINT []> oMeshIndices(new UINT[unNumberOfFaces * 3]); // Will hold the indices for this mesh

		// Retrieve the mesh data
		CHECK_BOOL_AND_RETURN_COM(oAssetLoader->getMeshData(unMeshIndex, oMeshVertexData.get(), oMeshIndices.get())); // Retrieve the current mesh's vertex and index buffers

		// Mesh's vertex buffer
		oD3DMeshVertexBufferDesc.ByteWidth = sizeof(SVertexNormalTangentBitangentTexture2D) * unNumberOfVertices; // Byte width of this vertex buffer

		oD3DMeshSubresourceData.pSysMem = reinterpret_cast<void *>(oMeshVertexData.get()); // Assign mesh's vertex buffer

		CHECK_COM(D3D_DEVICE->CreateBuffer(&oD3DMeshVertexBufferDesc, &oD3DMeshSubresourceData, &m_oVertexBufferArray[unMeshIndex]));

		// Mesh's index buffer
		oD3DMeshIndexBufferDesc.ByteWidth = sizeof(UINT) * oAssetLoader->getNumberOfIndices(unMeshIndex); // Byte width of the index buffer

		oD3DMeshSubresourceData.pSysMem = reinterpret_cast<void *>(oMeshIndices.get());

		CHECK_COM(D3D_DEVICE->CreateBuffer(&oD3DMeshIndexBufferDesc, &oD3DMeshSubresourceData, &m_oIndexBufferArray[unMeshIndex]));

		m_oVertexStrides.push_back(sizeof(SVertexNormalTangentBitangentTexture2D)); // Save vertex stride

		m_oVertexOffset.push_back(0); // Vertex offset

		m_oTotalIndices.push_back(oAssetLoader->getNumberOfIndices(unMeshIndex)); // Save total indices
	}

	//CHECK_COM(

	// Mesh subresource description
	//D3D11_SUBRESOURCE_DATA oD3DSubresourceData = {0};
	///oD3DSubresourceData.pSysMem = reinterpret_cast<void *>(oMeshVertexData.get()); // Mesh vertex data

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getNumberOfMeshes
// Desc: Get the number of meshes
//---------------------------------------------------------------------------
UINT CAsset::getNumberOfMeshes() const
{
	return m_unNumberOfMeshes;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Draw the asset with the specified index
//---------------------------------------------------------------------------
void CAsset::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext, DWORD dwMeshIndex)
{
	//pD3DDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // Set primitive topology
	//pD3DDeviceContext->IASetVertexBuffers(0, 0, &m_oVertexBufferArray[dwMeshIndex], &m_punVertexStride[dwMeshIndex], &m_punOffset[dwMeshIndex]); // Set vertex buffers
	//pD3DDeviceContext->IASetIndexBuffer(m_oIndexBufferArray[dwMeshIndex], DXGI_FORMAT_R32_UINT, 0); // Set index buffer

	g_pD3DGraphics->renderIndexedPrimitive(pD3DDeviceContext, pShader, m_oVertexBufferArray[dwMeshIndex], m_oIndexBufferArray[dwMeshIndex], m_oVertexStrides[dwMeshIndex], m_oVertexOffset[dwMeshIndex], m_oTotalIndices[dwMeshIndex]);
}