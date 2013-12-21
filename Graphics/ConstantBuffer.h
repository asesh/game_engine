// ConstantBuffer.h: Constant buffers interface
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

// Structures holding constant buffers
//

// Constant buffer that remains unchanged
struct SStaticConstantBuffer
{
	//---------------------------------------------------------------------------
	// Name: SStaticConstantBuffer
	// Desc: Default constructor
	//---------------------------------------------------------------------------
	SStaticConstantBuffer()
	{
		m_oProjectionMatrix.setIdentity();
	}

	CMatrix4x4 m_oProjectionMatrix; // Projection matrix
};

extern SStaticConstantBuffer *g_pStaticConstBuffer;

// Constant buffer that changes every frame
struct SChangesEveryFrameConstantBuffer
{
	//---------------------------------------------------------------------------
	// Name: SChangesEveryFrameConstantBuffer
	// Desc: Default constructor
	//---------------------------------------------------------------------------
	SChangesEveryFrameConstantBuffer()
	{
		m_oWorldMatrix.setIdentity();
		m_oInverseTransposeWorldMatrix.setIdentity();
		m_oViewMatrix.setIdentity();
		m_oViewProjectionMatrix.setIdentity();
		m_oHomogeneousMatrix.setIdentity();
	}

	//---------------------------------------------------------------------------
	// Name: buildTransformationMatrices
	// Desc: Build the transformation matrices including view-projection matrix
	//		 and homogeneous matrix
	//---------------------------------------------------------------------------
	void buildTransformationMatrices()
	{
		//m_oXMViewMatrix = ::XMMatrixTranspose(g_pCamera->getViewMatrix()); // View transformation matrix
		//m_oXMHomogeneousMatrix = m_oXMWorldMatrix * m_oXMViewMatrix * ::XMMatrixTranspose(g_pCamera->getProjectionMatrix()); // Calculate homogeneous transformation matrix
		m_oInverseTransposeWorldMatrix = m_oWorldMatrix.getInverseTranspose(); // Inverse transpose of world matrix
		m_oViewMatrix = g_pCamera->getViewMatrix(); // View transformation matrix
		m_oViewProjectionMatrix = m_oViewMatrix * g_pCamera->getProjectionMatrix(); // Build view-projection transformation matrix
		m_oHomogeneousMatrix = m_oWorldMatrix * m_oViewMatrix * g_pCamera->getProjectionMatrix(); // Build homogeneous transformation matrix
		m_oHomogeneousMatrix.setTranspose();
	}

	CMatrix4x4 m_oWorldMatrix; // World matrix
	CMatrix4x4 m_oInverseTransposeWorldMatrix; // Inverse transpose of world matrix
	CMatrix4x4 m_oViewMatrix; // View matrix
	CMatrix4x4 m_oViewProjectionMatrix; // View-projection matrix
	CMatrix4x4 m_oHomogeneousMatrix; // Homogeneous matrix
};

extern SChangesEveryFrameConstantBuffer *g_pChangesEveryFrameConstBuffer;

// Constant buffers for materials
struct SMaterialConstantBuffer
{
	CVector4 m_oAmbientMaterialColor;
};

//
// Structures holding constant buffers

#endif // CONSTANTBUFFER_H
