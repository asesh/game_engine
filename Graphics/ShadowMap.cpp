// ShadowMapping.cpp: Implementation of shadow mappping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "ShadowMap.h"

//------------------------------------------------------------------
// Name: CShadowMap
// Desc: Default constructor
//------------------------------------------------------------------
CShadowMap::CShadowMap()
{
	m_pD3DShadowMapTexture = NULL;
}

//------------------------------------------------------------------
// Name: ~CShadowMap
// Desc: Destructor
//------------------------------------------------------------------
CShadowMap::~CShadowMap()
{
	FREE_COM(m_pD3DShadowMapTexture);
}

//------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------

//------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------