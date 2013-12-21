// Game.h: 
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef GAME_H
#define GAME_H

enum class EGameMode;

// CGame class
class CGame final
{
public: // Public methods
	CGame(); // Default constructor
	~CGame(); // Destructor

	HRESULT initCoreEngine(); // Initialize the core graphics engine
	HRESULT initGameEngine(); // Initialize the core game engine

	bool pauseOrResume(); // Pause or resume the game

	bool isPaused() const; // Will return a boolean value determining

	EGameMode getMode() const; // Get the gaming mode

	void setMode(EGameMode oGameMode); // Set the gaming mode to the specified mode

	HRESULT onLoadGameEngine(); // Invoked when the game engine is loading
	HRESULT onPlay(); // Invoked when the game is being played
	HRESULT onPause(); // Invoked when the game is paused
	HRESULT onMenu(); // Invoked when on the on-screen menu

	HRESULT printScreen(); // Print the screen

	HRESULT display(float fDeltaTime); // Render the graphics onto the screen

private: // Private attributes
	CCubePrimitive *m_pCubePrimitive;
	CPlanePrimitive *m_pScreenAlignedQuadPrimitive, *m_pPlanarSurfacePrimitive;
	CInstancePlanePrimitive *m_pInstancePlanePrimitive;
	CPointPrimitive *m_pPointPrimitive;

	std::unique_ptr<CAsset> m_oSceneAsset; // Scene asset

	CTexture2D *m_pCubeTexture, *m_pPlaneTexture; // Textures
	CTexture2D *m_pCubeNormalMapTexture; // Normal maps

	bool m_bShowFPS, m_bPaused;

	EGameMode m_oGameMode; // Will hold the current status of game

	float m_fRotation;

	HRESULT m_hResult; // It will be used for checking errors
};

extern CGame *g_pGame;

// EGameMode enumeration
enum class EGameMode
{
	eLoading_Core_Engine, // The core engine is being loaded
	eLoading_Game_Engine, // The core game engine is being loaded
	ePlaying, // The user is playing the game
	ePaused, // The game is paused
	eMenu, // Menu is being displayed
	eQuit, // The game is about to quit
};

#endif // GAME_H