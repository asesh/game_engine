// Quaternion.cpp: Implementation of quaternion
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved


#include "..\Common\StdAfx.h"

#include <xnamath.h> // XNA Math

#include "Quaternion.h"

//------------------------------------------------------------------
// Name: CQuaternion
// Desc: Default constructor
//------------------------------------------------------------------
CQuaternion::CQuaternion()
{
}

//------------------------------------------------------------------
// Name: CQuaternion
// Desc: Constructor
//------------------------------------------------------------------
CQuaternion::CQuaternion(float fS, float fX, float fY, float fZ)
{
	m_oXMQuaternion = ::XMVectorSet(fS, fX, fY, fZ);
}

//------------------------------------------------------------------
// Name: ~CQuaternion
// Desc: Destructor
//------------------------------------------------------------------
CQuaternion::~CQuaternion()
{
}

//------------------------------------------------------------------
// Name: operator+
// Desc: Add quaternions
//------------------------------------------------------------------
CQuaternion CQuaternion::operator+(const CQuaternion &rQuaternion)
{
	m_oXMQuaternion = ::XMVectorAdd(m_oXMQuaternion, rQuaternion.m_oXMQuaternion);

	return *this;
}

//------------------------------------------------------------------
// Name: operator*
// Desc: Multiply quaternions
//------------------------------------------------------------------
CQuaternion CQuaternion::operator*(const CQuaternion &rQuaternion)
{
	m_oXMQuaternion = ::XMQuaternionMultiply(m_oXMQuaternion, rQuaternion.m_oXMQuaternion);

	return *this;
}

//------------------------------------------------------------------
// Name: operator++
// Desc: Increment the value of quaternion
//------------------------------------------------------------------
CQuaternion CQuaternion::operator++()
{
	m_oXMQuaternion = ::XMVectorAdd(m_oXMQuaternion, XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));

	return *this;
}

//------------------------------------------------------------------
// Name: operator--
// Desc: Decrement the value of quaternion
//------------------------------------------------------------------
CQuaternion CQuaternion::operator--()
{
	m_oXMQuaternion = ::XMVectorSubtract(m_oXMQuaternion, XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));

	return *this;
}

//------------------------------------------------------------------
// Name: operator=
// Desc: Assign one quaternion to the other
//------------------------------------------------------------------
CQuaternion CQuaternion::operator=(CQuaternion oQuaternion)
{
	m_oXMQuaternion = oQuaternion.m_oXMQuaternion;

	return *this;
}

//------------------------------------------------------------------
// Name: operator==
// Desc: Test for equality of two quaternions
//------------------------------------------------------------------
BOOL CQuaternion::operator==(const CQuaternion &rQuaternion)
{
	return ::XMQuaternionEqual(m_oXMQuaternion, rQuaternion.m_oXMQuaternion);
}

//------------------------------------------------------------------
// Name: operator!=
// Desc: Test for the inequality of two quaternions
//------------------------------------------------------------------
BOOL CQuaternion::operator!=(const CQuaternion &rQuaternion)
{
	return !::XMQuaternionEqual(m_oXMQuaternion, rQuaternion.m_oXMQuaternion);
}

//------------------------------------------------------------------
// Name: length
// Desc: Return the length of quaternion
//------------------------------------------------------------------
float CQuaternion::length() const
{
	return ::XMVectorGetX(::XMQuaternionLength(m_oXMQuaternion));
}

//------------------------------------------------------------------
// Name: operator XMVECTOR
// Desc: Cast operator of type XMVECTOR
//------------------------------------------------------------------
CQuaternion::operator XMVECTOR() const
{
	return m_oXMQuaternion;
}

//---------------------------------------------------------------------------
// Name: getS
// Desc: Get the value of s component
//---------------------------------------------------------------------------
float CQuaternion::getS() const
{
	return ::XMVectorGetX(m_oXMQuaternion);
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of x component
//---------------------------------------------------------------------------
float CQuaternion::getX() const
{
		return ::XMVectorGetX(m_oXMQuaternion);
}

//---------------------------------------------------------------------------
// Name: getX
// Desc: Get the value of y component
//---------------------------------------------------------------------------
float CQuaternion::getY() const
{
		return ::XMVectorGetY(m_oXMQuaternion);
}

//---------------------------------------------------------------------------
// Name: getZ
// Desc: Get the value of z component
//---------------------------------------------------------------------------
float CQuaternion::getZ() const
{
	return ::XMVectorGetZ(m_oXMQuaternion);
}
