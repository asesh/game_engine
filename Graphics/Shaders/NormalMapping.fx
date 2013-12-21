// NormalMapping.fx: Implementation of normal mapping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

//Texture2D g_texPrimitive[2]; // Primitive's texture and it's corresponding normal map
Texture2D g_texPrimitive, g_texNormalMap; // ""
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: VS_NormalMap_Proc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_NormalMap_Output VS_NormalMap_Proc(SVS_NormalMap_Input oNormalMapInput)
{
	SVS_NormalMap_Output oNormalMapOutput = (SVS_NormalMap_Output) 0;

	oNormalMapOutput.m_vecPosition = mul(oNormalMapInput.m_vecPosition, m_matHomogeneous); // Transform vertex to homogeneous space

	oNormalMapOutput.m_fNormal = normalize(mul(float4(oNormalMapInput.m_fNormal, 0.0f), m_matInverseTransposeWorld)).xyz; // Transform normal to world space

	oNormalMapOutput.m_fTexture = oNormalMapInput.m_fTexture; // Pass the texture coordinate as is

	oNormalMapOutput.m_fBinormal = normalize(mul(float4(oNormalMapInput.m_fBinormal, 0.0f), m_matInverseTransposeWorld).xyz); // Transform binormal

	oNormalMapOutput.m_fTangent = normalize(mul(float4(oNormalMapInput.m_fTangent, 0.0f), m_matInverseTransposeWorld).xyz); // Transform tangent

	return oNormalMapOutput;
};

//---------------------------------------------------------------------------
// Name: PS_NormalMap_Proc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PS_NormalMap_Proc(SVS_NormalMap_Output oNormalMapOutput) : SV_Target
{
	float4 fTextureColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oNormalMapOutput.m_fTexture); // Sample geometry's texture

	float4 fNormalMapTextureColor = g_texNormalMap.Sample(g_samPrimitiveTexture, oNormalMapOutput.m_fTexture); // Sample normal map texture

	fNormalMapTextureColor = (fNormalMapTextureColor * 2.0f) - 1.0f; // Move it into signed normalized range since it will be in unsigned normalized range

	// Calculate the normal map value from the data
	float3 fNormal = normalize(oNormalMapOutput.m_fNormal + fNormalMapTextureColor.x * oNormalMapOutput.m_fTangent + fNormalMapTextureColor.y * oNormalMapOutput.m_fBinormal);

	//m_fLightPosition = -normalize(m_fLightPosition); // Normalize and invert the light position

	float fLightIntensity = saturate(dot(fNormal, -m_fLightPosition)); // Calculate light intensity on this pixel based on normal map value

	float4 fDiffuseColor = saturate(float4(0.5f, 0.3f, 0.2f, 1.0f) * fLightIntensity); // Diffuse color

	float4 fPixelColor = fDiffuseColor * fNormalMapTextureColor; // Final pixel color

	return fPixelColor;
}

technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VS_NormalMap_Proc())); // Vertex shader
		SetGeometryShader(NULL); // Geometry shader
		SetPixelShader(CompileShader(ps_5_0, PS_NormalMap_Proc())); // Pixel shader
	}
}