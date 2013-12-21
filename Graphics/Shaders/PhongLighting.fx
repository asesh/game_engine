// Implementation of phong lighting
//

// Constant buffer that changes every frame
cbuffer CBChangesEveryFrame
{
	matrix m_matView, m_matWorld, m_matHomogeneous;
};

// Constant buffers that never changes
cbuffer CBNeverChanges
{
	matrix m_matProjection; // Projection matrix
};

Texture2D g_texPrimitive; // Primitive's texture
SamplerState g_samPrimitiveTexture; // Sampler state for primitive's texture

// Vertex shader input structure
struct SVS_Input
{
	vector m_vecPosition : POSITION; // Vertex position
	vector m_vecNormal : NORMAL; // Normal
	float2 m_fTexture : TEXCOOORD0; // Texture
};

// Vertex shader output structure
struct SVS_Output
{
	vector m_vecPosition : SV_Position; // Vertex position
	vector m_vecNormal : TEXCOORD1; // Normal
	float2 m_fTexture : TEXCOORD0; // Texture
};

//---------------------------------------------------------------------------
// Name: VSProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_Output VSProc(SVS_Input oVSInput)
{
	SVS_Output oVSOutput = (SVS_Output) 0;

	oVSOutput.m_vecPosition = mul(oVSInput.m_vecPosition, m_matHomogeneous); // Transform vertex to homogeneous clip space

	oVSOutput.m_vecNormal = normalize(mul(oVSInput.m_vecNormal, m_matWorld)); // Transform normal to world space and normalize it

	oVSOutput.m_fTexture = oVSInput.m_fTexture; // Pass the texture coordinates as is

	return oVSOutput;
}

//---------------------------------------------------------------------------
// Name: PSProc
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PSProc(SVS_Output oVSOutput) : SV_Target
{
	float4 fColor = g_texPrimitive.Sample(g_samPrimitiveTexture, oVSOutput.m_fTexture);

	return fColor;
}

//
technique11 t0
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_5_0, VSProc()));
		SetPixelShader(CompileShader(ps_5_0, PSProc()));
	}
}