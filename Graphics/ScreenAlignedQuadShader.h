// ScreenAlignedQuadShader.h: Interface of 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef SCREENALIGNEDQUADSHADER_H
#define SCREENALIGNEDQUADSHADER_H

#include "Shader.h"

// CScreenAlignedQuadShader class
class CScreenAlignedQuadShader : public CShader
{
public:
	CScreenAlignedQuadShader(); // Default constructor
	~CScreenAlignedQuadShader(); // Destructor

	//HRESULT updateConstantBuffers(SInstanceConstantBuffer *pInstanceConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext);
	HRESULT updateInstanceConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext);

private:
};

#endif // SCREENALIGNEDQUADSHADER_H