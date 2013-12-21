// BoundingVolume.h : Declaration and implementation of bounding volumes for collision detection
// Copyright (C) 2007-2011 Asesh Shrestha

#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

// SBoundingBox structure
struct SBoundingBox
{
	// Default constructor
	SBoundingBox()
	{
	}

	//---------------------------------------------------------
	// Name: isPointInside
	// Desc: It will be used to determinate whether
	//		 the specified point is inside the bounding box
	//---------------------------------------------------------
	//BOOL isPointInside(XMVECTOR *pXMPointVec)
	//{
	//	if(pXMVecPoint->x >= m_vecLowerLeftCorner.x && pXMVecPoint->y >= m_vecLowerLeftCorner.y && pXMVecPoint->z >= m_vecLowerLeftCorner.z
	//		&& pXMVecPoint->x <= m_vecUpperRightCorner.x && pXMVecPoint->y <= m_vecUpperRightCorner.y && pXMVecPoint->z <= m_vecUpperRightCorner.z)

	//		return TRUE; // Specifies that the point lies inside the bounding box
	//	else
	//		return FALSE; // Specifies that the point does not lie inside the bounding box
	//}

	// Corners of the bounding box
	XMVECTOR m_oLowerLeftCornerVec, m_oUpperRightCornerVec;
};

// SBoundingSphere structure
struct SBoundingSphere
{
	// Default constructor
	SBoundingSphere()
	{
		m_fRadius = 0.0f;
	}

	XMVECTOR m_oCoordinateCenterVec; // Coordinate center of the bounding sphere
	float m_fRadius; // Radius of the bounding sphere
};

#endif // BOUNDINGVOLUME_H