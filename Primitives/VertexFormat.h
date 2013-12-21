// VertexFormat.h: Definition of vertex formats
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

//---------------------------------------------------------------------------
// Name: SBaseVertexFormat
// Desc: Base vertex format
//---------------------------------------------------------------------------
struct SBaseVertexFormat
{
};

//---------------------------------------------------------------------------
// Name: SVertex
// Desc: Vertex format with vertices only
//---------------------------------------------------------------------------
struct SVertex : public SBaseVertexFormat
{
public:
	//float m_fX, m_fY, m_fZ; // Vertex coordinates
	//CVector3 m_oVertex;
	XMFLOAT3 m_oVertex;

	// Default constructor
	SVertex()
	{
	}

	// Constructor with vertex coordinates only
	SVertex(const CVector3 &rVertex)
	{
		// Assign vertices
		m_oVertex = rVertex;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexTexture2D
// Desc: Vertex format with vertices and 2D texture
//---------------------------------------------------------------------------
struct SVertexTexture2D : public SVertex
{
	//float m_fU, m_fV; // Texture coordinates	// Constructor with vertex coordinates, normals and 2D texture coordinates
	//CVector2 m_oUV;
	XMFLOAT2 m_oUV;

	// Default constructor
	SVertexTexture2D()
	{
	}
	
	// Constructor with vertex coordinates and 2D texture coordinates
	SVertexTexture2D(const CVector3 &rVertex, const CVector2 &rTextureCoordinate)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign texture coordinates
		m_oUV = rTextureCoordinate;

	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormal
// Desc: Vertex format with vertices and normals
//---------------------------------------------------------------------------
struct SVertexNormal : public SVertex
{
	//float m_fNormalX, m_fNormalY, m_fNormalZ; // Normals
	//CVector3 m_oNormalVector;
	XMFLOAT3 m_oNormalVector;

	// Default constructor
	SVertexNormal()
	{
	}

	// Constructor with vertex coordinates and normals
	SVertexNormal(const CVector3 &rVertex, const CVector3 &rNormalVector)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTexture2D
// Desc: Vertex format with vertices, normals and 2D texture
//---------------------------------------------------------------------------
struct SVertexNormalTexture2D : public SVertexNormal
{
	//float m_fU, m_fV; // Texture coordinates	// Constructor with vertex coordinates, normals and 2D texture coordinates
	//CVector2 m_oUV;
	XMFLOAT2 m_oUV;

	// Default constructor
	SVertexNormalTexture2D()
	{
	}
	
	// Constructor with vertex coordinates, normals and 2D texture coordinates
	SVertexNormalTexture2D(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector2 &rTextureCoordinate)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;

		// Assign vertices
		m_oUV = rTextureCoordinate;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangent
// Desc: Vertex format with vertices, normals, and tangent
//---------------------------------------------------------------------------
struct SVertexNormalTangent : public SVertexNormal
{
	//float m_fTangentX, m_fTangentY, m_fTangentZ;
	//CVector3 m_oTangentVector;
	XMFLOAT3 m_oTangentVector;

	// Default constructor
	SVertexNormalTangent()
	{
	}

	// Constructor
	SVertexNormalTangent(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;

		// Assign tangent 
		m_oTangentVector = rTangentVector;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangentTexture2D
// Desc: Vertex format with vertices, normal, tangent and 2D texture
//---------------------------------------------------------------------------
struct SVertexNormalTangentTexture2D : public SVertexNormalTangent
{
	//float m_fU, m_fV; // Texture coordinates
	//CVector2 m_oUV;
	XMFLOAT2 m_oUV;

	// Default constructor
	SVertexNormalTangentTexture2D()
	{
	}
	
	// Constructor
	SVertexNormalTangentTexture2D(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector, const CVector2 &rTextureCoordinate)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;

		// Assign tangent vector
		m_oTangentVector = rTangentVector;

		// Assign texture coordinates
		m_oUV = rTextureCoordinate;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangentBitangent
// Desc: Vertex format with vertices, normal, tangent and bitangent
//---------------------------------------------------------------------------
struct SVertexNormalTangentBitangent : public SVertexNormalTangent
{
	//float m_fBitangentX, m_fBitangentY, m_fBitangentZ; // Bitangents
	//CVector3 m_oBitangentVector;
	XMFLOAT3 m_oBitangentVector;

	// Default constructor
	SVertexNormalTangentBitangent()
	{
	}

	// Constructor
	SVertexNormalTangentBitangent(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector, const CVector3 &rBitangentVector)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal
		m_oNormalVector = rNormalVector;

		// Assign tangent
		m_oTangentVector = rTangentVector;

		// Assign bitangent
		m_oBitangentVector = rBitangentVector;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangentBitangentTexture2D
// Desc: Vertex format with vertices, normal, tangent, bitangent and 2D texture
//---------------------------------------------------------------------------
struct SVertexNormalTangentBitangentTexture2D : public SVertexNormalTangentBitangent
{
	//float m_fU, m_fV; // Texture coordinates
	//CVector2 m_oUV;
	XMFLOAT2 m_oUV;

	// Default constructor
	SVertexNormalTangentBitangentTexture2D()
	{
	}

	// Constructor
	SVertexNormalTangentBitangentTexture2D(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector, const CVector3 &rBitangentVector, const CVector2 &rTextureCoordinate)
	{
		// Assign vertices
		m_oVertex = rVertex;

		// Assign normal
		m_oNormalVector = rNormalVector;

		// Assign tangent
		m_oTangentVector = rTangentVector;

		// Assign bitangent
		m_oBitangentVector = rBitangentVector;

		// Assign texture coordinates
		m_oUV = rTextureCoordinate;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangentBinormal
// Desc: Vertex format with vertices, normal, tangent and binormal
//---------------------------------------------------------------------------
struct SVertexNormalTangentBinormal : public SVertexNormalTangent
{
	//float m_fBinormalX, m_fBinormalY, m_fBinormalZ; // Binormal
	//CVector3 m_oBinormalVector;
	XMFLOAT3 m_oBinormalVector;

	// Default constructor
	SVertexNormalTangentBinormal()
	{
	}

	// Constructor with vertex coordinates and normals
	SVertexNormalTangentBinormal(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector, const CVector3 &rBinormalVector)
	{
		// Assign vertex coordinate
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;

		// Assign tangent
		m_oTangentVector = rTangentVector;

		// Assign binormal
		m_oBinormalVector = rBinormalVector;
	}
};

//---------------------------------------------------------------------------
// Name: SVertexNormalTangentBinormalTexture2D
// Desc: Vertex format with vertices, normal, tangent, binormal and 2D texture
//---------------------------------------------------------------------------
struct SVertexNormalTangentBinormalTexture2D : public SVertexNormalTangentBinormal
{
	///float m_fU, m_fV; // Texture coordinates
	//CVector2 m_oUV;
	XMFLOAT2 m_oUV;

	// Default constructor
	SVertexNormalTangentBinormalTexture2D()
	{
	}

	// Constructor
	SVertexNormalTangentBinormalTexture2D(const CVector3 &rVertex, const CVector3 &rNormalVector, const CVector3 &rTangentVector, const CVector3 &rBinormalVector, const CVector2 &rTextureCoordinate)
	{
		// Assign vertex coordinate
		m_oVertex = rVertex;

		// Assign normal vector
		m_oNormalVector = rNormalVector;

		// Assign tangent
		m_oTangentVector = rTangentVector;

		// Assign binormal
		m_oBinormalVector = rBinormalVector;

		// Assign texture coordinate
		m_oUV = rTextureCoordinate;
	}

	// Constructor
	SVertexNormalTangentBinormalTexture2D(const CVector3 &rVertex, const CVector2 &rTextureCoordinate)
	{
		//const CVector3 &rNormalVector, rTangentVector, rBinormalVector;

		// Assign vertex coordinate
		m_oVertex = rVertex;

		//CMath::vectorComputeNormalTangentBinormal(rVertex, 
		
		// Assign vertex normals
		//m_fNormalX = rNormalVector.getX();
		//m_fNormalY = rNormalVector.getY();
		//m_fNormalZ = rNormalVector.getZ();

		//// Assign tangent
		//m_fTangentX = rTangentVector.getX();
		//m_fTangentY = rTangentVector.getY();
		//m_fTangentZ = rTangentVector.getZ();

		//// Assign binormal
		//m_fBinormalX = rBinormalVector.getX();
		//m_fBinormalY = rBinormalVector.getY();
		//m_fBinormalZ = rBinormalVector.getZ();

		// Assign texture coordinate
		m_oUV = rTextureCoordinate;
	}
};

#endif // VERTEXFORMAT_H