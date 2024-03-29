// Agent.cpp: 
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "Agent.h"

//---------------------------------------------------------------------------
// Name: CAgent
// Desc: Default constructor
//---------------------------------------------------------------------------
CAgent::CAgent()
{
	m_bArmed = false;
}

//---------------------------------------------------------------------------
// Name: CAgent
// Desc: Constructor
//---------------------------------------------------------------------------
CAgent::CAgent(EAgentType oAgentType, short sHeight, short sWeight, short sSpeed, short sLifeSpan)
{
	m_oAgentType = oAgentType;

	m_sHeight = sHeight;
	m_sWeight = sWeight;
	m_sSpeed = sSpeed;
	m_sLifeSpan = sLifeSpan;
}

//---------------------------------------------------------------------------
// Name: ~CAgent
// Desc: Destructor
//---------------------------------------------------------------------------
CAgent::~CAgent()
{
}

//---------------------------------------------------------------------------
// Name: getHeight
// Desc: Get the height of the agent
//---------------------------------------------------------------------------
short CAgent::getHeight() const
{
	return m_sHeight;
}

//---------------------------------------------------------------------------
// Name: getWeight
// Desc: Get the weight of the agent
//---------------------------------------------------------------------------
short CAgent::getWeight() const
{
	return m_sWeight;
}

//---------------------------------------------------------------------------
// Name: getSpeed
// Desc: Get the speed of the agent
//---------------------------------------------------------------------------
short CAgent::getSpeed() const
{
	return m_sSpeed;
}


//---------------------------------------------------------------------------
// Name: getType
// Desc: Get the type of the agent
//---------------------------------------------------------------------------
EAgentType CAgent::getType() const
{
	return m_oAgentType;
}

//---------------------------------------------------------------------------
// Name: setHeight
// Desc: Set the height of the agent
//---------------------------------------------------------------------------
void CAgent::setHeight(short sHeight)
{
	m_sHeight = sHeight;
}

//---------------------------------------------------------------------------
// Name: setWeight
// Desc: Set the weight of the agent
//---------------------------------------------------------------------------
void CAgent::setWeight(short sWeight)
{
	m_sWeight = sWeight;
}

//---------------------------------------------------------------------------
// Name: setSpeed
// Desc: Set the speed of the agent
//---------------------------------------------------------------------------
void CAgent::setSpeed(short sSpeed)
{
	m_sSpeed = sSpeed;
}

//---------------------------------------------------------------------------
// Name: setType
// Desc: Set the type of the agent
//---------------------------------------------------------------------------
void CAgent::setType(EAgentType oAgentType)
{
	m_oAgentType = oAgentType;
}

//---------------------------------------------------------------------------
// Name: isArmed
// Desc: Returns a boolean value indicating an agent is armed or not
//---------------------------------------------------------------------------
bool CAgent::isArmed() const
{
	return m_bArmed;
}

//---------------------------------------------------------------------------
// Name: walk
// Desc: Walk
//---------------------------------------------------------------------------
void CAgent::walk()
{
}

//---------------------------------------------------------------------------
// Name: run
// Desc: Run
//---------------------------------------------------------------------------
void CAgent::run()
{
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------

CAgent g_oHeroAgent;
CAgent *g_pHeroAgent = &g_oHeroAgent;