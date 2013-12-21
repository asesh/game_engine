// CubeMap.cpp: Implementation of cube mapping
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "CubeMap.h"

//---------------------------------------------------------------------------
// Name: CCubeMap
// Desc: Default constructor
//---------------------------------------------------------------------------
CCubeMap::CCubeMap()
{
	m_pCubeMapTexture = NULL;
}

//---------------------------------------------------------------------------
// Name: ~CCubeMap
// Desc: Destructor
//---------------------------------------------------------------------------
CCubeMap::~CCubeMap()
{
	DELETE_FREE(m_pCubeMapTexture);
}

//---------------------------------------------------------------------------
// Name: create
// Desc: Create a cubemap with the specified settings
//---------------------------------------------------------------------------
bool CCubeMap::create(float fHeight, float fWidth, float fDepth)
{
	// Create a cube primitive with the specified properties
	m_pCubePrimitive = new CCubePrimitive(fWidth, fHeight, fDepth);
	if(!m_pCubePrimitive)
		return false;

	return true;
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------