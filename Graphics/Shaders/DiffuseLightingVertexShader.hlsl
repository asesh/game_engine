// DiffuseLightingVertexShader.hlsl: Vertex shader for diffuse lighting
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

//---------------------------------------------------------------------------
// Name: VSDiffuseLightingProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output main(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0; // Zero out the vertex shader output structure

	// Transform vertex position to world space
	float4 fWorldPosition = mul(oVSInput.m_vecPosition, m_matWorld);

	// Transform the vertex position to homogeneous clipping space
	oVSOutput.m_vecPosition = mul(oVSInput.m_vecPosition, m_matHomogeneous);

	// Transform the normal and normalize it
	oVSOutput.m_fNormal = normalize(mul(float4(oVSInput.m_fNormal, 0.0f), m_matInverseTransposeWorld)).xyz;

	float3 fAmbient = m_fAmbientMaterialColor.xyz * m_fAmbientLightColor.xyz; // Compute ambient color

	float3 fDiffuse = max(dot(oVSInput.m_fNormal, -m_fLightPosition), 0.0f) * (m_fDiffuseMaterialColor * m_fDiffuseLightColor).rgb; // Implementation of diffuse lighting

	oVSOutput.m_fMaterialColor.rgb = fAmbient + fDiffuse; // Implementation of ambient-diffuse lighting
	oVSOutput.m_fMaterialColor.a = m_fDiffuseMaterialColor.a; // Copy the material's alpha component as-is

	// Pass out the texture coordinates as is
	oVSOutput.m_fTexture = oVSInput.m_fTexture;

	return oVSOutput; // Return the vertex shader output
}