// MotionBlur.fx: Effect for motion blur
// Copyright (C) 2011 Asesh Shrestha. All rights reserved

uniform matrix g_matWorld, g_matView, g_matHomo;

// SVS_Input structure
struct SVS_Input
{
	vector m_vecPosition : SV_Position; // Vertex position in object space
	float2 m_fTexCoord : TEXCOORD0; // 
};

// SVS_Output structure
struct SVS_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
	float2 m_fTexCoord : TEXCOORD0; // 
};

//---------------------------------------------------------------------------
// Name: vertexShader
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output vertexShader(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	return oVSOutput;
}

//---------------------------------------------------------------------------
// Name: pixelShader
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 pixelShader(SVS_Output oVSOutput) : SV_Target
{
	float fPixelColor;

	return fPixelColor;
}

technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, vertexShader()));
		SetPixelShader(CompileShader(ps_5_0, pixelShader()));
	}
}