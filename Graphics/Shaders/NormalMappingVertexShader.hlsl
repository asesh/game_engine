// NormalMappingVertexShader.fx: Implementation of vertex shader for normal mapping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

//---------------------------------------------------------------------------
// Name: main
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_NormalMap_Output main(SVS_NormalMap_Input oNormalMapInput)
{
	SVS_NormalMap_Output oNormalMapOutput = (SVS_NormalMap_Output) 0;

	oNormalMapOutput.m_vecPosition = mul(oNormalMapInput.m_vecPosition, m_matHomogeneous); // Transform vertex to homogeneous space

	oNormalMapOutput.m_fNormal = normalize(mul(float4(oNormalMapInput.m_fNormal, 0.0f), m_matInverseTransposeWorld)).xyz; // Transform normal to world space

	oNormalMapOutput.m_fTexture = oNormalMapInput.m_fTexture; // Pass the texture coordinate as is

	oNormalMapOutput.m_fBitangent = normalize(mul(float4(oNormalMapInput.m_fBitangent, 0.0f), m_matInverseTransposeWorld).xyz); // Transform bitangent

	oNormalMapOutput.m_fTangent = normalize(mul(float4(oNormalMapInput.m_fTangent, 0.0f), m_matInverseTransposeWorld).xyz); // Transform tangent

	return oNormalMapOutput;
};