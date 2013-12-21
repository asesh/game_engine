// DiffuseLighting.fx: Implementation of ambient-diffuse lighting
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

//---------------------------------------------------------------------------
// Name: VSDiffuseLightingProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output VSDiffuseLightingProc(SVS_Input oVSInput)
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

//---------------------------------------------------------------------------
// Name: GSDiffuseLightingProc
// Desc: Geometry shader procedure
//---------------------------------------------------------------------------
[maxvertexcount(3)]
void GSDiffuseLightingProc(triangle SVS_Output oInput[3], inout TriangleStream<SVS_Output> triOutputStream)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	// Loop to read the input triangle data
	for(uint uiCount = 0; uiCount < 3; uiCount++)
	{
		// Pass the input data as is
		oVSOutput.m_vecPosition = oInput[uiCount].m_vecPosition; // Position
		oVSOutput.m_fNormal = oInput[uiCount].m_fNormal; // Normal
		oVSOutput.m_fTexture = oInput[uiCount].m_fTexture; // Texture
		oVSOutput.m_fMaterialColor = oInput[uiCount].m_fMaterialColor; // Material color

		triOutputStream.Append(oVSOutput); // Append output data to an existing stream
	}

	triOutputStream.RestartStrip(); // End the current primitive strip
}

//---------------------------------------------------------------------------
// Name: PSDiffuseLightingProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PSDiffuseLightingProc(SVS_Output oVSOutput) : SV_Target
{
	//m_fLightPosition = -m_fLightPosition; // Invert the light direction

	float fSaturatedValue = saturate(dot(oVSOutput.m_fNormal, -m_fLightPosition));

	// Sample the texture
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture);// * oVSOutput.m_fMaterialColor;// * fSaturatedValue;

	return fColor;
}

technique11 t0
{
	pass p0 // Diffuse lighting pass for materials
	{
		SetVertexShader(CompileShader(vs_5_0, VSDiffuseLightingProc())); // Vertex shader for materials
		SetGeometryShader(CompileShader(gs_5_0, GSDiffuseLightingProc())); // Geometry shader
		SetPixelShader(CompileShader(ps_5_0, PSDiffuseLightingProc())); // Pixel shader
	}
};
