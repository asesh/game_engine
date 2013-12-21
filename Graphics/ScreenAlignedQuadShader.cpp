// ScreenAlignedQuadShader.cpp: 
// Copyright (C) 2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "Shader.h"
#include "ScreenAlignedQuadShader.h"

//---------------------------------------------------------------------------
// Name: CScreenAlignedQuadShader
// Desc: Default constructor
//---------------------------------------------------------------------------
CScreenAlignedQuadShader::CScreenAlignedQuadShader()
{
}

//---------------------------------------------------------------------------
// Name: ~CScreenAlignedQuadShader
// Desc: Destructor
//---------------------------------------------------------------------------
CScreenAlignedQuadShader::~CScreenAlignedQuadShader()
{
}

//---------------------------------------------------------------------------
// Name: updateConstantBuffers
// Desc: 
//---------------------------------------------------------------------------
//HRESULT CScreenAlignedQuadShader::updateConstantBuffers(SInstanceConstantBuffer *pInstanceConstantBuffer, ID3D11DeviceContext *pD3DDeviceContext)
//{
//	return S_OK;
//}

//---------------------------------------------------------------------------
// Name: updateInstanceConstantBuffers
// Desc: 
//---------------------------------------------------------------------------
HRESULT CScreenAlignedQuadShader::updateInstanceConstantBuffers(ID3D11DeviceContext *pD3DDeviceContext)
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: 
// Desc: 
//---------------------------------------------------------------------------