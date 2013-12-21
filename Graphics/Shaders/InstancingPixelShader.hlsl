// InstancingPixelShader.hlsl: Implementation of pixel shader for instancing
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

// Pixel shader procedure
float4 main(SVS_Output oVSOutput) : SV_Target
{
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture); // Sample

	return fColor;
}