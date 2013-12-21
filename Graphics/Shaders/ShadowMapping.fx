// ShadowMapping.fx: Implementation of shadow mapping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

// Constant buffers used for shadow mapping
shared cbuffer CBShadowMap
{
	vector m_vecLight; // Light's position vector
};

// Vertex shader procedure
SVS_Output VS_Shadow_Mapping_Proc(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	return oVSOutput;
}

// Pixel shader procedure
SPSOutput PS_Shadow_Mapping_Proc(SVS_Output oVSOutput)
{
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture); // Sample the texture

	return fColor;
}

technique t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_Shadow_Mapping_Proc());
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS_Shadow_Mapping_Proc());
	}
}