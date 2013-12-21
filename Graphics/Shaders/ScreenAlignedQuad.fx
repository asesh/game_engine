// ScreenAlign.fx: Implementation of a screen aligned quad
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

// Depth stencil state
DepthStencilState disableDepthBuffer
{
	DepthEnable = false;
};

//---------------------------------------------------------------------------
// Name: VSProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output VSProc(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	oVSOutput.m_vecPosition = mul(oVSInput.m_vecPosition, m_matHomogeneous); // Transform to view-projection space

	oVSOutput.m_fNormal = mul(float4(oVSInput.m_fNormal, 0.0f), m_matViewProjection).xyz; // Transform normal

	oVSOutput.m_fTexture = oVSInput.m_fTexture; // Pass the texture as is

	return oVSOutput;
}

//---------------------------------------------------------------------------
// Name: PSProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PSProc(SVS_Output oVSOutput) : SV_Target
{
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture); // Sample the input texture

	return fColor;
}

//
technique11 t0
{
	pass p0
	{
		SetDepthStencilState(disableDepthBuffer, 0); // Disable depth buffer

		SetVertexShader(CompileShader(vs_5_0, VSProc())); // Vertex shader
		//SetGeometryShader(NULL); // Geometry shader
		SetPixelShader(CompileShader(ps_5_0, PSProc())); // Pixel shader
	}
}