// CumbeMapping.fx: Implementation of cube mapping
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "Data.fx"

TextureCube g_texCubeMap;

// Rasterizer state
RasterizerState CubeMapRasterizeState
{
	//FillMode = Solid;
	CullMode = None; // Disable culling when rendering our cubemap
};

// Depth-stencil state
DepthStencilState CubeMapDepthStencilState
{
	DepthEnable = true;
	DepthWriteMask = All;
	DepthFunc = LESS_EQUAL;
};

//---------------------------------------------------------------------------
// Name: VSDiffuseLightingProc
// Desc: Vertex shader procedure
//---------------------------------------------------------------------------
SVS_CubeMap_Output VS_CubeMap(SVS_CubeMap_Input oVSInput)
{
	SVS_CubeMap_Output oVSCubeMapOutput = (SVS_CubeMap_Output) 0;

	oVSCubeMapOutput.m_vecPosition = mul(oVSInput.m_vecPosition, m_matHomogeneous).xyww; // Set the depth value to be always farthest from the camera

	oVSCubeMapOutput.m_fCubeTexture = oVSInput.m_fCubeTexture;

	return oVSCubeMapOutput;
}

//---------------------------------------------------------------------------
// Name: PS_CubeMap
// Desc: Pixel shader procedure
//---------------------------------------------------------------------------
float4 PS_CubeMap(SVS_CubeMap_Output oVSOutput) : SV_Target
{
	return g_texCubeMap.Sample(g_samType, oVSOutput.m_fCubeTexture);
}

technique11 t0
{
	pass p0
	{
		SetRasterizerState(CubeMapRasterizeState); // Set cubemap's rasterizer state
		SetDepthStencilState(CubeMapDepthStencilState, 0); // Set cubemap's depth-stencil state

		SetVertexShader(CompileShader(vs_5_0, VS_CubeMap())); // Vertex shader
		SetPixelShader(CompileShader(ps_5_0, PS_CubeMap())); // Pixel shader
	}
}