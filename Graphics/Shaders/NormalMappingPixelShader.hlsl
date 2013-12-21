// NormalMappingPixelShader.hlsl: Implementation of pixel shader normal mapping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

Texture2D g_texPrimitive[2]; // Primitive's texture and it's corresponding normal map
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: main
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 main(SVS_NormalMap_Output oNormalMapOutput) : SV_Target
{
	float4 fTextureColor = g_texPrimitive[0].Sample(g_samPrimitiveTexture, oNormalMapOutput.m_fTexture); // Sample geometry's texture

	float4 fNormalMapTextureColor = g_texPrimitive[1].Sample(g_samPrimitiveTexture, oNormalMapOutput.m_fTexture); // Sample normal map texture

	fNormalMapTextureColor = (fNormalMapTextureColor * 2.0f) - 1.0f; // Move it into signed normalized range since it will be in unsigned normalized range

	// Calculate the normal map value from the data
	float3 fNormal = normalize(oNormalMapOutput.m_fNormal + fNormalMapTextureColor.x * oNormalMapOutput.m_fTangent + fNormalMapTextureColor.y * oNormalMapOutput.m_fBitangent);

	//m_fLightPosition = -normalize(m_fLightPosition); // Normalize and invert the light position

	//m_fLightPosition = float3(10.0f, 50.0f, -10.0f); // Light position

	float3 fLightVector = normalize(-float3(10.0f, 50.0f, 5.0f)); // Light vector

	float fUnsaturatedLightIntensity = dot(fNormal, fLightVector); // Calculate light intensity

	float fLightIntensity = saturate(fUnsaturatedLightIntensity); // Calculate light intensity on this pixel based on normal map value

	float3 fAmbientColor = float3(0.2f, 0.3f, 0.1f); // Ambient color

	float4 fDiffuseColor = saturate(float4(0.5f, 0.3f, 0.2f, 1.0f) * fLightIntensity); // Diffuse color

	float4 fPixelColor = float4(fAmbientColor, 0.0f) + (fDiffuseColor * fNormalMapTextureColor); // Final pixel color

	return fPixelColor;
}