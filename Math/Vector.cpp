// Vector.cpp: Implementation of 2D, 3D and 4D vectors
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "..\Common\StdAfx.h"

#include <xnamath.h> // XNA Math

#include "Vector.h"

//---------------------------------------------------------------------------
// Name: CVector4
// Desc: Default constructor
//---------------------------------------------------------------------------
CVector4::CVector4()
{
	//m_fX = m_fY = m_fZ = m_fW = 0.0f;
	m_oXMVector = ::XMVectorZero();
}

//---------------------------------------------------------------------------
// Name: CVector4
// Desc: Constructor with x, y and z components
//---------------------------------------------------------------------------
CVector4::CVector4(float fX, float fY, float fZ)
{
	m_oXMVector = ::XMVectorSet(fX, fY, fZ, 1.0f);
	//m_fX = fX; m_fY = fY; m_fZ = fZ; m_fW = 1.0f;
}

//---------------------------------------------------------------------------
// Name: CVector4
// Desc: Constructor with x, y, z and w components
//---------------------------------------------------------------------------
CVector4::CVector4(float fX, float fY, float fZ, float fW)
{
	m_oXMVector = ::XMVectorSet(fX, fY, fZ, fW);
	//m_fX = fX; m_fY = fY; m_fZ = fZ; m_fW = fW;
}

//---------------------------------------------------------------------------
// Name: ~CVector4
// Desc: Destructor
//---------------------------------------------------------------------------
CVector4::~CVector4()
{
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Pre increment the values of vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator++()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f, ::XMVectorGetZ(m_oXMVector) + 1.0f, 1.0f);

	//m_fX++;	m_fY++;	m_fZ++;	m_fW++;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Post increment the values of vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator++(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f, ::XMVectorGetZ(m_oXMVector) + 1.0f, 1.0f);

	//++m_fX;	++m_fY;	++m_fZ;	++m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Pre decrement the values of vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator--()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f, ::XMVectorGetZ(m_oXMVector) - 1.0f, 1.0f);

	//--m_fX;	--m_fY;	--m_fZ;	--m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Post decrement the values of vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator--(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f, ::XMVectorGetZ(m_oXMVector) - 1.0f, 1.0f);

	//m_fX--;	m_fY--;	m_fZ--;	m_fW--;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+
// Desc: Operator to add vectors
//---------------------------------------------------------------------------
CVector4 CVector4::operator+(const CVector4 &rVector)
{
	m_oXMVector = ::XMVectorAdd(m_oXMVector, rVector.m_oXMVector);

	//m_fX += rVector.m_fX; m_fY += rVector.m_fY; m_fZ += rVector.m_fZ; m_fW += rVector.m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-
// Desc: Operator to subtract vectors
//---------------------------------------------------------------------------
CVector4 CVector4::operator-(const CVector4 &rVector)
{
	m_oXMVector = ::XMVectorSubtract(m_oXMVector, rVector.m_oXMVector);

	///m_fX -= rVector.m_fX; m_fY -= rVector.m_fY; m_fZ -= rVector.m_fZ; m_fW -= rVector.m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vectors
//---------------------------------------------------------------------------
CVector4 CVector4::operator*(const CVector4 &rVector)
{
	m_oXMVector = ::XMVectorMultiply(m_oXMVector, rVector.m_oXMVector);

	//m_fX *= rVector.m_fX; m_fY *= rVector.m_fY; m_fZ *= rVector.m_fZ; m_fW *= rVector.m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vector and a floating point value
//---------------------------------------------------------------------------
CVector4 CVector4::operator*(float fValue)
{
	m_oXMVector = m_oXMVector * fValue;

	//m_fX *= fValue; m_fY *= fValue; m_fZ *= fValue; m_fW *= fValue;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>
// Desc: Check if the vector is greater than the other vector
//---------------------------------------------------------------------------
BOOL CVector4::operator>(const CVector4 &rVector)
{
	//if(m_fX > oVector.m_fX && m_fY > oVector.m_fY && m_fZ > oVector.m_fZ && m_fW > oVector.m_fW) // It's greater
	//	return true;

	//return false; // It's lesser

	return ::XMVector4Greater(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator<
// Desc: Check if the vector is lesser than the other vector
//---------------------------------------------------------------------------
BOOL CVector4::operator<(const CVector4 &rVector)
{
	//if(m_fX < oVector.m_fX && m_fY < oVector.m_fY && m_fZ < oVector.m_fZ && m_fW < oVector.m_fW) // It's lesser
	//	return true;

	//return false; // It's greater

	return ::XMVector4Less(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of the current type
//---------------------------------------------------------------------------
CVector4 CVector4::operator=(const CVector4 &rVector)
{
	m_oXMVector = rVector.m_oXMVector;
	//m_fX = rVector.m_fX; m_fY = rVector.m_fY; m_fZ = rVector.m_fZ; m_fW = rVector.m_fW;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of type XMVECTOR
//---------------------------------------------------------------------------
CVector4 CVector4::operator=(const XMVECTOR &rXMVector)
{
	//m_fX = ::XMVectorGetX(rXMVector);
	//m_fY = ::XMVectorGetY(rXMVector);
	//m_fZ = ::XMVectorGetZ(rXMVector);
	//m_fW = ::XMVectorGetW(rXMVector);
	m_oXMVector = rXMVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator+=(const CVector4 &rVector)
{
	m_oXMVector += rVector.m_oXMVector;

	//*this + rVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector4 CVector4::operator-=(const CVector4 &rVector)
{
	m_oXMVector -= rVector.m_oXMVector;

	//*this - rVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>=
// Desc: Check if a vector is greater than/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector4::operator>=(const CVector4 &rVector)
{
	//if(m_fX >= oVector.m_fX && m_fY >= oVector.m_fY && m_fZ >= oVector.m_fZ && m_fW >= oVector.m_fW) // The vector components are greater/equal to the other vector components
	//	return true;

	return ::XMVector4GreaterOrEqual(m_oXMVector, rVector.m_oXMVector);

	//return false; // It's not greater/equal to the other vector
}

//---------------------------------------------------------------------------
// Name: operator<=
// Desc: Check if a vector is lesser/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector4::operator<=(const CVector4 &rVector)
{
	//if(m_fX <= oVector.m_fX && m_fY <= oVector.m_fY && m_fZ <= oVector.m_fZ && m_fW <= oVector.m_fW) // The vector components are lesser/equal to the other vector components
	//	return true;

	//return false; // It's not less/equal to the other vector

	return ::XMVector4LessOrEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Operator to check for the equality of vectors
//---------------------------------------------------------------------------
BOOL CVector4::operator==(const CVector4 &rVector)
{
	return ::XMVector4Equal(m_oXMVector, rVector.m_oXMVector);

	// Compute the values of vector components
	//if(m_fX == rVector.m_fX && m_fY == rVector.m_fY && m_fZ == rVector.m_fZ && m_fW == rVector.m_fW) // All the components are equal
	//	return true;

	//return false; // The vector component(s) are not equal
}

//---------------------------------------------------------------------------
// Name: operator!=
// Desc: Operator to check for the inequality of vectors
//---------------------------------------------------------------------------
BOOL CVector4::operator!=(const CVector4 &rVector)
{
	//if(::XMVector3NotEqual(m_oXMVector, rVector.m_oXMVector))
	//	return true; // Vector component(s) are not equal

	// Compute the values of vector components
	//if(m_fX != rVector.m_fX || m_fY != rVector.m_fY || m_fZ != rVector.m_fZ || m_fW != rVector.m_fW) // All/one of the components are not equal
	//	return true;

	return ::XMVector4NotEqual(m_oXMVector, rVector.m_oXMVector); // Check if the specified vector is > than our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // It's greater

	//return false; // The vector component(s) are equal
}

//---------------------------------------------------------------------------
// Name: operator[]
// Desc: Cast operator for indexing
//---------------------------------------------------------------------------
float CVector4::operator[](int nIndex) const
{
	float fIndexedValue;

	switch(nIndex)
	{
	case 0:
		fIndexedValue = ::XMVectorGetX(m_oXMVector);
		break;

	case 1:
		fIndexedValue = ::XMVectorGetY(m_oXMVector);
		break;

	case 2:
		fIndexedValue = ::XMVectorGetZ(m_oXMVector);
		break;

	case 3:
		fIndexedValue = ::XMVectorGetW(m_oXMVector);
		break;

	default:
		fIndexedValue = 0.0f;
		break;
	}

	return fIndexedValue;
}

//---------------------------------------------------------------------------
// Name: operator XMVECTOR
// Desc: Cast operator of type XMVECTOR
//---------------------------------------------------------------------------
CVector4::operator XMVECTOR() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, m_fW);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: operator XMFLOAT4
// Desc: Cast operator of type XMFLOAT4
//---------------------------------------------------------------------------
CVector4::operator XMFLOAT4() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, m_fW);

	return ::XMFLOAT4(::XMVectorGetX(m_oXMVector), ::XMVectorGetY(m_oXMVector), ::XMVectorGetZ(m_oXMVector), ::XMVectorGetW(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: length
// Desc: Compute and retruns and the length of the vector
//---------------------------------------------------------------------------
float CVector4::length() const
{
	return ::XMVectorGetX(::XMVector3Length(m_oXMVector));

	//return ::sqrtf(::powf(m_fX, 2) + ::powf(m_fY, 2) + ::powf(m_fZ, 2) + ::powf(m_fW, 2));
}

//---------------------------------------------------------------------------
// Name: cross
// Desc: Computes the cross product of the vector specified witht the current
//		 vector
//---------------------------------------------------------------------------
CVector4 CVector4::cross(const CVector4 &rVector) const
{
	CVector4 oVector;
	oVector.m_oXMVector = ::XMVector3Cross(m_oXMVector, rVector.m_oXMVector); // Compute cross product

	return oVector;
}

//---------------------------------------------------------------------------
// Name: normalize
// Desc: Normalize the current vector
//---------------------------------------------------------------------------
CVector4 CVector4::normalize()
{
	//float fMagnitude = length();

	//CVector4 oVector = CVector4(m_fX / fMagnitude, m_fY / fMagnitude, m_fZ / fMagnitude, m_fW / fMagnitude);

	//*this = oVector;
	m_oXMVector = ::XMVector4Normalize(m_oXMVector);

	return *this;
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of x component
//---------------------------------------------------------------------------
float CVector4::getX() const
{
	return ::XMVectorGetX(m_oXMVector);
	//return m_fX;
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of y component
//---------------------------------------------------------------------------
float CVector4::getY() const
{
	return ::XMVectorGetY(m_oXMVector);
	//return m_fY;
}

//---------------------------------------------------------------------------
// Name: getZ
// Desc: Get the value of z component
//---------------------------------------------------------------------------
float CVector4::getZ() const
{
	return ::XMVectorGetZ(m_oXMVector);

	//return m_fZ;
}

//---------------------------------------------------------------------------
// Name: getW
// Desc: Get the value of w component
//---------------------------------------------------------------------------
float CVector4::getW() const
{
	return ::XMVectorGetW(m_oXMVector);

//	return m_fW;
}

//---------------------------------------------------------------------------
// Name: getMagnitude
// Desc: Get the magnitude of the current vector
//---------------------------------------------------------------------------
float CVector4::getMagnitude() const
{
	//return ::sqrtf(::powf(m_fX, 2.0f) + ::powf(m_fY, 2.0f) + ::powf(m_fZ, 2.0f) + ::powf(m_fW, 2.0f));

	return ::XMVectorGetX(::XMVector4Length(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: getXMVector
// Desc: Get the XMVECTOR equivalent
//---------------------------------------------------------------------------
XMVECTOR CVector4::getXMVector() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, m_fW);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: setX
// Desc: Set the x component
//---------------------------------------------------------------------------
void CVector4::setX(float fX)
{
	::XMVectorSetX(m_oXMVector, fX);
}

//---------------------------------------------------------------------------
// Name: setY
// Desc: Set the y component
//---------------------------------------------------------------------------
void CVector4::setY(float fY)
{
	::XMVectorSetY(m_oXMVector, fY);
}

//---------------------------------------------------------------------------
// Name: setZ
// Desc: Set the z component
//---------------------------------------------------------------------------
void CVector4::setZ(float fZ)
{
	::XMVectorSetZ(m_oXMVector, fZ);
}

//---------------------------------------------------------------------------
// Name: setW
// Desc: Set the w component
//---------------------------------------------------------------------------
void CVector4::setW(float fW)
{
	::XMVectorSetW(m_oXMVector, fW);
}

//---------------------------------------------------------------------------
// Name: CVector3
// Desc: Default constructor
//---------------------------------------------------------------------------
CVector3::CVector3()
{
	//m_fX = m_fY = m_fZ = 0.0f;
	m_oXMVector = ::XMVectorZero();
}

//---------------------------------------------------------------------------
// Name: CVector3
// Desc: Constructor with x, y and z components
//---------------------------------------------------------------------------
CVector3::CVector3(float fX, float fY, float fZ)
{
	m_oXMVector = ::XMVectorSet(fX, fY, fZ, 0.0f);

	/*m_fX = fX; m_fY = fY; m_fZ = fZ;*/
}

//---------------------------------------------------------------------------
// Name: ~CVector3
// Desc: Destructor
//---------------------------------------------------------------------------
CVector3::~CVector3()
{
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Pre increment the values of vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator++()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f, ::XMVectorGetZ(m_oXMVector) + 1.0f, 0.0f);
	//++m_fX;
	//++m_fY;
	//++m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Post increment the values of vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator++(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f, ::XMVectorGetZ(m_oXMVector) + 1.0f, 0.0f);
	//m_fX++;
	//m_fY++;
	//m_fZ++;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Pre decrement the values of vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator--()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f, ::XMVectorGetZ(m_oXMVector) - 1.0f, 0.0f);
	//--m_fX;
	//--m_fY;
	//--m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Post decrement the values of vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator--(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f, ::XMVectorGetZ(m_oXMVector) - 1.0f, 0.0f);
	//m_fX--;
	//m_fY--;
	//m_fZ--;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+
// Desc: Operator to add vectors
//---------------------------------------------------------------------------
CVector3 CVector3::operator+(const CVector3 &rVector)
{
	m_oXMVector = ::XMVectorAdd(m_oXMVector, rVector.m_oXMVector);
	//m_fX += rVector.m_fX;
	//m_fY += rVector.m_fY;
	//m_fZ += rVector.m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-
// Desc: Operator to subtract vectors
//---------------------------------------------------------------------------
CVector3 CVector3::operator-(const CVector3 &rVector)
{
	m_oXMVector = ::XMVectorSubtract(m_oXMVector, rVector.m_oXMVector);
	//m_fX -= rVector.m_fX;
	//m_fY -= rVector.m_fY;
	//m_fZ -= rVector.m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vectors
//---------------------------------------------------------------------------
CVector3 CVector3::operator*(const CVector3 &rVector)
{
	m_oXMVector = ::XMVectorMultiply(m_oXMVector, rVector.m_oXMVector);
	//m_fX *= rVector.m_fX;
	//m_fY *= rVector.m_fY;
	//m_fZ *= rVector.m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vector and a floating point value
//---------------------------------------------------------------------------
CVector3 CVector3::operator*(float fValue)
{
	m_oXMVector = m_oXMVector * fValue;
	/*m_fX *= fValue;
	m_fY *= fValue;
	m_fZ *= fValue;*/

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>
// Desc: Check if the vector is greater than the other vector
//---------------------------------------------------------------------------
BOOL CVector3::operator>(const CVector3 &rVector)
{
	//if(m_fX > oVector.m_fX && m_fY > oVector.m_fY && m_fZ > oVector.m_fZ) // It's greater
	//	return true;
	//XMVECTOR oXMResult = ::XMVectorGreater(m_oXMVector, rVector); // Check if the specified vector is > than our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // It's greater

	//return false; // It's lesser

	return ::XMVector3Greater(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator<
// Desc: Check if the vector is lesser than the other vector
//---------------------------------------------------------------------------
BOOL CVector3::operator<(const CVector3 &rVector)
{
	//if(m_fX < oVector.m_fX && m_fY < oVector.m_fY && m_fZ < oVector.m_fZ) // It's greater
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorLess(m_oXMVector, rVector); // Check if the specified vector is < than our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // It's lesser

	//return false; // It's greater

	return ::XMVector3Less(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of the current type
//---------------------------------------------------------------------------
CVector3 CVector3::operator=(const CVector3 &rVector)
{
	//m_oXMVector = rVector.m_oXMVector;
	//m_fX = rVector.m_fX;
	//m_fY = rVector.m_fY;
	//m_fZ = rVector.m_fZ;

	m_oXMVector = rVector.m_oXMVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of type XMVECTOR
//---------------------------------------------------------------------------
CVector3 CVector3::operator=(const XMVECTOR &rXMVector)
{
	//m_fX = ::XMVectorGetX(rXMVector);
	//m_fY = ::XMVectorGetY(rXMVector);
	//m_fZ = ::XMVectorGetZ(rXMVector);
	m_oXMVector = rXMVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator+=(const CVector3 &rVector)
{
	m_oXMVector += rVector.m_oXMVector;
	//m_fX += rVector.m_fX;
	//m_fY += rVector.m_fY;
	//m_fZ += rVector.m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector3 CVector3::operator-=(const CVector3 &rVector)
{
	m_oXMVector -= rVector.m_oXMVector;
	//m_fX -= rVector.m_fX;
	//m_fY -= rVector.m_fY;
	//m_fZ -= rVector.m_fZ;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>=
// Desc: Check if a vector is greater than/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector3::operator>=(const CVector3 &rVector)
{
	//if(m_fX >= oVector.m_fX && m_fY >= oVector.m_fY && m_fZ >= oVector.m_fZ) // The vector components are greater/equal to the other vector components
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorGreaterOrEqual(m_oXMVector, rVector); // Check if the specified vector is >= to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's not greater/equal to the other vector

	return ::XMVector3GreaterOrEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator<=
// Desc: Check if a vector is lesser/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector3::operator<=(const CVector3 &rVector)
{
	//XMVECTOR oXMResult = ::XMVectorLessOrEqual(m_oXMVector, rVector); // Check if the specified vector is <= to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's not less/equal to the other vector

	return ::XMVector3LessOrEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Operator to check for the equality of vectors
//---------------------------------------------------------------------------
BOOL CVector3::operator==(const CVector3 &rVector)
{
	//if(::XMVector3Equal(m_oXMVector, rVector.m_oXMVector))
	//	return true; // All the vector components are equal

	// Compute the values of vector components
	//if(m_fX == rVector.m_fX && m_fY == rVector.m_fY && m_fZ == rVector.m_fZ) // All the components are equal
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorEqual(m_oXMVector, rVector); // Compute the equality of the vectors

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true;

	//return false; // The vector component(s) are not equal

	return ::XMVector3Equal(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator!=
// Desc: Operator to check for the inequality of vectors
//---------------------------------------------------------------------------
BOOL CVector3::operator!=(const CVector3 &rVector)
{
	//if(::XMVector3NotEqual(m_oXMVector, rVector.m_oXMVector))
	//	return true; // Vector component(s) are not equal
	/*if(m_fX != rVector.m_fX || m_fY != rVector.m_fY || m_fZ != rVector.m_fZ)
		return true;*/

	//XMVECTOR oXMResult = ::XMVectorNotEqual(m_oXMVector, (XMVECTOR) rVector); // Compute the inequality of the vectors

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true;

	//return false; // The vector component(s) are equal

	return ::XMVector3NotEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator[]
// Desc: Cast operator for indexing
//---------------------------------------------------------------------------
float CVector3::operator[](int nIndex) const
{
	float fIndexedValue;

	switch(nIndex)
	{
	case 0:
		fIndexedValue = ::XMVectorGetX(m_oXMVector);
		break;

	case 1:
		fIndexedValue = ::XMVectorGetY(m_oXMVector);
		break;

	case 2:
		fIndexedValue = ::XMVectorGetZ(m_oXMVector);
		break;

	default:
		fIndexedValue = 0.0f;
		break;
	}

	return fIndexedValue;
}

//---------------------------------------------------------------------------
// Name: operator XMVECTOR
// Desc: Cast operator of type XMVECTOR
//---------------------------------------------------------------------------
CVector3::operator XMVECTOR() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, 0.0f);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: operator XMFLOAT3
// Desc: Cast operator of type XMFLOAT3
//---------------------------------------------------------------------------
CVector3::operator XMFLOAT3() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, m_fW);

	return ::XMFLOAT3(::XMVectorGetX(m_oXMVector), ::XMVectorGetY(m_oXMVector), ::XMVectorGetZ(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: length
// Desc: Compute and retruns and the length of the vector
//---------------------------------------------------------------------------
float CVector3::length() const
{
	return ::XMVectorGetX(::XMVector3Length(m_oXMVector));
	//return ::sqrtf(::powf(m_fX, 2.0f) + ::powf(m_fY, 2.0f) + ::powf(m_fZ, 2.0f));
}

//---------------------------------------------------------------------------
// Name: cross
// Desc: Computes the cross product of the vector specified with the current
//		 vector
//---------------------------------------------------------------------------
CVector3 CVector3::cross(const CVector3 &rVector) const
{
	CVector3 oVector;
	oVector.m_oXMVector = ::XMVector3Cross(m_oXMVector, rVector.m_oXMVector); // Compute cross product

	return oVector;
}

//---------------------------------------------------------------------------
// Name: normalize
// Desc: Normalize the current vector
//---------------------------------------------------------------------------
CVector3 CVector3::normalize()
{
	/*float fMagnitude = length();

	CVector3 oVector = CVector3(m_fX / fMagnitude, m_fY / fMagnitude, m_fZ / fMagnitude);

	*this = oVector;*/

	m_oXMVector = ::XMVector3Normalize(m_oXMVector);

	return *this;
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of x component
//---------------------------------------------------------------------------
float CVector3::getX() const
{
	// return m_fX; // 
	return ::XMVectorGetX(m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of y component
//---------------------------------------------------------------------------
float CVector3::getY() const
{
	//return m_fY; // 
	return ::XMVectorGetY(m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: getZ
// Desc: Get the value of z component
//---------------------------------------------------------------------------
float CVector3::getZ() const
{
	//return m_fZ; // 
	return ::XMVectorGetZ(m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: getMagnitude
// Desc: Get the magnitude of the current vector
//---------------------------------------------------------------------------
float CVector3::getMagnitude() const
{
	//return ::sqrtf(::powf(m_fX, 2.0f) + ::powf(m_fY, 2.0f) + ::powf(m_fZ, 2.0f));
	//return ::sqrtf(::powf(::XMVectorGetX(m_oXMVector), 2.0f) + ::powf(::XMVectorGetY(m_oXMVector), 2.0f) + ::powf(::XMVectorGetZ(m_oXMVector), 2.0f));

	return ::XMVectorGetX(::XMVector3Length(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: getXMVector
// Desc: Get the XMVECTOR equivalent
//---------------------------------------------------------------------------
XMVECTOR CVector3::getXMVector() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, 0.0f);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: setX
// Desc: Set the x component
//---------------------------------------------------------------------------
void CVector3::setX(float fX)
{
	::XMVectorSetX(m_oXMVector, fX);
}

//---------------------------------------------------------------------------
// Name: setY
// Desc: Set the y component
//---------------------------------------------------------------------------
void CVector3::setY(float fY)
{
	::XMVectorSetY(m_oXMVector, fY);
}

//---------------------------------------------------------------------------
// Name: setZ
// Desc: Set the z component
//---------------------------------------------------------------------------
void CVector3::setZ(float fZ)
{
	::XMVectorSetZ(m_oXMVector, fZ);
}

//---------------------------------------------------------------------------
// Name: CVector2
// Desc: Default constructor
//---------------------------------------------------------------------------
CVector2::CVector2()
{
	//m_fX = m_fY = 0.0f;
	m_oXMVector = ::XMVectorZero();
}

//---------------------------------------------------------------------------
// Name: CVector2
// Desc: Constructor with x, y and z components
//---------------------------------------------------------------------------
CVector2::CVector2(float fX, float fY)
{
	m_oXMVector = ::XMVectorSet(fX, fY, 0.0f, 0.0f);

	//m_fX = fX; m_fY = fY;
}

//---------------------------------------------------------------------------
// Name: ~CVector2
// Desc: Destructor
//---------------------------------------------------------------------------
CVector2::~CVector2()
{
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Pre increment the values of vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator++()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f,  0.0f, 0.0f);

	//++m_fX;
	//++m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator++
// Desc: Post increment the values of vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator++(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) + 1.0f, ::XMVectorGetY(m_oXMVector) + 1.0f,  0.0f, 0.0f);
	//m_fX++;
	//m_fY++;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Pre decrement the values of vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator--()
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f,  0.0f, 0.0f);
	/*--m_fX;
	--m_fY;*/

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator--
// Desc: Post decrement the values of vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator--(int)
{
	m_oXMVector = ::XMVectorSet(::XMVectorGetX(m_oXMVector) - 1.0f, ::XMVectorGetY(m_oXMVector) - 1.0f, 0.0f, 0.0f);
	//m_fX++;
	//m_fY++;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+
// Desc: Operator to add vectors
//---------------------------------------------------------------------------
CVector2 CVector2::operator+(const CVector2 &rVector)
{
	m_oXMVector = ::XMVectorAdd(m_oXMVector, rVector.m_oXMVector);
	//m_fX += rVector.m_fX;
	//m_fY += rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-
// Desc: Operator to subtract vectors
//---------------------------------------------------------------------------
CVector2 CVector2::operator-(const CVector2 &rVector)
{
	m_oXMVector = ::XMVectorSubtract(m_oXMVector, rVector.m_oXMVector);
	//m_fX -= rVector.m_fX;
	//m_fY -= rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vectors
//---------------------------------------------------------------------------
CVector2 CVector2::operator*(const CVector2 &rVector)
{
	m_oXMVector = ::XMVectorMultiply(m_oXMVector, rVector.m_oXMVector);
	//m_fX *= rVector.m_fX;
	//m_fY *= rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator*
// Desc: Operator to multiply vector and a floating point value
//---------------------------------------------------------------------------
CVector2 CVector2::operator*(float fValue)
{
	m_oXMVector = m_oXMVector * fValue;
	//m_fX *= fValue;
	//m_fY *= fValue;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>
// Desc: Check if the vector is greater than the other vector
//---------------------------------------------------------------------------
BOOL CVector2::operator>(const CVector2 &rVector)
{
	//if(m_fX > oVector.m_fX && m_fY > oVector.m_fY) // It's greater
	//	return true;
	//XMVECTOR oXMResult = ::XMVectorGreater(m_oXMVector, rVector); // Check if the specified vector is > to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's not greater

	return ::XMVector2Greater(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator<
// Desc: Check if the vector is lesser than the other vector
//---------------------------------------------------------------------------
BOOL CVector2::operator<(const CVector2 &rVector)
{
	//if(m_fX < oVector.m_fX && m_fY < oVector.m_fY) // It's lesser
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorLess(m_oXMVector, rVector); // Check if the specified vector < our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's greater

	return ::XMVector2Less(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of the current type
//---------------------------------------------------------------------------
CVector2 CVector2::operator=(const CVector2 &rVector)
{
	m_oXMVector = rVector.m_oXMVector;
	//m_fX = rVector.m_fX;
	//m_fY = rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator=
// Desc: Assign vector of type XMVECTOR
//---------------------------------------------------------------------------
CVector2 CVector2::operator=(const XMVECTOR &rXMVector)
{
	//m_fX = ::XMVectorGetX(rXMVector);
	//m_fY = ::XMVectorGetY(rXMVector);

	m_oXMVector = rXMVector;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator+=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator+=(const CVector2 &rVector)
{
	m_oXMVector += rVector.m_oXMVector;
	//m_fX += rVector.m_fX;
	//m_fY += rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator-=
// Desc: Assign vector
//---------------------------------------------------------------------------
CVector2 CVector2::operator-=(const CVector2 &rVector)
{
	m_oXMVector -= rVector.m_oXMVector;
	//m_fX -= rVector.m_fX;
	//m_fY -= rVector.m_fY;

	return *this;
}

//---------------------------------------------------------------------------
// Name: operator>=
// Desc: Check if a vector is greater than/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector2::operator>=(const CVector2 &rVector)
{
	//if(m_fX >= oVector.m_fX && m_fY >= oVector.m_fY) // The vector components are greater/equal to the other vector components
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorGreaterOrEqual(m_oXMVector, rVector); // Check if the specified vector is >= to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's not greater/equal to the other vector

	return ::XMVector2GreaterOrEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator<=
// Desc: Check if a vector is lesser/equal to the other vector
//---------------------------------------------------------------------------
BOOL CVector2::operator<=(const CVector2 &rVector)
{
	//if(m_fX <= oVector.m_fX && m_fY <= oVector.m_fY) // The vector components are lesser/equal to the other vector components
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorLessOrEqual(m_oXMVector, rVector); // Check if the specified vector is <= our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // It's not less/equal to the other vector

	return ::XMVector2LessOrEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator==
// Desc: Operator to check for the equality of vectors
//---------------------------------------------------------------------------
BOOL CVector2::operator==(const CVector2 &rVector)
{
	//if(::XMVector3Equal(m_oXMVector, rVector.m_oXMVector))
	//	return true; // All the vector components are equal

	//XMVECTOR oXMResult = ::XMVectorGreaterOrEqual(m_oXMVector, rVector); // Check if the specified vector == to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // The vector component(s) are not equal

	return ::XMVector2Equal(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator!=
// Desc: Operator to check for the inequality of vectors
//---------------------------------------------------------------------------
BOOL CVector2::operator!=(const CVector2 &rVector)
{
	//if(::XMVector3NotEqual(m_oXMVector, rVector.m_oXMVector))
	//	return true; // Vector component(s) are not equal
	//if(m_fX != rVector.m_fX || m_fY != rVector.m_fY) // Vector component(s) is/are not equal
	//	return true;

	//XMVECTOR oXMResult = ::XMVectorNotEqual(m_oXMVector, rVector); // Check if the specified vector is != to our vector

	//if((static_cast<int>(::XMVectorGetX(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetY(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF) && (static_cast<int>(::XMVectorGetZ(oXMResult)) & 0xFFFFFFFF == 0xFFFFFFFF))
	//	return true; // true

	//return false; // The vector component(s) are equal

	return ::XMVector2NotEqual(m_oXMVector, rVector.m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: operator[]
// Desc: Cast operator for indexing
//---------------------------------------------------------------------------
float CVector2::operator[](int nIndex) const
{
	float fIndexedValue;

	switch(nIndex)
	{
	case 0:
		fIndexedValue = ::XMVectorGetX(m_oXMVector);
		break;

	case 1:
		fIndexedValue = ::XMVectorGetY(m_oXMVector);
		break;

	default:
		fIndexedValue = 0.0f;
		break;
	}

	return fIndexedValue;
}

//---------------------------------------------------------------------------
// Name: operator XMVECTOR
// Desc: Cast operator of type XMVECTOR
//---------------------------------------------------------------------------
CVector2::operator XMVECTOR() const
{
	///XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, 0.0f, 1.0f);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: operator XMFLOAT2
// Desc: Cast operator of type XMFLOAT2
//---------------------------------------------------------------------------
CVector2::operator XMFLOAT2() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, m_fZ, m_fW);

	return ::XMFLOAT2(::XMVectorGetX(m_oXMVector), ::XMVectorGetY(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: length
// Desc: Compute and retruns and the length of the vector
//---------------------------------------------------------------------------
float CVector2::length() const
{
	return ::XMVectorGetX(::XMVector3Length(m_oXMVector));

	//return ::sqrtf(::powf(::XMVectorGetX(m_oXMVector), 2.0f) + ::powf(::XMVectorGetY(m_oXMVector), 2.0f));
	//return ::sqrtf(::powf(m_fX, 2.0f) + ::powf(m_fY, 2.0f));
}

//---------------------------------------------------------------------------
// Name: cross
// Desc: Computes the cross product of the vector specified witht the current
//		 vector
//---------------------------------------------------------------------------
CVector2 CVector2::cross(const CVector2 &rVector) const
{
	CVector2 oVector;
	oVector.m_oXMVector = ::XMVector3Cross(m_oXMVector, rVector.m_oXMVector); // Compute cross product

	return oVector;
}

//---------------------------------------------------------------------------
// Name: normalize
// Desc: Normalize the current vector
//---------------------------------------------------------------------------
CVector2 CVector2::normalize()
{
	//float fMagnitude = length();

	//CVector2 oVector = CVector2(m_fX / fMagnitude, m_fY / fMagnitude);

	//*this = oVector;

	m_oXMVector = ::XMVector2Normalize(m_oXMVector);

	return *this;
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of x component
//---------------------------------------------------------------------------
float CVector2::getX() const
{
	return ::XMVectorGetX(m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of y component
//---------------------------------------------------------------------------
float CVector2::getY() const
{
	return ::XMVectorGetY(m_oXMVector);
}

//---------------------------------------------------------------------------
// Name: getMagnitude
// Desc: Get the magnitude of the current vector
//---------------------------------------------------------------------------
float CVector2::getMagnitude() const
{
	//return ::sqrtf(::powf(m_fX, 2.0f) + ::powf(m_fY, 2.0f));

	return ::XMVectorGetX(::XMVector2Length(m_oXMVector));
}

//---------------------------------------------------------------------------
// Name: getXMVector
// Desc: Get the XMVECTOR equivalent of the current vector
//---------------------------------------------------------------------------
XMVECTOR CVector2::getXMVector() const
{
	//XMVECTOR oXMVector = ::XMVectorSet(m_fX, m_fY, 0.0f, 0.0f);

	return m_oXMVector;
}

//---------------------------------------------------------------------------
// Name: setX
// Desc: Set the x component
//---------------------------------------------------------------------------
void CVector2::setX(float fX)
{
	::XMVectorSetX(m_oXMVector, fX);
}

//---------------------------------------------------------------------------
// Name: setY
// Desc: Set the y component
//---------------------------------------------------------------------------
void CVector2::setY(float fY)
{
	::XMVectorSetY(m_oXMVector, fY);
}