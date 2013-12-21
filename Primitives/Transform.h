// Transform.h: Implementation of transformation components
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef TRANSFORM_H
#define TRANSFORM_H

// CTransform class
class CTransform
{
public:
	CTransform(); // Default constructor
	~CTransform(); // Destructor

	void scale(float fX, float fY, float fZ); // Scale
	void scale(const CVector3 &rScaleVector); // Scale
	void rotate(const CQuaternion &rQuaternion); // Rotate using quaternion
	void translate(float fX, float fY, float fZ); // Translate
	void translate(const CVector3 &rTranslateVector); // Translate

	CVector3 getLocalPosition() const; // Get the local space position
	CVector3 getLocalScale() const; // Get the local scale data
	CQuaternion getLocalRotation() const; // Get the local rotation quaternion
	CQuaternion getWorldRotation() const; // Get the world rotation quaternion
	CVector3 getForward() const; // Get the forward vector
	CVector3 getRight() const; // Get the right vector
	CVector3 getUp() const; // Get the up vector

private:
	CVector3 m_oLocalPosition, m_oWorldPosition; // Positions
	CVector3 m_oLocalScale, m_oWorldScale; // Scale values
	CQuaternion m_oLocalRotation, m_oWorldRotation; // Rotation

	CMatrix4x4 m_oWorldMatrix; // World transformation matrix

	CVector3 m_oForwardVector, m_oRightVector, m_oUpVector; // Vectors corresponding to Euler angles of game object

	CBasePrimitive *m_pParentPrimitive; // Parent primitive of the current primitive
};

#endif // TRANSFORM_H