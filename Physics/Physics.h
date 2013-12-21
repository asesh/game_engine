// Physics.h: Implementation of physics using Bullet physics
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef PHYSICS_H
#define PHYSICS_H

//using namespace physx;
//using namespace physx::pubfnd3;

// CPxDefaultAllocatorCallback class
//class CPxDefaultAllocatorCallback : public PxAllocatorCallback
//{
//	void *allocate(size_t size, const char *, const char *, int)
//	{
//		return _aligned_malloc(size, 16);
//	}
//
//	void deallocate(void *pData)
//	{
//		_aligned_free(pData);
//	}
//};
//
//// CPxDefaultErrorCallback class
//class CPxDefaultErrorCallback : public PxErrorCallback
//{
//public:
//	virtual void reportError(PxErrorCode::Enum e, const char *message, const char *file, int line)
//	{
//		const char *pszErrorCode = NULL;
//
//		switch(e)
//		{
//		case PxErrorCode::eDEBUG_INFO:
//			pszErrorCode = "info";
//			break;
//
//		case PxErrorCode::eDEBUG_WARNING:
//			pszErrorCode = "warning";
//			break;
//
//		case PxErrorCode::eINVALID_OPERATION:
//			break;
//
//		case PxErrorCode::eINVALID_PARAMETER:
//			pszErrorCode = "Invalid operation";
//			break;
//
//		case PxErrorCode::eOUT_OF_MEMORY:
//			pszErrorCode = "Out of memory";
//			break;
//
//		default:
//			pszErrorCode = "Unknown error";
//			break;
//		}
//	}
//};

// CPhysics class
class CPhysics
{
public:
	CPhysics(); // Default constructor
	~CPhysics(); // Destructor

	//PxActor *createActor(PxTriangleMeshDesc *pPxTriangleMeshDesc); // Create an actor
	//PxMaterial *createMaterial(PxReal pxStaticFriction, PxReal pxDynamicFriction, PxReal pxRestitution); // Create a material

	//PxScene *getScene() const; // Get the scene

	bool initCoreEngine(); // Initialize the core physics engine
	bool initGameEngine(); // Initialize the game physics engine

private:
	//PxFoundation *m_pPxFoundation; // Foundation

	//PxPhysics *m_pPxPhysics; // Physics

	//PxCooking *m_pPxCooking; // Cooking

	//PxScene *m_pPxScene; // Scene

	//PxActor *m_pPxActor; // Actor

	//PxMaterial *m_pPxMaterial; // Material 

	//PxDefaultCpuDispatcher *m_pPxDefaultCpuDispatcher; // CPU task dispatcher

	//CPxDefaultAllocatorCallback m_oPxDefaultAllocatorCallback;
	//CPxDefaultErrorCallback m_oPxDefaultErrorCallback;
};

extern CPhysics *g_pPhysics;

#endif // PHYSICS_H