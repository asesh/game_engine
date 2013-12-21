// Transform.cpp: Implementation of transformation components
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "Transform.h"

//---------------------------------------------------------------------------
// Name: CTransform
// Desc: Defautlt constructor
//---------------------------------------------------------------------------
CTransform::CTransform()
{
	m_oForwardVector = CVector3(0.0f, 0.0f, 1.0f); // Forward vector
	m_oRightVector = CVector3(1.0f, 0.0f, 0.0f); // Right vector
	m_oUpVector = CVector3(0.0f, 1.0f, 0.0f); // Up vector
}

//---------------------------------------------------------------------------
// Name: ~CTransform
// Desc: Destructor
//---------------------------------------------------------------------------
CTransform::~CTransform()
{
}

//---------------------------------------------------------------------------
// Name: scale
// Desc: Perform scaling operation
//---------------------------------------------------------------------------
void CTransform::scale(float fX, float fY, float fZ)
{
}

//---------------------------------------------------------------------------
// Name: scale
// Desc: Perform scaling operation
//---------------------------------------------------------------------------
void CTransform::scale(const CVector3 &rScaleVector)
{
	//m_
}

//---------------------------------------------------------------------------
// Name: rotate
// Desc: Perform rotation operation using quaternion
//---------------------------------------------------------------------------
void CTransform::rotate(const CQuaternion &rQuaternion)
{
}

//---------------------------------------------------------------------------
// Name: translate
// Desc: Perform translation operation
//---------------------------------------------------------------------------
void CTransform::translate(float fX, float fY, float fZ)
{
	//m_o
}

//---------------------------------------------------------------------------
// Name: translate
// Desc: Perform translation operation
//---------------------------------------------------------------------------
void CTransform::translate(const CVector3 &rTranslateVector)
{
	//m_o
}

//---------------------------------------------------------------------------
// Name: getLocalPosition
// Desc: Get the local position of the corresponding object
//---------------------------------------------------------------------------
CVector3 CTransform::getLocalPosition() const
{
	return m_oLocalPosition;
}

//---------------------------------------------------------------------------
// Name: getLocalScale
// Desc: Get the local scaling value of the corresponding object
//---------------------------------------------------------------------------
CVector3 CTransform::getLocalScale() const
{
	return m_oLocalScale;
}

//---------------------------------------------------------------------------
// Name: getLocalRotation
// Desc: Get the local rotation of the corresponding object
//---------------------------------------------------------------------------
CQuaternion CTransform::getLocalRotation() const
{
	return m_oLocalRotation;
}

//---------------------------------------------------------------------------
// Name: getWorldRotation
// Desc: Get the world rotation of the corresponding object
//---------------------------------------------------------------------------
CQuaternion CTransform::getWorldRotation() const
{
	return m_oWorldRotation;
}