// GameManager.h : Declaration of CGameManager class
// Copyright (C) 2007-2010 Asesh Shrestha

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Forward declarations
enum EActiveWeapon;
enum EActiveScene;
enum EGameStatus;

// CGameManager class
class CGameManager
{
public:
	CGameManager(); // Default constructor
	~CGameManager(); // Destructor

	HRESULT initIntro(); // Initialize the intro
	HRESULT initLoader(); // Initialize the loading progress screen

	HRESULT initGameEngine(UINT uiWindowWidth, UINT uiWindowHeight, HWND hWnd); // Initialize the game engine

	HRESULT renderGameScene(float fDeltaTime); // Render game scene

	HRESULT initMeshes(); // Initialize the meshes

	HRESULT switchWeapons(); // Switch to another weapon

public: // Public attributes
	EActiveWeapon m_oActiveWeapon; // This will hold the active weapon
	EActiveScene m_oActiveScene; // This will hold the active scene
	EGameStatus m_oGameStatus;

private: // Private attributes

	IGameExplorer2 *m_pGameExplorer;
	IGameStatistics *m_pGameStatistics;

	// References to matrices
	XMMATRIX &m_oXMScaleMat, &m_oXMTransMat, &m_oXMRotMat;
	XMMATRIX &m_oXMWorldMat, &m_oXMViewMat, &m_oXMProjMat, &m_oXMHomoMat; // Referenced transformation matrices
	XMMATRIX m_oXMShadowMat; // Shadow transformation matrix

	//XMPLANE m_oD3DXShadowPlane; // Shadow plane

	XMVECTOR m_oD3DXPlayerPosVec; // Player's position vector

	DWORD m_dwMachineGunBullets, m_dwAK47Bullets, m_dwPistolBullets, m_dwGrenades, m_dwMissiles; // Weapons' ammo count

	DWORD m_dwNumOfMeshMats; // Will hold the number of materials in the mesh
	DWORD m_dwCount, m_dwSubCount; // Loop counters

	DWORD m_dwActiveWeapon; // Index of an active weapon

	DWORD m_dwStaminaAmount; // Amount of stamina the player has

	WCHAR m_szWeaponInfo[MAX_PATH]; // Will hold information of the current weapon

	// Deques
	std::deque<DWORD> m_oSceneMeshMatCountDeq, m_oWeaponMeshMatCountDeq, m_oSkinnedMeshMatCountDeq; // Meshes' material deques
	std::deque<IDirect3DTexture9 **> m_oSceneMeshTextureDeq, m_oWeaponMeshTextureDeq, m_oSkinnedMeshTextureDeq; // Texture deque for meshes
	std::deque<ID3DXMesh *> m_oSceneMeshDeq, m_oWeaponMeshDeq, m_oSkinnedMeshDeq, m_oVehicleMeshDeq; // Mesh deques
	std::deque<ID3DXSkinInfo *> m_oSkinInfoDeq; // Mesh skin info deque
	std::deque<SBoundingBox *> m_oBoundingBoxDeq; // Bounding box deque
	std::deque<SBoundingSphere *> m_oBoundingSphereDeq; // Bounding sphere deque

	HRESULT m_hResult; // It will be used for checking errors
};

extern CGameManager *g_pGameManager;

//------------------------------------------------------------------
// Name: EGameStatus (enumeration)
// Desc: It will be used to determine the current game-status
//------------------------------------------------------------------
enum EGameStatus
{
	Intro = 1, // Into time
	GameUI, // Game user interface
	LoadingScene, // Loading a scene
	DisplayingMenu, // Displaying menu
	Paused, // The game is paused
	Playing // The game is being played
};

// EActiveScene enumeration
enum EActiveScene
{
	CrateFactory = 1, // Crate factory
	BarrelFactory, // Barrel factory
	FountainPark, // Fountain park
};

// EActiveWeapon enumeration
enum EActiveWeapon
{
	Pistol = 1, // Pistol
	MachineGun, // Machine gun
	AK47, // AK47
	Revolver, // Revolver
	Grenade, // Grenade
	MissileLauncher, // Missile launcher
	Knife, // Knife
};

#endif // GAMEMANAGER_H