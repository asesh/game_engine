// Instancing.fx: Implementation of instancing
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

// Vertex shader procedure
SVS_Output VS_Instance_Proc(SVS_Instance_Input oVSInstanceInput)
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

// Pixel shader procedure
float4 PS_Instance_Proc(SVS_Output oVSOutput) : SV_Target
{
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture); // Sample

	return fColor;
}

// Technique
technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Instance_Proc())); // Vertex shader
		SetGeometryShader(NULL); // Geometry shader
		SetPixelShader(CompileShader(ps_5_0, PS_Instance_Proc())); // Pixel shader
	}
}