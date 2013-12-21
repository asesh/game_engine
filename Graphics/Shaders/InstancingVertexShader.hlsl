// InstancingVertexShader.hlsl: Implementation of vertex shader for instancing
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

// Vertex shader procedure
SVS_Output main(SVS_Instance_Input oVSInstanceInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	//oVSOutput.m_vecPosition = mul(oVSInstanceInput.m_vecPosition, m_matHomogeneous); // Transform vertex to homogeneous space.

	oVSInstanceInput.m_vecPosition += vector(m_vecInstancePosition.x + oVSInstanceInput.m_uiInstanceID * 2.0f, m_vecInstancePosition.yz, 1.0f); // Assign instance position

	oVSOutput.m_vecPosition = mul(oVSInstanceInput.m_vecPosition, m_matHomogeneous); // Transform by the specified matrix
	//oVSOutput.m_vecPosition.xyzw += float4(oVSInstanceInput.m_matTransformation._41, oVSInstanceInput.m_matTransformation._42, oVSInstanceInput.m_matTransformation._43, oVSInstanceInput.m_matTransformation._44); // Transform by the specified matrix

	oVSOutput.m_fNormal = normalize(mul(float4(oVSInstanceInput.m_fNormal, 0.0f), m_matInverseTransposeWorld)).xyz; // Transform normal and normalize it

	oVSOutput.m_fTexture = oVSInstanceInput.m_fTexture; // Pass the texture as is

	//oVSOutput.m_fMaterialColor = float4(1.0f, 1.0f, 1.0f, 1.0f); // Color

	return oVSOutput;
}