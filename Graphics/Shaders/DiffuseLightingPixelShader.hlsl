// DiffuseLightingPixelShader.hlsl: Pixel shader for diffuse lighting
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: PSDiffuseLightingProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 main(SVS_Output oVSOutput) : SV_Target
{
	//m_fLightPosition = -m_fLightPosition; // Invert the light direction

	float fSaturatedValue = saturate(dot(oVSOutput.m_fNormal, -m_fLightPosition));

	// Sample the texture
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture);// * oVSOutput.m_fMaterialColor;// * fSaturatedValue;

	return fColor;
}