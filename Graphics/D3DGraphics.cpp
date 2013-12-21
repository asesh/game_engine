// D3DGraphics.cpp: Implementation of 3D graphics rendering engine
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#include "../Common/StdAfx.h"
#include "../Common/GameEngine.h"
#include "Shader.h"
#include "DiffuseLightShader.h"
#include "MotionBlurShader.h"
#include "InstanceShader.h"
#include "NormalMapShader.h"
#include "ScreenAlignedQuadShader.h"
#include "SpecularLightShader.h"
#include "D2DGraphics.h" // D2D graphics
#include "D3DGraphics.h"

//---------------------------------------------------------------------------
// Name: CD3DGraphics
// Desc: Default constructor
//---------------------------------------------------------------------------
CD3DGraphics::CD3DGraphics()
{
	// DXGI
	m_pDXGIFactory = nullptr;

	m_pDXGIOutput = nullptr;

	m_pDXGIAdapter = nullptr;

	m_pDXGISwapChain = nullptr;

	m_pDXGIScreenAlignedQuadKeyedMutex = nullptr;

	m_pDXGIResource = nullptr;

	// Device
	m_pD3DDevice = nullptr;

	// Device contexts
	m_pD3DImmDevContext = m_pD3DDefDevContext = nullptr;

	// Views
	m_pD3DRTView = nullptr;
	m_pD3DDSView = nullptr;

	// Rasterizer states
	m_pD3DDefRState = m_pD3DWireFrameRState = m_pD3DCullingDisabledRState = nullptr;

	// Depth-stencil states
	m_pD3DDefDSState = m_pD3DDepthDisabledDSState = nullptr;

	// Sampler states
	m_pD3DDefSamplerState = m_pD3DWrapSamplerState = m_pD3DMirrorSamplerState = nullptr;

	// Blend states
	m_pD3DDefBlendState = m_pD3DTransAlphaBlendState = nullptr;

	// Queries
	m_pD3DOcclusionQuery = m_pD3DEventQuery = m_pD3DPipelineStatsQuery = nullptr;

	m_pD3DOccPredicate = nullptr;

	m_pD3DCounter = nullptr;

	m_pD3DAsynchronous = nullptr;

	m_pD3DComputeShader = nullptr;

	m_pD3DClassLinkage = nullptr;

	m_pD3DSharedTexture = nullptr;

	m_pD3DSRV = nullptr;

#ifdef _DEBUG // _DEBUG

	m_pD3DDebug = nullptr;
	m_pD3DInfoQueue = nullptr;

#endif // _DEBUG

	//m_hRenderEvent = nullptr;

	//m_hGraphicsCommandThread = nullptr;

	m_uiNumOfSamplesPassed = 0;

	// Initialize and take ownership of the rendering critical section object
	/*::InitializeCriticalSection(&m_oRenderThreadCriticalSection);
	::EnterCriticalSection(&m_oRenderThreadCriticalSection);*/

	// Set render target color to black
	//for(DWORD dwCount = 0; dwCount < 3; dwCount++)
	for(float &rfRenderTargetCount : m_fRenderTargetColor)
		rfRenderTargetCount = 0.0f;
	m_fRenderTargetColor[3] = 1.0f; // Alpha

	m_bSolidFillMode = true; // Initially set the fill mode to solid

	m_bExitThread = false; // Initially signal not to exit the thread

	m_hResult = S_OK; // HRESULT
}

//---------------------------------------------------------------------------
// Name: ~CD3DGraphics
// Desc: Destructor to release the used resources
//---------------------------------------------------------------------------
CD3DGraphics::~CD3DGraphics()
{
	// Leave the ownership and delete the critical section object
	/*::LeaveCriticalSection(&m_oRenderThreadCriticalSection);
	::DeleteCriticalSection(&m_oRenderThreadCriticalSection);*/

	//FREE_HANDLE(m_hRenderEvent); // Render event

	// Direct3D
	//

#ifdef _DEBUG // _DEBUG

	FREE_COM(m_pD3DDebug);
	FREE_COM(m_pD3DInfoQueue);

#endif // _DEBUG

	FREE_COM(m_pD3DSRV);

	FREE_COM(m_pD3DSharedTexture);

	FREE_COM(m_pD3DClassLinkage);

	// Compute shaders
	FREE_COM(m_pD3DComputeShader);

	FREE_COM(m_pD3DAsynchronous);

	// Counter
	FREE_COM(m_pD3DCounter);

	// Occlusion predicate
	FREE_COM(m_pD3DOccPredicate);

	// Queries
	FREE_COM(m_pD3DPipelineStatsQuery);
	FREE_COM(m_pD3DOcclusionQuery);
	FREE_COM(m_pD3DEventQuery);

	// Blend states
	FREE_COM(m_pD3DTransAlphaBlendState);
	FREE_COM(m_pD3DDefBlendState);

	// Sampler states
	FREE_COM(m_pD3DDefSamplerState);
	FREE_COM(m_pD3DWrapSamplerState);
	FREE_COM(m_pD3DMirrorSamplerState);

	// Depth-stencil states
	FREE_COM(m_pD3DDefDSState);
	FREE_COM(m_pD3DDepthDisabledDSState);

	// Rasterizer states
	FREE_COM(m_pD3DDefRState);
	FREE_COM(m_pD3DWireFrameRState);
	FREE_COM(m_pD3DCullingDisabledRState);

	// Views
	FREE_COM(m_pD3DDSView);
	FREE_COM(m_pD3DRTView);

	// Command list
	FREE_COM(m_pD3DCommandList);

	// Device contexts
	FREE_COM(m_pD3DImmDevContext);
	FREE_COM(m_pD3DDefDevContext);

	// Device
	FREE_COM(m_pD3DDevice);

	//
	// Direct3D

	// DXGI
	//

	FREE_COM(m_pDXGIResource); // Resource

	FREE_COM(m_pDXGIScreenAlignedQuadKeyedMutex); // Keyed mutex

	FREE_COM(m_pDXGIOutput); // Output

	FREE_COM(m_pDXGISwapChain); // Swap chain

	FREE_COM(m_pDXGIAdapter); // Adapter

	FREE_COM(m_pDXGIFactory); // Factory

	//
	// DXGI
}

//---------------------------------------------------------------------------
// Name: createDeviceAndSwapChain
// Desc: Create Direct3D device and swap chain
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createDeviceAndSwapChain()
{
	UINT uiAdapterCount = 0, uiSuppAdapterCount = 0;
	std::vector<IDXGIAdapter *> oDXGIAdapterVec; // Will hold the adapters on the system

	UINT uiRuntimeLayers; // Will hold the runtime layers

	// Direct3D feature level
	D3D_FEATURE_LEVEL oD3DFeatureLevel[] = {D3D_FEATURE_LEVEL_11_0};

	// Supported feature levels
	D3D_FEATURE_LEVEL oD3DFeatureLevelSupp;

	//
	D3D11_FEATURE_DATA_THREADING oD3DThreadingFeature; // Will hold multithreading support information

	// Create a factory
	CHECK_COM(::CreateDXGIFactory(GUID(IDXGIFactory), reinterpret_cast<void **>(&m_pDXGIFactory)));

	// Enumerate an adapter on the system
	//CHECK_COM(m_pDXGIFactory->EnumAdapters(uiAdapterCount, &m_pDXGIAdapter));
	
	// Retrieve the description of the adapter
	//CHECK_COM(m_pDXGIAdapter->GetDesc(&m_oDXGIAdapterDesc));

	// Enumerate all the adapters on the system
	while(m_pDXGIFactory->EnumAdapters(uiAdapterCount, &m_pDXGIAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		oDXGIAdapterVec.push_back(m_pDXGIAdapter);

		uiAdapterCount++;
	}

	// If none of the cards support D3D 11 then return failure
	if(oDXGIAdapterVec.size() <= 0) // No adapters were found
		return E_FAIL;
	else if(oDXGIAdapterVec.size() == 1) // A single adapter was found on the system
	{
		m_pDXGIAdapter = oDXGIAdapterVec[0];
	}
	else // More than 1 adapter was found
	{
	}

	// Enumerate adapter outputs
	CHECK_COM(m_pDXGIAdapter->EnumOutputs(0, &m_pDXGIOutput));

#ifdef _DEBUG // Debug versions

	uiRuntimeLayers = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT; // Debug/D2D support

#else // Release versions

	uiRuntimeLayers = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // D2D support

#endif // _DEBUG

	// Swap chain description
	DXGI_SWAP_CHAIN_DESC oDXGISwapChainDesc = {0};
	oDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// Unsigned 32-bit format
	oDXGISwapChainDesc.BufferDesc.Height = g_pMainFrame->getWindowHeight(); // Height
	oDXGISwapChainDesc.BufferDesc.Width = g_pMainFrame->getWindowWidth(); // Width
	oDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // 
	oDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // 60 Hz
	//oDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	//oDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	oDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Use the buffer as render target output
	oDXGISwapChainDesc.BufferCount = 1; // No. of buffers in the swap chain
	oDXGISwapChainDesc.OutputWindow = g_pMainFrame->getWindowHandle(); // Window handle
	oDXGISwapChainDesc.Windowed = TRUE; // Windowed
	//oDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
	oDXGISwapChainDesc.SampleDesc.Count = 1; // Number of multisamples per pixel
	//oDXGISwapChainDesc.SampleDesc.Quality = 0; // Image quality level
	oDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // The contents of the back buffer are discarded after calling 'Present'

	// Create the device and swap chain
	CHECK_COM(::D3D11CreateDeviceAndSwapChain(m_pDXGIAdapter, // Default adapter
		D3D_DRIVER_TYPE_UNKNOWN, // We are passing an adapter so pass it an unknown driver type
		nullptr, // Software
		uiRuntimeLayers, // Runtime layers to enable
		oD3DFeatureLevel, // Feature levels
		ARRAY_SIZE(oD3DFeatureLevel, D3D_FEATURE_LEVEL), // Number of feature levels
		D3D11_SDK_VERSION, // SDK version
		&oDXGISwapChainDesc, // Swap chain description
		&m_pDXGISwapChain, // Swap chain
		&m_pD3DDevice, // Device
		&oD3DFeatureLevelSupp, // Feature level
		&m_pD3DImmDevContext)); // Device context

#ifdef _DEBUG // Debug versions

	// Retrieve the handles to the debug interfaces
	CHECK_COM(m_pD3DDevice->QueryInterface(GUID(ID3D11Debug), reinterpret_cast<void **>(&m_pD3DDebug))); // Debug interface
	CHECK_COM(m_pD3DDevice->QueryInterface(GUID(ID3D11InfoQueue), reinterpret_cast<void **>(&m_pD3DInfoQueue))); // Info queue interface

#endif // _DEBUG

	// Check if multi-threaded rendering is supported
	CHECK_COM(m_pD3DDevice->CheckFeatureSupport(D3D11_FEATURE_THREADING, &oD3DThreadingFeature, sizeof(D3D11_FEATURE_DATA_THREADING)));

	// Create a deferred device context for a playback of command lists
	if(SUCCEEDED(m_pD3DDevice->CreateDeferredContext(0, &m_pD3DDefDevContext)))
	{
		// Create a thread which will record graphics commands
		/*m_hGraphicsCommandThread = ::CreateThread(NULL, 0, recordGraphicsCommands, NULL, CREATE_SUSPENDED, &m_dwRenderThreadID);
		if(m_hGraphicsCommandThread == NULL)
			return E_FAIL;*/

		// Create an event that will be used for the synchronization of multi-threaded rendering
		//m_hRenderEvent = ::CreateEvent(nullptr, TRUE, TRUE, nullptr);  // Initially set it the signaled state
		//if(m_hRenderEvent == nullptr)
		//	return E_FAIL;
	}
	else // Multithreaded rendering is not supported
		return E_FAIL; // So return failure

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createRenderTargetAndDepthStencilViews
// Desc: Create render target and depth-stencil views
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createRenderTargetAndDepthStencilViews()
{
	ID3D11Texture2D *pD3DRTTexture, *pD3DDSTexture;

	D3D11_RENDER_TARGET_VIEW_DESC oD3DRenderTargetViewDesc;
	::memset(&oD3DRenderTargetViewDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC)); // Zero it out

	// Get a pointer to the back buffer
	CHECK_COM(m_pDXGISwapChain->GetBuffer(0, GUID(ID3D11Texture2D), reinterpret_cast<void **>(&pD3DRTTexture))); // 2D texture
	//CHECK_COM(m_pDXGISwapChain->GetBuffer(0, GUID(IDXGISurface), reinterpret_cast<void **>(&g_pD2DGraphics->m_pDXGISurface))); // DXGI surface

	// Create a render-target view
	CHECK_COM(m_pD3DDevice->CreateRenderTargetView(pD3DRTTexture, nullptr, &m_pD3DRTView));

	SAFE_RELEASE_COM(pD3DRTTexture); // Free the render target texture since it's no longer needed

	// Depth-stencil texture description
	D3D11_TEXTURE2D_DESC oD3DDSTextureDesc = {0};
	oD3DDSTextureDesc.Width = g_pMainFrame->getWindowWidth(); // Width of the texture
	oD3DDSTextureDesc.Height = g_pMainFrame->getWindowHeight(); // Height of the texture
	oD3DDSTextureDesc.ArraySize = 1; // 1 texture in the texture array
	oD3DDSTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // Bind depth-stencil buffer
	oD3DDSTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 24-bit depth buffer and 8-bit stencil buffer
	oD3DDSTextureDesc.MipLevels = 1; // 
	oD3DDSTextureDesc.SampleDesc.Count = 1; // Number of multisamples per-pixel
	oD3DDSTextureDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU

	// Create a depth-stencil texture
	CHECK_COM(m_pD3DDevice->CreateTexture2D(&oD3DDSTextureDesc, nullptr, &pD3DDSTexture));

	// Depth stencil view description
	D3D11_DEPTH_STENCIL_VIEW_DESC oD3DDepthStencilViewDesc;
	::memset(&oD3DDepthStencilViewDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC)); // Zero it out

	//
	oD3DDepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // 24-bit depth buffer and 8-bit stencil buffer
	oD3DDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // Resource will be accessed as a 2D texture

	// Create a depth-stencil view
	CHECK_COM(m_pD3DDevice->CreateDepthStencilView(pD3DDSTexture, &oD3DDepthStencilViewDesc, &m_pD3DDSView));

	SAFE_FREE_COM(pD3DDSTexture); // Free the depth-stencil texture resource since it's no longer needed

	// Now bind the render target and depth-stencil buffer to the output-merger stage
	m_pD3DImmDevContext->OMSetRenderTargets(1, &m_pD3DRTView, m_pD3DDSView);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createViewports
// Desc: Create and bind viewports
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createViewports()
{
	D3D11_VIEWPORT oD3DViewport = {0};

	// Default viewport
	oD3DViewport.Height = static_cast<float>(g_pMainFrame->getWindowHeight()); // Viewport height
	oD3DViewport.Width = static_cast<float>(g_pMainFrame->getWindowWidth()); // Viewport width
	oD3DViewport.MaxDepth = 1.0f; // Max depth of the viewport
	oD3DViewport.MinDepth = 0.0f; // Min depth of the viewport

	// Bind the viewport
	m_pD3DImmDevContext->RSSetViewports(ARRAY_SIZE(oD3DViewport, D3D11_VIEWPORT), &oD3DViewport);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createRasterizerStates
// Desc: Create rasterizer states
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createRasterizerStates()
{
	// Rasterizer state description
	D3D11_RASTERIZER_DESC oD3DRasterizerDesc;
	::memset(&oD3DRasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));

	// Create a default rasterizer state
	oD3DRasterizerDesc.FillMode = D3D11_FILL_SOLID; // Solid fill mode
	oD3DRasterizerDesc.CullMode = D3D11_CULL_BACK; // Cull backfacing triangles
	oD3DRasterizerDesc.DepthClipEnable = TRUE; // Enable clipping based on distance
	CHECK_COM(m_pD3DDevice->CreateRasterizerState(&oD3DRasterizerDesc, &m_pD3DDefRState));
	m_pD3DImmDevContext->RSSetState(m_pD3DDefRState); // Set the rasterizer state

	// Rasterizer state with backface culling disabled
	oD3DRasterizerDesc.CullMode = D3D11_CULL_NONE; // Disable backface culling
	CHECK_COM(m_pD3DDevice->CreateRasterizerState(&oD3DRasterizerDesc, &m_pD3DCullingDisabledRState));

	// Rasterizer state with fill mode set to wireframe mode
	oD3DRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME; // Fill mode to wireframe mode
	oD3DRasterizerDesc.CullMode = D3D11_CULL_BACK; // Cull backfacing triangles
	CHECK_COM(m_pD3DDevice->CreateRasterizerState(&oD3DRasterizerDesc, &m_pD3DWireFrameRState));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createDepthStencilStates
// Desc: Create depth-stencil states
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createDepthStencilStates()
{
	// Depth-stencil description
	D3D11_DEPTH_STENCIL_DESC oD3DDepthStencilDesc;
	::memset(&oD3DDepthStencilDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// Default depth-stencil state
	oD3DDepthStencilDesc.DepthEnable = TRUE; // Enable depth testing
	oD3DDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // Tun on writes to the DS buffer
	oD3DDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; // Comparison passes if the source data is less than dest. data
	oD3DDepthStencilDesc.StencilEnable = FALSE; // Disable stencil testing
	//oD3DDepthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK; // Default stencil read mask
	//oD3DDepthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK; // Default stencil write mask
	//oD3DDepthStencilDesc.BackFace = 
	CHECK_COM(m_pD3DDevice->CreateDepthStencilState(&oD3DDepthStencilDesc, &m_pD3DDefDSState));

	m_pD3DImmDevContext->OMSetDepthStencilState(m_pD3DDefDSState, 0); // Set the depth-stencil state of the output-merger stage

	// Depth-stencil state with depth buffer disabled
	oD3DDepthStencilDesc.DepthEnable = FALSE; // Disable depth testing
	oD3DDepthStencilDesc.StencilEnable = FALSE; // Disable stencil testing
	CHECK_COM(m_pD3DDevice->CreateDepthStencilState(&oD3DDepthStencilDesc, &m_pD3DDepthDisabledDSState));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createSamplerStates
// Desc: Create sampler states
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createSamplerStates()
{
	// Sampler description
	D3D11_SAMPLER_DESC oD3DSamplerDesc;
	::memset(&oD3DSamplerDesc, 0, sizeof(D3D11_SAMPLER_DESC));

	// Default sampler state
	oD3DSamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC; // Anisotropic interpolation for mag, min and mip-level sampling
	oD3DSamplerDesc.AddressU = oD3DSamplerDesc.AddressV = oD3DSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP; // Clamp
	oD3DSamplerDesc.MaxAnisotropy = 4; // Anisotropy value
	CHECK_COM(m_pD3DDevice->CreateSamplerState(&oD3DSamplerDesc, &m_pD3DDefSamplerState));

	// Sampler state with UVW texture wrapping and anisotropic filtering
	oD3DSamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC; // Anisotropic filtering
	oD3DSamplerDesc.AddressU = oD3DSamplerDesc.AddressV = oD3DSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // Wrap texturing addressing mode
	CHECK_COM(m_pD3DDevice->CreateSamplerState(&oD3DSamplerDesc, &m_pD3DWrapSamplerState));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createBlendStates
// Desc: Create the blend states
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createBlendStates()
{
	D3D11_BLEND_DESC oD3DBlendDesc = {0};

	// Default blend state with blending disabled
	oD3DBlendDesc.RenderTarget[0].BlendEnable = FALSE; // Disable blending
	CHECK_COM(m_pD3DDevice->CreateBlendState(&oD3DBlendDesc, &m_pD3DDefBlendState));

	// Blend state with transparent alpha
	oD3DBlendDesc.RenderTarget[0].BlendEnable = TRUE; // Enable blending
	oD3DBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // Add source 1 and source 2
	oD3DBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR; // Source blend factor = src color
	oD3DBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // Dest. blend factor = 1 - src alpha
	oD3DBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // Add alpha 1 and alpha 2
	oD3DBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // Dest. blend alpha = 0
	oD3DBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // Src. blend alpha = 1
	CHECK_COM(m_pD3DDevice->CreateBlendState(&oD3DBlendDesc, &m_pD3DTransAlphaBlendState));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createQueries
// Desc: Create the queries
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createQueries()
{
	D3D11_QUERY_DESC oD3DQueryDesc;
	::memset(&oD3DQueryDesc, 0, sizeof(D3D11_QUERY_DESC));

	// Event query
	oD3DQueryDesc.Query = D3D11_QUERY_EVENT;
	CHECK_COM(m_pD3DDevice->CreateQuery(&oD3DQueryDesc, &m_pD3DEventQuery));

	// Occlusion query
	oD3DQueryDesc.Query = D3D11_QUERY_OCCLUSION;
	CHECK_COM(m_pD3DDevice->CreateQuery(&oD3DQueryDesc, &m_pD3DOcclusionQuery));

	// Pipeline statistics query
	oD3DQueryDesc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
	CHECK_COM(m_pD3DDevice->CreateQuery(&oD3DQueryDesc, &m_pD3DPipelineStatsQuery));

	// Occlusion query predicate
	oD3DQueryDesc.Query = D3D11_QUERY_OCCLUSION_PREDICATE;
	CHECK_COM(m_pD3DDevice->CreatePredicate(&oD3DQueryDesc, &m_pD3DOccPredicate));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createCounter
// Desc: Create a counter
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createCounters()
{
	D3D11_COUNTER_DESC oD3DCounterDesc;
	::memset(&oD3DCounterDesc, 0, sizeof(D3D11_COUNTER_DESC));

	//CHECK_COM(m_pD3DDevice->CreateCounter(&oD3DCounterDesc, &m_pD3DCounter));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createClassLinkage
// Desc: Create a class linkage for dynamic shader linkage
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createClassLinkage()
{
	RETURN_COM(m_pD3DDevice->CreateClassLinkage(&m_pD3DClassLinkage));
}

//---------------------------------------------------------------------------
// Name: createComputeShader
// Desc: Create a compute shader for high-speed GP computing on the GPU
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createComputeShaders()
{
	//CHECK_COM(m_pD3DDevice->CreateComputeShader(NULL, NULL, NULL, &m_pD3DComputeShader));

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: createShaders
// Desc: Create shaders
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::createShaders()
{
	std::wstring oVertexShaderFilenameString, oGeometryShaderFilenameString, oPixelShaderFilenameString; // Will hold the path of shader files

#ifdef _DEBUG // Debug version

	WCHAR szShaderFilePath[MAX_PATH]; // Will hold the path where all the effects are stored

	CLog::log(L"Inside createShaders method");

	// Get the path of the effects
	::SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szShaderFilePath);
	::StringCbCat(szShaderFilePath, ARRAY_SIZE(szShaderFilePath, WCHAR), L"\\Visual Studio 2012\\Projects\\Visual C++\\Direct3D\\GameEngine\\Graphics\\Shaders\\");
	::SetCurrentDirectory(szShaderFilePath);

	//g_pLog->log(L"About to load GlobalLighting.fx shader");

	// Diffuse lighting effect
	//oShaderFilenameString = L"GlobalIllumination.fx";
	//CHECK_COM(g_pGlobalLightingShader->create(oShaderFilenameString, m_pD3DDevice));
	//CHECK_COM(g_pGlobalLightingShader->setSamplerVariable(m_pD3DDefSamplerState)); // Set the default sampler state in the effect

	//g_pLog->log(L"Successfully loaded GlobalIllumination.fx shader");

	CLog::log(L"Loading DiffuseLighting shader");

	// Diffuse lighting effect
	oVertexShaderFilenameString = L"DiffuseLightingVertexShader.hlsl";
	oPixelShaderFilenameString = L"DiffuseLightingPixelShader.hlsl";
	//CHECK_COM(g_pDiffuseLightShader->create(oShaderFilenameString, L"C:\\Users\\Asesh\\Pictures\\Textures\\iron12_mod2.jpg", m_pD3DDevice));
	CHECK_COM(g_pDiffuseLightShader->create(oVertexShaderFilenameString, oGeometryShaderFilenameString, oPixelShaderFilenameString, L"C:\\Users\\Asesh\\Pictures\\Textures\\iron12_mod2.jpg", m_pD3DDevice));
	g_pDiffuseLightShader->setSamplerVariable(m_pD3DDefSamplerState); // Set the default sampler state in the effect

	CLog::log(L"Successfully loaded DiffuseLighting shader");

	CLog::log(L"Loading Instancing shader");

	// Instancing effect
	oVertexShaderFilenameString = L"InstancingVertexShader.hlsl";
	oPixelShaderFilenameString = L"InstancingPixelShader.hlsl";
	CHECK_COM(g_pInstanceShader->create(oVertexShaderFilenameString, oGeometryShaderFilenameString, oPixelShaderFilenameString, sizeof(SInstanceConstantBuffer), L"C:\\Users\\Asesh\\Pictures\\Textures\\water2.jpg", m_pD3DDevice));
	g_pInstanceShader->setSamplerVariable(m_pD3DDefSamplerState); // Set the default sampler state in the effect

	CLog::log(L"Successfully loaded Instancing shader");

	CLog::log(L"Loading NormalMapping shader");

	// Normal mapping effect
	oVertexShaderFilenameString = L"NormalMappingVertexShader.hlsl";
	oPixelShaderFilenameString = L"NormalMappingPixelShader.hlsl";
	CHECK_COM(g_pNormalMapShader->create(oVertexShaderFilenameString, oGeometryShaderFilenameString, oPixelShaderFilenameString, L"C:\\Users\\Asesh\\Pictures\\Textures\\crate2.dds", L"C:\\Users\\Asesh\\Pictures\\Textures\\crate2_normalmap.dds", m_pD3DDevice));
	g_pNormalMapShader->setSamplerVariable(m_pD3DDefSamplerState); // Set the default sampler state in the effect

	CLog::log(L"Successfully loaded NormalMapping shader");

	//CLog::log(L"About to load ScreenAlignedQuad.fx shader");

	//// Screen align effect
	//oShaderFilenameString = L"ScreenAlignedQuad.fx";
	//CHECK_COM(g_pScreenAlignedQuadShader->create(oShaderFilenameString, m_pD3DDevice));
	//CHECK_COM(g_pScreenAlignedQuadShader->setSamplerVariable(m_pD3DDefSamplerState)); // Set the default sampler state in the effect

	//CLog::log(L"Successfully loaded ScreenAlignedQuad.fx shader");

	//CLog::log(L"About to load NormalEffect.fx shader");

	//// Normal effect
	//oShaderFilenameString = L"NormalEffect.fx";
	//CHECK_COM(g_pNormalShader->create(oShaderFilenameString, m_pD3DDevice));
	//CHECK_COM(g_pNormalShader->setSamplerVariable(m_pD3DDefSamplerState)); // Set the default sampler state in the effect

	//CLog::log(L"Successfully loaded NormalEffect.fx shader");

#else // Release verions

	//CHECK_COM(g_pGenericEffect->create(generic

#endif // _DEBUG

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getFactory
// Desc: Get the handle to the factory
//---------------------------------------------------------------------------
IDXGIFactory *CD3DGraphics::getFactory() const
{
	return m_pDXGIFactory;
}

//---------------------------------------------------------------------------
// Name: getAdapter
// Desc: Get the handle to the adapter
//---------------------------------------------------------------------------
IDXGIAdapter *CD3DGraphics::getAdapter() const
{
	return m_pDXGIAdapter;
}

//---------------------------------------------------------------------------
// Name: getDevice
// Desc: Get the handle to the Direct3D device
//---------------------------------------------------------------------------
ID3D11Device *CD3DGraphics::getDevice() const
{
	return m_pD3DDevice;
}

//---------------------------------------------------------------------------
// Name: getImmediateDeviceContext
// Desc: Get A handle to the device context
//---------------------------------------------------------------------------
ID3D11DeviceContext *CD3DGraphics::getImmediateDeviceContext() const
{
	return m_pD3DImmDevContext;
}

//---------------------------------------------------------------------------
// Name: getDeferredDeviceContext
// Desc: Get the handle to the device context
//---------------------------------------------------------------------------
ID3D11DeviceContext *CD3DGraphics::getDeferredDeviceContext() const
{
	return m_pD3DDefDevContext;
}

//---------------------------------------------------------------------------
// Name: getRenderTargetView
// Desc: Get the render target view
//---------------------------------------------------------------------------
ID3D11RenderTargetView *CD3DGraphics::getRenderTargetView() const
{
	return m_pD3DRTView;
}

//---------------------------------------------------------------------------
// Name: getDepthStencilView
// Desc: Get the depth-stencil view
//---------------------------------------------------------------------------
ID3D11DepthStencilView *CD3DGraphics::getDepthStencilView() const
{
	return m_pD3DDSView;
}

//---------------------------------------------------------------------------
// Name: getKeyedMutex
// Desc: Get the handle to the keyed mutex
//---------------------------------------------------------------------------
IDXGIKeyedMutex *CD3DGraphics::getKeyedMutex() const
{
	return m_pDXGIScreenAlignedQuadKeyedMutex;
}

//---------------------------------------------------------------------------
// Name: getSharedResourceHandle
// Desc: Get the handle to the shared resource
//---------------------------------------------------------------------------
HANDLE CD3DGraphics::getSharedResourceHandle() const
{
	return m_hSharedResource;
}

//---------------------------------------------------------------------------
// Name: getDisplaySurfaceData
// Desc: Get the display surface data
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::getDisplaySurfaceData() const
{
	return S_OK;
}

//---------------------------------------------------------------------------
// Name: getFullscreenState
// Desc: Get the fullscreen state
//---------------------------------------------------------------------------
BOOL CD3DGraphics::getFullscreenState() const
{
	return m_bFullscreenState;
}

//---------------------------------------------------------------------------
// Name: setDefaultRasterizerState
// Desc: Set the default rasterizer state
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setDefaultRasterizerState(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->RSSetState(m_pD3DDefRState); // Set the default rasterizer state

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setSolidFillMode
// Desc: Set the solid fill mode
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setSolidFillMode(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->RSSetState(m_pD3DDefRState); // Set the default rasterizer state

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setWireFrameFillMode
// Desc: Set the wire frame fill mode
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setWireFrameFillMode(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->RSSetState(m_pD3DWireFrameRState); // Set the wireframe rasterizer state

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setDefaultDSState
// Desc: Set the default depth-stencil state
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setDefaultDSState(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->OMSetDepthStencilState(m_pD3DDefDSState, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setDisabledDBDSState
// Desc: Set the default depth-stencil state where depth buffer is disabled
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setDisabledDBDSState(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->OMSetDepthStencilState(m_pD3DDepthDisabledDSState, 0);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setDefaultBlendState
// Desc: Set the default blend state--blending disabled
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setDefaultBlendState(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->OMSetBlendState(m_pD3DDefBlendState, nullptr, 0xFFFFFFFF);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: setSpriteBlendState
// Desc: Set the blend state for the sprite
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::setSpriteBlendState(ID3D11DeviceContext *pD3DDeviceContext)
{
	pD3DDeviceContext->OMSetBlendState(m_pD3DTransAlphaBlendState, nullptr, 0xFFFFFFFF);

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: addSupportForD2D
// Desc: Add support for Direct2D
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::addSupportForD2D()
{
	// Offscreen surface desc
	D3D11_TEXTURE2D_DESC oD3DTexture2DDesc = {0};
	oD3DTexture2DDesc.ArraySize = 1;
	oD3DTexture2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // Bind render target and shader resource
	oD3DTexture2DDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // 32-bit BGRA UNORM
	oD3DTexture2DDesc.Height = g_pMainFrame->getWindowHeight(); // Height
	oD3DTexture2DDesc.Width = g_pMainFrame->getWindowWidth(); // Width
	oD3DTexture2DDesc.MipLevels = 1; // 
	oD3DTexture2DDesc.SampleDesc.Count = 1; // 
	oD3DTexture2DDesc.Usage = D3D11_USAGE_DEFAULT; // R/W access by the GPU
	oD3DTexture2DDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX; // Allow synchronization

	// Create an texture in which D2D to render the onto
	CHECK_COM(m_pD3DDevice->CreateTexture2D(&oD3DTexture2DDesc, nullptr, &m_pD3DSharedTexture));

	// Get the keyed mutex from the shared texture
	CHECK_COM(m_pD3DSharedTexture->QueryInterface(GUID(IDXGIKeyedMutex), reinterpret_cast<void **>(&m_pDXGIScreenAlignedQuadKeyedMutex)));

	// Retrieve a handle to an IDXGIResource interface
	CHECK_COM(m_pD3DSharedTexture->QueryInterface(&m_pDXGIResource));
	
	// Get a handle to the shared resource
	CHECK_COM(m_pDXGIResource->GetSharedHandle(&m_hSharedResource));

	// Create a shader-resource view for accessing data in a resource
	CHECK_COM(m_pD3DDevice->CreateShaderResourceView(m_pD3DSharedTexture, nullptr, &m_pD3DSRV));

	SAFE_FREE_COM(m_pDXGIResource); // Don't need it anymore

//	// Use the texture to obtain a DXGI surface
//	//CHECK_COM(m_pD3DSharedTexture->QueryInterface(&g_pD2DGraphics->getDXGISurface()));
//
//	// Swap chain description
//	DXGI_SWAP_CHAIN_DESC oDXGISwapChainDesc = {0};
//	oDXGISwapChainDesc.BufferCount = 1;
//	oDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	oDXGISwapChainDesc.BufferDesc.Height = g_pMainFrame->getWindowHeight();
//	oDXGISwapChainDesc.BufferDesc.Width = g_pMainFrame->getWindowWidth();
//	oDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
//	oDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
//	oDXGISwapChainDesc.OutputWindow = g_pMainFrame->getWindowHandle();
//	oDXGISwapChainDesc.Windowed = TRUE;
//	oDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	oDXGISwapChainDesc.SampleDesc.Count = 1;
//
//	// Create a swap chain for rendering 2D contents
//	CHECK_COM(m_pDXGIFactory->CreateSwapChain(m_pD3D101Device, &oDXGISwapChainDesc, &m_pDXGI2DSwapChain));
//
//	CHECK_COM(m_pDXGI2DSwapChain->GetBuffer(0, GUID(IDXGISurface), reinterpret_cast<void **>(&g_pD2DGraphics->getDXGISurface())))

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: enableDepthBuffer
// Desc: Enable depth buffer
//---------------------------------------------------------------------------
void CD3DGraphics::enableDepthBufer()
{
	m_pD3DImmDevContext->OMSetDepthStencilState(m_pD3DDefDSState, 0);
}

//---------------------------------------------------------------------------
// Name: enableAlphaBlending
// Desc: Enable alpha blending
//---------------------------------------------------------------------------
void CD3DGraphics::enableAlphaBlending()
{
	//m_pD3DImmDevContext->OMSetDepthStencilState(m_pD3DDepthDisabledDSState, 0);
}

//---------------------------------------------------------------------------
// Name: enableBackfaceCulling
// Desc: Enable backface culling
//---------------------------------------------------------------------------
void CD3DGraphics::enableBackfaceCulling()
{
	m_pD3DImmDevContext->RSSetState(m_pD3DDefRState);
}

//---------------------------------------------------------------------------
// Name: disableDepthBuffer
// Desc: Disable depth buffer
//---------------------------------------------------------------------------
void CD3DGraphics::disableDepthBuffer()
{
	m_pD3DImmDevContext->OMSetDepthStencilState(m_pD3DDefDSState, 0);
}

//---------------------------------------------------------------------------
// Name: disableAlphaBlending
// Desc: Disable alpha blending
//---------------------------------------------------------------------------
void CD3DGraphics::disableAlphaBlending()
{
	//m_pD3DImmDevContext->OMSetDepthStencilState(m_pD3DDepthDisabledDSState, 0);
}

//---------------------------------------------------------------------------
// Name: disableBackfaceCulling
// Desc: Disable backface culling
//---------------------------------------------------------------------------
void CD3DGraphics::disableBackfaceCulling()
{
	m_pD3DImmDevContext->RSSetState(m_pD3DCullingDisabledRState);
}

//---------------------------------------------------------------------------
// Name: beginOcclusionQuery
// Desc: Begin occlusion query
//---------------------------------------------------------------------------
void CD3DGraphics::beginOcclusionQuery()
{
	m_pD3DImmDevContext->Begin(m_pD3DOcclusionQuery); // Begin occlusion query
}

//---------------------------------------------------------------------------
// Name: endOcclusionQuery
// Desc: End occlusion query
//---------------------------------------------------------------------------
void CD3DGraphics::endOcclusionQuery()
{
	m_pD3DImmDevContext->End(m_pD3DOcclusionQuery); // End occlusion query
}


//---------------------------------------------------------------------------
// Name: getOcclusionQueryDataAsync
// Desc: Get occlusion query data from the GPU asynchronously
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::getOcclusionQueryDataAsync(UINT64 &ruiNumOfSamplesPassed)
{
	return m_pD3DImmDevContext->GetData(m_pD3DOcclusionQuery, reinterpret_cast<void *>(&ruiNumOfSamplesPassed), sizeof(UINT64), 0);
}

//---------------------------------------------------------------------------
// Name: endAndGetOcclusionQueryData
// Desc: End and get the occlusion query data
//---------------------------------------------------------------------------
UINT64 CD3DGraphics::endAndGetOcclusionQueryData()
{
	m_pD3DImmDevContext->End(m_pD3DOcclusionQuery);

	// Loop until the query data is retrieved
	while(m_pD3DImmDevContext->GetData(m_pD3DOcclusionQuery, reinterpret_cast<void *>(&m_uiNumOfSamplesPassed), sizeof(UINT64), 0) == S_FALSE);

	return m_uiNumOfSamplesPassed;
}


//---------------------------------------------------------------------------
// Name: getOcclusionQueryData
// Desc: Get occlusion query data
//---------------------------------------------------------------------------
UINT64 CD3DGraphics::getOcclusionQueryData()
{
	// Loop until the query data is retrieved
	while(m_pD3DImmDevContext->GetData(m_pD3DOcclusionQuery, reinterpret_cast<void *>(&m_uiNumOfSamplesPassed), sizeof(UINT64), 0) == S_FALSE);

	return m_uiNumOfSamplesPassed;
}

//---------------------------------------------------------------------------
// Name: beginPipelineStatsQuery
// Desc: Begin the pipeline statistics query 
//---------------------------------------------------------------------------
void CD3DGraphics::beginPipelineStatsQuery()
{
	m_pD3DImmDevContext->Begin(m_pD3DPipelineStatsQuery);
}

//---------------------------------------------------------------------------
// Name: endPipelineStatsQuery
// Desc: End pipeline statistics query
//---------------------------------------------------------------------------
void CD3DGraphics::endPipelineStatsQuery()
{
	m_pD3DImmDevContext->End(m_pD3DPipelineStatsQuery);
}

//---------------------------------------------------------------------------
// Name: getPipelineStatsQueryDataAsync
// Desc: Get the pipeline stats query data asynchronously
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::getPipelineStatsQueryDataAsync(D3D11_QUERY_DATA_PIPELINE_STATISTICS &rD3DQueryDataPipelineStats)
{
	return m_pD3DImmDevContext->GetData(m_pD3DPipelineStatsQuery, reinterpret_cast<void *>(&rD3DQueryDataPipelineStats), sizeof(D3D11_QUERY_DATA_PIPELINE_STATISTICS), 0);
}

//---------------------------------------------------------------------------
// Name: getPipelineStatsQueryData
// Desc: Get the pipeline statistics query data
//---------------------------------------------------------------------------
D3D11_QUERY_DATA_PIPELINE_STATISTICS *CD3DGraphics::getPipelineStatsQueryData()
{
	while(m_pD3DImmDevContext->GetData(m_pD3DPipelineStatsQuery, reinterpret_cast<void *>(&m_oD3DQueryDataPipelineStats), sizeof(D3D11_QUERY_DATA_PIPELINE_STATISTICS), 0) == S_FALSE);

	return &m_oD3DQueryDataPipelineStats;
}

//---------------------------------------------------------------------------
// Name: endAndGetPipelineStatsQueryData
// Desc: End and get the pipeline statistics query data
//---------------------------------------------------------------------------
D3D11_QUERY_DATA_PIPELINE_STATISTICS *CD3DGraphics::endAndGetPipelineStatsQueryData()
{
	m_pD3DImmDevContext->End(m_pD3DPipelineStatsQuery);

	while(m_pD3DImmDevContext->GetData(m_pD3DPipelineStatsQuery, reinterpret_cast<void *>(&m_oD3DQueryDataPipelineStats), sizeof(D3D11_QUERY_DATA_PIPELINE_STATISTICS), 0) == S_FALSE);

	return &m_oD3DQueryDataPipelineStats;
}

//---------------------------------------------------------------------------
// Name: toggleFullscreenState
// Desc: Toggle fullscreen/windowed mode depending on the argument
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::toggleFullscreenState()
{
	// Display mode description
	DXGI_MODE_DESC oDXGIModeDesc = {0};
	oDXGIModeDesc.Width = g_pMainFrame->getWindowWidth(); // Window width
	oDXGIModeDesc.Height = g_pMainFrame->getWindowHeight(); // Window height
	oDXGIModeDesc.RefreshRate.Numerator = 60; // Refresh rate numerator
	oDXGIModeDesc.RefreshRate.Denominator = 1; // Refresh rate denominator

	// Get the current fullscreen state of the swap chain
	CHECK_COM(m_pDXGISwapChain->GetFullscreenState(&m_bFullscreenState, &m_pDXGIOutput));

	if(m_bFullscreenState) // On fullscreen mode
	{
		CHECK_COM(m_pDXGISwapChain->ResizeTarget(&oDXGIModeDesc)); // Resize the target output
		CHECK_COM(m_pDXGISwapChain->ResizeBuffers(1, g_pMainFrame->getWindowWidth(), g_pMainFrame->getWindowHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)); // Resize the buffer
		CHECK_COM(m_pDXGISwapChain->SetFullscreenState(FALSE, m_pDXGIOutput)); // Toggle to windowed mode
	}
	else // On windowed mode
	{
		CHECK_COM(m_pDXGISwapChain->ResizeTarget(&oDXGIModeDesc)); // Resize the target output
		CHECK_COM(m_pDXGISwapChain->ResizeBuffers(1, g_pMainFrame->getWindowWidth(), g_pMainFrame->getWindowHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)); // Resize the buffer
		CHECK_COM(m_pDXGISwapChain->SetFullscreenState(TRUE, m_pDXGIOutput)); // Toggle to fullscreen mode
	}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: toggleFullscreenState
// Desc: Toggle fullscreen/windowed mode depending on the argument
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::toggleFullscreenState(bool bFullScreen)
{
	// Display mode description
	DXGI_MODE_DESC oDXGIModeDesc = {0};
	oDXGIModeDesc.Width = g_pMainFrame->getWindowWidth();
	oDXGIModeDesc.Height = g_pMainFrame->getWindowHeight();
	oDXGIModeDesc.RefreshRate.Numerator = 60;
	oDXGIModeDesc.RefreshRate.Denominator = 1;

	// Get the current fullscreen state of the swap chain
	CHECK_COM(m_pDXGISwapChain->GetFullscreenState(&m_bFullscreenState, &m_pDXGIOutput));

	if(!bFullScreen && m_bFullscreenState) // On fullscreen mode
	{
		CHECK_COM(m_pDXGISwapChain->ResizeTarget(&oDXGIModeDesc)); // Resize the target output
		CHECK_COM(m_pDXGISwapChain->ResizeBuffers(1, g_pMainFrame->getWindowWidth(), g_pMainFrame->getWindowHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)); // Resize the buffer
		CHECK_COM(m_pDXGISwapChain->SetFullscreenState(FALSE, m_pDXGIOutput)); // Toggle to windowed mode
	}
	else if(bFullScreen && !m_bFullscreenState) // On windowed mode
	{
		CHECK_COM(m_pDXGISwapChain->ResizeTarget(&oDXGIModeDesc)); // Resize the target output
		CHECK_COM(m_pDXGISwapChain->ResizeBuffers(1, g_pMainFrame->getWindowWidth(), g_pMainFrame->getWindowHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)); // Resize the buffer
		CHECK_COM(m_pDXGISwapChain->SetFullscreenState(TRUE, m_pDXGIOutput)); // Toggle to fullscreen mode
	}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: toggleFillMode
// Desc: Toggle fill mode
//---------------------------------------------------------------------------
void CD3DGraphics::toggleFillMode(ID3D11DeviceContext *pD3DDeviceContext)
{
	if(!m_bSolidFillMode) // The current fill mode is wireframe
	{
		pD3DDeviceContext->RSSetState(m_pD3DDefRState); // Set to default rasterizer state
		m_bSolidFillMode = true;
	}
	else // The current fill mode is solid
	{
		pD3DDeviceContext->RSSetState(m_pD3DWireFrameRState); // Set the wireframe fill mode
		m_bSolidFillMode = false;
	}
}

//---------------------------------------------------------------------------
// Name: initCoreEngine
// Desc: Initialize the core 3D graphics engine
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::initCoreEngine()
{
	CHECK_COM(createDeviceAndSwapChain()); // Device and swap chain
	CHECK_COM(createRenderTargetAndDepthStencilViews()); // Render-target and depth-stencil views
	CHECK_COM(createViewports()); // Viewports
	CHECK_COM(createRasterizerStates()); // Rasterizer states
	CHECK_COM(createDepthStencilStates()); // Depth-stencil states
	CHECK_COM(createSamplerStates()); // Sampler states
	CHECK_COM(createBlendStates()); // Blend states
	CHECK_COM(createCounters()); // Counters
	//CHECK_COM(addSupportForD2D()); // Add support for Direct2D

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: initGameEngine
// Desc: Initialize the core game engine
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::initGameEngine()
{
	CHECK_COM(createQueries()); // Queries
	//CHECK_COM(createThreadPump()); // Thread pump
	CHECK_COM(createClassLinkage()); // Class linkage
	CHECK_COM(createComputeShaders()); // Compute shader
	CHECK_COM(createShaders()); // Shaders
	//CHECK_COM(g_pInputLayout->init(m_pD3DDevice)); // Initialize the input layouts

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: clearRenderTargetAndDepthStencilViews
// Desc: Clear the render target and depth-stencil views
//---------------------------------------------------------------------------
void CD3DGraphics::clearRenderTargetAndDepthStencilViews()
{
	// Clear the views
	m_pD3DImmDevContext->ClearRenderTargetView(m_pD3DRTView, m_fRenderTargetColor); // Render target view
	m_pD3DImmDevContext->ClearDepthStencilView(m_pD3DDSView, D3D11_CLEAR_STENCIL | D3D11_CLEAR_DEPTH, 1.0f, 0); // Depth-stencil view
}

//---------------------------------------------------------------------------
// Name: render
// Desc: Render
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::render()
{
	//::ResetEvent(m_hRenderEvent); // Set the render event state to unsignaled

	//::SetEvent(m_hRenderEvent); // Set the render event state to signaled

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: renderPrimitive
// Desc: Render a primitive
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::renderPrimitive(CShader *pShader, ID3D11Buffer *pD3DVertexBuffer, UINT uiStride, UINT uiOffset)
{
	//beginOcclusionQuery();
	//g_pDiffuseLightingShader->apply(0, m_pD3DImmDevContext); // Apply the pass
	//m_pD3DImmDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_pD3DImmDevContext->IASetIndexBuffer(pD3DIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//m_pD3DImmDevContext->IASetVertexBuffers(0, 1, &pD3DVertexBuffer, &uiStride, &uiOffset);
	//m_pD3DImmDevContext->DrawIndexed(36, 0, 0);
	//endAndGetOcclusionQueryData();

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: renderIndexedPrimitive
// Desc: Render an indexed primitive
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::renderIndexedPrimitive(ID3D11DeviceContext *pD3DDeviceContext, 
	CShader *pShader, 
	ID3D11Buffer *pD3DVertexBuffer, 
	ID3D11Buffer *pD3DIndexBuffer, 
	UINT uiStride, 
	UINT uiOffset, 
	UINT uiTotalIndices)
{
	//pShader->setInputLayout(pD3DDeviceContext); // Set input layout
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // Set primitive topology
	pD3DDeviceContext->IASetIndexBuffer(pD3DIndexBuffer, DXGI_FORMAT_R32_UINT, 0); // Set index buffer
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &pD3DVertexBuffer, &uiStride, &uiOffset); // Set vertex buffer

	pShader->set(pD3DDeviceContext); // Set the shader and it's corresponding resources
	//pShader->updateMaterialConstantBuffers(pD3DDeviceContext); // Update materials' constant buffers

	// Apply all the passes
	//while(pShader->applyAllPasses(pD3DDeviceContext))
	//{
	pD3DDeviceContext->DrawIndexed(uiTotalIndices, 0, 0); // Render the indexed primitive
	//}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: renderIndexedInstancedPrimitive
// Desc: Render an indexed instanced primitive
//---------------------------------------------------------------------------
HRESULT CD3DGraphics::renderIndexedInstancedPrimitive(ID3D11DeviceContext *pD3DDeviceContext, 
	CShader *pShader, 
	ID3D11Buffer **ppD3DVertexBuffer, 
	UINT uiNumOfVertexBuffers, 
	ID3D11Buffer *pD3DIndexBuffer, 
	UINT uiTotalIndices, 
	UINT *puiStride, 
	UINT *puiOffset, 
	UINT uiNumOfInstances)
{
	//pShader->setInputLayout(pD3DDeviceContext); // Set input layout
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // Set primitive topology
	pD3DDeviceContext->IASetVertexBuffers(0, uiNumOfVertexBuffers, ppD3DVertexBuffer, puiStride, puiOffset); // Set vertex buffers
	pD3DDeviceContext->IASetIndexBuffer(pD3DIndexBuffer, DXGI_FORMAT_R32_UINT, 0); // Set index buffer
	
	pShader->set(pD3DDeviceContext); // Set the shader and it's corresponding resources

	// Apply all the passes
	//while(pShader->applyAllPasses(pD3DDeviceContext))
	//{
	pD3DDeviceContext->DrawIndexedInstanced(uiTotalIndices, uiNumOfInstances, 0, 0, 0); // Render the indexed primitive
	//}

	return S_OK;
}

//---------------------------------------------------------------------------
// Name: recordAndExecuteCommands
// Desc: Record graphics commands into a command list and execute them
//---------------------------------------------------------------------------
void CD3DGraphics::recordAndExecuteCommands()
{
	// Try to enter the critical section and obtain ownership of it
	//while(!::TryEnterCriticalSection(&m_oRenderThreadCriticalSection))
	//	::Sleep(2); // Sleep for the specified number of MS before trying again

	// 
	while(!m_bExitThread)
	{
		// Wait for the render event to be signaled so that multithreaded rendering can be done
		//if(::WaitForSingleObject(m_hRenderEvent, INFINITE) != WAIT_OBJECT_0)
		//{
		//	::Sleep(1); // Sleep for a millsecond

		//	continue;
		//}
		// The render event has been signaled so now it's time to do some multithreaded rendering

		// Record graphics commands into the command list
		m_pD3DDefDevContext->FinishCommandList(FALSE, &m_pD3DCommandList);

		// Queue commands from a command list onto a device
		m_pD3DDefDevContext->ExecuteCommandList(m_pD3DCommandList, FALSE);

		//::ResetEvent(m_hRenderEvent); // Unsignal the event since we are done rendering a single frame
	}

	//::LeaveCriticalSection(&m_oRenderThreadCriticalSection); // Leave the ownership of the critical section since the thread is about to terminate
}

//---------------------------------------------------------------------------
// Name: present
// Desc: Present the rendered image to the user
//---------------------------------------------------------------------------
void CD3DGraphics::present()
{
	m_pDXGISwapChain->Present(0, 0);
}

//---------------------------------------------------------------------------
// Name: recordGraphicsCommands
// Desc: Record graphics commands into a command list
//---------------------------------------------------------------------------
DWORD WINAPI recordGraphicsCommands(LPVOID lpParam)
{
	g_pD3DGraphics->recordAndExecuteCommands();

	return 0;
}

CD3DGraphics g_oD3DGraphics;
CD3DGraphics *g_pD3DGraphics = &g_oD3DGraphics;
