// SpecularLightingPixelShader.hlsl: Implementation of pixel shader for specular lighting
// Copyright (C) 2013 Asesh Shrestha. All rights reserved

#include "Data.hlsli"

//---------------------------------------------------------------------------
// Name: main
// Desc: Specular lighting pixel shader
//---------------------------------------------------------------------------
float4 main(SVS_SpecularLight_Output oSpecularLightOutput) : SV_Target
{
	float4 fPixelColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

	return fPixelColor;
}