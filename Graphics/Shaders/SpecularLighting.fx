// SpecularLighting.fx: 
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

// Constant buffer that changes every frame
cbuffer CBEveryFrame
{
	matrix m_matWorld, m_matView, m_matHomogeneous;
};

// Constant buffer that never changes
cbuffer CBNeverChanges
{
	matrix m_matProj;
};

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

vector g_vecLight;

float4 g_fLightDirection; // Will hold the light direction

// Vertex shader input structure
struct SVS_Input
{
	vector m_vecPosition : POSITION; // Vertex position in object space
	vector m_vecNormal : NORMAL0; // Normal vector
	float2 m_fTexture : TEXCOORD0; // Texture
	float4 m_fDiffuseColor : COLOR0; // Diffuse color
};

// Vertex shader output structure
struct SVS_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
	vector m_vecNormal : TEXCOORD1; // Normal
	float4 m_fDiffuseColor : TEXCOORD2; // Diffuse color
	float2 m_fTexture : TEXCOORD0; // Texture
};

// Pixel shader output
struct SPSOutput
{
	float4 m_fColor : SV_Target; // Color
	//float m_fDepthData : SV_Depth; // Depth buffer data
};

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
	oVSOutput.m_vecNormal = normalize(mul(oVSInput.m_vecNormal, m_matWorld));

	oVSOutput.m_fDiffuseColor = float4(1.0f, 1.0f, 1.0f, 0.0f); //oVSInput.m_fDiffuseColor; // Pass the diffuse color as is

	// Pass out the texture coordinates as is
	oVSOutput.m_fTexture = oVSInput.m_fTexture;

	return oVSOutput; // Return the vertex shader output
}

//---------------------------------------------------------------------------
// Name: GSProc
// Desc: Geometry shader procedure
//---------------------------------------------------------------------------
[maxvertexcount(3)]
void GSProc(triangle SVS_Output oInput[3], inout TriangleStream<SVS_Output> triOutputStream)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	for(uint uiCount = 0; uiCount < 3; uiCount++)
	{
		oVSOutput.m_vecPosition = oInput[uiCount].m_vecPosition;
		oVSOutput.m_vecNormal = oInput[uiCount].m_vecNormal;
		oVSOutput.m_fTexture = oInput[uiCount].m_fTexture;
		oVSOutput.m_fDiffuseColor = oInput[uiCount].m_fDiffuseColor;

		triOutputStream.Append(oVSOutput);
	}

	triOutputStream.RestartStrip();
}

//---------------------------------------------------------------------------
// Name: PSProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
SPSOutput PSProc(SVS_Output oVSOutput)
{
	SPSOutput oPSOutput = (SPSOutput) 0;

	// 2D texture lookup
	if(primitiveTextureSampler != 0)
		oPSOutput.m_fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture) * oVSOutput.m_fDiffuseColor;

	//oPSOutput.m_fDepthData = oPSOutput.m_fDepthData;

	return oPSOutput;
}

technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VSProc())); // Vertex shader
		//SetGeometryShader(CompileShader(gs_5_0, GSProc())); // Geometry shader
		SetPixelShader(CompileShader(ps_5_0, PSProc())); // Pixel shader
	}
};
