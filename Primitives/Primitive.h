// Primitive.h: Interface for loading and manipulating primitives
// Copyright (C) 2010-2013 Asesh Shrestha. All rights reserved

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

// Forward declarations
class CTransform;
struct SMaterial;

//---------------------------------------------------------------------------
// Name: CBasePrimitive
// Type: Class
// Desc: Base class for primitives
//---------------------------------------------------------------------------
class CBasePrimitive
{
public: // Public methods
	CBasePrimitive(); // Default constructor
	virtual ~CBasePrimitive(); // Destructor

	//virtual HRESULT create() = 0; // Primitive creation method; must be overridden

	// Get methods
	virtual D3D_PRIMITIVE_TOPOLOGY getPrimitiveTopology() const; // Get the primitive topology
	virtual ID3D11Buffer *getVertexBuffer() const; // Get the vertex buffer
	virtual ID3D11Buffer *getIndexBuffer() const; // Get the index buffer
	virtual UINT getTotalNumberOfVertices() const; // Get the total number of vertices
	virtual UINT getTotalNumberOfIndices() const; // Get the total number of indices
	virtual UINT getVertexStride() const; // Get the size of the element of vertex buffer

	// Set methods
	//virtual void setMaterial(SMaterial *pMaterial); // Set the material for this primitive
	//virtual void setDefaultMaterialAttributes(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Set default material attributes
	//virtual void setMaterialAttributes(const SMaterial *pMaterial); // Set material
	//virtual void setMaterialAttributes(CVector4 oDiffuseMaterialColor, CVector4 oDiffuseLightColor, CVector4 oAmbientMaterialColor, CVector4 oAmbientLightColor); // Set a generic material's attributes
	//virtual void setMaterialAttributes(CVector4 oDiffuseMaterialColor, CVector4 oDiffuseLightColor, CVector4 oAmbientMaterialColor, CVector4 oAmbientLightColor, CVector4 oSpecularMaterialColor, CVector4 oSpecularLightColor, float fSpecularPower); // Set a shiny material's attributes

	virtual bool isValid() const; // Test if the cube was successfully created or not
	virtual bool isNotValid() const; // Test if the cube was successfully created or not

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext) = 0; // Primitive draw method; must be overridden

protected: // Protected attributes

	ID3D11Buffer *m_pD3DVertexBuffer; // Vertex buffer of the corresponding primitive
	ID3D11Buffer *m_pD3DIndexBuffer; // Index buffer of the corresponding primitive

	D3D11_BUFFER_DESC m_oD3DBufferDesc; // Buffer description
	D3D11_SUBRESOURCE_DATA m_oD3DSubrsrcData; // Subresource data description

	D3D_PRIMITIVE_TOPOLOGY m_oD3DPrimitiveTopology; // Will hold the primitive topology

	SMaterial *m_pMaterial; // Material of this primitive

	UINT m_uiVertexStride, m_uiOffset, m_uiTotalIndices, m_uiTotalVertices;

	CTransform *m_pTransform; // Transformation

	HRESULT m_hResult; // Used for checking errors
};

//---------------------------------------------------------------------------
// Name: CInstanceBasePrimitive
// Type: Class
// Desc: Base class for instanced primitives
//---------------------------------------------------------------------------
class CInstanceBasePrimitive : public CBasePrimitive
{
public:
	CInstanceBasePrimitive(); // Default constructor
	virtual ~CInstanceBasePrimitive(); // Destructor

	// Get methods
	virtual UINT getNumOfInstances() const; // Get the number of instances
	virtual ID3D11Buffer *getInstanceDataBuffer() const; // Get the instance data buffer

	// Update methods
	virtual HRESULT updateInstanceBuffer(void *pSourceData, UINT uiSizeOfElement, UINT uiNumOfInstancesToUpdate, ID3D11DeviceContext *pD3DDeviceContext); // Update the instance buffer
	virtual HRESULT updateInstanceBuffer(ID3D11DeviceContext *pD3DDeviceContext); // Update the instance buffer

protected:
	ID3D11Buffer *m_pD3DInstanceBuffer; // Instance data buffer
	ID3D11Buffer *m_pD3DVertexBufferArray[2]; // Vertex buffer array

	D3D11_MAPPED_SUBRESOURCE m_oD3DMappedSubresource; // Subresource data

	UINT m_uiNumOfInstances; // Number of instances

	UINT m_uiStrideArray[2]; // Stride array
	UINT m_uiOffsetArray[2]; // Offset array
};

//---------------------------------------------------------------------------
// Name: CLinePrimitive
// Type: Class
// Desc: Class for line primitives
//---------------------------------------------------------------------------
class CLinePrimitive : public CBasePrimitive
{
public:
	CLinePrimitive(); // Default constructor
	CLinePrimitive(float fHeight); // Constructor
	virtual ~CLinePrimitive(); // Destructor

	virtual HRESULT create(float fHeight); // Create a line primitive with the specified height

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the line primitive

private:
};

//---------------------------------------------------------------------------
// Name: CCirclePrimitive
// Type: Class
// Desc: Class for circle primitives
//---------------------------------------------------------------------------
class CCirclePrimitive : public CBasePrimitive
{
public:
	CCirclePrimitive(); // Default constructor
	CCirclePrimitive(float fRadius, DWORD dwSlices); // Constructor
	virtual ~CCirclePrimitive(); // Destructor

	virtual HRESULT create(); // Creat a circle with normalized coordinates
	virtual HRESULT create(float fRadius, DWORD dwSlices); // Create a circle

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the circle

private:
	int m_nRadius;
};

//---------------------------------------------------------------------------
// Name: CSpherePrimitive
// Type: Class
// Desc: Class for sphere primitives
//---------------------------------------------------------------------------
class CSpherePrimitive : public CBasePrimitive
{
	CSpherePrimitive(); // Default constructor
	CSpherePrimitive(float fRadius, DWORD dwSlices, DWORD dwStacks); // Constructor
	virtual ~CSpherePrimitive(); // Destructor

	virtual HRESULT create(); // Create a sphere with normalize coordinates
	virtual HRESULT create(float fRadius, DWORD dwSlices, DWORD dwStacks); // Create a sphere

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the sphere

private:
};

//---------------------------------------------------------------------------
// Name: CCylinderPrimitive
// Type: Class
// Desc: Class for cylinder primitives
//---------------------------------------------------------------------------
class CCylinderPrimitive : public CBasePrimitive
{
public:
	CCylinderPrimitive(); // Default constructor
	CCylinderPrimitive(float fRadius1, float fRadius2, float fLength, DWORD dwSlices, DWORD dwStacks); // Constructor
	virtual ~CCylinderPrimitive(); // Destructor

	virtual HRESULT create(); // Create a cylinder with normalized coordinates
	virtual HRESULT create(float fRadius1, float fRadius2, float fLength, DWORD dwSlices, DWORD dwStacks); // Create a cylinder

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the cylinder

private:
};

//---------------------------------------------------------------------------
// Name: CCubePrimitive
// Type: Class
// Desc: Class for cube primitives
//---------------------------------------------------------------------------
class CCubePrimitive : public CBasePrimitive
{
public:
	CCubePrimitive(); // Default constructor
	CCubePrimitive(float fWidth, float fHeight, float fDepth); // Constructor
	virtual ~CCubePrimitive(); // Destructor

	virtual HRESULT create(); // Create a cube with normalized coordinates
	virtual HRESULT create(float fWidth, float fHeight, float fDepth); // Create a cube

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the cube

private:
};

//---------------------------------------------------------------------------
// Name: CInstanceCubePrimitive
// Type: Class
// Desc: Class for instanced cube primitives
//---------------------------------------------------------------------------
class CInstanceCubePrimitive : public CInstanceBasePrimitive
{
public:
	CInstanceCubePrimitive(); // Default constructor
	CInstanceCubePrimitive(float fWidth, float fHeight, float fDepth, UINT uiNumOfInstances); // Constructor to create an instanced cube
	virtual ~CInstanceCubePrimitive(); // Destructor

	virtual HRESULT create(float fWidth, float fHeight, float fDepth, UINT uiNumOfInstances); // Create an instanced cube

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render instanced cube

private:
	CCubePrimitive m_oCube;
};

//---------------------------------------------------------------------------
// Name: CCapsulePrimitive
// Type: Class
// Desc: Class for capsule primitives
//---------------------------------------------------------------------------
class CCapsulePrimitive : public CBasePrimitive
{
public:
	CCapsulePrimitive(); // Default constructor
	virtual ~CCapsulePrimitive(); // Destructor

	virtual HRESULT create(); // Create a capsule

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the capsule

private:
};

//---------------------------------------------------------------------------
// Name: CGridPrimitive
// Type: Class
// Desc: Class for grid primitives
//---------------------------------------------------------------------------
class CGridPrimitive : public CBasePrimitive
{
public:
	CGridPrimitive(); // Default constructor
	CGridPrimitive(DWORD dwNumOfCellsPerRow, DWORD dwNumOfCellsPerColumn, float fXSpacePerCell, float fZSpacePerCell); // Constructor
	virtual ~CGridPrimitive(); // Destructor

	virtual HRESULT create(); // Create a grid with normalize coordinates
	virtual HRESULT create(DWORD dwNumOfCellsPerRow, DWORD dwNumOfCellsPerColumn, float fXSpacePerCell, float fZSpacePerCell); // Create a grid

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the grid

private:
};

//---------------------------------------------------------------------------
// Name: CPlanePrimitive
// Type: Class
// Desc: Class for plane primitives
//---------------------------------------------------------------------------
class CPlanePrimitive : public CBasePrimitive
{
public:
	CPlanePrimitive(); // Default constructor
	CPlanePrimitive(float fWidth, float fHeight); // Constructor to create a plane
	virtual ~CPlanePrimitive(); // Destructor

	virtual HRESULT create(); // Create a plane with normalized coordinates
	virtual HRESULT create(float fWidth, float fHeight); // Create a plane with the specified width and height

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render the plane

private:
};

//---------------------------------------------------------------------------
// Name: CInstancePlanePrimitive
// Type: Class
// Desc: Class for instanced plane primitives
//---------------------------------------------------------------------------
class CInstancePlanePrimitive : public CInstanceBasePrimitive
{
public:
	CInstancePlanePrimitive(); // Default constructor
	CInstancePlanePrimitive(float fWidth, float fHeight, UINT uiNumOfInstances, UINT uiInstanceDataStride, void *pInstanceSourceData); // Constructor to create an instanced plane
	virtual ~CInstancePlanePrimitive(); // Destructor

	virtual HRESULT create(); // Create an instanced plane
	virtual HRESULT create(float fWidth, float fHeight, UINT uiNumOfInstances, UINT uiInstanceDataStride, void *pInstanceSourceData); // Create an instanced plane
	virtual HRESULT create(float fWidth, float fHeight, UINT uiNumOfInstances, void *pInstanceSourceData); // Create an instanced plane

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render an instanced plane

private:
	CPlanePrimitive m_oPlane;
};

//---------------------------------------------------------------------------
// Name: CFullscreenQuadPrimitive
// Type: Class
// Desc: Class for full-screen quad primitives
//---------------------------------------------------------------------------
class CFullscreenQuadPrimitive : public CBasePrimitive
{
public:
	CFullscreenQuadPrimitive(); // Default constructor
	virtual ~CFullscreenQuadPrimitive(); // Destructor

	virtual HRESULT create(); // Create a fullscreen quad

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render fullscreen quad

private:
};

//---------------------------------------------------------------------------
// Name: CScreenAlignedQuadPrimitive
// Type: Class
// Desc: Class for screen-aligned quad primitives
//---------------------------------------------------------------------------
class CScreenAlignedQuadPrimitive : public CBasePrimitive
{
public:
	CScreenAlignedQuadPrimitive(); // Default constructor
	virtual ~CScreenAlignedQuadPrimitive(); // Destructor

	virtual HRESULT create(); // Create a fullscreen quad

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render screen aligned quad

private:
};

//---------------------------------------------------------------------------
// Name: CPointPrimitive
// Type: Class
// Desc: Class for point primitives
//---------------------------------------------------------------------------
class CPointPrimitive : public CInstanceBasePrimitive
{
public:
	CPointPrimitive(); // Default constructor
	CPointPrimitive(float fWidth, float fHeight, float fNumOfPointsAlongX, float fNumOfPointsAlongY); // Constructor
	virtual ~CPointPrimitive(); // Destructor

	virtual HRESULT create(); // Create point primitives
	virtual HRESULT create(float fWidth, float fHeight, float fNumOfPointsAlongX, float fNumOfPointsAlongY); // Create point primitives

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Draw point primitive

private:
};

//---------------------------------------------------------------------------
// Name: CAsset
// Type: Class
// Desc: Class for loading assets
//---------------------------------------------------------------------------
class CAsset
{
public: // Public methods
	CAsset(); // Default constructor
	virtual ~CAsset(); // Destructor

	virtual HRESULT load(std::wstring oAssetFilePath); // Load the specified asset

	// Get methods
	UINT getNumberOfMeshes() const; // Get the number of meshes

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext, DWORD dwMeshIndex = 0); // Draw the asset

protected: // Protected attributes

	std::vector<ID3D11Buffer *> m_oVertexBufferArray, m_oIndexBufferArray; // Vertex and index buffers

	//CTexture2D **m_pAssetTextures; // Asset textures
	std::vector<CTexture2D *> m_oAssetTextures; // Assets' texture

	std::vector<UINT> m_oVertexStrides; // Vertex stride of vertex data for all the assets
	std::vector<UINT> m_oVertexOffset; // Vertex offset of all the assets

	std::vector<UINT> m_oTotalIndices; // Total indices per-mesh

	UINT m_unNumberOfMeshes; // Will hold the number of meshes

	HRESULT m_hResult; // Will hold the result
};


//---------------------------------------------------------------------------
// Name: CSkeletalAsset class
// Type: Class
// Desc: Class for loading skeletal characters
//---------------------------------------------------------------------------
class CSkeletalAsset : public CAsset
{
public:
	CSkeletalAsset(); // Default constructor
	virtual ~CSkeletalAsset(); // Destructor

private:
};

#endif // PRIMITIVE_H