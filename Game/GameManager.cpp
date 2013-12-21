// GameManager.cpp : Implementation of CGameManager class
// Copyright (C) 2007-2010 Asesh Shrestha

#include "StdAfx.h"
#include "GameManager.h"

//------------------------------------------------------------------
// Name: CGameManager
// Desc: Default constructor
//------------------------------------------------------------------
CGameManager::CGameManager() : m_oXMScaleMat(g_pD3DGraphics->m_oXMScaleMat), m_oXMTransMat(g_pD3DGraphics->m_oXMTransMat),
							   m_oXMWorldMat(g_pD3DGraphics->m_oXMWorldMat), m_oXMViewMat(g_pD3DGraphics->m_oXMViewMat),
							   m_oXMProjMat(g_pD3DGraphics->m_oXMProjMat), m_oXMHomoMat(g_pD3DGraphics->m_oXMHomoMat),
							   m_D3DXWorldMatHandle(g_pD3DGraphics->m_D3DXWorldMatHandle), m_D3DXViewMatHandle(g_pD3DGraphics->m_D3DXViewMatHandle),
							   m_D3DXProjMatHandle(g_pD3DGraphics->m_D3DXProjMatHandle), m_D3DXHomoMatHandle(g_pD3DGraphics->m_D3DXHomoMatHandle)
{
	m_pGameExplorer = NULL; // Game explorer
	m_pGameStatistics = NULL; // Game statistics

	m_oGameStatus = Intro; // Set intial game status to "Intro"

	m_pD3DXSkinInfo = NULL; // Mesh skin info

	m_dwStaminaAmount = 100;

	m_oActiveScene = CrateFactory; // Set "Create Factory" as the active scene
	m_oActiveWeapon = AK47; // Set "AK47" as the initially active weapon

	// Weapons statistics
	m_dwAK47Bullets = 60;
	m_dwMachineGunBullets = 120;
	m_dwPistolBullets = 120;
	m_dwGrenades = 90;
	m_dwMissiles = 30;

	m_hResult = 0; // HRESULT
}

//------------------------------------------------------------------
// Name: ~CGameManager
// Desc: Destructor
//------------------------------------------------------------------
CGameManager::~CGameManager()
{
	DWORD dwSubCount;

	// Clear all the elements of the deques
	//
	// Scene mesh
	if(!m_oSceneMeshDeq.empty())
		m_oSceneMeshDeq.clear();

	// Weapon mesh
	if(!m_oWeaponMeshDeq.empty())
		m_oWeaponMeshDeq.clear();

	// Skinned mesh
	if(!m_oSkinnedMeshDeq.empty())
		m_oSkinnedMeshDeq.clear();

	// Scene mesh texture
	if(!m_oSceneMeshTextureDeq.empty())
		m_oSceneMeshTextureDeq.clear();

	// Weapon mesh texture
	if(!m_oWeaponMeshTextureDeq.empty())
		m_oWeaponMeshTextureDeq.clear();

	// Skinned mesh texture
	if(!m_oSkinnedMeshTextureDeq.empty())
		m_oSkinnedMeshTextureDeq.clear();

	// Bounding box deque
	if(!m_oBoundingBoxDeq.empty())
		m_oBoundingBoxDeq.empty();

	// Bounding sphere
	if(!m_oBoundingSphereDeq.empty())
		m_oBoundingSphereDeq.empty();

	// Scene mesh material counter
	if(!m_oSceneMeshMatCountDeq.empty())
		m_oSceneMeshMatCountDeq.clear();

	// Weapon mesh material counter
	if(!m_oWeaponMeshMatCountDeq.empty())
		m_oWeaponMeshMatCountDeq.clear();

	// Skinned mesh material counter
	if(!m_oSkinnedMeshMatCountDeq.empty())
		m_oSkinnedMeshMatCountDeq.clear();

	// Mesh skin info
	if(!m_oSkinInfoDeq.empty())
		m_oSkinInfoDeq.clear();
}

//------------------------------------------------------------------
// Name: initIntro
// Desc: Initialize the intro scene
//------------------------------------------------------------------
HRESULT CGameManager::initIntro()
{
	return S_OK; // Success
}

//------------------------------------------------------------------
// Name: initLoader
// Desc: Initialize the loading progress screen
//------------------------------------------------------------------
HRESULT CGameManager::initLoader()
{
	return S_OK; // Success
}

//------------------------------------------------------------------
// Name: initGameEngine
// Desc: Initialize the game engine
//------------------------------------------------------------------
HRESULT CGameManager::initGameEngine(UINT uiWindowWidth, UINT uiWindowHeight, HWND hWnd)
{
	// Initialize the core graphics engine
	CHECK_COM(g_pD3DGraphics->init());

	return S_OK;
}

//------------------------------------------------------------------
// Name: renderGameScene
// Desc: Render the game scene
//------------------------------------------------------------------
HRESULT CGameManager::renderGameScene(float fDeltaTime)
{
	return S_OK;
}

//------------------------------------------------------------------
// Name: initMeshes
// Desc: Initialize the meshes
//------------------------------------------------------------------
HRESULT CGameManager::initMeshes()
{
	//WCHAR szMeshPath[MAX_PATH];
	//::SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szMeshPath);
	//::StringCbCat(szMeshPath, ASCII_EQ_BYTES(szMeshPath), L"\\Autodesk Projects\\3ds max projects\\export");
	//::SetCurrentDirectory(szMeshPath);

	//// Scene meshes
	//const WCHAR szSceneMesh[] = L"SmallScene1.x";

	//// Skinned meshes
	//const WCHAR szSkinnedMesh[] = L"SkinnedMesh1.x";

	//// Weapon meshes
	//const WCHAR szWeaponMesh[] = L"AK47.x";

	//SBoundingBox oBoundingBox;
	//SBoundingSphere oBoundingSphere;

	//// Load, optimize and compute the bounding box/sphere of the meshes
	//CHECK_COM(loadMesh(szSceneMesh, &m_dwNumOfMeshMats, pD3DDevice, m_ppD3DSceneMeshTexture, m_pD3DXSceneMesh));
	//optimizeInPlace(m_pD3DXSceneMesh);
	//computeBoundingBox(m_pD3DXSceneMesh, &oBoundingBox);

	//try
	//{
	//	m_oSceneMeshDeq.push_back(m_pD3DXSceneMesh); // Save the loaded scene mesh to the deque
	//	m_oSceneMeshTextureDeq.push_back(m_ppD3DSceneMeshTexture); // Save the loaded scene mesh's textures to the deque
	//	m_oSceneMeshMatCountDeq.push_back(m_dwNumOfMeshMats); // Save the scene mesh's material count to the deque
	//	m_oBoundingBoxDeq.push_back(&oBoundingBox); // Save the bounding box data of the mesh
	//}
	//catch(...)
	//{
	//	return E_OUTOFMEMORY;
	//}

	//// Load, optimize and compute the bounding box/sphere of the main skinned mesh
	//CHECK_COM(loadMesh(szSkinnedMesh, &m_dwNumOfMeshMats, pD3DDevice, m_ppD3DSkinnedMeshTexture, m_pD3DXSkinnedMesh));
	//optimizeInPlace(m_pD3DXSkinnedMesh);
	//computeBoundingBox(m_pD3DXSkinnedMesh, &oBoundingBox);

	//try
	//{
	//	m_oSkinnedMeshDeq.push_back(m_pD3DXSkinnedMesh); // Save the skinned mesh to the deque
	//	m_oSkinnedMeshTextureDeq.push_back(m_ppD3DSkinnedMeshTexture); // Save the skinned mesh's textures
	//	m_oSkinnedMeshMatCountDeq.push_back(m_dwNumOfMeshMats); // Save the skinned mesh's material count to the deque
	//	m_oBoundingBoxDeq.push_back(&oBoundingBox); // Save the bounding box data of the loaded skinned mesh
	//}
	//catch(...)
	//{
	//	return E_OUTOFMEMORY;
	//}

	//// Load, optimize and compute the bounding box/sphere of the default weapon mesh--Machine gun
	//CHECK_COM(loadMesh(szWeaponMesh, &m_dwNumOfMeshMats, pD3DDevice, m_ppD3DWeaponMeshTexture, m_pD3DXWeaponMesh));
	//optimizeInPlace(m_pD3DXWeaponMesh);
	//computeBoundingBox(m_pD3DXWeaponMesh, &oBoundingBox);

	//try
	//{
	//	m_oWeaponMeshDeq.push_back(m_pD3DXWeaponMesh); // Add the loaded weapon mesh to the deque
	//	m_oWeaponMeshTextureDeq.push_back(m_ppD3DWeaponMeshTexture); // Add the loaded weapon mesh's textures to the deque
	//	m_oWeaponMeshMatCountDeq.push_back(m_dwNumOfMeshMats); // Save the weapon mesh's material count to the deque
	//	m_oBoundingBoxDeq.push_back(&oBoundingBox); // Save the bounding box data of the loaded weapon mesh to the deque
	//}
	//catch(...)
	//{
	//	return E_OUTOFMEMORY;
	//}

	return S_OK; // Success
}

CGameManager g_oGameManager;
CGameManager *g_pGameManager = &g_oGameManager;