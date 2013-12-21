// Vertex.h: 
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

#ifndef VERTEX_H
#define VERTEX_H

//---------------------------------------------------------------------------
// Name: S3DPosVertex
// Desc: 3D vertex only
//---------------------------------------------------------------------------
struct S3DPosVertex
{

/*#ifndef D3D10_COMPILE_CODE

	// Constructor with 3D vertex position
	S3DPosVertex(float fXCoord, float fYCoord, float fZCoord)
	{
		m_fX = fXCoord; m_fY = fYCoord; m_fZ = fZCoord;
	}

#endif // D3D10_COMPILE_CODE*/

	float m_fX, m_fY, m_fZ; // 3D vertex position
};

//---------------------------------------------------------------------------
// Name: S3DPos2DTexVertex
// Desc: 3D vertex with 2D texture coordinate type
//---------------------------------------------------------------------------
struct S3DPos2DTexVertex
{

/*#ifndef D3D10_COMPILE_CODE

	// Constructor with 3D vertex position and 2D texture coordinates
	S3DPos2DTexVertex(float fXCoord, float fYCoord, float fZCoord, float fUCoord, float fVCoord)
	{
		m_fX = fXCoord; m_fY = fYCoord; m_fZ = fZCoord;
		m_fU = fUCoord; m_fV = fVCoord;
	}

#endif // D3D10_COMPILE_CODE*/

	float m_fX, m_fY, m_fZ; // 3D position of vertices
	float m_fU, m_fV; // 2D texture coordinates
};

//---------------------------------------------------------------------------
// Name: S3DPos3DNorm2DTexVertex
// Desc: 3D vertex, 3D normal and 2D texture coordinate type
//---------------------------------------------------------------------------
struct S3DPos3DNorm2DTexVertex
{

/*#ifndef D3D10_COMPILE_CODE

	// Constructor with 3D vertex position, 3D normals and 2D texture coordinates
	S3DPos3DNorm2DTexVertex(float fXCoord, float fYCoord, float fZCoord, float fNormalX, float fNormalY, \
		float fNormalZ, float fUCoord, float fVCoord)
	{
		m_fX = fXCoord; m_fY = fYCoord; m_fZ = fZCoord;
		m_fNormX = fNormalX; m_fNormY = fNormalY; m_fNormZ = fNormalZ;
		m_fU = fUCoord; m_fV = fVCoord;
	}

#endif // D3D10_COMPILE_CODE*/

	float m_fX, m_fY, m_fZ; // 3D position of vertices
	float m_fNormX, m_fNormY, m_fNormZ; // Vertex normals
	float m_fU, m_fV; // Texture coordinates
};

#endif // VERTEX_H