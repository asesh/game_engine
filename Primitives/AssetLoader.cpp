// AssetLoader.cpp: Implementation of asset loader
// Copyright (C) 2012-2013 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "Primitive.h"
#include "AssetLoader.h"

#pragma comment(lib, "assimp.lib") // Assimp library

#define ASSIMP_FREE_SCENE(X) X.FreeScene()

//---------------------------------------------------------------------------
// Name: CAssetLoader
// Desc: Default constructor
//---------------------------------------------------------------------------
CAssetLoader::CAssetLoader()
{
	m_pScene = nullptr;

	m_unLoaderFlags = aiProcess_CalcTangentSpace | aiProcess_MakeLeftHanded; // Default loader flags
}

//---------------------------------------------------------------------------
// Name: CAssetLoader
// Desc: Constructor
//---------------------------------------------------------------------------
CAssetLoader::CAssetLoader(std::string oFilePathString)
{
}

//---------------------------------------------------------------------------
// Name: ~CAssetLoader
// Desc: Destructor
//---------------------------------------------------------------------------
CAssetLoader::~CAssetLoader()
{
	ASSIMP_FREE_SCENE(m_oImporter);
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the specified asset
//---------------------------------------------------------------------------
bool CAssetLoader::load(std::string oFilePathString, unsigned int unPostProcessingSteps, bool bAsynchronous)
{
	// Read the specified file
	m_pScene = m_oImporter.ReadFile(oFilePathString.data(), unPostProcessingSteps);
	if(m_pScene == nullptr)
		return false;

	// Assign the scene's data
	m_unNumberOfMaterials = m_pScene->mNumMaterials; // Number of materials
	m_unNumberOfLights = m_pScene->mNumLights; // Number of lights
	m_unNumberOfMeshes = m_pScene->mNumMeshes; // Number of meshes
	m_unNumberOfAnimations = m_pScene->mNumAnimations; // Number of animations
	m_unNumberOfTextures = m_pScene->mNumTextures; // Number of textures

	//m_oImporter.FreeScene();

	return true;
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the specified asset from memory
//---------------------------------------------------------------------------
bool CAssetLoader::load(void *pMemoryLocation, size_t stBufferLength, bool bAsynchronous)
{
	// Load scene from the file
	m_pScene = m_oImporter.ReadFileFromMemory(pMemoryLocation, stBufferLength, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_MakeLeftHanded);
	if(m_pScene == nullptr)
		return false;

	// Assign the scene's data
	m_unNumberOfMaterials = m_pScene->mNumMaterials; // Number of materials
	m_unNumberOfLights = m_pScene->mNumLights; // Number of lights
	m_unNumberOfMeshes = m_pScene->mNumMeshes; // Number of meshes
	m_unNumberOfAnimations = m_pScene->mNumAnimations; // Number of animations
	m_unNumberOfTextures = m_pScene->mNumTextures; // Number of textures

	return true;
}

//---------------------------------------------------------------------------
// Name: getNumberOfVertices
// Desc: Get the number of vertices of the mesh with the specified index
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfVertices(int nMeshIndex) const
{
	// Retrieve the mesh with specified index
	aiMesh *pMesh = m_pScene->mMeshes[nMeshIndex];
	if(pMesh == nullptr) // The mesh with the specified index doesn't exist
		return 0;

	return pMesh->mNumVertices; // Return the number of vertices in this mesh
}

//---------------------------------------------------------------------------
// Name: getNumberOfPolygons
// Desc: Get the number of polygons of the mesh with the specified index
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfIndices(int nMeshIndex) const
{
	// Retrieve the mesh with the specified index
	aiMesh *pMesh = m_pScene->mMeshes[nMeshIndex];
	if(pMesh == nullptr)
		return 0;

	return pMesh->mFaces->mNumIndices; // Return the number of indices in this mesh
}

//---------------------------------------------------------------------------
// Name: getNumberOfFaces
// Desc: Get the number of faces of the mesh with the specified index
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfFaces(int nMeshIndex) const
{
	// Retrieve the mesh with the specified index
	aiMesh *pMesh = m_pScene->mMeshes[nMeshIndex];
	if(pMesh == nullptr)
		return 0;

	return pMesh->mNumFaces;
}

//---------------------------------------------------------------------------
// Name: getNumberOfTextures
// Desc: Get the number of textures
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfTextures() const
{
	return m_pScene->mNumTextures;
}

//---------------------------------------------------------------------------
// Name: getNumberOfMeshes
// Desc: Get the number of meshes
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfMeshes() const
{
	return m_pScene->mNumMeshes;
}

//---------------------------------------------------------------------------
// Name: getNumberOfAnimations
// Desc: Get the number of animations
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfAnimations(int nMeshIndex) const
{
	return m_pScene->mNumAnimations;
}

//---------------------------------------------------------------------------
// Name: getNumberOfMaterials
// Desc: Get the number of materials
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfMaterials(int nMeshIndex) const
{
	return m_pScene->mNumMaterials;
}

//---------------------------------------------------------------------------
// Name: getNumberOfLights
// Desc: Get the number of lights
//---------------------------------------------------------------------------
UINT CAssetLoader::getNumberOfLights(int nMeshIndex) const
{
	return m_pScene->mNumLights;
}

//---------------------------------------------------------------------------
// Name: getMesh
// Desc: Get the mesh of the specified index
//---------------------------------------------------------------------------
aiMesh *CAssetLoader::getMesh(DWORD dwMeshIndex) const
{
	// Check if the specified mesh index is within the range of the number of meshes
	if(dwMeshIndex > getNumberOfMeshes()) // The specified mesh index is out of range
		return nullptr;

	aiMesh *pMesh = m_pScene->mMeshes[dwMeshIndex]; // Assign the specified mesh index

	return pMesh; // Return the specified mesh
}

//---------------------------------------------------------------------------
// Name: getMeshData
// Desc: Get the mesh data
//---------------------------------------------------------------------------
//bool CAssetLoader::getMeshData(DWORD dwMeshIndex, CVector3 &rVertices, CVector3 &rIndices) const
//{
//	return true;
//}

//---------------------------------------------------------------------------
// Name: getMeshData
// Desc: Get the mesh vertices, indices and texture coordinates
//---------------------------------------------------------------------------
//bool CAssetLoader::getMeshData(DWORD dwMeshIndex, CVector3 &rVertices, CVector3 &rIndices, CVector3 &rTextureCoordinates) const
//{
//	return true;
//}

//---------------------------------------------------------------------------
// Name: getMeshData
// Desc: Get the mesh's vertices, indices, texture coordinates, tangents and
//		 bitangents
//---------------------------------------------------------------------------
bool CAssetLoader::getMeshData(DWORD dwMeshIndex, CVector3 *&rpVertices, DWORD *&rpIndices, CVector3 *&rpTextureCoordinates, CVector3 *&rpTangents, CVector3 *&rpBitangents) const
{
	aiMesh *pMesh = m_pScene->mMeshes[dwMeshIndex > getNumberOfMeshes() ? 0 : dwMeshIndex]; // Assign the mesh with the specified index
	if(pMesh == nullptr)
		return false;

	for(DWORD dwVertexIndex = 0; dwVertexIndex < pMesh->mNumVertices; dwVertexIndex++)
	{
		rpVertices[dwVertexIndex] = CVector3(pMesh->mVertices->x, pMesh->mVertices->y, pMesh->mVertices->z); // Assign vertices
	}

	// Assign indices
	for(DWORD dwIndexCount = 0; dwIndexCount < pMesh->mFaces->mNumIndices; dwIndexCount++)
	{
		rpIndices[dwIndexCount] = pMesh->mFaces->mIndices[dwIndexCount]; // Assign indices
	}

	DWORD dwMaterialIndex = pMesh->mMaterialIndex; // Assign the material index used by this mesh

	// Assign texture coordinates
	for(DWORD dwTextureCoordinateIndex = 0; dwTextureCoordinateIndex < pMesh->mNumUVComponents[dwMaterialIndex]; dwTextureCoordinateIndex++)
	{
		rpTextureCoordinates[dwTextureCoordinateIndex] = CVector3(pMesh->mTextureCoords[dwMaterialIndex]->x, pMesh->mTextureCoords[dwMaterialIndex]->y, 0.0f); // Assign texture coordinate
	}

	// Assign tangents
	for(DWORD dwTangentIndex = 0; pMesh->mTangents != nullptr; dwTangentIndex++)
	{
		rpTangents[dwTangentIndex] = CVector3(pMesh->mTangents[dwTangentIndex].x, pMesh->mTangents[dwTangentIndex].y, pMesh->mTangents[dwTangentIndex].z); // Assign tangent
	}

	// Assign bitangents
	for(DWORD dwBitangentIndex = 0; pMesh->mBitangents != nullptr; dwBitangentIndex++)
	{
		rpBitangents[dwBitangentIndex] = CVector3(pMesh->mBitangents[dwBitangentIndex].x, pMesh->mBitangents[dwBitangentIndex].y, pMesh->mBitangents[dwBitangentIndex].z); // Assign bitangent
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: getMeshData
// Desc: Get the mesh vertex, normal, tangent, bitangent, 2D texture and indices
//---------------------------------------------------------------------------
bool CAssetLoader::getMeshData(DWORD dwMeshIndex, SVertexNormalTangentBitangentTexture2D *pMeshVertexNormalTangentBitangentTexture2D, UINT *punIndices)
{
	// Get the mesh with the specified index
	aiMesh *pMesh = getMesh(dwMeshIndex);
	if(pMesh == nullptr) // The mesh is null
		return false;

	UINT unMaterialIndex = pMesh->mMaterialIndex; // Assign the material index used by this mesh

	UINT unNumberOfFaces = pMesh->mNumFaces; // Assign the number of faces in this mesh

	// Check if the mesh has all the required data as specified by the user
	if(!pMesh->HasPositions() || !pMesh->HasNormals() || !pMesh->HasTangentsAndBitangents() || !pMesh->HasTextureCoords(0)) // One of the required data doesn't exist
		return false; // Since one of the data doesn't exist return failure

	// Copy all the vertices
	for(UINT unVertexCount = 0; unVertexCount < pMesh->mNumVertices; unVertexCount++)
	{
		// Assign the vertics, normals, tangents, bitangents and texture coordinates for this vertex
		SVertexNormalTangentBitangentTexture2D oVertexNormalTangentBitangentTexture2D(CVector3(pMesh->mVertices[unVertexCount].x, pMesh->mVertices[unVertexCount].y, pMesh->mVertices[unVertexCount].z), // Vertices
			CVector3(pMesh->mNormals[unVertexCount].x, pMesh->mNormals[unVertexCount].y, pMesh->mNormals[unVertexCount].z), // Normals
			CVector3(pMesh->mTangents[unVertexCount].x, pMesh->mTangents[unVertexCount].y, pMesh->mTangents[unVertexCount].z), // Tangents
			CVector3(pMesh->mBitangents[unVertexCount].x, pMesh->mBitangents[unVertexCount].y, pMesh->mBitangents[unVertexCount].z), // Bitangents
			CVector2(pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][unVertexCount].x, pMesh->mTextureCoords[0][unVertexCount].y : 0.0f, 0.0f)); // Texture coordinates

		//ppMeshVertexNormalTangentBitangentTexture2D = &oVertexNormalTangentBitangentTexture2D;
		::memcpy(pMeshVertexNormalTangentBitangentTexture2D++, &oVertexNormalTangentBitangentTexture2D, sizeof(SVertexNormalTangentBitangentTexture2D)); // Copy the contents of the vertex bufffer
	}

	// Copy all the indices
	//for(UINT unIndexCount = 0; unIndexCount < pMesh->mFaces->mNumIndices; unIndexCount++)
	//{
	//	::memcpy(punIndices++, &pMesh->mFaces->mIndices[unIndexCount], sizeof(UINT));
	//}

	// Copy all the faces
	for(UINT unFaceCount = 0; unFaceCount < unNumberOfFaces; unFaceCount++)
	{
		const aiFace &rFace = pMesh->mFaces[unFaceCount]; // Assign a face with the current face index

		// Copy all the indices
		for(UINT unIndexCount = 0; unIndexCount < pMesh->mFaces[unFaceCount].mNumIndices; unIndexCount++)
		{
			// Copy all the indices of this face
			::memcpy(&punIndices[unFaceCount], &rFace.mIndices[unIndexCount], pMesh->mFaces[unFaceCount].mNumIndices * sizeof(UINT));
		}

		//punIndices
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: getMeshData
// Desc: Get the mesh vertex, normal and 2D texture
//---------------------------------------------------------------------------
bool CAssetLoader::getMeshData(DWORD dwMeshIndex, SVertexNormalTexture2D *&rpMeshVertexNormalTexture2D)
{
	// Get the mesh with the specified index
	aiMesh *pMesh = getMesh(dwMeshIndex);
	if(pMesh == nullptr)
		return false;

	DWORD dwMaterialIndex = pMesh->mMaterialIndex; // Assign the material index used by the mesh

	// Check if the mesh has vertex, normal and 2D texture
	if(!pMesh->HasPositions() || !pMesh->HasNormals() || !pMesh->HasTextureCoords(0)) // One of the required data doesn't exist
		return false;

	// Loop through all the vertices of this mesh
	for(DWORD dwVertexCount = 0; dwVertexCount < pMesh->mNumVertices; dwVertexCount++)
	{
		rpMeshVertexNormalTexture2D[dwVertexCount] = SVertexNormalTexture2D(CVector3(pMesh->mVertices[dwVertexCount].x, pMesh->mVertices[dwVertexCount].y, pMesh->mVertices[dwVertexCount].z), // Vertices
			CVector3(pMesh->mNormals[dwVertexCount].x, pMesh->mNormals[dwVertexCount].y, pMesh->mNormals[dwVertexCount].z), // Normals
			CVector2(pMesh->mTextureCoords[dwMaterialIndex][dwVertexCount].x, pMesh->mTextureCoords[dwMaterialIndex][dwVertexCount].y)); // Texture coordinates
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: getPrimitiveType
// Desc: Get the type of the mesh
//---------------------------------------------------------------------------
aiPrimitiveType CAssetLoader::getMeshType(DWORD dwMeshIndex) const
{
	// Get the mesh with the specified index
	aiMesh *pMesh = getMesh(dwMeshIndex);
	if(pMesh == nullptr) // Mesh with the specified index doesn't exist
		return static_cast<aiPrimitiveType>(NULL);

	return static_cast<aiPrimitiveType>(pMesh->mPrimitiveTypes); // Return the primitive type of the specified mesh index
}

//---------------------------------------------------------------------------
// Name: C3DSAssetLoader
// Desc: Default constructor
//---------------------------------------------------------------------------
C3DSAssetLoader::C3DSAssetLoader()
{
}

//---------------------------------------------------------------------------
// Name: ~C3DSAssetLoader
// Desc: Destructor
//---------------------------------------------------------------------------
C3DSAssetLoader::~C3DSAssetLoader()
{
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load 3ds asset from the specified file
//---------------------------------------------------------------------------
bool C3DSAssetLoader::load(std::string oFilePathString, bool bAsynchronous)
{
	CHECK_BOOL(CAssetLoader::load(oFilePathString));

	return true;
}

//---------------------------------------------------------------------------
// Name: loadFromMemory
// Desc: 
//---------------------------------------------------------------------------
bool C3DSAssetLoader::loadFromMemory(void *pMemoryLocation, size_t stBufferLength, bool bAsynchronous)
{
	return true;
}

//---------------------------------------------------------------------------
// Name: COBJAssetLoader
// Desc: Default constructor
//---------------------------------------------------------------------------
COBJAssetLoader::COBJAssetLoader()
{
}

//---------------------------------------------------------------------------
// Name: COBJAssetLoader
// Desc: Default constructor
//---------------------------------------------------------------------------
COBJAssetLoader::COBJAssetLoader(std::wstring oFilePathString)
{
}

//---------------------------------------------------------------------------
// Name: ~COBJAssetLoader
// Desc: Destructor
//---------------------------------------------------------------------------
COBJAssetLoader::~COBJAssetLoader()
{
}

//---------------------------------------------------------------------------
// Name: CFBXAssetLoader
// Desc: Default constructor
//---------------------------------------------------------------------------
CFBXAssetLoader::CFBXAssetLoader()
{
	//m_pFbxManager = nullptr;

	//m_pFbxScene = nullptr;
}

//---------------------------------------------------------------------------
// Name: CFBXAssetLoader
// Desc: Constructor
//---------------------------------------------------------------------------
CFBXAssetLoader::CFBXAssetLoader(std::string oAssetPathString)
{
}

//---------------------------------------------------------------------------
// Name: ~CFBXAssetLoader
// Desc: Destructor
//---------------------------------------------------------------------------
CFBXAssetLoader::~CFBXAssetLoader()
{
	//FREE_FBX(m_pFbxIOSettings);

	//FREE_FBX(m_pFbxScene);

	//FREE_FBX(m_pFbxManager);
}

//---------------------------------------------------------------------------
// Name: getNumberOfNodes
// Desc: Get the number of nodes
//---------------------------------------------------------------------------
int CFBXAssetLoader::getNumberOfNodes() const
{
	return m_nNumberOfNodes;
}

//---------------------------------------------------------------------------
// Name: getNumberOfTextures
// Desc: Get the number of textures
//---------------------------------------------------------------------------
int CFBXAssetLoader::getNumberOfTextures() const
{
	return m_nNumberOfTextures;
}

//---------------------------------------------------------------------------
// Name: getNumberOfMaterials
// Desc: Get the number of materials
//---------------------------------------------------------------------------
int CFBXAssetLoader::getNumberOfMaterials() const
{
	return m_nNumberOfMaterials;
}

//---------------------------------------------------------------------------
// Name: getNumberOfPolygons
// Desc: Get the number of pologons
//---------------------------------------------------------------------------
int CFBXAssetLoader::getNumberOfPolygons() const
{
	return m_nNumberOfPolygons;
}

//---------------------------------------------------------------------------
// Name: load
// Desc: Load the specified asset
//---------------------------------------------------------------------------
bool CFBXAssetLoader::load(std::string oAssetPathString, bool bAsynchronous)
{
	//m_pFbxManager = FbxManager::Create(); // Initialize the SDK manager
	//if(!m_pFbxManager)
	//	return false;

	//m_pFbxIOSettings = FbxIOSettings::Create(m_pFbxManager, IOSROOT); // Create IO settings object
	//m_pFbxManager->SetIOSettings(m_pFbxIOSettings);

	//// Create an importer for importing FBX file
	//FbxImporter *pFbxImporter = FbxImporter::Create(m_pFbxManager, "");

	//// Initialize the importer by providing a filename to load with the specified IO settings
	//CHECK_BOOL(pFbxImporter->Initialize(oAssetPathString.c_str(), -1, m_pFbxIOSettings));

	//// Create a new scene where the imported file will be populated
	//m_pFbxScene = FbxScene::Create(m_pFbxManager, "scene");

	//// Check if asynchronous flag has been specified
	//if(bAsynchronous) // Asynchronous option specified
	//{
	//	// Import the contents of file into the scene using asynchronous operation
	//	CHECK_BOOL(pFbxImporter->Import(m_pFbxScene, true));
	//}
	//else // Synchronous option specified
	//{
	//	// Import the contents of file into the scene using synchronous operation
	//	CHECK_BOOL(pFbxImporter->Import(m_pFbxScene));
	//}

	//// Get data from the loaded file
	//m_nNumberOfNodes = m_pFbxScene->GetNodeCount(); // Get the number of nodes
	//m_nNumberOfTextures = m_pFbxScene->GetTextureCount(); // Get the number of textures
	//m_nNumberOfMaterials = m_pFbxScene->GetMaterialCount(); // Get the number of materials

	//// Get the root node of the scene
	//FbxNode *pFbxRootNode = m_pFbxScene->GetRootNode();
	//if(pFbxRootNode)
	//{
	//	// Iterate through all the child nodes
	//	for(int nNodeCount = 0; nNodeCount < pFbxRootNode->GetChildCount(); nNodeCount++)
	//	{
	//		FbxNode *pFbxChildNode = pFbxRootNode->GetChild(nNodeCount); // Get the child node of this root node

	//		const char *pszNodeName = pFbxChildNode->GetName(); // Get child node's name

	//		// Get the attribute of this node
	//		FbxNodeAttribute *pFbxNodeAttribute = pFbxChildNode->GetNodeAttribute();
	//		switch(pFbxNodeAttribute->GetAttributeType())
	//		{
	//		case FbxNodeAttribute::eMesh: // It's a Mesh
	//			//::OutputDebugString(L"\nNode's attribute: mesh\n");

	//			extractMeshData(pFbxChildNode->GetMesh()); // Extract mesh data of the current mesh
	//			break;

	//		case FbxNodeAttribute::eSkeleton: // It's a skeleton
	//			///::OutputDebugString(L"Node's attribute: skeleton");

	//			extractSkeletonData(pFbxChildNode->GetSkeleton());
	//			break;

	//		case FbxNodeAttribute::eLight: // It's a light
	//			///::OutputDebugString(L"Node's attribute: light");

	//			extractLightData(pFbxChildNode->GetLight());
	//			break;
	//		}
	//	}
	//}

	//// Now since the file has been imported we can get rid of importer
	//DESTROY_FBX(pFbxImporter);

	return true;
}

//---------------------------------------------------------------------------
// Name: draw
// Desc: Render the current FBX asset
//---------------------------------------------------------------------------
void CFBXAssetLoader::draw(CShader *pShader, ID3D11DeviceContext *pD3DDeviceContext)
{
}

//---------------------------------------------------------------------------
// Name: extractMeshData
// Desc: Extract mesh data
//---------------------------------------------------------------------------
//bool CFBXAssetLoader::extractMeshData(FbxMesh *pFbxMesh)
//{
//	FbxArray<FbxVector2> oFbxUV; // Will hold the UVs
//
//	FbxArray<FbxVector4> oFbxNormal; // Will hold the normals
//
//	int nPolygonCount = pFbxMesh->GetPolygonCount(); // Get the number of polygons
//	if(nPolygonCount == 0)
//		return false;
//
//	int nVertexCount = pFbxMesh->GetPolygonVertexCount(); // Get the number of vertices
//	if(nVertexCount == 0)
//		return false;
//
//	int *pnPolygonVertices = nullptr; // Will hold the vertices of this mesh
//
//	pnPolygonVertices = pFbxMesh->GetPolygonVertices(); // Get the vertices of this mesh
//
//	int nStartIndex = pFbxMesh->GetPolygonVertexIndex(3);
//
//	SVertexNormalTexture2D *pVertexNormalTexture = new SVertexNormalTexture2D[nVertexCount]; // Allocate memory for the vertices
//
//	pFbxMesh->ComputeVertexNormals(); // Compute vertex normals
//
//	pFbxMesh->GenerateTangentsData(0); // Generate tangents
//	///pFbxMesh->no
//
//	pFbxMesh->GetPolygonVertexNormals(oFbxNormal); // Get the vertex normals
//
//	pFbxMesh->GetPolygonVertexUVs(nullptr, oFbxUV); // Get the UVs
//
//	FbxVector4 *pFbxExtractedNormal = oFbxNormal.GetArray(); // Get the array of normals
//
//	FbxVector2 *pFbxExtractedUV = oFbxUV.GetArray(); // Get the array of UVs
//
//	// Loop to initialize the vertex buffer data
//	for(int nVertexIndex = 0; nVertexIndex < nVertexCount; nVertexIndex++)
//	{
//		// Format a vertex buffer
//		pVertexNormalTexture[nVertexIndex] = SVertexNormalTexture2D(static_cast<float>(*(pnPolygonVertices + nVertexIndex)), static_cast<float>(*(pnPolygonVertices + nVertexIndex + 1)), static_cast<float>(*(pnPolygonVertices + nVertexIndex + 2)), // Vertex
//			pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal + nVertexIndex)->mData[0]) : nullptr, pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal + nVertexIndex + 1)->mData[1]) : nullptr, pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal + nVertexIndex + 2)->mData[2]) : nullptr, // Normal
//			pFbxExtractedUV ? static_cast<float>((pFbxExtractedUV + nVertexIndex)->mData[0]) : nullptr, pFbxExtractedUV ? static_cast<float>((pFbxExtractedUV + nVertexIndex + 2)->mData[1]) : nullptr); // UV
//
//		//pVertexNormalTexture[nVertexIndex] = SVertexNormalTexture2D(static_cast<float>(*pnPolygonVertices++), static_cast<float>(*pnPolygonVertices++), static_cast<float>(*pnPolygonVertices++), // Vertex
//		//	pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal++)->mData[0]) : nullptr, pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal++)->mData[1]) : nullptr, pFbxExtractedNormal ? static_cast<float>((pFbxExtractedNormal + nVertexIndex + 2)->mData[2]) : nullptr, // Normal
//		//	pFbxExtractedUV ? static_cast<float>((pFbxExtractedUV++)->mData[0]) : nullptr, pFbxExtractedUV ? static_cast<float>((pFbxExtractedUV++)->mData[1]) : nullptr); // UV
//	}
//
//	m_oD3DBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Bind vertex buffer
//	m_oD3DBufferDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU
//	m_oD3DBufferDesc.ByteWidth = sizeof(SVertexNormalTexture2D) * nVertexCount; // Size of the vertex buffer
//
//	m_oD3DSubrsrcData.pSysMem = reinterpret_cast<int *>(pVertexNormalTexture); // Vertices of the mesh
//
//	if(FAILED(g_pD3DGraphics->getDevice()->CreateBuffer(&m_oD3DBufferDesc, &m_oD3DSubrsrcData, &m_pD3DVertexBuffer))) // Create vertex buffer for the mesh
//		return false;
//
//	m_uiVertexStride = sizeof(SVertexNormalTexture2D); // Stride of our vertex format
//
//	SAFE_DELETE_ARRAY(pVertexNormalTexture); // Deallocate the memory allocated for the vertices
//
//	m_oD3DBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // Bind index buffer
//	//m_oD3DBufferDesc.ByteWidth = sizeof(DWORD) * 
//
//	pFbxMesh->Destroy(); // Destroy the mesh since it's no longer necessary
//
//	//SAFE_DELETE_ARRAY(pnPolygonVertices); // Deallocate the memory allocated for the vertices of this mesh
//
//	return true;
//}
//
////---------------------------------------------------------------------------
//// Name: extractSkeletonData
//// Desc: Extract skeleton data
////---------------------------------------------------------------------------
//bool CFBXAssetLoader::extractSkeletonData(FbxSkeleton *pFbxSkeleton)
//{
//	return true;
//}
//
////---------------------------------------------------------------------------
//// Name: extractLightData
//// Desc: Extract light data
////---------------------------------------------------------------------------
//bool CFBXAssetLoader::extractLightData(FbxLight *pFbxLight)
//{
//	return true;
//}