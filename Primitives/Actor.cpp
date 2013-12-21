// Actor.cpp: Implementation of an actor
// Copyright (C) 2012-2013 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "..\Camera\Camera.h"
#include "..\Primitives\Transform.h"
#include "..\Primitives\Primitive.h"
#include "..\Primitives\AssetLoader.h"
#include "..\Script\Script.h"
#include "..\AI\Agent.h"
#include "..\Primitives\Material.h"
#include "..\Graphics\Shader.h"
#include "Actor.h"

//---------------------------------------------------------------------------
// Name: Actor
// Desc: Default constructor
//---------------------------------------------------------------------------
CActor::CActor()
{
	m_pPrimitive = nullptr;

	m_pCamera = nullptr;

	m_pTransform = nullptr;

	m_pShader = nullptr;

	m_pScript = nullptr;

	m_pAgent = nullptr;

	m_pMaterial = nullptr;
}

//---------------------------------------------------------------------------
// Name: Actor
// Desc: Constructor
//---------------------------------------------------------------------------
CActor::CActor(const std::wstring oActorName, const std::wstring oActorTag, CBasePrimitive *pBasePrimitive, CCamera *pCamera, CTransform *pTransform, CShader *pShader, CScript *pScript, CAgent *pAgent, SMaterial *pMaterial)
{
}

//---------------------------------------------------------------------------
// Name: ~CActor
// Desc: Destructor
//---------------------------------------------------------------------------
CActor::~CActor()
{
	DELETE_FREE(m_pPrimitive);

	DELETE_FREE(m_pAgent);

	DELETE_FREE(m_pScript);

	DELETE_FREE(m_pShader);

	DELETE_FREE(m_pTransform);

	DELETE_FREE(m_pCamera);

	DELETE_FREE(m_pMaterial);
}

//---------------------------------------------------------------------------
// Name: onInit
// Desc: Method called on initialization
//---------------------------------------------------------------------------
void CActor::onInit()
{
}

//---------------------------------------------------------------------------
// Name: onRender
// Desc: Method called on render
//---------------------------------------------------------------------------
void CActor::onRender()
{
	// Check if this actor is enabled or not
	if(!m_bEnabled) // This actor is not enabled
		return; // Since this actor is not enabled, don't render this actor
}

//---------------------------------------------------------------------------
// Name: setName
// Desc: Set the name of this actor
//---------------------------------------------------------------------------
bool CActor::setName(std::wstring oActorName)
{
	m_oActorName = oActorName;

	return true;
}

//---------------------------------------------------------------------------
// Name: setTag
// Desc: Set the tag for this actor
//---------------------------------------------------------------------------
bool CActor::setTag(std::wstring oActorTag)
{
	m_oActorTag = oActorTag;

	return true;
}

//---------------------------------------------------------------------------
// Name: setPrimitive
// Desc: Set primitive to this actor
//---------------------------------------------------------------------------
bool CActor::setPrimitive(CBasePrimitive *pBasePrimitive)
{
	m_pPrimitive = pBasePrimitive;

	return true;
}

//---------------------------------------------------------------------------
// Name: setCamera
// Desc: Set camera to this actor
//---------------------------------------------------------------------------
bool CActor::setCamera(CCamera *pCamera)
{
	m_pCamera = pCamera;

	return true;
}

//---------------------------------------------------------------------------
// Name: setTransform
// Desc: Set transformation to this actor
//---------------------------------------------------------------------------
bool CActor::setTransform(CTransform *pTransform)
{
	m_pTransform = pTransform;

	return true;
}

//---------------------------------------------------------------------------
// Name: setShader
// Desc: Set shader to this actor
//---------------------------------------------------------------------------
bool CActor::setShader(CShader *pShader)
{
	m_pShader = pShader;

	return true;
}

//---------------------------------------------------------------------------
// Name: setScript
// Desc: Set script to this actor
//---------------------------------------------------------------------------
bool CActor::setScript(CScript *pScript)
{
	m_pScript = pScript;

	return true;
}

//---------------------------------------------------------------------------
// Name: setAgent
// Desc: Set agent to this actor
//---------------------------------------------------------------------------
bool CActor::setAgent(CAgent *pAgent)
{
	m_pAgent = pAgent;

	return true;
}

//---------------------------------------------------------------------------
// Name: setMaterial
// Desc: Set material to this actor
//---------------------------------------------------------------------------
bool CActor::setMaterial(SMaterial *pMaterial)
{
	m_pMaterial = pMaterial;

	return true;
}

//---------------------------------------------------------------------------
// Name: setEnabled
// Desc: Enable/disable this actor
//---------------------------------------------------------------------------
bool CActor::setEnabled(bool bEnabled)
{
	return m_bEnabled = bEnabled;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign actor to this actor instance
//---------------------------------------------------------------------------
CActor CActor::operator=(const CActor &rActor)
{
	m_pPrimitive = rActor.m_pPrimitive;
	m_pCamera = rActor.m_pCamera;
	m_pTransform = rActor.m_pTransform;
	m_pAgent = rActor.m_pAgent;
	m_pScript = rActor.m_pScript;
	m_pShader = rActor.m_pShader;
	m_pMaterial = rActor.m_pMaterial;

	return *this; // return this instance
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Check for the equality of the specified actor with the current one
//---------------------------------------------------------------------------
bool CActor::operator==(const CActor &rActor)
{
	// Check if all the attributes are of the current type
	if(m_pAgent == rActor.m_pAgent && m_pPrimitive == rActor.m_pPrimitive && m_pCamera == rActor.m_pCamera && m_pScript == rActor.m_pScript && m_pShader == rActor.m_pShader && m_pMaterial == rActor.m_pMaterial) // All the attributes are of the current type
		return true; // Return true since all the attributes are of the current type

	return false; // Not all of the attributes are of the current type
}

//---------------------------------------------------------------------------
// Name: getName
// Desc: Get an actor's name
//---------------------------------------------------------------------------
std::wstring CActor::getName() const
{
	return m_oActorName;
}

//---------------------------------------------------------------------------
// Name: getTag
// Desc: Get an actor's tag
//---------------------------------------------------------------------------
std::wstring CActor::getTag() const
{
	return m_oActorTag;
}

//---------------------------------------------------------------------------
// Name: getPrimitive
// Desc: Get the geometry associated with an actor
//---------------------------------------------------------------------------
CBasePrimitive *CActor::getPrimitive() const
{
	return m_pPrimitive;
}

//---------------------------------------------------------------------------
// Name: getCamera
// Desc: Get a camera associated with an actor
//---------------------------------------------------------------------------
CCamera *CActor::getCamera() const
{
	return m_pCamera;
}

//---------------------------------------------------------------------------
// Name: getTransform
// Desc: Get the transformation of an actor
//---------------------------------------------------------------------------
CTransform *CActor::getTransform() const
{
	return m_pTransform;
}

//---------------------------------------------------------------------------
// Name: getShader
// Desc: Return a shader associated with this actor
//---------------------------------------------------------------------------
CShader *CActor::getShader() const
{
	return m_pShader;
}

//---------------------------------------------------------------------------
// Name: getScript
// Desc: Get the script of an actor
//---------------------------------------------------------------------------
CScript *CActor::getScript() const
{
	return m_pScript;
}

//---------------------------------------------------------------------------
// Name: getAgent
// Desc: Get the agent of an actor
//---------------------------------------------------------------------------
CAgent *CActor::getAgent() const
{
	return m_pAgent;
}

//---------------------------------------------------------------------------
// Name: getMaterial
// Desc: Get the material of an actor
//---------------------------------------------------------------------------
SMaterial *CActor::getMaterial() const
{
	return m_pMaterial;
}

//---------------------------------------------------------------------------
// Name: render
// Desc: Render this actor
//---------------------------------------------------------------------------
HRESULT CActor::render(ID3D11DeviceContext *pD3DDeviceContext)
{
	m_pPrimitive->draw(getShader(), pD3DDeviceContext);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: isEnabled
// Desc: Returns a boolean value indicating if it's enabled/disabled
//---------------------------------------------------------------------------
bool CActor::isEnabled() const
{
	return m_bEnabled;
}