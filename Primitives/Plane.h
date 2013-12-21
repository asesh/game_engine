// Plane.h: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef PLANE_H
#define PLANE_H

// CPlane class
class CPlane
{
public:
	CPlane(); // Default constructor
	CPlane(float fX, float fY, float fZ, float fW); // Constructor
	~CPlane(); // Destructor

	HRESULT create(float fX, float fY, float fZ, float fW); // Create a plane

private:
	float m_fX, m_fY, m_fZ, m_fW; // Plane components
};

#endif // PLANE_H