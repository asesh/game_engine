// SpecularLightShader.h: Interface of specular light
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef SPECULARLIGHTSHADER_H
#define SPECULARLIGHTSHADER_H

#include "Shader.h"

// CSpecularLightShader class
class CSpecularLightShader : public CShader
{
public:
	CSpecularLightShader(); // Default constructor
	~CSpecularLightShader(); // Destructor

	virtual HRESULT updateInstanceConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext);

private:
};

#endif // SPECULARLIGHTSHADER_H