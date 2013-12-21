// Camera.h: Interface of camera
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef CAMERA_H
#define CAMERA_H

//
// Forward declarations
//
enum class ECameraMode;
enum class ECameraOrientation;

class CCubeMap;

//
// End Forward declarations
//

// CCamera class
class CCamera
{
public: // Public methods
	CCamera(); // Default constructor
	CCamera(CVector3 *pEyePosVec, CVector3 *pLookAtVec, CVector3 *pUpVec); // Constructor
	CCamera(CVector3 *pEyePosVec, CVector3 *pLookAtVec); // Constructor
	~CCamera(); // Destructor

	void createProjectionMatrix(ID3D11DeviceContext *pD3DDeviceContext); // Create a projection matrix
	void createProjectionMatrix(CMatrix4x4 &rProjectionMatrix); // Create a projection matrix

	CVector3 getViewVector() const; // Get the view vector
	CMatrix4x4 getViewMatrix() const; // Get the view transformation matrix
	CMatrix4x4 getProjectionMatrix() const; // Get the projection transformation matrix
	CMatrix4x4 getViewProjectionMatrix() const; // Get the view-projection matrix

	// Camera lens
	void setLens(CVector3 *pEyePosVec, CVector3 *pLookAtVec); // Set the lens of the camera
	void setLens(CVector3 *pEyePosVec, CVector3 *pLookAtVec, CVector3 *pUpVec); // 

	void toogleMode(ECameraMode oCameraMode); // Toggle camera mode

	void walk(float fUnits); // Walk
	void strafe(float fUnits); // Strafe
	void fly(float fUnits); // Fly
	void roll(float fAngle); // Roll: rotation around the z-axis
	void yaw(float fAngle); // Yaw: rotation around the y-axis
	void pitch(float fAngle); // Pitch: rotation around the x-axis
	void rotateAboutCenter(float fAngle); // Rotate about the center point
	void shoot(); // Shoot

private: // Private methods
	void buildFrustumPlanes(); // Build the frustum planes

private: // Private attributes
	CVector3 m_oPositionVec, m_oLookAtVec, m_oRightVec, m_oUpVec;

	CMatrix4x4 m_oViewMatrix, m_oProjectionMatrix, m_oViewProjectionMatrix; // View, projection and combined view-projection transformation matrices

	CVector4 m_oFrustumPlanes[6]; // 6 frustum planes

	CCubeMap *m_pSkyBox; // Skybox

	ECameraMode m_oCameraMode; // Camera mode
	ECameraOrientation m_oCameraOrientation; // Camera orientation

	float m_fXPosition, m_fYPosition, m_fZPosition; // Position of the camera
};

extern CCamera *g_pCamera;

// ECameraMode enumeration
enum class ECameraMode
{
	eCamera_Mode_Land, // 
	eCamera_Mode_Air,
};

// ECameraOrientation enumeration
enum class ECameraOrientation
{
	eCamera_Orientation_FirstPerson, // First person type camera
	eCamera_Orientation_ThirdPerson, // Third person type camera
};

#endif CAMERA_H // CAMERA_H