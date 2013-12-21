// CubeMap.h: Implementation of cube mapping
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#ifndef CUBEMAP_H
#define CUBEMAP_H

// CCubeMap class
class CCubeMap : public CShader
{
public:
	CCubeMap(); // Default constructor
	CCubeMap(std::wstring oCubeMapTexturePathString); // Constructor
	~CCubeMap(); // Destructor

	bool create(float fHeight, float fWidth, float fDepth); // Create a cubemap with specified settings

private:
	CCubePrimitive *m_pCubePrimitive; // Cube primitive where cube map textures will be mapped onto

	CTextureCube *m_pCubeMapTexture; // Will hold our cubemap texture
};

#endif // CUBEMAP_H