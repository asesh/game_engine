// Game.cpp: Implementation of CGame class
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "../Graphics/ConstantBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/DiffuseLightShader.h"
#include "../Graphics/MotionBlurShader.h"
#include "../Graphics/InstanceShader.h"
#include "../Graphics/NormalMapShader.h"
#include "../Graphics/ScreenAlignedQuadShader.h"
#include "../Graphics/SpecularLightShader.h"
#include "Game.h"
#include "../Common/Libs.h"

//---------------------------------------------------------------------------
// Name: CGame
// Desc: Default constructor
//---------------------------------------------------------------------------
CGame::CGame()
{
#ifdef _DEBUG // Debug versions

	m_bShowFPS = true; // Show FPS

#else // Release versions

	m_bShowFPS = false; // Don't show FPS

#endif // _DEBUG

	m_bPaused = false; // Initially the game is not paused

	m_pCubePrimitive = nullptr;
	m_pScreenAlignedQuadPrimitive = nullptr;
	m_pPlanarSurfacePrimitive = nullptr;
	m_pPointPrimitive = nullptr;
	m_pInstancePlanePrimitive = nullptr;

	m_pCubeTexture = nullptr;
	m_pPlaneTexture = nullptr;
	m_pCubeNormalMapTexture = nullptr;

	setMode(EGameMode::eLoading_Core_Engine); // Initially set the game mode to loading core engine since it's the first step of engine initialization

	m_hResult = S_OK;
}

//---------------------------------------------------------------------------
// Name: ~CGame
// Desc: Destructor
//---------------------------------------------------------------------------
CGame::~CGame()
{
	DELETE_FREE(m_pCubeNormalMapTexture);
	DELETE_FREE(m_pCubeTexture);
	DELETE_FREE(m_pPlaneTexture);

	DELETE_FREE(m_pPlanarSurfacePrimitive);
	DELETE_FREE(m_pInstancePlanePrimitive);
	DELETE_FREE(m_pCubePrimitive);
	DELETE_FREE(m_pScreenAlignedQuadPrimitive);
	DELETE_FREE(m_pPointPrimitive);
}

//---------------------------------------------------------------------------
// Name: initCoreEngine
// Desc: Initialize the core game engine
//---------------------------------------------------------------------------
HRESULT CGame::initCoreEngine()
{
	CLog::log(L"Initializing core engine");

	CHECK_COM(g_pD3DGraphics->initCoreEngine()); // Initialize the core 3D graphics engine

	CLog::log(L"Core engine initialization complete");

	g_pCamera->createProjectionMatrix(IMM_DEV_CONTEXT); // Create projection matrix

	//CHECK_COM(g_pD2DGraphics->initCoreEngine()); // Initialize core 2D graphics engine

	CLog::log(L"Initializing the scripting engine");

	///g_pScript->init(); // Initialize the scripting engine

	CLog::log(L"Scripting engine initialization complete");

	setMode(EGameMode::eLoading_Game_Engine); // Now since the core engine has finished loading, signal that the game engine is about to load

	CLog::log(L"Core engine initialization complete");

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: initGameEngine
// Desc: Initialize the game engine
//---------------------------------------------------------------------------
HRESULT CGame::initGameEngine()
{
	WCHAR szFolderPath[MAX_PATH]; // Will hold the path of the specified folder

	CLog::log(L"Initializing game engine");

	::SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, 0, szFolderPath); // Get the path of documents

	std::wstring oMeshPathString(szFolderPath);
	oMeshPathString += L"\\Autodesk Projects\\3ds Max Projects\\export\\";
	::SetCurrentDirectory(oMeshPathString.data());

	// Load asset
	m_oSceneAsset = std::unique_ptr<CAsset>(new CAsset());
	CHECK_COM(m_oSceneAsset->load(L"Test.3ds"));

	//CFBXAsset oFBXAsset;
	//oFBXAsset.load("SMG.FBX");

	//oMeshPathString += L"SMG.3DS";

	::SHGetFolderPath(nullptr, CSIDL_MYPICTURES, nullptr, NULL, szFolderPath); // Get the path of Pictures folder

	std::wstring oTexturePathString(szFolderPath);

	//CLog::log(L"Initializing core PhysX");

	//// Initialize PhysX
	//if(!g_pPhysics->initCoreEngine())
	//	return E_FAIL;

	//CLog::log(L"PhysX initialization complete");

	// Load texture for the plane
	//oTexturePathString = szFolderPath;
	//oTexturePathString +=  L"\\Textures\\iron12_mod2.jpg"; // Plane texture
	//CHECK_VALIDATION(m_pPlaneTexture = new CTexture(oTexturePathString));

	CHECK_COM(g_pD3DGraphics->initGameEngine()); // Initialize 3D graphics game engine

	//CHECK_COM(g_pD2DGraphics->initGameEngine()); // Initialize 2D graphics game engine

	// Build cube geometry
	CHECK_VALIDATION((m_pCubePrimitive = new CCubePrimitive(1.0f, 1.0f, 1.0f)));

	// Build plane geometry
	//CHECK_VALIDATION(m_pScreenAlignedQuadPrimitive = new CPlanePrimitive(1.0f, 1.0f));

	// Planar surface primitive
	CHECK_VALIDATION((m_pPlanarSurfacePrimitive = new CPlanePrimitive(1.0f, 1.0f)));

	std::vector<CVector4> oInstancePosition(3); // Will hold the instance position of the planes
	for(int nCount = 0; nCount < oInstancePosition.size(); nCount++) // Iterate through all the instances
		oInstancePosition[nCount]  += CVector4(nCount + 2.0f, -1.0f, 0.0f, 0.0f); // Shift the planes by 2 units on the x-axis
	g_pInstanceShader->updateConstantBuffer(&oInstancePosition[0], IMM_DEV_CONTEXT); // Update instance constant buffer

	// Create instances of plane
	CHECK_VALIDATION((m_pInstancePlanePrimitive = new CInstancePlanePrimitive(1.0f, 1.0f, 3, sizeof(CVector4), &oInstancePosition[0])));

	//// Build point primitives
	//CHECK_VALIDATION(m_pPointPrimitive = new CPointPrimitive(1.0f, 1.0f, 20.0f, 20.0f));

	// Load texture for the cube
	//oTexturePathString = szFolderPath;
	//oTexturePathString += L"\\Textures\\crate2.dds"; // Cube texture
	//CHECK_VALIDATION(m_pCubeTexture = new CTexture(oTexturePathString));

	//// Load normal map texture for the cube
	//oTexturePathString = szFolderPath;
	//oTexturePathString +=  L"\\Textures\\crate2_normalmap.dds";
	//CHECK_VALIDATION(m_pCubeNormalMapTexture = new CTexture(oTexturePathString));

	g_pDiffuseLightShader->updateStaticConstantBuffer(IMM_DEV_CONTEXT);

	setMode(EGameMode::ePlaying); // Set game mode to playing

	CLog::log(L"Game engine initialization complete");

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: pauseOrResume
// Desc: Pause/resume the game
//---------------------------------------------------------------------------
bool CGame::pauseOrResume()
{
	if(isPaused()) // The game is paused
	{
		setMode(EGameMode::ePlaying); // Resume the game

		m_bPaused = false; // Signal that the game has been resumed

		//g_pInput->showCursor(FALSE); // hide the cursor
	}
	else // The game is not paused
	{
		setMode(EGameMode::ePaused); // Pause the game

		m_bPaused = true; // Signal that the game has been paused

		//g_pInput->showCursor(TRUE); // show the cursor
	}

	return true;
}

//---------------------------------------------------------------------------
// Name: isPaused
// Desc: Will return a boolean value indicating if the game is paused/not
//---------------------------------------------------------------------------
bool CGame::isPaused() const
{
	return (m_bPaused == true);
}

//---------------------------------------------------------------------------
// Name: getMode
// Desc: Get the gaming mode
//---------------------------------------------------------------------------
EGameMode CGame::getMode() const
{
	return m_oGameMode;
}

//---------------------------------------------------------------------------
// Name: setMode
// Desc: Set the gaming mode to the specified mode
//---------------------------------------------------------------------------
void CGame::setMode(EGameMode oGameMode)
{
	m_oGameMode = oGameMode; // Assign the specified game mode
	switch(m_oGameMode)
	{
	case EGameMode::eLoading_Core_Engine: // Loading core engine
		break;

	case EGameMode::eLoading_Game_Engine: // Loading game engine
		g_pInput->showCursor(FALSE);
		break;

	case EGameMode::ePlaying: // Playing
		g_pInput->showCursor(FALSE);
		break;

	case EGameMode::ePaused: // Paused
		g_pInput->showCursor(TRUE);
		break;

	case EGameMode::eMenu: // Menu
		g_pInput->showCursor(TRUE);
		break;

	case EGameMode::eQuit: // Quit
		g_pInput->showCursor(TRUE);
		break;
	}
}

//---------------------------------------------------------------------------
// Name: onPlaying
// Desc: The game is being played
//---------------------------------------------------------------------------
HRESULT CGame::onPlay()
{
	g_pInput->centerCursor(g_pMainFrame->getWindowHandle()); // Center the cursor

	g_pCamera->shoot(); // Start shooting with the camera

	g_pD3DGraphics->clearRenderTargetAndDepthStencilViews(); // Clear the render target and depth-stencil views

	g_pD3DGraphics->enableBackfaceCulling(); // Enable backface culling

	// Apply diffuse lighting and render a cube
	//g_pDiffuseLightingShader->apply(0, g_pD3DGraphics->getImmediateDeviceContext());
	//g_pD3DGraphics->beginOcclusionQuery();

	// Render the instanced plane
	g_pChangesEveryFrameConstBuffer->m_oWorldMatrix.setIdentity(); // Set world matrix to identity
	g_pTransformMatrices->translate(0.0f, -10.0f, 0.0f); // Translation
	g_pTransformMatrices->rotateIdentity(); // Rotation
	g_pTransformMatrices->scale(10.0f, 10.0f, 10.0f); // Scaling
	g_pTransformMatrices->calculateWorldTransform(g_pChangesEveryFrameConstBuffer->m_oWorldMatrix); // Combine world transformation matrices
	//for(DWORD dwInstanceCount = 0; dwInstanceCount < m_pInstancePlanePrimitive->getNumOfInstances(); dwInstanceCount++) // Iterate through all the instances of the plane
	//{
		//g_pInstanceShader->updateConstantBuffer(
		//m_pInstancePlanePrimitive->getInstanceDataBuffer()-
		///m_pInstancePlanePrimitive->updateData(&CVector3(dwInstanceCount * 2.0f, 0.0f, dwInstanceCount * 2.0f), sizeof(CVector3), m_pInstancePlanePrimitive->getNumOfInstances(), IMM_DEV_CONTEXT); // Update instancing data
	//	//m_pInstancesMatrix[dwInstanceCount].setIdentity();
	//	//m_pInstancesMatrix[dwInstanceCount] = g_pMath->matrixTranslation(dwInstanceCount * 10.0f, 0.0f, dwInstanceCount * 10.0f);
	//	//m_pInstancesMatrix[dwCount] = g_pChangesEveryFrameConstBuffer->m_oWorldMatrix * g_pCamera->getViewMatrix() * g_pCamera->getProjectionMatrix();
	//	//m_pInstancesMatrix[dwCount] = g_pTransformMatrices->translate
	//}
	//m_pPlaneTexture->set(g_pInstanceShader); // Set plane texture
	m_pInstancePlanePrimitive->draw(g_pInstanceShader, IMM_DEV_CONTEXT); // Render the instanced plane

	// Render screen aligned quad
	//g_pChangesEveryFrameConstBuffer->m_oHomogeneousMatrix.setIdentity(); // Reset the transformation since we are rendering fullscreen quad
	//m_pPlaneTexture->set(g_pScreenAlignEffect); // Set plane texture
	//m_pScreenAlignedQuadPrimitive->draw(g_pScreenAlignEffect, IMM_DEV_CONTEXT); // Render the screen aligned plane

	// Render plane
	g_pChangesEveryFrameConstBuffer->m_oWorldMatrix.setIdentity(); // Set world matrix to identity
	g_pTransformMatrices->rotateIdentity(); // Do not rotate
	g_pTransformMatrices->scale(5, 5, 5); // Scaling
	g_pTransformMatrices->translate(0.0f, -1.0f, 5.0f); // Translation
	//m_pPlaneTexture->set(g_pDiffuseLightShader); // Set plane texture
	g_pTransformMatrices->calculateWorldTransform(g_pChangesEveryFrameConstBuffer->m_oWorldMatrix); // Calculate the world transformation
	m_pPlanarSurfacePrimitive->draw(g_pDiffuseLightShader, IMM_DEV_CONTEXT); // Render the screen aligned plane

	// Render the cube
	g_pChangesEveryFrameConstBuffer->m_oWorldMatrix.setIdentity(); // Set world matrix to identity
	g_pTransformMatrices->translate(0.0f, 0.0f, 5.0f); // Translation
	g_pTransformMatrices->rotateY(g_pMath->getRotation()); // Rotation
	g_pTransformMatrices->scaleIdentity(); // Scaling
	g_pTransformMatrices->calculateWorldTransform(g_pChangesEveryFrameConstBuffer->m_oWorldMatrix); // Calculate the world transformation
	//m_pCubeTexture->set(g_pDiffuseLightingShader); // Set diffuse lighting effect
	m_pCubePrimitive->draw(g_pNormalMapShader, IMM_DEV_CONTEXT); // Draw the cube

	g_pD3DGraphics->disableBackfaceCulling(); // Disable backface culling

	// Render the scene
	g_pChangesEveryFrameConstBuffer->m_oWorldMatrix.setIdentity(); // Identity world transformation
	g_pTransformMatrices->rotateIdentity();
	g_pTransformMatrices->scaleIdentity();
	g_pTransformMatrices->translateIdentity();
	g_pTransformMatrices->calculateWorldTransform(g_pChangesEveryFrameConstBuffer->m_oWorldMatrix);
	for(DWORD dwMeshIndex = 0; dwMeshIndex < m_oSceneAsset->getNumberOfMeshes(); dwMeshIndex++)
		m_oSceneAsset->draw(g_pDiffuseLightShader, IMM_DEV_CONTEXT, dwMeshIndex); // Draw the entire scene

	g_pD3DGraphics->render(); // Render 3D graphics

	//g_pD3DGraphics->endAndGetOcclusionQuery();

	//g_pD2DGraphics->render(); // Render 2D graphics

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: onPause
// Desc: The game is paused
//---------------------------------------------------------------------------
HRESULT CGame::onPause()
{
	//g_pInput->showCursor(TRUE);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: onMenu
// Desc: The menu is being displayed
//---------------------------------------------------------------------------
HRESULT CGame::onMenu()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: printScreen
// Desc: Print the screen
//---------------------------------------------------------------------------
HRESULT CGame::printScreen()
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: display
// Desc: Display the graphics onto the screen
//---------------------------------------------------------------------------
HRESULT CGame::display(float fDeltaTime)
{
	m_fRotation += fDeltaTime; // Accumulate the elapsed time

	g_pMath->calculateRotation(fDeltaTime);

	g_pMath->calculateFPS(fDeltaTime); // Calculate FPS

	switch(m_oGameMode)
	{
	case EGameMode::eLoading_Game_Engine: // The game engine is loading
		CHECK_CLOSE_COM(initGameEngine());
		break;

	case EGameMode::ePlaying: // The game is being played
		CHECK_CLOSE_COM(onPlay());
		break;

	case EGameMode::ePaused: // The game is paused
		onPause();
		break;

	case EGameMode::eMenu: // Displaying game menu
		onMenu();
		break;
	}

	g_pD3DGraphics->present(); // Present the rendered 3D graphics onto the screen
	//g_pD2DGraphics->present(); // Present the rendered 2D graphics onto the screen

	return S_OK;
}

CGame g_oGame;
CGame *g_pGame = &g_oGame;