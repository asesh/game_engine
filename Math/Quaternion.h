// Quaternion.h: Implementation of quaternion
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef QUATERNION_H
#define QUATERNION_H

// CQuaternion class
class CQuaternion
{
public:
	CQuaternion(); // Default constructor
	CQuaternion(float fS, float fX, float fY, float fZ); // 
	~CQuaternion(); // Destructor

	// Operator over loading
	CQuaternion operator+(const CQuaternion &rQuaternion); // Add quaternions
	CQuaternion operator*(const CQuaternion &rQuaternion); // Multiply quaternions
	CQuaternion operator++(); // Increment the value of quaternions
	CQuaternion operator--(); // Decrement the vlaue of quaternions
	CQuaternion operator=(CQuaternion oQuaternion); // Assign quaternion
	BOOL operator==(const CQuaternion &rQuaternion); // Test for the equality of two quaternions
	BOOL operator!=(const CQuaternion &rQuaternion); // Test for the inequality of two quaternions

	// Typecast operators
	operator XMVECTOR() const; // Typecast XMVECTOR

	float length() const; // Return length of quaternion

	float getS() const; // Get the s component
	float getX() const; // Get the x component
	float getY() const; // Get the y component
	float getZ() const; // Get the z component

private:
	XMVECTOR m_oXMQuaternion;
};

#endif // QUATERNION_H