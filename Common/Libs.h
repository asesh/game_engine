// Libs.h: Link to static libraries
// Copyright (C) 2011-2012 Asesh Shrestha. All rights reserved

#ifndef LIBS_H
#define LIBS_H

// Link to static libraries
//

// DirectX libraries
//
#pragma comment(lib, "d3d11.lib") // D3D 11
#pragma comment(lib, "d3dcompiler.lib") // D3D compiler
#pragma comment(lib, "d3d10_1.lib") // D3D 10.1
#pragma comment(lib, "dxgi.lib") // DXGI
#pragma comment(lib, "dwrite.lib") // DirectWrite
#pragma comment(lib, "d2d1.lib") // Direct2D
//#pragma comment(lib, "xaudio2") // XAudio 2
//
// End DirectX libraries

#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "wininet.lib")

#ifdef _DEBUG // Debug versions

#pragma comment(lib, "d3dx11d.lib") // Debug version of D3D 11 extension library

//#pragma comment(lib, "fbxsdk-2013.2-mdd.lib") // FBX

#ifdef _WIN64 // x64

#pragma comment(lib, "effects11.lib") // D3DX 11 effects framework

#else // x86

#pragma comment(lib, "effects11.lib") // D3DX 11 effects framework

#endif // _WIN64

#else // Release versions

#pragma comment(lib, "d3dx11.lib") // D3D 11 extesion

//#pragma comment(lib, "fbxsdk-2013.2-md") // FBX

#ifdef _WIN64 // x64

#pragma comment(lib, "effects11.lib") // D3DX 11 effects framework

#else // x86

#pragma comment(lib, "effects11.lib") // D3DX 11 effects framework

#endif // _WIN64

#endif // _DEBUG

//
// PhysX libraries
//
//#pragma comment(lib, "FoundationDEBUG.lib")
#pragma comment(lib, "PhysX3Common_x64.lib")
//#pragma comment(lib, "PhysX3CharacterDynamic.lib")
#pragma comment(lib, "PhysX3CharacterKinematic_x64.lib")
#pragma comment(lib, "PhysX3Vehicle.lib")
#pragma comment(lib, "PhysX3Cooking_x64.lib")
#pragma comment(lib, "PhysX3_x64.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
//#pragma comment(lib, "LowLevel.lib")
//#pragma comment(lib, "GeomUtilsDEBUG.lib")
//#pragma comment(lib, "SceneQuery.lib")
//#pragma comment(lib, "SimulationController.lib")
//#pragma comment(lib, "PvdRuntime.lib")
#pragma comment(lib, "RepX3.lib")
//
// End Physx libraries
//

//
// Link to static libraries

#endif // LIBS_H