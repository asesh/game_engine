// Vector.h: Interface of 2D, 3D and 4D vectors
// Copyright (C) 2011-2013 Asesh Shrestha. All rights reserved

#ifndef VECTOR_H
#define VECTOR_H

// CVector4 class
class CVector4
{
public:
	CVector4(); // Default constructor
	CVector4(float fX, float fY, float fZ); // Constructor
	CVector4(float fX, float fY, float fZ, float fW); // Constructor
	~CVector4(); // Destructor

	CVector4 operator++(); // Prefix increment
	CVector4 operator++(int); // Postfix increment
	CVector4 operator--(); // Prefix increment
	CVector4 operator--(int); // Postfix increment
	CVector4 operator+(const CVector4 &rVector); // Add vectors
	CVector4 operator-(const CVector4 &rVector); // Subtract vectors
	CVector4 operator*(const CVector4 &rVector); // Multiply vectors
	CVector4 operator*(float fValue); // Multiply vector and a scalar floating point value
	BOOL operator>(const CVector4 &rVector); // Greater comparison
	BOOL operator<(const CVector4 &rVector); // Lesser comparison
	CVector4 operator=(const CVector4 &rVector); // Assign vector
	CVector4 operator=(const XMVECTOR &rXMVector); // Assign and return vector of type XMVECTOR
	CVector4 operator+=(const CVector4 &rVector); // Increment assignment
	CVector4 operator-=(const CVector4 &rVector); // Decrement assignment
	BOOL operator>=(const CVector4 &rVector); // Greater/equivalent comparison
	BOOL operator<=(const CVector4 &rVector); // Lesser/equivalent comparision
	BOOL operator==(const CVector4 &rVector); // Equality check
	BOOL operator!=(const CVector4 &rVector); // Inequality check
	float operator[](int nIndex) const; // Indexing

	operator XMVECTOR() const; // Cast operator of type XMVECTOR
	operator XMFLOAT4() const; // Cast operator of type XMFLOAT4

	float length() const; // Get the length of the vector
	CVector4 cross(const CVector4 &rVector) const; // Compute the cross product of the vectors
	CVector4 normalize(); // Normalize the current vector

	float getX() const; // Get the x component
	float getY() const; // Get the y component
	float getZ() const; // Get the z component
	float getW() const; // Get the w component
	float getMagnitude() const; // Get the magnitude of the current vector
	XMVECTOR getXMVector() const; // Get the XMVECTOR equivalent of the current vector

	// Set methods
	void setX(float fX); // Set the x component
	void setY(float fY); // Set the y component
	void setZ(float fZ); // Set the z component
	void setW(float fW); // Set the w component

private:
	XMVECTOR m_oXMVector;
	//float m_fX, m_fY, m_fZ, m_fW; // Vector components
};

#define ZeroVector4 CVector4(0.0f, 0.0f, 0.0f, 0.0f) // 4D 0 vector

// CVector3 class
class CVector3
{
public:
	CVector3(); // Default constructor
	CVector3(float fX, float fY, float fZ); // Constructor
	~CVector3(); // Destructor

	CVector3 operator++(); // Prefix increment
	CVector3 operator++(int); // Postfix increment
	CVector3 operator--(); // Prefix increment
	CVector3 operator--(int); // Postfix increment
	CVector3 operator+(const CVector3 &rVector); // Add vectors
	CVector3 operator-(const CVector3 &rVector); // Subtract vectors
	CVector3 operator*(const CVector3 &rVector); // Multiply vectors
	CVector3 operator*(float fValue); // Multiply vector and a scalar floating point value
	BOOL operator>(const CVector3 &rVector); // Greater comparison
	BOOL operator<(const CVector3 &rVector); // Lesser comparison
	CVector3 operator=(const CVector3 &rVector); // Assign vector
	CVector3 operator=(const XMVECTOR &rXMVector); // Assign and return vector of type XMVECTOR
	CVector3 operator+=(const CVector3 &rVector); // Increment assignment
	CVector3 operator-=(const CVector3 &rVector); // Decrement assignment
	BOOL operator>=(const CVector3 &rVector); // Greater/equivalent comparison
	BOOL operator<=(const CVector3 &rVector); // Lesser/equivalent comparision
	BOOL operator==(const CVector3 &rVector); // Equality check
	BOOL operator!=(const CVector3 &rVector); // Inequality check
	float operator[](int nIndex) const; // Indexing

	operator XMVECTOR() const; // Cast operator of type XMVECTOR
	operator XMFLOAT3() const; // Cast operator of type XMFLOAT3

	float length() const; // Get the length of the vector
	CVector3 cross(const CVector3 &rVector) const; // Compute the cross product of the vectors
	CVector3 normalize(); // Normalize the current vector

	// Get methods
	float getX() const; // Get the x component
	float getY() const; // Get the y component
	float getZ() const; // Get the z component
	float getMagnitude() const; // Get the magnitude of the current vector
	XMVECTOR getXMVector() const; // Get the XMVECTOR equivalent of the current vector

	// Set methods
	void setX(float fX); // Set the x component
	void setY(float fY); // Set the y component
	void setZ(float fZ); // Set the z component

private:
	XMVECTOR m_oXMVector;

	//float m_fX, m_fY, m_fZ; // Vector components
};

#define ZeroVector3 CVector3(0.0f, 0.0f, 0.0f) // 3D 0 vector

// CVector2 class
class CVector2
{
public:
	CVector2(); // Default constructor
	CVector2(float fX, float fY); // Constructor
	~CVector2(); // Destructor

	CVector2 operator++(); // Prefix increment
	CVector2 operator++(int); // Postfix increment
	CVector2 operator--(); // Prefix increment
	CVector2 operator--(int); // Postfix increment
	CVector2 operator+(const CVector2 &rVector); // Add vectors
	CVector2 operator-(const CVector2 &rVector); // Subtract vectors
	CVector2 operator*(const CVector2 &rVector); // Multiply vectors
	CVector2 operator*(float fValue); // Multiply vector and a scalar floating point value
	BOOL operator>(const CVector2 &rVector); // Greater comparison
	BOOL operator<(const CVector2 &rVector); // Lesser comparison
	CVector2 operator=(const CVector2 &rVector); // Assign vector
	CVector2 operator=(const XMVECTOR &rXMVector); // Assign and return vector of type XMVECTOR
	CVector2 operator+=(const CVector2 &rVector); // Increment assignment
	CVector2 operator-=(const CVector2 &rVector); // Decrement assignment
	BOOL operator>=(const CVector2 &rVector); // Greater/equivalent comparison
	BOOL operator<=(const CVector2 &rVector); // Lesser/equivalent comparision
	BOOL operator==(const CVector2 &rVector); // Equality check
	BOOL operator!=(const CVector2 &rVector); // Inequality check
	float operator[](int nIndex) const; // Indexing

	operator XMVECTOR() const; // Cast operator of type XMVECTOR
	operator XMFLOAT2() const; // Cast operator of type XMFLOAT2

	float length() const; // Get the length of the vector
	CVector2 cross(const CVector2 &rVector) const; // Compute the cross product of the vectors
	CVector2 normalize(); // Normalize the current vector

	float getX() const; // Get the x component
	float getY() const; // Get the y component
	float getMagnitude() const; // Get the magnitude of the current vector
	XMVECTOR getXMVector() const; // Get the XMVECTOR equivalent of the current vector

	// Set methods
	void setX(float fX); // Set the x component
	void setY(float fY); // Set the y component

private:
	XMVECTOR m_oXMVector;

	//float m_fX, m_fY; // Vector components
};

#define ZeroVector2 CVector2(0.0f, 0.0f) // 2D 0 vector

#endif // VECTOR_H