// ShadowMap.h: Implementation of shadow mapping
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef SHADOWMAP_H
#define SHADOWMAP_H

// CShadowMapping class
class CShadowMap : public CShader
{
public:
	CShadowMap(); // Default constructor
	~CShadowMap(); // Destructor

private:
	ID3D11Texture2D *m_pD3DShadowMapTexture;
};

#endif // SHADOWMAP_H