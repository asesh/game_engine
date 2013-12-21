// Math.cpp : Implementaton of CMath class for mathematical calculation
// Copyright (C) 2007-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "Math.h"

//------------------------------------------------------------------
// Name: CMath
// Desc: Default constructor
//------------------------------------------------------------------
CMath::CMath()
{
	m_fRotation = 0.0f;

	// Seed the pseudo-random number generator
	::srand(::timeGetTime());
}

//------------------------------------------------------------------
// Name: ~CMath
// Desc: Destructor
//------------------------------------------------------------------
CMath::~CMath()
{
}

//------------------------------------------------------------------
// Name: calculateFPS
// Desc: Calculate the frames rendered per-second
//------------------------------------------------------------------
float CMath::calculateFPS(float fTimeDelta)
{
	static float fFrameCount, fTimeElapsed;

	fFrameCount++; // Increment the frame counter
	fTimeElapsed += m_fTimeDelta = fTimeDelta; // Add the delta time to the elapsed time

	// Calculate FPS
	if(fTimeElapsed >= 1.0f) // More than or 1 second has elapsed
	{
		m_fFPS = fFrameCount / fTimeElapsed; // Set FPS
		fTimeElapsed = fFrameCount = 0.0f;
	}

	// Format the FPS data to a string
	::StringCbPrintf(m_szFPSData, ARRAY_SIZE(m_szFPSData, WCHAR), L"FPS: %.02f", m_fFPS);
	m_oFPSDataString = m_szFPSData;

	return m_fFPS; // Return the number of frames rendered per-second
}

//------------------------------------------------------------------
// Name: calculateFPS
// Desc: Calculate the frames rendered per-second
//------------------------------------------------------------------
float CMath::calculateRotation(float fTimeDelta)
{
	m_fRotation += fTimeDelta;

	// Limit the rotation value to full 360 degree
	if(m_fRotation >= 6.28f) // The rotation value is greater than or equal to 360 degree
		m_fRotation = 0.0f; // Reset the rotation value

	return m_fRotation;
}

//------------------------------------------------------------------
// Name: matrixOrthographicLH
// Desc: Calculate left-handed orthographic projection matrix
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixOrthographicLH(float fFrustumWidth, float fFrustumHeight, float fNearPlane, float fFarPlane)
{
	CMatrix4x4 oOrthographicProjectionMatrix;

	oOrthographicProjectionMatrix = ::XMMatrixOrthographicLH(fFrustumWidth, fFrustumHeight, fNearPlane, fFarPlane);

	return oOrthographicProjectionMatrix;
}

//------------------------------------------------------------------
// Name: matrixOrthographicLH
// Desc: Calculate left-handed orthographic projection matrix
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixOrthographicRH(float fFrustumWidth, float fFrustumHeight, float fNearPlane, float fFarPlane)
{
	CMatrix4x4 oOrthographicProjectionMatrix;

	oOrthographicProjectionMatrix = ::XMMatrixOrthographicRH(fFrustumWidth, fFrustumHeight, fNearPlane, fFarPlane);

	return oOrthographicProjectionMatrix;
}

//------------------------------------------------------------------
// Name: matrixPerspectiveFovLH
// Desc: Calculate left-handed perspective projection matrix
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixPerspectiveFovLH(float fFOVAngleY, float fAspectRatio, float fNearPlane, float fFarPlane)
{
	CMatrix4x4 oPerspectiveProjectionMatrix;
	
	oPerspectiveProjectionMatrix = ::XMMatrixPerspectiveFovLH(fFOVAngleY, // FOV
		fAspectRatio, // Aspect ratio
		fNearPlane, // Distance to near clipping plane
		fFarPlane); // Distance to far clipping plane

	return oPerspectiveProjectionMatrix;
}

//------------------------------------------------------------------
// Name: matrixPerspectiveFovLH
// Desc: Calculate left-handed perspective projection matrix
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixPerspectiveFovRH(float fFOVAngleY, float fAspectRatio, float fNearPlane, float fFarPlane)
{
	CMatrix4x4 oPerspectiveProjectionMatrix;
	
	oPerspectiveProjectionMatrix = ::XMMatrixPerspectiveFovRH(fFOVAngleY, // FOV
		fAspectRatio, // Aspect ratio
		fNearPlane, // Distance to near clipping plane
		fFarPlane); // Distance to far clipping plane

	return oPerspectiveProjectionMatrix;
}

//------------------------------------------------------------------
// Name: matrixRotationAxis
// Desc: Calculate a matrix that rotates around an arbitrary axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationAxis(CVector3 oAxisVector, float fAngle)
{
	CMatrix4x4 oRotationAxis;
	
	oRotationAxis = ::XMMatrixRotationAxis(::XMVectorSet(oAxisVector.getX(), oAxisVector.getY(), oAxisVector.getZ(), 1.0f), fAngle);

	return oRotationAxis;
}

//------------------------------------------------------------------
// Name: matrixRotationNormalAxis
// Desc: Calculate a matrix that rotates around an arbitrary 
//		 arbitrary axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationNormalAxis(const CVector3 &rNormalAxisVector, float fAngle)
{
	CMatrix4x4 oRotationAxis;
	
	oRotationAxis = ::XMMatrixRotationNormal(::XMVectorSet(rNormalAxisVector.getX(), rNormalAxisVector.getY(), rNormalAxisVector.getZ(), 1.0f), fAngle);

	return oRotationAxis;
}

//------------------------------------------------------------------
// Name: matrixRotationNormalAxis
// Desc: Calculate a matrix that rotates around an arbitrary 
//		 arbitrary axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationNormalAxis(const CVector4 &rNormalAxisVector, float fAngle)
{
	CMatrix4x4 oRotationAxis;
	
	oRotationAxis = ::XMMatrixRotationNormal(::XMVectorSet(rNormalAxisVector.getX(), rNormalAxisVector.getY(), rNormalAxisVector.getZ(), 1.0f), fAngle);

	return oRotationAxis;
}

//------------------------------------------------------------------
// Name: matrixRotationAroundX
// Desc: Calculate the rotation around x-axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationAroundX(float fAngle)
{
	CMatrix4x4 oMatrix;
	
	oMatrix = ::XMMatrixRotationX(fAngle);

	return oMatrix;
}

//------------------------------------------------------------------
// Name: matrixRotationAroundY
// Desc: Calculate the rotation around y-axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationAroundY(float fAngle)
{
	CMatrix4x4 oMatrix;
	
	oMatrix = ::XMMatrixRotationY(fAngle);

	return oMatrix;
}

//------------------------------------------------------------------
// Name: matrixRotationAroundZ
// Desc: Calculate the rotation around z-axis
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixRotationAroundZ(float fAngle)
{
	CMatrix4x4 oMatrix;
	
	oMatrix = ::XMMatrixRotationZ(fAngle);

	return oMatrix;
}

//------------------------------------------------------------------
// Name: matrixDeterminant
// Desc: Calculate the determinant of the specified matrix
//------------------------------------------------------------------
float CMath::matrixDeterminant(CMatrix4x4 &rMatrix)
{
	return rMatrix.getDeterminant();
}

//------------------------------------------------------------------
// Name: matrixTranslation
// Desc: Translate the matrix with the specified values
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixTranslation(float fX, float fY, float fZ)
{
	CMatrix4x4 oMatrix;

	oMatrix = ::XMMatrixTranslation(fX, fY, fZ);

	return oMatrix;
}

//------------------------------------------------------------------
// Name: matrixScaling
// Desc: Scale the matrix with the specified values
//------------------------------------------------------------------
CMatrix4x4 CMath::matrixScaling(float fX, float fY, float fZ)
{
	CMatrix4x4 oMatrix;

	oMatrix = ::XMMatrixScaling(fX, fY, fZ);

	return oMatrix;
}

//------------------------------------------------------------------
// Name: vectorMultiply
// Desc: Calculate vector multiplication
//------------------------------------------------------------------
CVector2 CMath::vectorMultiply(const CVector2 &rVectorA, const CVector2 &rVectorB)
{
	CVector2 oVector;

	oVector = ::XMVectorMultiply(rVectorA.getXMVector(), rVectorB.getXMVector());

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorDotProduct
// Desc: Compute the dot product of two vectors
//------------------------------------------------------------------
float CMath::vectorDotProduct(const CVector2 &rVectorA, const CVector2 &rVectorB)
{
	return ::XMVectorGetX(::XMVector3Dot(rVectorA.getXMVector(), rVectorB.getXMVector()));
}

//------------------------------------------------------------------
// Name: vectorNormalize
// Desc: Normalize the specified vector
//------------------------------------------------------------------
CVector2 CMath::vectorNormalize(CVector2 oVector)
{
	CVector2 oNormalizedVector;

	oNormalizedVector = ::XMVector3Normalize(oVector.getXMVector());

	return oNormalizedVector;
}

//------------------------------------------------------------------
// Name: vectorCrossProduct
// Desc: Compute the cross product of two vector
//------------------------------------------------------------------
CVector2 CMath::vectorCrossProduct(const CVector2 &rVectorA, const CVector2 &rVectorB)
{
	CVector2 oVector;

	oVector = ::XMVector3Cross(rVectorA.getXMVector(), rVectorB.getXMVector());

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorCrossProduct
// Desc: Compute the cross product of two vector
//------------------------------------------------------------------
CVector2 CMath::vectorTransformCoordinate(CVector2 oVector, const CMatrix4x4 &rMatrix)
{
	return oVector = ::XMVector3TransformCoord(oVector.getXMVector(), rMatrix.getXMMatrix());
}

//------------------------------------------------------------------
// Name: vectorMultiply
// Desc: Calculate vector multiplication
//------------------------------------------------------------------
CVector3 CMath::vectorMultiply(const CVector3 &rVectorA, const CVector3 &rVectorB)
{
	CVector3 oVector;

	oVector = ::XMVectorMultiply(rVectorA.getXMVector(), rVectorB.getXMVector());

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorDotProduct
// Desc: Compute the dot product of two vectors
//------------------------------------------------------------------
float CMath::vectorDotProduct(const CVector3 &rVectorA, const CVector3 &rVectorB)
{
	return ::XMVectorGetX(::XMVector3Dot(rVectorA.getXMVector(), rVectorB.getXMVector()));
}

//------------------------------------------------------------------
// Name: vectorNormalize
// Desc: Normalize the specified vector
//------------------------------------------------------------------
CVector3 CMath::vectorNormalize(CVector3 oVector)
{
	CVector3 oNormalizedVector;

	oNormalizedVector = ::XMVector3Normalize(oVector.getXMVector());

	return oNormalizedVector;
}

//------------------------------------------------------------------
// Name: vectorCrossProduct
// Desc: Compute the cross product of two vector
//------------------------------------------------------------------
CVector3 CMath::vectorCrossProduct(const CVector3 &rVectorA, const CVector3 &rVectorB)
{
	CVector3 oVector;

	oVector = ::XMVector3Cross(rVectorA.getXMVector(), rVectorB.getXMVector());

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorTransformCoordinate
// Desc: Transform a vector by the given matrix
//------------------------------------------------------------------
CVector3 CMath::vectorTransformCoordinate(CVector3 oVector, const CMatrix4x4 &rMatrix)
{
	return oVector = ::XMVector3TransformCoord(oVector.getXMVector(), rMatrix.getXMMatrix());
}

//------------------------------------------------------------------
// Name: vectorComputeNormal
// Desc: Compute normal vector from the given vertices
//------------------------------------------------------------------
void CMath::vectorComputeNormal(const CVector3 &rVertexA, const CVector3 &rVertexB, const CVector3 &rVertexC, CVector3 &rNormalVector)
{
	CVector3 oVector1, oVector2;

	// Calculate the two vectors for computing normal
	//oVector1 = CVector3(rVertexC.getX() - rVertexA.getX(), rVertexC.getY() - rVertexA.getY(), rVertexC.getZ() - rVertexA.getZ());
	oVector1 = rVertexC - rVertexA;

	//oVector2 = CVector3(rVertexB.getX() - rVertexA.getX(), rVertexB.getY() - rVertexA.getY(), rVertexB.getZ() - rVertexA.getZ());
	oVector2 = rVertexB - rVertexA;

	rNormalVector = CMath::vectorCrossProduct(oVector1, oVector2); // Compute the normal vector

	//return true;
}

//------------------------------------------------------------------
// Name: vectorComputeNormal
// Desc: Compute normal vector from the specified tangent and binormal
//------------------------------------------------------------------
void CMath::vectorComputeNormal(const CVector3 &rTangentVector, const CVector3 &rBinormalVector, CVector3 &rNormalVector)
{
	rNormalVector = CMath::vectorCrossProduct(rBinormalVector, rTangentVector); // Compute the normal vector for LH coordinate syste,

	//return true;
}

//------------------------------------------------------------------
// Name: vectorComputeNormalTangentBinormal
// Desc: Compute normal, tangent and binormal from the given vertices
//------------------------------------------------------------------
void CMath::vectorComputeNormalTangentBinormal(const SVertexTexture2D &rVertexA, const SVertexTexture2D &rVertexB, const SVertexTexture2D &rVertexC, CVector3 &rNormalVector, CVector3 &rTangent, CVector3 &rBinormal)
{
	// Algorithm taken from rastertek via bump mapping tutorial

	CVector3 oVector1, oVector2;
	CVector2 oTextureVectorU, oTextureVectorV;

	// Calculate the two vectors for computing normal
	oVector1 = CVector3(rVertexC.m_oVertex.x - rVertexA.m_oVertex.x, rVertexC.m_oVertex.y - rVertexA.m_oVertex.y, rVertexC.m_oVertex.z - rVertexA.m_oVertex.z);

	oVector2 = CVector3(rVertexB.m_oVertex.x - rVertexA.m_oVertex.x, rVertexB.m_oVertex.y - rVertexA.m_oVertex.y, rVertexB.m_oVertex.z - rVertexA.m_oVertex.z);

	rNormalVector = CMath::vectorCrossProduct(oVector1, oVector2); // Compute the normal vector
	//rNormalVector.normalize(); // Normalize the normal vector

	// Calculate the texture space vectors
	oTextureVectorU = CVector2(rVertexB.m_oUV.x - rVertexA.m_oUV.x, rVertexC.m_oUV.x - rVertexA.m_oUV.x);
	oTextureVectorV = CVector2(rVertexB.m_oUV.y - rVertexA.m_oUV.y, rVertexC.m_oUV.x - rVertexA.m_oUV.y);

	// Calculate the denominator of the tangent/binormal equation
	float fDenominator = 1.0f / (oTextureVectorU[0] * oTextureVectorV[1] - oTextureVectorU[1] * oTextureVectorV[0]);

	// Calculate tangent
	rTangent = CVector3((oTextureVectorV[1] * oVector1[0] - oTextureVectorV[0] * oVector2[0]) * fDenominator, // X
		(oTextureVectorV[1] * oVector1[1] - oTextureVectorV[0] * oVector2[1]) * fDenominator, // Y
		(oTextureVectorV[1] * oVector1[2] - oTextureVectorV[0] * oVector2[2]) * fDenominator); // Z
	//rTangent.normalize(); // Normalize the calculated tangent

	// Calculate binormal
	rBinormal = CVector3((oTextureVectorU[0] * oVector2[0] - oTextureVectorU[0] * oVector1[0]) * fDenominator, // X
		(oTextureVectorU[0] * oVector2[1] - oTextureVectorU[0] * oVector1[1]) * fDenominator, // Y
		(oTextureVectorU[0] * oVector2[2] - oTextureVectorU[0] * oVector1[2]) * fDenominator); // Z
	//rBinormal.normalize(); // Normalize the calculated binormal

	//return true;
}

//------------------------------------------------------------------
// Name: vectorComputeTangentBinormal
// Desc: Compute tangent and binormal from the given vertices
//------------------------------------------------------------------
void CMath::vectorComputeTangentBinormal(const SVertexTexture2D &rVertexA, const SVertexTexture2D &rVertexB, const SVertexTexture2D &rVertexC, CVector3 &rTangent, CVector3 &rBinormal)
{
	// Algorithm taken from rastertek via bump mapping tutorial

	CVector3 oVector1, oVector2;
	CVector2 oTextureVectorU, oTextureVectorV;

	// Calculate the two vectors for this face
	oVector1 = CVector3(rVertexC.m_oVertex.x - rVertexA.m_oVertex.x, rVertexC.m_oVertex.y - rVertexA.m_oVertex.y, rVertexC.m_oVertex.z - rVertexA.m_oVertex.z);

	oVector2 = CVector3(rVertexB.m_oVertex.x - rVertexA.m_oVertex.x, rVertexB.m_oVertex.y - rVertexA.m_oVertex.y, rVertexB.m_oVertex.z - rVertexA.m_oVertex.z);

	// Calculate the texture space vectors
	oTextureVectorU = CVector2(rVertexB.m_oUV.x - rVertexA.m_oUV.x, rVertexC.m_oUV.x - rVertexA.m_oUV.x); // U
	oTextureVectorV = CVector2(rVertexB.m_oUV.y - rVertexA.m_oUV.y, rVertexC.m_oUV.x - rVertexA.m_oUV.y); // V

	// Calculate the denominator of the tangent/binormal equation
	float fDenominator = 1.0f / (oTextureVectorU[0] * oTextureVectorV[1] - oTextureVectorU[1] * oTextureVectorV[0]);

	// Calculate tangent
	rTangent = CVector3((oTextureVectorV[1] * oVector1[0]) - (oTextureVectorV[0] * oVector2[0]) * fDenominator, // X
		(oTextureVectorV[1] * oVector1[1]) - (oTextureVectorV[0] * oVector2[1]) * fDenominator, // Y
		(oTextureVectorV[1] * oVector1[2]) - (oTextureVectorV[0] * oVector2[2]) * fDenominator); // Z
	rTangent.normalize(); // Normalize the calculated tangent
	//float fTangentMagnitude = rTangent.length(); // Tangent magnitude

	// Calculate binormal
	rBinormal = CVector3((oTextureVectorU[0] * oVector2[0]) - (oTextureVectorU[1] * oVector1[0]) * fDenominator, // X
		(oTextureVectorU[0] * oVector2[1]) - (oTextureVectorU[1] * oVector1[1]) * fDenominator, // Y
		(oTextureVectorU[0] * oVector2[2]) - (oTextureVectorU[1] * oVector1[2]) * fDenominator); // Z
	rBinormal.normalize(); // Normalize the calculated binormal
	///float fBinormalMagnitude = rBinormal.length(); // Binormal magnitude

	//return true;
}

//------------------------------------------------------------------
// Name: vectorMultiply
// Desc: Calculate vector multiplication
//------------------------------------------------------------------
CVector4 CMath::vectorMultiply(const CVector4 &rVectorA, const CVector4 &rVectorB)
{
	CVector4 oVector;

	oVector = ::XMVectorMultiply(rVectorA, rVectorB);

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorDotProduct
// Desc: Compute the dot product of two vectors
//------------------------------------------------------------------
float CMath::vectorDotProduct(const CVector4 &rVectorA, const CVector4 &rVectorB)
{
	return ::XMVectorGetX(::XMVector3Dot(rVectorA.getXMVector(), rVectorB.getXMVector()));
}

//------------------------------------------------------------------
// Name: vectorNormalize
// Desc: Normalize the specified vector
//------------------------------------------------------------------
CVector4 CMath::vectorNormalize(CVector4 oVector)
{
	CVector4 oNormalizedVector;

	oNormalizedVector = ::XMVector3Normalize(oVector.getXMVector());

	return oNormalizedVector;
}

//------------------------------------------------------------------
// Name: vectorCrossProduct
// Desc: Compute the cross product of two vector
//------------------------------------------------------------------
CVector4 CMath::vectorCrossProduct(const CVector4 &rVectorA, const CVector4 &rVectorB)
{
	CVector4 oVector;

	oVector = ::XMVector3Cross(rVectorA.getXMVector(), rVectorB.getXMVector());

	return oVector;
}

//------------------------------------------------------------------
// Name: vectorTransformCoordinate
// Desc: Compute a vector by the given matrix
//------------------------------------------------------------------
CVector4 CMath::vectorTransformCoordinate(CVector4 oVector, const CMatrix4x4 &rMatrix)
{
	return oVector = ::XMVector3TransformCoord(oVector.getXMVector(), rMatrix.getXMMatrix());
}

//------------------------------------------------------------------
// Name: getTimeDelta
// Desc: Get the time difference
//------------------------------------------------------------------
float CMath::getTimeDelta() const
{
	return m_fTimeDelta;
}

//------------------------------------------------------------------
// Name: getFPS
// Desc: Get the number of frames rendered per-second
//------------------------------------------------------------------
float CMath::getFPS() const
{
	return m_fFPS;
}

//------------------------------------------------------------------
// Name: getFPSData
// Desc: Get the number of frames rendered per-second
//------------------------------------------------------------------
std::wstring CMath::getFPSData() const
{
	return m_oFPSDataString;
}

//------------------------------------------------------------------
// Name: getRotation
// Desc: Get the rotation value in radians
//------------------------------------------------------------------
float CMath::getRotation() const
{
	return m_fRotation;
}

//------------------------------------------------------------------
// Name: getRandomVector
// Desc: Generate the random vector and return the result
//------------------------------------------------------------------
CVector2 CMath::getRandomVector(CVector2 *pMinVector, CVector2 *pMaxVector)
{
	float fX, fY, fFraction;
	CVector2 oRandomVec; // Will hold the random values

	// Assign the random values to the random vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fX = (static_cast<float>(pMinVector->getX()) + rand() % static_cast<int>(pMaxVector->getX()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fY = (static_cast<float>(pMinVector->getY()) + rand() % static_cast<int>(pMaxVector->getY()) + fFraction); // Generate integral part in the range of min and max vector
	oRandomVec = CVector2(fX, fY);

	return oRandomVec; // Return the vector holding random values
}

//------------------------------------------------------------------
// Name: getRandomVector
// Desc: Generate the random vector and return the result
//------------------------------------------------------------------
CVector3 CMath::getRandomVector(CVector3 *pMinVector, CVector3 *pMaxVector)
{
	float fX, fY, fZ, fFraction;
	CVector3 oRandomVec; // Will hold the random values

	// Assign the random values to the random vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fX = (static_cast<float>(pMinVector->getX()) + rand() % static_cast<int>(pMaxVector->getX()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fY = (static_cast<float>(pMinVector->getY()) + rand() % static_cast<int>(pMaxVector->getY()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fZ = (static_cast<float>(pMinVector->getZ()) + rand() % static_cast<int>(pMaxVector->getZ()) + fFraction); // Generate integral part in the range of min and max vector
	oRandomVec = CVector3(fX, fY, fZ);

	return oRandomVec; // Return the vector holding random values
}

//------------------------------------------------------------------
// Name: getRandomVector
// Desc: Generate the random vector and return the result
//------------------------------------------------------------------
CVector4 CMath::getRandomVector(CVector4 *pMinVector, CVector4 *pMaxVector)
{
	float fX, fY, fZ, fW, fFraction;
	CVector4 oRandomVec; // Will hold the random values

	// Assign the random values to the random vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fX = (static_cast<float>(pMinVector->getX()) + rand() % static_cast<int>(pMaxVector->getX()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fY = (static_cast<float>(pMinVector->getY()) + rand() % static_cast<int>(pMaxVector->getY()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fZ = (static_cast<float>(pMinVector->getZ()) + rand() % static_cast<int>(pMaxVector->getZ()) + fFraction); // Generate integral part in the range of min and max vector
	fFraction = static_cast<float>(0 + ::rand() % 999) / 1000.0f; // Generate fractional part in the range 0-999
	fW = (static_cast<float>(pMinVector->getW()) + rand() % static_cast<int>(pMaxVector->getW()) + fFraction); // Generate integral part in the range of min and max vector
	oRandomVec = CVector4(fX, fY, fZ, fW);

	return oRandomVec; // Return the vector holding random values
}

//------------------------------------------------------------------
// Name: calculatePickingRay
// Desc: Calculate the picking ray
//------------------------------------------------------------------
//SRay &CMath::calculatePickingRay(int nXCoord, int nYCoord)
//{
//	return m_oRay;
//}

//------------------------------------------------------------------
// Name: transformRay
// Desc: Transform the ray
//------------------------------------------------------------------
void CMath::transformRay(SRay *pRay, CMatrix4x4 *pRayTransformMatrix)
{
}

//------------------------------------------------------------------
// Name: calculateProjectionMotion
// Desc: Calculate the projection motion
//------------------------------------------------------------------
//SProjMotionData &CMath::calculateProjectionMotion(float fPointOfProjection,
//												  float fAngleOfProjection,
//												  float fInitialVelocity)
//{
//	///////////////////////////////////////////////////////////////////////////
//	// Formulae and visual representation of the projectile motion
//	// |
//	// |        A
//	// |	   /\
//	// |	  /  \
//	// |     /    \
//	// |    /	   \
//	// |   /	    \
//	// |  /			 \
//	// | /			  \
//	// |/)Theta		   \
//	// |________________________________
//	// O				B
//	// Here, O = point of projection
//	// Theta = angle of projection
//	// OB = Horizontal range the projection travels to
//	//
//	// Formulae:
//	// Time of flight (T): 2u * sin theta / g
//	// Horizontal range: u^2 * sin 2 theta / g
//	// Maximum height (H): u^2 * sin^2 theta / 2*g
//	///////////////////////////////////////////////////////////////////////////
//
//	// Calculate the time of flight
//	m_oProjMotionData.fTimeOfFlight = (2 * fInitialVelocity * ::sinf(fAngleOfProjection)) / ACCEL_GRAVITY;
//
//	// Calculate the horizontal range the projection travels to
//	m_oProjMotionData.fRange = (::powf(fInitialVelocity, 2) * ::sinf(2 * fAngleOfProjection)) / ACCEL_GRAVITY;
//
//	// Calculate the maximum height the projection will reach
//
//	return m_oProjMotionData;
//}

CMath g_oMath;
CMath *g_pMath = &g_oMath;