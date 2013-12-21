// Camera.cpp: Implementation of Camera
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"
#include "..\Common\GameEngine.h"
#include "..\Graphics\ConstantBuffer.h"
#include "..\Graphics\CubeMap.h"
#include "..\Math\Vector.h"
#include "..\Math\Matrix.h"
#include "Camera.h"

//---------------------------------------------------------------------------
// Name: CCamera
// Desc: Default constructor
//---------------------------------------------------------------------------
CCamera::CCamera()
{
	m_oUpVec = CVector3(0.0f, 1.0f, 0.0f); // Up vector
	m_oPositionVec = CVector3(0.0f, 0.0f, -1.0f); // Position vector
	m_oLookAtVec = CVector3(0.0f, 0.0f, 1.0f); // Look-at vector
	m_oRightVec = CVector3(1.0f, 0.0f, 0.0f); // Right vector
	//m_oViewMatrix = ::XMMatrixLookAtLH(m_oPositionVec, m_oLookAtVec, m_oUpVec);

	m_oViewMatrix.setIdentity(); // View matrix
	m_oProjectionMatrix.setIdentity(); // Projection matrix

	m_pSkyBox = nullptr; // Sky box
}

//---------------------------------------------------------------------------
// Name: CCamera
// Desc: Constructor
//---------------------------------------------------------------------------
CCamera::CCamera(CVector3 *pEyePosVec, CVector3 *pLookAtVec, CVector3 *pUpVec)
{
	m_oPositionVec = *pEyePosVec; // Position vector
	m_oLookAtVec = *pLookAtVec; // Look-at vector
	m_oUpVec = *pUpVec; // Up vector

	m_oViewMatrix.setIdentity(); // View matrix
	m_oProjectionMatrix.setIdentity(); // Projection matrix

	m_pSkyBox = nullptr; // Sky box
}

//---------------------------------------------------------------------------
// Name: CCamera
// Desc: Constructor
//---------------------------------------------------------------------------
CCamera::CCamera(CVector3 *pEyePosVec, CVector3 *pLookAtVec)
{
	m_oPositionVec = *pEyePosVec; // Position vector
	m_oLookAtVec = *pLookAtVec; // Look-at vector
	m_oUpVec = CVector3(0.0f, 1.0f, 0.0f);

	m_oViewMatrix.setIdentity(); // View matrix
	m_oProjectionMatrix.setIdentity(); // Projection matrix

	m_pSkyBox = nullptr; // Sky box
}

//---------------------------------------------------------------------------
// Name: ~CCamera
// Desc: Destructor
//---------------------------------------------------------------------------
CCamera::~CCamera()
{
	DELETE_FREE(m_pSkyBox); // Sky box
}

//---------------------------------------------------------------------------
// Name: createProjectionMatrix
// Desc: Create a default projection matrix
//---------------------------------------------------------------------------
void CCamera::createProjectionMatrix(ID3D11DeviceContext *pD3DDeviceContext)
{
	float fAspectRatio = static_cast<float>(static_cast<float>(g_pMainFrame->getWindowWidth()) / static_cast<float>(g_pMainFrame->getWindowHeight()));

	// Construct a left handed perspective projection matrix
	m_oProjectionMatrix = CMath::matrixPerspectiveFovLH(XM_PI * 0.5f, // FOV
		fAspectRatio, // Aspect ratio
		0.01f, // Distance to near clipping plane
		10000.0f); // Distance to far clipping plane

	// Update constant buffers
	g_pStaticConstBuffer->m_oProjectionMatrix = m_oProjectionMatrix;
	//g_pDiffuseLightingEffect->updateConstantBuffers(g_pStaticConstBuffer, pD3DDeviceContext);
}

//---------------------------------------------------------------------------
// Name: createProjectionMatrix
// Desc: Create a projection matrix based on the specified matrix
//---------------------------------------------------------------------------
void CCamera::createProjectionMatrix(CMatrix4x4 &rProjectionMatrix)
{
	m_oProjectionMatrix = rProjectionMatrix;
}

//---------------------------------------------------------------------------
// Name: getViewVector
// Desc: Get the view vector
//---------------------------------------------------------------------------
CVector3 CCamera::getViewVector() const
{
	return m_oLookAtVec;
}

//---------------------------------------------------------------------------
// Name: getViewMatrix
// Desc: Get the view transformation matrix
//---------------------------------------------------------------------------
CMatrix4x4 CCamera::getViewMatrix() const
{
	return m_oViewMatrix;
}

//---------------------------------------------------------------------------
// Name: getViewProjectionMatrix
// Desc: Get the projection transformation matrix
//---------------------------------------------------------------------------
CMatrix4x4 CCamera::getProjectionMatrix() const
{
	return m_oProjectionMatrix;
}

//---------------------------------------------------------------------------
// Name: getProjectionMatrix
// Desc: Get the combined view-projection transformation matrix
//---------------------------------------------------------------------------
CMatrix4x4 CCamera::getViewProjectionMatrix() const
{
	return m_oViewProjectionMatrix;// = m_oViewMatrix * m_oProjectionMatrix;
}

//---------------------------------------------------------------------------
// Name: setLens
// Desc: Set the lens of the camera
//---------------------------------------------------------------------------
void CCamera::setLens(CVector3 *pEyePosVec, CVector3 *pLookAtVec)
{
	m_oPositionVec = *pEyePosVec;
	m_oLookAtVec = *pLookAtVec;
}

//---------------------------------------------------------------------------
// Name: walk
// Desc: Walk in the specified direction
//---------------------------------------------------------------------------
void CCamera::walk(float fUnits)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Land: // Land mode camera
		m_oPositionVec += CVector3(m_oLookAtVec.getX(), 0.0f, m_oLookAtVec.getZ()) * fUnits;
		break;

	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		break;
	}
}

//---------------------------------------------------------------------------
// Name: strafe
// Desc: Move side-to-side
//---------------------------------------------------------------------------
void CCamera::strafe(float fUnits)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Land: // Land mode camera
		m_oPositionVec += CVector3(m_oRightVec.getX(), 0.0f, m_oRightVec.getZ()) * fUnits;
		break;

	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		break;
	}
}

//---------------------------------------------------------------------------
// Name: fly
// Desc: Fly
//---------------------------------------------------------------------------
void CCamera::fly(float fUnits)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Land: // Land mode camera
		break;

	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		m_oPositionVec += CVector3(0.0f, m_oPositionVec.getY(), 0.0f) * fUnits;
		break;
	}
}

//---------------------------------------------------------------------------
// Name: roll
// Desc: Roll the camera ie rotate around the z-axis
//---------------------------------------------------------------------------
void CCamera::roll(float fAngle)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		m_oViewMatrix = CMath::matrixRotationNormalAxis(m_oLookAtVec, fAngle); // Rotate around lookat vector
		m_oUpVec = CMath::vectorTransformCoordinate(m_oUpVec, m_oViewMatrix); // Transform up vector
		m_oRightVec = CMath::vectorTransformCoordinate(m_oRightVec, m_oViewMatrix); // Transform right vector
		break;
	}
}

//---------------------------------------------------------------------------
// Name: yaw
// Desc: Yaw the camera i.e. rotate around the y-axis
//---------------------------------------------------------------------------
void CCamera::yaw(float fAngle)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Land: // Land mode camera
		m_oViewMatrix = CMath::matrixRotationNormalAxis(m_oUpVec, fAngle); // Rotate around the up vector
		m_oLookAtVec = CMath::vectorTransformCoordinate(m_oLookAtVec, m_oViewMatrix); // Transform lookat vector
		m_oRightVec = CMath::vectorTransformCoordinate(m_oRightVec, m_oViewMatrix); // Transform right vector
		break;

	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		break;
	}
}

//---------------------------------------------------------------------------
// Name: pitch
// Desc: Pitch the camera ie rotate around the x-axis
//---------------------------------------------------------------------------
void CCamera::pitch(float fAngle)
{
	switch(m_oCameraMode)
	{
	case ECameraMode::eCamera_Mode_Land: // Land mode camera
		m_oViewMatrix = CMath::matrixRotationNormalAxis(m_oRightVec, fAngle); // Rotate around the right vector
		m_oLookAtVec = CMath::vectorTransformCoordinate(m_oLookAtVec, m_oViewMatrix); // Transform lookat vector
		m_oUpVec = CMath::vectorTransformCoordinate(m_oUpVec, m_oViewMatrix); // Transform up vector
		break;

	case ECameraMode::eCamera_Mode_Air: // Air mode camera
		break;
	}
}

//---------------------------------------------------------------------------
// Name: shoot
// Desc: Start shooting
//---------------------------------------------------------------------------
void CCamera::shoot()
{
	m_oLookAtVec = CMath::vectorNormalize(m_oLookAtVec); // Normalize the look-at vector

	// Generate an up vector from the right and look-at vector
	m_oUpVec = CMath::vectorCrossProduct(m_oLookAtVec, m_oRightVec); // Calculate an orthogonalized up vector
	m_oUpVec = CMath::vectorNormalize(m_oUpVec); // Normalize the up vector

	// Generate right vector from the look-at and up vector
	m_oRightVec = CMath::vectorCrossProduct(m_oUpVec, m_oLookAtVec); // Calculate an orthogonalized right vector
	m_oRightVec = CMath::vectorNormalize(m_oRightVec); // Normalize right vector

	// Calculate the position of the viewer
	m_fXPosition = -CMath::vectorDotProduct(m_oRightVec, m_oPositionVec); // X-position
	//m_fXPosition = -m_fXPosition; // Negate the x-position
	m_fYPosition = -CMath::vectorDotProduct(m_oUpVec, m_oPositionVec); // Y-position
	//m_fYPosition = -m_fYPosition; // Negate the y-position
	m_fZPosition = -CMath::vectorDotProduct(m_oLookAtVec, m_oPositionVec); // Z-position
	//m_fZPosition = -m_fZPosition; // Negate the z-position

	////////////////////////////////////////////////////////////
	// View transformation matrix layout
	// Column 1: right vector
	// Column 2: up vector
	// Column 3: look-at vector
	// Row 4: position vector
	////////////////////////////////////////////////////////////

	// Construct right vector
	m_oViewMatrix(0, 0) = m_oRightVec.getX(); // _11
	m_oViewMatrix(1, 0) = m_oRightVec.getY(); // _21
	m_oViewMatrix(2, 0) = m_oRightVec.getZ(); // _31

	// Construct up vector
	m_oViewMatrix(0, 1) = m_oUpVec.getX(); // _12
	m_oViewMatrix(1, 1) = m_oUpVec.getY(); // _22
	m_oViewMatrix(2, 1) = m_oUpVec.getZ(); // _32

	// Construct look-at vector
	m_oViewMatrix(0, 2) = m_oLookAtVec.getX(); // _13
	m_oViewMatrix(1, 2) = m_oLookAtVec.getY(); // _23
	m_oViewMatrix(2, 2) = m_oLookAtVec.getZ(); // _33

	// Construct position vector
	m_oViewMatrix(3, 0) = m_fXPosition; // _41
	m_oViewMatrix(3, 1) = m_fYPosition; // _42
	m_oViewMatrix(3, 2) = m_fZPosition; // _43

	m_oViewProjectionMatrix = m_oViewMatrix * m_oProjectionMatrix; // Build view-projection matrix

	//g_pChagesEveryFrameConstBuffer->m_oViewMatrix = m_oViewMatrix;
}

//---------------------------------------------------------------------------
// Name: buildFrustumPlanes
// Desc: Build the frustum planes
//---------------------------------------------------------------------------
void CCamera::buildFrustumPlanes()
{
	// Reference: Intro. to 3D game programming with DirectX 9.0c Frank Luna

	// Extract frustum planes from the view-projection matrix
}

CCamera g_oCamera;
CCamera *g_pCamera = &g_oCamera;