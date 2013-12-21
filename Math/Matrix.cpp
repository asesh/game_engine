// Matrix.cpp: Implementation of matrices
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"

#include <xnamath.h> // XNA Math

#include "Math.h"
#include "Matrix.h"

//---------------------------------------------------------------------------
// Name: CMatrix4x4
// Desc: Default constructor
//---------------------------------------------------------------------------
CMatrix4x4::CMatrix4x4()
{
	m_oXMMatrix = ::XMMatrixIdentity();
}

//---------------------------------------------------------------------------
// Name: CMatrix4x4
// Desc: Constructor
//---------------------------------------------------------------------------
CMatrix4x4::CMatrix4x4(float f_11, float f_12, float f_13, float f_14,
				float f_21, float f_22, float f_23, float f_24,
				float f_31, float f_32, float f_33, float f_34,
				float f_41, float f_42, float f_43, float f_44)
{
	m_oXMMatrix = ::XMMatrixSet(f_11, f_12, f_13, f_14, f_21, f_22, f_23, f_24, f_31, f_32, f_33, f_34, f_41, f_42, f_43, f_44);
}

//---------------------------------------------------------------------------
// Name: ~CMatrix4x4
// Desc: Destructor
//---------------------------------------------------------------------------
CMatrix4x4::~CMatrix4x4()
{
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Multiply matrices
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::operator*(const CMatrix4x4 &rMatrix)
{
	CMatrix4x4 oMatrix;

	oMatrix.m_oXMMatrix = m_oXMMatrix * rMatrix.m_oXMMatrix;
	
	return oMatrix;
}

//---------------------------------------------------------------------------
// Name: operator+
// Desc: Add matrices
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::operator+(const CMatrix4x4 &rMatrix)
{
	CMatrix4x4 oMatrix;

	//oMatrix.m_oXMMatrix = m_oXMMatrix + rMatrix.m_oXMMatrix;
	
	return oMatrix;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type CMatrix4x4
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::operator=(const CMatrix4x4 &rMatrix)
{
	m_oXMMatrix = rMatrix.m_oXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type CMatrix4x4
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::operator*=(const CMatrix4x4 &rMatrix)
{
	m_oXMMatrix *= rMatrix.m_oXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type XMMATRIX
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::operator=(const XMMATRIX &rXMMatrix)
{
	m_oXMMatrix = rXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Check the equality of matrices
//---------------------------------------------------------------------------
bool CMatrix4x4::operator==(const CMatrix4x4 &rMatrix)
{
	return true;
}

//---------------------------------------------------------------------------
// Name: operator()
// Desc: Index matrix element
//---------------------------------------------------------------------------
float &CMatrix4x4::operator()(UINT uiRow, UINT uiColumn)
{
	return m_oXMMatrix(uiRow, uiColumn);
	//return 0.0f;
}

//---------------------------------------------------------------------------
// Name: getXMMatrix
// Desc: Get the XMMATRIX equivalent of the matrix
//---------------------------------------------------------------------------
XMMATRIX CMatrix4x4::getXMMatrix() const
{
	return m_oXMMatrix;
}

//---------------------------------------------------------------------------
// Name: setIdentity
// Desc: Make identity matrix
//---------------------------------------------------------------------------
void CMatrix4x4::setIdentity()
{
	m_oXMMatrix = ::XMMatrixIdentity();
}

//---------------------------------------------------------------------------
// Name: setInverse
// Desc: Make the inverse of the current matrix
//---------------------------------------------------------------------------
void CMatrix4x4::setInverse()
{
	//XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	m_oXMMatrix = ::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix);
}

//---------------------------------------------------------------------------
// Name: setTranspose
// Desc: Make the transpose of the current matrix
//---------------------------------------------------------------------------
void CMatrix4x4::setTranspose()
{
	//XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	m_oXMMatrix = ::XMMatrixTranspose(m_oXMMatrix);
}

//---------------------------------------------------------------------------
// Name: setInverseTranspose
// Desc: Compute and set the inverse-tranpose of the current matrix
//---------------------------------------------------------------------------
void CMatrix4x4::setInverseTranspose()
{
	//XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	m_oXMMatrix = ::XMMatrixTranspose(::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix)); // Compute inverse transpose of a matrix
}

//---------------------------------------------------------------------------
// Name: getInverse
// Desc: Compute and return the inverse of the current matrix
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::getInverse()
{
	CMatrix4x4 oInverseMatrix;

	//XMVECTOR oXMDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	oInverseMatrix = ::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix); // Compute inverse of a matrix

	return oInverseMatrix; // Return the inverse of matrix
}

//---------------------------------------------------------------------------
// Name: getTranspose
// Desc: Get the transpose of the current matrix
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::getTranspose()
{
	CMatrix4x4 oMatrix;

	oMatrix = ::XMMatrixTranspose(m_oXMMatrix); // Compute transpose of a matrix

	return oMatrix;
}

//---------------------------------------------------------------------------
// Name: getInverseTranspose
// Desc: Compute and return the inverse-tranpose of the current matrix
//---------------------------------------------------------------------------
CMatrix4x4 CMatrix4x4::getInverseTranspose()
{
	CMatrix4x4 oInverseTransposeMatrix;

	//XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	oInverseTransposeMatrix = ::XMMatrixTranspose(::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix)); // Compute inverse transpose of a matrix

	return oInverseTransposeMatrix; // Return the inverse-transpose matrix
}

//---------------------------------------------------------------------------
// Name: getDeterminant
// Desc: Calculate and return the determinant of the matrix
//---------------------------------------------------------------------------
float CMatrix4x4::getDeterminant()
{
	return ::XMVectorGetX(::XMMatrixDeterminant(m_oXMMatrix));
}

//---------------------------------------------------------------------------
// Name: CMatrix3x3
// Desc: Default constructor
//---------------------------------------------------------------------------
CMatrix3x3::CMatrix3x3()
{
	m_oXMMatrix = ::XMMatrixIdentity();
}

//---------------------------------------------------------------------------
// Name: CMatrix3x3
// Desc: Constructor
//---------------------------------------------------------------------------
CMatrix3x3::CMatrix3x3(float f_11, float f_12, float f_13,
	float f_21, float f_22, float f_23,
	float f_31, float f_32, float f_33)
{
	m_oXMMatrix = ::XMMatrixSet(f_11, f_12, f_13, 0.0f, f_21, f_22, f_23, 0.0f, f_31, f_32, f_33, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

//---------------------------------------------------------------------------
// Name: ~CMatrix3x3
// Desc: Destructor
//---------------------------------------------------------------------------
CMatrix3x3::~CMatrix3x3()
{
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Multiply matrices
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::operator*(const CMatrix3x3 &rMatrix)
{
	CMatrix3x3 oMatrix;

	oMatrix.m_oXMMatrix = m_oXMMatrix * rMatrix.m_oXMMatrix;
	
	return oMatrix;
}

//---------------------------------------------------------------------------
// Name: operator+
// Desc: Add matrices
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::operator+(const CMatrix3x3 &rMatrix)
{
	CMatrix3x3 oMatrix;

	//oMatrix.m_oXMMatrix = m_oXMMatrix + rMatrix.m_oXMMatrix;
	
	return oMatrix;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type CMatrix3x3
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::operator=(const CMatrix3x3 &rMatrix)
{
	m_oXMMatrix = rMatrix.m_oXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type CMatrix3x3
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::operator*=(const CMatrix3x3 &rMatrix)
{
	m_oXMMatrix *= rMatrix.m_oXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign matrix of type XMMATRIX
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::operator=(const XMMATRIX &rXMMatrix)
{
	m_oXMMatrix = rXMMatrix;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Check the equality of matrices
//---------------------------------------------------------------------------
bool CMatrix3x3::operator==(const CMatrix3x3 &rMatrix)
{
	return true;
}

//---------------------------------------------------------------------------
// Name: operator()
// Desc: Index matrix element
//---------------------------------------------------------------------------
float &CMatrix3x3::operator()(UINT uiRow, UINT uiColumn)
{
	return m_oXMMatrix(uiRow, uiColumn);
	//return 0.0f;
}

//---------------------------------------------------------------------------
// Name: getXMMatrix
// Desc: Get the XMMATRIX equivalent of the matrix
//---------------------------------------------------------------------------
XMMATRIX CMatrix3x3::getXMMatrix() const
{
	return m_oXMMatrix;
}

//---------------------------------------------------------------------------
// Name: setIdentity
// Desc: Make identity matrix
//---------------------------------------------------------------------------
void CMatrix3x3::setIdentity()
{
	m_oXMMatrix = ::XMMatrixIdentity();
}

//---------------------------------------------------------------------------
// Name: setInverse
// Desc: Make the inverse of the current matrix
//---------------------------------------------------------------------------
void CMatrix3x3::setInverse()
{
	XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	m_oXMMatrix = ::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix);
}

//---------------------------------------------------------------------------
// Name: setInverseTranspose
// Desc: Compute and set the inverse-tranpose of the current matrix
//---------------------------------------------------------------------------
void CMatrix3x3::setInverseTranspose()
{
	XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	m_oXMMatrix = ::XMMatrixTranspose(::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix)); // Compute inverse transpose of the matrix
}

//---------------------------------------------------------------------------
// Name: getInverse
// Desc: Compute and return the inverse of the current matrix
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::getInverse()
{
	CMatrix3x3 oInverseMatrix;

	//XMVECTOR oXMDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	oInverseMatrix = ::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix); // Compute inverse of the matrix

	return oInverseMatrix; // Return the inverse of matrix
}

//---------------------------------------------------------------------------
// Name: getInverseTranspose
// Desc: Compute and return the inverse-tranpose of the current matrix
//---------------------------------------------------------------------------
CMatrix3x3 CMatrix3x3::getInverseTranspose()
{
	CMatrix3x3 oInverseTransposeMatrix;

	XMVECTOR oDeterminantVector = ::XMMatrixDeterminant(m_oXMMatrix); // Computer determinant

	oInverseTransposeMatrix = ::XMMatrixTranspose(::XMMatrixInverse(&::XMMatrixDeterminant(m_oXMMatrix), m_oXMMatrix)); // Compute inverse transpose of the matrix

	return oInverseTransposeMatrix; // Return the inverse-transpose matrix
}

//---------------------------------------------------------------------------
// Name: getDeterminant
// Desc: Calculate and return the determinant of the matrix
//---------------------------------------------------------------------------
float CMatrix3x3::getDeterminant()
{
	return ::XMVectorGetX(::XMMatrixDeterminant(m_oXMMatrix));
}

//---------------------------------------------------------------------------
// Name: CTransformMatrices
// Desc: Default constructor
//---------------------------------------------------------------------------
CTransformMatrices::CTransformMatrices()
{
}

//---------------------------------------------------------------------------
// Name: ~CTransformMatrices
// Desc: Destructor
//---------------------------------------------------------------------------
CTransformMatrices::~CTransformMatrices()
{
}

//---------------------------------------------------------------------------
// Name: translate
// Desc: Translate along the specified coordinates
//--------------------------------------------------------------------------- 
void CTransformMatrices::translate(float fX, float fY, float fZ)
{
	m_oTranslationMatrix = CMath::matrixTranslation(fX, fY, fZ);
}

//---------------------------------------------------------------------------
// Name: translateIdentity
// Desc: Set translation matrix to identity
//---------------------------------------------------------------------------
void CTransformMatrices::translateIdentity()
{
	m_oTranslationMatrix.setIdentity();
}

//---------------------------------------------------------------------------
// Name: rotate
// Desc: Rotate around the specified coordinates
//---------------------------------------------------------------------------
void CTransformMatrices::rotate(float fRotateAroundX, float fRotateAroundY, float fRotationAroundZ)
{
}

//---------------------------------------------------------------------------
// Name: rotateIdentity
// Desc: Set rotation matrix to identity matrix
//---------------------------------------------------------------------------
void CTransformMatrices::rotateIdentity()
{
	m_oRotationMatrix.setIdentity();
}

//---------------------------------------------------------------------------
// Name: scale
// Desc: Scaling along the specified coordinates
//---------------------------------------------------------------------------
void CTransformMatrices::scale(float fX, float fY, float fZ)
{
	m_oScalingMatrix = CMath::matrixScaling(fX, fY, fZ);
}

//---------------------------------------------------------------------------
// Name: scaleIdentity
// Desc: Set scaling matrix to identity
//---------------------------------------------------------------------------
void CTransformMatrices::scaleIdentity()
{
	m_oScalingMatrix.setIdentity();
}

//---------------------------------------------------------------------------
// Name: rotateX
// Desc: Rotate around the x-axis
//---------------------------------------------------------------------------
void CTransformMatrices::rotateX(float fAngle)
{
	m_oRotationMatrix = CMath::matrixRotationAroundX(fAngle);
}

//---------------------------------------------------------------------------
// Name: rotateY
// Desc: Rotate around the y-axis
//---------------------------------------------------------------------------
void CTransformMatrices::rotateY(float fAngle)
{
	m_oRotationMatrix = CMath::matrixRotationAroundY(fAngle);
}

//---------------------------------------------------------------------------
// Name: rotateZ
// Desc: Rotate around the z-axis
//---------------------------------------------------------------------------
void CTransformMatrices::rotateZ(float fAngle)
{
	m_oRotationMatrix = CMath::matrixRotationAroundZ(fAngle);
}

//---------------------------------------------------------------------------
// Name: calculateWorldTransform
// Desc: Combine the matrices to from the world transformation matrix
//---------------------------------------------------------------------------
CMatrix4x4 CTransformMatrices::calculateWorldTransform()
{
	return m_oScalingMatrix * m_oRotationMatrix * m_oTranslationMatrix;
}

//---------------------------------------------------------------------------
// Name: calculateWorldTransform
// Desc: Combine the matrices to from the world transformation matrix
//---------------------------------------------------------------------------
void CTransformMatrices::calculateWorldTransform(CMatrix4x4 &rWorldMatrix)
{
	rWorldMatrix = m_oScalingMatrix * m_oRotationMatrix * m_oTranslationMatrix;
}


CTransformMatrices g_oTransformMatrices;
CTransformMatrices *g_pTransformMatrices = &g_oTransformMatrices;