// GlobalIllumination.fx: Implementation of global lighting effect
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: VSProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output VSProc(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0; // Zero out the vertex shader output structure

	// Transform the vertex position to homogeneous clipping space
	oVSOutput.m_vecPosition = mul(oVSInput.m_vecPosition, m_matHomogeneous);

	// Transform the normals to world space
	oVSOutput.m_fNormal = normalize(mul(float4(oVSInput.m_fNormal, 0.0f), m_matInverseTransposeWorld)).xyz;

	// Pass out the texture coordinates as is
	oVSOutput.m_fTexture = oVSInput.m_fTexture;

	return oVSOutput; // Return the vertex shader output
}

//---------------------------------------------------------------------------
// Name: PSProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PSProc(SVS_Output oVSOutput) : SV_Target
{
	// Sample the texture
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture);

	return fColor;
}

technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VSProc())); // Vertex shader
		SetPixelShader(CompileShader(ps_5_0, PSProc())); // Pixel shader
	}
};
