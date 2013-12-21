// Point.h: Interface of point in n-dimensional space
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef POINT_H
#define POINT_H

// CPoint3D class
class CPoint3D
{
	CPoint3D(); // Default constructor
	~CPoint3D(); // Destructor

private:
	XMFLOAT3 m_oXMPoint3D; // 3D point
};

#endif // POINT_H