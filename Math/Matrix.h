// Matrix.h: Interface of matrices
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef MATRIX_H
#define MATRIX_H

// CMatrix4x4 class
class CMatrix4x4
{
public:
	CMatrix4x4(); // Default constructor
	CMatrix4x4(float f_11, float f_12, float f_13, float f_14,
			float f_21, float f_22, float f_23, float f_24,
			float f_31, float f_32, float f_33, float f_34,
			float f_41, float f_42, float f_43, float f_44);
	~CMatrix4x4(); // Destructor

	CMatrix4x4 operator*(const CMatrix4x4 &rMatrix); // Multiply matrices
	CMatrix4x4 operator+(const CMatrix4x4 &rMatrix); // Add matrices
	CMatrix4x4 operator=(const CMatrix4x4 &rMatrix); // Assign matrix
	CMatrix4x4 operator=(const XMMATRIX &rMatrix); // Assign matrix of type XMMATRIX
	//XMMATRIX operator=(const CMatrix4x4 &rMatrix); // Assign matrix of type CMatrix4x4
	CMatrix4x4 operator*=(const CMatrix4x4 &rMatrix); // Multiplicative assignment
	bool operator==(const CMatrix4x4 &rMatrix); // Check the equality of matrices
	float &operator()(UINT uiRow, UINT uiColumn); // Index matrix element

	XMMATRIX getXMMatrix() const; // Get XMMATRIX equivalent

	void setIdentity(); // Make identity matrix
	void setInverse(); // Make inverse matrix
	void setTranspose(); // Make tranpose matrix
	void setInverseTranspose(); // Make inverse tranpose matrix

	// Get methods
	CMatrix4x4 getInverse(); // Get the inverse of the current matrix
	CMatrix4x4 getTranspose(); // Get the transpose of the current matrix
	CMatrix4x4 getInverseTranspose(); // Get the inverse transpose of the current matrix
	float getDeterminant(); // Get the determinant

private:
	XMMATRIX m_oXMMatrix;
};

// CMatrix3x3 class
class CMatrix3x3
{
public:
	CMatrix3x3(); // Default constructor
	CMatrix3x3(float f_11, float f_12, float f_13,
			float f_21, float f_22, float f_23,
			float f_31, float f_32, float f_33);
	~CMatrix3x3(); // Destructor

	CMatrix3x3 operator*(const CMatrix3x3 &rMatrix); // Multiply matrices
	CMatrix3x3 operator+(const CMatrix3x3 &rMatrix); // Add matrices
	CMatrix3x3 operator=(const CMatrix3x3 &rMatrix); // Assign matrix
	CMatrix3x3 operator=(const XMMATRIX &rMatrix); // Assign matrix of type XMMATRIX
	//XMMATRIX operator=(const CMatrix3x3 &rMatrix); // Assign matrix of type CMatrix3x3
	CMatrix3x3 operator*=(const CMatrix3x3 &rMatrix); // Multiplicative assignment
	bool operator==(const CMatrix3x3 &rMatrix); // Check the equality of matrices
	float &operator()(UINT uiRow, UINT uiColumn); // Index matrix element

	XMMATRIX getXMMatrix() const; // Get XMMATRIX equivalent

	void setIdentity(); // Make identity matrix
	void setInverse(); // Make inverse matrix
	void setInverseTranspose(); // Make inverse tranpose matrix

	// Get methods
	CMatrix3x3 getInverse(); // Calculate inverse of the current matrix
	CMatrix3x3 getInverseTranspose(); // Compute inverse transpose of the current matrix
	float getDeterminant(); // Calculate determinant

private:
	XMMATRIX m_oXMMatrix;
};

// CTransformMatrices class
class CTransformMatrices
{
public:
	CTransformMatrices(); // Default constructor
	~CTransformMatrices(); // Destructor

	void translate(float fX, float fY, float fZ);
	void translateIdentity();

	void rotate(float fRotateAroundX, float fRotateAroundY, float fRotationAroundZ);
	void rotateIdentity();

	void scale(float fX, float fY, float fZ);
	void scaleIdentity();

	void rotateX(float fAngle);
	void rotateY(float fAngle);
	void rotateZ(float fAngle);

	CMatrix4x4 calculateWorldTransform(); // Calculate world transformation matrix
	void calculateWorldTransform(CMatrix4x4 &rWorldMatrix); // Calculate world transformation matrix

private:
	CMatrix4x4 m_oRotationMatrix, m_oTranslationMatrix, m_oScalingMatrix;
};
extern CTransformMatrices *g_pTransformMatrices;

#endif // MATRIX_H