// Physics.cpp: Implementation of physics using PhysX
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"

// PhysX
//
//#include <PxPhysicsAPI.h> // PhysX
//#include <PxExtensionsAPI.h> // PhysX extensions
//
// End PhysX

// Bullet physics
//

#include <btBulletDynamicsCommon.h> // Dynamics

//
// Bullet physics

#include "Physics.h"

//------------------------------------------------------------------
// Name: CPhysics
// Desc: Default constructor
//------------------------------------------------------------------
CPhysics::CPhysics()
{
	//m_pPxPhysics = NULL;

	//m_pPxCooking = NULL;

	//m_pPxScene = NULL;

	//m_pPxActor = NULL;

	//m_pPxMaterial = NULL;

	//m_pPxDefaultCpuDispatcher = NULL;
}

//------------------------------------------------------------------
// Name: ~CPhysics
// Desc: Destructor
//------------------------------------------------------------------
CPhysics::~CPhysics()
{
	//if(m_pPxPhysics)
	//	::PxCloseExtensions(); // Close the PhysX extensions

	//FREE_PHYSX(m_pPxDefaultCpuDispatcher);

	//FREE_PHYSX(m_pPxMaterial);

	//FREE_PHYSX(m_pPxActor);

	//FREE_PHYSX(m_pPxScene);

	//FREE_PHYSX(m_pPxCooking);

	//FREE_PHYSX(m_pPxPhysics);

	//FREE_PHYSX(m_pPxFoundation);
}

//------------------------------------------------------------------
// Name: createActor
// Desc: Create an actor
//------------------------------------------------------------------
//PxActor *CPhysics::createActor(PxTriangleMeshDesc *pPxTriangleMeshDesc)
//{
//	return NULL;
//}
//
////------------------------------------------------------------------
//// Name: createMaterial
//// Desc: Create a material
////------------------------------------------------------------------
//PxMaterial *CPhysics::createMaterial(PxReal pxStaticFriction, PxReal pxDynamicFriction, PxReal pxRestitution)
//{
//	//PxMaterialDesc oPxMaterialDesc = {0};
//
//	return NULL;
//}
//
////------------------------------------------------------------------
//// Name: 
//// Desc: 
////------------------------------------------------------------------
//
////------------------------------------------------------------------
//// Name: getScene
//// Desc: Get the scene
////------------------------------------------------------------------
//PxScene *CPhysics::getScene() const
//{
//	return m_pPxScene;
//}

//------------------------------------------------------------------
// Name: initCoreEngine
// Desc: Initialize the core physics engine
//------------------------------------------------------------------
bool CPhysics::initCoreEngine()
{
	//m_pPxFoundation = ::PxCreateFoundation(PX_PHYSICS_VERSION, m_oPxDefaultAllocatorCallback, m_oPxDefaultErrorCallback);
	//if(!m_pPxFoundation)
	//	return false;

	//// Create an instance of the physics SDK
	//m_pPxPhysics = ::PxCreatePhysics(PX_PHYSICS_VERSION, *m_pPxFoundation, PxTolerancesScale(), true);
	//if(!m_pPxPhysics)
	//	return false;

	//// Intialize the PhysX extensions
	//if(!::PxInitExtensions(*m_pPxPhysics))
	//	return false;

	//// Create an instance of cooking interface
	//m_pPxCooking = ::PxCreateCooking(PX_PHYSICS_VERSION, *m_pPxFoundation, PxCookingParams());
	//if(!m_pPxCooking)
	//	return false;

	// Scene description
	//PxSceneDesc oPxSceneDesc(m_pPxPhysics->getTolerancesScale());
	//oPxSceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f); // Gravity
	//oPxSceneDesc.cpuDispatcher = m_pPxDefaultCpuDispatcher = ::PxDefaultCpuDispatcherCreate(1);
	//m_pPxScene = m_pPxPhysics->createScene(oPxSceneDesc); // Create a scene which is the representation of the our world

	// Material
	//m_pPxMaterial = m_pPxPhysics->createMaterial(0.5, 0.5f, 0.1f); // Create a material with static friction, dynamic friction, restitution

	return true;
}

//------------------------------------------------------------------
// Name: initGameEngine
// Desc: Initialize the game physics engine
//------------------------------------------------------------------
bool CPhysics::initGameEngine()
{
	return true;
}

//------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------

CPhysics g_oPhysics;
CPhysics *g_pPhysics = &g_oPhysics;