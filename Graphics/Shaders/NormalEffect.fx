// Normal.fx: Implementation to draw vertex normal
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: VS_Vertex_Normal
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Vertex_Normal_Output VS_Vertex_Normal(SVS_Vertex_Normal_Input oVSVertexNormalInput)
{
	SVS_Vertex_Normal_Output oVSVertexNormalOutput = (SVS_Vertex_Normal_Output) 0; // Zero out vertex normal output structure

	oVSVertexNormalOutput.m_vecPosition = normalize(mul(oVSVertexNormalInput.m_vecPosition, m_matHomogeneous)); // Transform and normalize the vertex to homogeneous space

	return oVSVertexNormalOutput;
}

//---------------------------------------------------------------------------
// Name: PS_Vertex_Normal
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PS_Vertex_Normal() : SV_Target
{
	return float4(0.0f, 0.0f, 1.0f, 1.0f); // Return the color of vertex normal pixel
}

// Technique
technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Vertex_Normal())); // Vertex shader
		SetPixelShader(CompileShader(ps_5_0, PS_Vertex_Normal())); // Pixel shader
	}
};