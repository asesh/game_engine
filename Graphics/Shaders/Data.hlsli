// Data.hlsli: Includes all the input/output data types of vertex/pixel/geometry shader and constant buffers
// Copyright (C) 2011-2013 Asesh Shrestha. All rights reserved

#ifndef DATA_HLSLI
#define DATA_HLSLI

#include "ConstantBuffers.hlsli"

// Instancing
//

// Vertex shader instanced input structure
struct SVS_Instance_Input
{
	vector m_vecPosition : POSITION; // Position
	float3 m_fNormal : NORMAL; // Normal
	float2 m_fTexture : TEXCOORD0; // Texture
	//float3 m_fInstancePosition : TEXCOORD1; // Instance position
	//float4 m_fColor : COLOR; // Color
	//matrix m_matInstanceTransformation : mTransform; // Matrix
	uint m_uiVertexID : SV_VertexID; // Vertex ID
	uint m_uiInstanceID : SV_InstanceID; // Instance ID
};

// 
// Instancing

// Generic vertex shader input structure
struct SVS_Input
{
	vector m_vecPosition : POSITION; // Homogeneous position
	float3 m_fNormal : NORMAL; // Normal
	float2 m_fTexture : TEXCOORD0; // Texture
	//float4 m_fAmbientColor : COLOR0; // Ambient color
	//float4 m_fDiffuseColor : COLOR1; // Diffuse color
	//uint m_uiVertexID : SV_VertexID; // Vertex ID
};

// Vertex shader input structure for vertex normal
struct SVS_Vertex_Normal_Input
{
	vector m_vecPosition : POSITION; // Object space vertex position
};

// Normal mapping
//

// Normal mapping vertex shader input structure
struct SVS_NormalMap_Input
{
	vector m_vecPosition : POSITION; // Position
	float3 m_fNormal : NORMAL; // Normal
	float2 m_fTexture : TEXCOORD0; // Texture
	float3 m_fTangent : TANGENT; // Tangent
	float3 m_fBitangent : BITANGENT; // Bitangent
};

// Normal mapping vertex shader output structure
struct SVS_NormalMap_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
	float3 m_fNormal : NORMAL; // Normal
	float2 m_fTexture : TEXCOORD0; // Texture
	float3 m_fTangent : TANGENT; // Tangent
	float3 m_fBitangent : BITANGENT; // Bitangent
};

//
// End Normal mapping

// Cube mapping
//

// Cube mapping vertex shader output
struct SVS_CubeMap_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
	float3 m_fCubeTexture : TEXCOORD; // Cube texture
};

// Cube mapping vertex shader input
struct SVS_CubeMap_Input
{
	vector m_vecPosition : POSITION; // Vertex position in object space
	float3 m_fCubeTexture : TEXCOORD; // Cube texture
	float3 m_fNormal : NORMAL; // Normal of cubemap
};

// 
// End cube mapping

// Generic vertex shader output structure
struct SVS_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
	float2 m_fTexture : TEXCOORD0; // Texture
	float3 m_fNormal : TEXCOORD1; // Normal
	float4 m_fMaterialColor : TEXCOORD2; // Material color
};

// Vertex shader output for vertex normals
struct SVS_Vertex_Normal_Output
{
	vector m_vecPosition : SV_Position; // Vertex position
};

// Pixel shader output structure
struct SPS_Output
{
	float4 m_fColor : SV_Target;
	float m_fDepth : SV_Depth;
};

// Specular lighting
//

// Specular lighting vertex shader input
struct SVS_SpecularLight_Input
{
	vector m_vecPosition : POSITION; // Vertex position in object space
	float2 m_fTexture : TEXCOORD0; // Texture
};

// Specular lighting vertex shader output
struct SVS_SpecularLight_Output
{
	vector m_vecPosition : SV_Position; // Vertex position in homogeneous space
};

//
// End specular lighting

#endif // DATA_HLSLI