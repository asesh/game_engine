// Effect implementation
//

// Global variables

float2 g_fFogDepth; // Fog depth values

float g_fSunPixelIntensity; // Intesity of the pixel to render the sun 

// Transformation matrices
shared matrix g_matWorld, g_matView, g_matProjection; // World, view and projection transformation matrices
shared matrix g_matHomogeneous; // Homogeneous matrix

// Samplers
sampler g_samTexture = sampler_state
{
	MinFilter = Linear; // Minification filter
	MagFilter = Linear; // Magnification filter
	MipFilter = Linear; // Mip fitler
};

sampler g_samSunTexture = sampler_state
{
	MinFilter = Linear; // Minification filter
	MagFilter = Linear; // Magnification filter
};

samplerCUBE g_samCubeTexture = sampler_state
{
	MinFilter = Linear; // Minification filter
	MagFilter = Linear; // Magnification filter
};

//-------------------------------------------------------------
// Name: SVS_Output
// Desc: Vertex shader output structure
//-------------------------------------------------------------
struct SVS_Output
{
	// vector m_vecDiffuse : COLOR0; // Diffuse color
	vector m_vecPosition : POSITION; // Vertex position in homogeneous space
	float2 m_fTexCoord : TEXCOORD0; // Texture coordinate
	float3 m_fNormal : TEXCOORD1; // Normal vector
};

//-------------------------------------------------------------
// Name: SVS_Input
// Desc: Vetex shader input structure
//-------------------------------------------------------------
struct SVS_Input
{
	vector m_vecPosition : POSITION0; // Vertex position in object space
	//vector m_vecDiffue : COLOR0; // Diffuse color
	float2 m_fTexCoord : TEXCOORD0; // Texture coordinate
	float3 m_fNormal : NORMAL0; // Normal vector
};

//-------------------------------------------------------------
// Name: SPSOutput
// Desc: Pixel shader output structure
//-------------------------------------------------------------
struct SPSOutput
{
	vector m_vecOutputColor : COLOR0; // Output color
};

//-------------------------------------------------------------
// Name: transformGeometry
// Desc: Vertex shader procedure for transforming geometry
//-------------------------------------------------------------
SVS_Output transformGeometry(SVS_Input vsinput)
{
	SVS_Output vsoutput = (SVS_Output) 0;

	// Transform vertices to homogeneous clip space
	vsoutput.m_vecPosition = mul(vsinput.m_vecPosition, g_matHomogeneous);

	// Assign the input texture coordinate to the pixel shader
	vsoutput.m_fTexCoord = vsinput.m_fTexCoord;
	
	// Transform the normal from object space to world space
	vsoutput.m_fNormal = normalize(mul(vsinput.m_fNormal, (float3x3) g_matWorld));

	return vsoutput;
}

//-------------------------------------------------------------
// Name: sampleSun
// Desc: Sample the sun texture and apply effects to it
//-------------------------------------------------------------
float4 sampleSun(float2 fTexCoord : TEXCOORD0) : COLOR
{
	// 2D texture lookup on the sun texture
	float4 fSunTexture = tex2D(g_samSunTexture, fTexCoord);

	// Increase or decrease the intensity of the pixel based on the input
	// If the value of input pixel intesity is less than 0.0f then it's negative
	// so we decrease the intensity of the output pixel color
	if(g_fSunPixelIntensity < 0.0f)
		fSunTexture -= g_fSunPixelIntensity;

	// A positive value has been input so we increase the intensity of the output
	// pixel color
	else
		fSunTexture += g_fSunPixelIntensity;
		
	return fSunTexture; // Return the result
}		

//-------------------------------------------------------------
// Name: sampleSkyCube
// Desc: Pixel shader procedure for sampling a 3D cube texture
//-------------------------------------------------------------
float4 sampleSkyCube(float3 fTexCoord : TEXCOORD0) : COLOR
{
	//SPSOutput psoutput = (SPSOutput) 0;

	// Cube texture lookup
	float4 fDiffuseColor = texCUBE(g_samTexture, fTexCoord);

	return fDiffuseColor;
}

//-------------------------------------------------------------
// Name: textureMesh
// Desc: Pixel shader procedure
//-------------------------------------------------------------
float4 textureMesh(float2 fTexCoord : TEXCOORD0) : COLOR
{
	SPSOutput psoutput = (SPSOutput) 0;

	// 2D texture lookup
	psoutput.m_vecOutputColor = tex2D(g_samTexture, fTexCoord);

	// Increase the intensity of the pixel
	//psoutput.m_vecOutputColor += 0.1f;

	return psoutput.m_vecOutputColor;
}

//-------------------------------------------------------------
// Name: linearFogEffect
// Desc: Apply custom linear for effect
//-------------------------------------------------------------
void linearFogEffect()
{
	//float fFogEnd = fFog.x;
	//float fFogStart = fFog.y;
}

// Technique basicEffect
technique basicEffect
{
	pass p0
	{

		//PixelShader = compile ps_2_0 textureMesh(); // Pixel shader

		//VertexShader = compile vs_2_0 transformGeometry(); // Vertex shader

		// Texture addressing modes
		//AddressU[0] = Wrap; // U-coordinate
		//AddressV[0] = Wrap; // V-coordinate

		// Miscellaneous render states
		//FillMode = WireFrame; // Set fillmode to solid
		//Ambient = 0xFFFFFFFF; // Ambient lighting color
		//Lighting = false; // Disable Direct3D lighting
		//ZWriteEnable = false; // Disable writes to the z-buffer
		//ZEnable = false; // Disable z-buffering
	}
}

// Technique sun
technique sun
{
	pass p0
	{

		VertexShader = compile vs_2_0 transformGeometry(); // Vertex shader

		PixelShader = compile ps_2_0 sampleSun(); // Pixel shader
	}
}
