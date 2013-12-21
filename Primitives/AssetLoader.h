// AssetLoader.h: Interface of asset loader
// Copyright (C) 2012-2013 Asesh Shrestha. All rights reserved

#ifndef ASSETLOADER_H
#define ASSETLOADER_H

// Assimp
//

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

//
// Assimp

// CAssetLoader class
class CAssetLoader
{
public:
	CAssetLoader(); // Default constructor
	CAssetLoader(std::string oFilePathString); // Constructor
	virtual ~CAssetLoader(); // Destructor

	virtual bool load(std::string oFilePathString, unsigned int unPostProcessingSteps = aiProcess_CalcTangentSpace | aiProcess_ConvertToLeftHanded | aiProcess_Triangulate, bool bAsynchronous = false); // Load an asset from the specified file
	virtual bool load(void *pMemoryLocation, size_t stBufferLength, bool bAsynchronous = false); // Load an asset from memory

	// Get methods
	//
	virtual UINT getNumberOfVertices(int nMeshIndex = 0) const; // Get the number vertices of the mesh with the specified index
	virtual UINT getNumberOfIndices(int nMeshIndex = 0) const; // Get the number of indices of the mesh with the specified index
	virtual UINT getNumberOfFaces(int nMeshIndex = 0) const; // Get the number of faces of the mesh with the specified index
	virtual UINT getNumberOfTextures() const; // Get number of textures
	virtual UINT getNumberOfMeshes() const; // Get number of meshes
	virtual UINT getNumberOfAnimations(int nMeshIndex = 0) const; // Get number of animations
	virtual UINT getNumberOfMaterials(int nMeshIndex = 0) const; // Get number of materials
	virtual UINT getNumberOfLights(int nMeshIndex = 0) const; // Get number of lights

	// Get mesh data
	virtual aiMesh *getMesh(DWORD dwMeshIndex = 0) const; // Get the mesh with the specified index
	//virtual bool getMeshData(DWORD dwMeshIndex, CVector3 &rVertices, CVector3 &rIndices) const; // Get the mesh's vertices and indices
	//virtual bool getMeshData(DWORD dwMeshIndex, CVector3 &rVertices, CVector3 &rIndices, CVector3 &rTextureCoordinates) const; // Get the mesh vertices, indices and texture coordinates
	virtual bool getMeshData(DWORD dwMeshIndex, CVector3 *&rpVertices, DWORD *&rpdwIndices, CVector3 *&rpTextureCoordinates, CVector3 *&rpTangents, CVector3 *&rpBitangents) const; // Get the mesh's vertices, indices, texture coordinates, tangents and bitangents
	virtual bool getMeshData(DWORD dwMeshIndex, SVertexNormalTangentBitangentTexture2D *pMeshVertexNormalTangentBitangentTexture2D, UINT *punIndices); // Get the mesh vertex, normal, tangent, bitangent, texture and indices
	virtual bool getMeshData(DWORD dwMeshIndex, SVertexNormalTexture2D *&rpMeshVertexNormalTexture2D); // Get the mesh vertex, normal and texture

	virtual aiPrimitiveType getMeshType(DWORD dwMeshIndex = 0) const; // Get the type of the mesh
	//
	// Get methods

protected:
	const aiScene *m_pScene; // Scene

	unsigned int m_unLoaderFlags; // Loader flags

	// Attributes of an asset
	UINT m_unNumberOfAnimations, m_unNumberOfMeshes, m_unNumberOfTextures, m_unNumberOfMaterials, m_unNumberOfLights;

	//int m_nNumberOfTextures, m_nNumberOfMaterials; // Attributes of an asset

	Assimp::Importer m_oImporter; 

	HRESULT m_hResult;
};

// C3DSAssetLoader class
class C3DSAssetLoader : public CAssetLoader
{
public:
	C3DSAssetLoader(); // Default constructor
	C3DSAssetLoader(std::string oFilePathString, bool bAsynchronous = false); // Constructor
	virtual ~C3DSAssetLoader(); // Destructor

	virtual bool load(std::string oFilePathString, bool bAsynchronous = false); // Load an asset from the specified file
	virtual bool loadFromMemory(void *pMemoryLocation, size_t stBufferLength, bool bAsynchronous = false); // Load an asset from memory

private:
};

// COBJAssetLoader class
class COBJAssetLoader : public CAssetLoader
{
public:
	COBJAssetLoader(); // Default constructor
	COBJAssetLoader(std::wstring oFilePathString); // Constructor
	virtual ~COBJAssetLoader(); // Destructor

	//virtual HRESULT load(std::wstring oFilePathString); // Load an obj asset from the specified file
	//virtual HRESULT loadAsync(std::wstring oFilePathString); // Load an asset from the specified file asynchronously
	//virtual HRESULT loadFromMemory(void *pMemoryLocation, size_t stBufferLength); // Load an obj asset from memory
	//virtual HRESULT loadFromMemoryAsync(void *pMemoryLocation, size_t stBufferLength); // Load an asset from memory asynchronously

private:
};

#define FBXSDK_SHARED

// CFBXAssetLoader class
class CFBXAssetLoader : public CBasePrimitive
{
public: // Public methods
	CFBXAssetLoader(); // Default constructor
	CFBXAssetLoader(std::string oAssetPathString); // Constructor
	virtual ~CFBXAssetLoader(); // Destructor

	// Get methods
	//
	virtual int getNumberOfNodes() const; // Get the number of nodes
	virtual int getNumberOfTextures() const; // Get the number of textures
	virtual int getNumberOfMaterials() const; // Get the number of materials
	virtual int getNumberOfPolygons() const; // Get the number of polygons

	//
	// End get methods

	bool load(std::string oAssetPathString, bool bAsynchronous = false); // Load the specified asset

	virtual void draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext); // Render FBX file

private: // Private methods
	//bool extractMeshData(FbxMesh *pFbxMesh); // Extract mesh data
	//bool extractSkeletonData(FbxSkeleton *pFbxSkeleton); // Extract skeleton data
	//bool extractLightData(FbxLight *pFbxLight); // Extract light data

protected: // Protected attributes
	int m_nNumberOfNodes; // Holds the number of nodes

private: // Private attributes
	//FbxManager *m_pFbxManager; // FBX SDK manager

	//FbxIOSettings *m_pFbxIOSettings; // FBX IO settings

	//FbxScene *m_pFbxScene; // FBX scene

	// Attributes of an asset
	int m_nNumberOfAnimations, m_nNumberOfMeshes, m_nNumberOfTextures, m_nNumberOfMaterials, m_nNumberOfVertices, m_nNumberOfPolygons, m_nNumberOfLights;
};

#endif // ASSETLOADER_H