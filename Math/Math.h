// Math.h : Declaration of game algorithm class, structures and their corresponding data
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#ifndef MATH_H
#define MATH_H

#include "Vector.h" // Vector
#include "Matrix.h" // Matrix
#include "Quaternion.h" // Quaternion
#include "..\Primitives\VertexFormat.h"

// Macros
#define EPSILON(X) (X < 0.001f ? true : false) // Macro which will return TRUE if 'X' is less than 0.001f else FALSE

// Forward declarations
//
struct SRay;
struct SProjMotionData;
class CVector2;
class CVector3;
class CVector4;
class CMatrix4x4;
//
// End Forward declarations

// CMath class
class CMath
{
public:
	CMath(); // Default constructor
	~CMath(); // Destructor

	BOOL isSupported() const; // Will return a boolean value indicating if XNA math is supported by the processor

	float calculateFPS(float fTimeDelta); // Calculate the FPS
	float calculateRotation(float fTimeDelta); // Calculate rotation value

	// Matrix calculations
	//
	static CMatrix4x4 matrixOrthographicLH(float fFrustumWidth, float fFrustumHeight, float fNearPlane, float fFarPlane); // Calculate LH orthogonal projection matrix
	static CMatrix4x4 matrixOrthographicRH(float fFrustumWidth, float fFrustumHeight, float fNearPlane, float fFarPlane); // Calculate LH orthogonal projection matrix
	static CMatrix4x4 matrixPerspectiveFovLH(float fFOVAngleY, float fAspectRatio, float fNearPlane, float fFarPlane); // Calculate LH perspective projection matrix
	static CMatrix4x4 matrixPerspectiveFovRH(float fFOVAngleY, float fAspectRatio, float fNearPlane, float fFarPlane); // Calculate LH perspective projection matrix
	static CMatrix4x4 matrixRotationAxis(CVector3 oAxisVector, float fAngle); // Calculate a matrix that rotates around an arbitrary axis
	static CMatrix4x4 matrixRotationNormalAxis(const CVector3 &rNormalAxisVector, float fAngle); // Calculate a matrix that rotates around an arbitrary normal axis
	static CMatrix4x4 matrixRotationNormalAxis(const CVector4 &rNormalAxisVector, float fAngle); // Calculate a matrix that rotates around an arbitrary normal axis
	static CMatrix4x4 matrixRotationAroundX(float fAngle); // Calculate a matrix that rotates around x-axis
	static CMatrix4x4 matrixRotationAroundY(float fAngle); // Calculate a matrix that rotates around y-axis
	static CMatrix4x4 matrixRotationAroundZ(float fAngle); // Calculate a matrix that rotates around z-axis
	static float matrixDeterminant(CMatrix4x4 &rMatrix); // Calculate the determinant of the specified matrix
	static CMatrix4x4 matrixTranslation(float fX, float fY, float fZ); // Calculate the translation matrix
	static CMatrix4x4 matrixScaling(float fX, float fY, float fZ); // Calculate the scaling matrix

	//
	// Matrix calculations

	// Vector calculations
	//

	// 2D vector
	static CVector2 vectorMultiply(const CVector2 &rVectorA, const CVector2 &rVectorB); // Vector multiplication
	static float vectorDotProduct(const CVector2 &rVectorA, const CVector2 &rVectorB); // Calculate dot product
	static CVector2 vectorNormalize(CVector2 oVector); // Calculate the normalized vector
	static CVector2 vectorCrossProduct(const CVector2 &rVectorA, const CVector2 &rVectorB); // Calculate the cross product of two vectors
	static CVector2 vectorTransformCoordinate(CVector2 oVector, const CMatrix4x4 &rMatrix); // Transform a vector by the given matrix

	// 3D vector
	static CVector3 vectorMultiply(const CVector3 &rVectorA, const CVector3 &rVectorB); // Vector multiplication
	static float vectorDotProduct(const CVector3 &rVectorA, const CVector3 &rVectorB); // Calculate dot product
	static CVector3 vectorNormalize(CVector3 oVector); // Calculate the normalized vector
	static CVector3 vectorCrossProduct(const CVector3 &rVectorA, const CVector3 &rVectorB); // Calculate the cross product of two vectors
	static CVector3 vectorTransformCoordinate(CVector3 oVector, const CMatrix4x4 &rMatrix); // Transform a vector by the given matrix
	static void vectorComputeNormal(const CVector3 &rVertexA, const CVector3 &rVertexB, const CVector3 &rVertexC, CVector3 &rNormalVector); // Compute normal vector
	static void vectorComputeNormal(const CVector3 &rTangentVector, const CVector3 &rBinormalVector, CVector3 &rNormalVector); // Compute normal vector from the specified tangent and binormal
	static void vectorComputeNormalTangentBinormal(const SVertexTexture2D &rVertexA, const SVertexTexture2D &rVertexB, const SVertexTexture2D &rVertexC, CVector3 &rNormalVector, CVector3 &rTangent, CVector3 &rBinormal); // Compute normal, tangent and binormal
	static void vectorComputeTangentBinormal(const SVertexTexture2D &rVertexA, const SVertexTexture2D &rVertexB, const SVertexTexture2D &rVertexC, CVector3 &rTangent, CVector3 &rBinormal); // Compute tangent and binormal

	// 4D vector
	static CVector4 vectorMultiply(const CVector4 &rVectorA, const CVector4 &rVectorB); // Vector multiplication
	static float vectorDotProduct(const CVector4 &rVectorA, const CVector4 &rVectorB); // Calculate dot product
	static CVector4 vectorNormalize(CVector4 oVector); // Calculate the normalized vector
	static CVector4 vectorCrossProduct(const CVector4 &rVectorA, const CVector4 &rVectorB); // Calculate the cross product of two vectors
	static CVector4 vectorTransformCoordinate(CVector4 oVector, const CMatrix4x4 &rMatrix); // Transform a vector by the given matrix
	//
	// Vector calculations

	float getTimeDelta() const; // Get the time difference value
	float getFPS() const; // Get the frames rendered per-second
	std::wstring getFPSData() const; // Get the FPS data
	float getRotation() const; // 
	float getRandomFloat() const; // Get a random floating point value
	CVector2 getRandomVector(CVector2 *pMinVector, CVector2 *pMaxVector); // Get the random vector
	CVector3 getRandomVector(CVector3 *pMinVector, CVector3 *pMaxVector); // Get the random vector
	CVector4 getRandomVector(CVector4 *pMinVector, CVector4 *pMaxVector); // Get the random vector

	// Ray related functions
	//SRay &calculatePickingRay(int nXCoord, int nYCoord); // Calculate the picking ray
	void transformRay(SRay *pRay, CMatrix4x4 *pRayTransformMatrix); // Transform the ray

	// Projection motion algorithms
	//SProjMotionData &calculateProjectionMotion(float fPointOfProjection, float fAngleOfProjection, float fInitialVelocity);

private:
	float m_fFPS, m_fRotation, m_fTimeDelta;

	//SProjMotionData m_oProjMotionData;

	//SRay m_oRay;

	std::wstring m_oFPSDataString;
	WCHAR m_szFPSData[50];
};

extern CMath *g_pMath;

// SRay structure
struct SRay
{
	//XMVECTOR m_oXMOriginVec; // Origin of the ray
	///XMVECTOR m_oXMDirectionVec; // Direction of the ray

	//CVector4 m_oOriginVector; // Origin of the ray
	//CVector3 m_oDirectionVector; // Direction of the ray
};

// Projectile motion output structure
struct SProjMotionData
{
	float fTimeOfFlight; // Time of the flight of the projectile
	float fRange; // Horizontal range or range
	float fMaxHeightReached; // Maximum height reached by the projectile
};

#endif // MATH_H