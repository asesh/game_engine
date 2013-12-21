// ConstantBuffers.hlsli: Declaration of constant buffers
// Copyright (C) 2012-2013 Asesh Shrestha. All rights reserved

#ifndef CONSTANTBUFFERS_HLSLI
#define CONSTANTBUFFERS_HLSLI

// Constant buffer that changes every frame
cbuffer CBEveryFrame
{
	matrix m_matWorld; // World matrix
	matrix m_matInverseTransposeWorld; // Inverse transpose of world matrix
	matrix m_matView; // View matrix
	matrix m_matViewProjection; // View-projection matrix
	matrix m_matHomogeneous; // Homogeneous matrix
};

// Constant buffer that's static
shared cbuffer CBStatic
{
	row_major matrix m_matProjection; // Projection matrix
};

// Constant buffer for ambient materials
cbuffer CBAmbientMaterial
{
	float4 m_fAmbientMaterialColor; // Ambient material color
	float4 m_fAmbientLightColor; // Ambient light color
};

// Constant buffer for diffuse materials
cbuffer CBDiffuseMaterial
{
	float4 m_fDiffuseMaterialColor; // Diffuse material color
	float4 m_fDiffuseLightColor; // Diffuse light color
};

// Constant buffer for shiny materials
cbuffer CBSpecularMaterial
{
	float4 m_fSpecularMaterialColor; // Specular material color
	float4 m_fSpecularLightColor; // Specular light color
	float m_fSpecularPower; // Specular power
};

// Constant buffer holding position for each instances
cbuffer CBInstancePosition
{
	vector m_vecInstancePosition; // Position of each instance
};

// Constant buffer holding position and color for each instances
cbuffer CBInstancePositionColor
{
	///vector m_vecInstancePosition; // Position of each instance
	float4 m_fInstanceColor; // Color for each instance
};

// Constant buffer holding position, texure and color for each instances
cbuffer CBInstancePositionColorTexture
{
	//vector m_vecInstancePosition; // Position of each instance
	float2 m_fTexture; // Texture for each instance
	//float4 m_fInstanceColor; // Color for each instance
};

// Constant buffer for lights
cbuffer CBLight
{
	float3 m_fLightPosition = float3(10.0f, 50.0f, -10.0f); // Light position
};

#endif // CONSTANTBUFFERS_HLSLI