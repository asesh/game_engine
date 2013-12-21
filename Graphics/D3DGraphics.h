// D3DGraphics.h: Implementation of 3D graphics rendering engine
// Copyright (C) 2010-2012 Asesh Shrestha. All rights reserved

#ifndef D3DGRAPHICS_H
#define D3DGRAPHICS_H

#include "Shader.h"

// Forward declarations
//class CShader;

// Constants
#define D3D_DEVICE		g_pD3DGraphics->getDevice() // Will return a D3D device
#define IMM_DEV_CONTEXT g_pD3DGraphics->getImmediateDeviceContext() // Will return an immediate device context
#define DEF_DEV_CONTEXT g_pD3DGraphics->getDeferredDeviceContext() // Will return a deferred device context

// Function prototypes
DWORD WINAPI recordGraphicsCommands(LPVOID lpParam); // Thread for recording graphics commands

// CD3DGraphics class
class CD3DGraphics final
{
public: // Public methods
	CD3DGraphics(); // Default constructor
	~CD3DGraphics(); // Destructor

	// Create methods
	//
	HRESULT createDeviceAndSwapChain(); // Create device and swap chain

	HRESULT createRenderTargetAndDepthStencilViews(); // Create render targets

	HRESULT createViewports(); // Create viewports

	HRESULT createRasterizerStates(); // Create rasterizer states

	HRESULT createDepthStencilStates(); // Create depth-stencil states

	HRESULT createSamplerStates(); // Create sampler states

	HRESULT createBlendStates(); // Create blend states

	HRESULT createQueries(); // Create queries

	HRESULT createThreadPump(); // Create a thread pump

	HRESULT createCounters(); // Create a counter

	HRESULT createClassLinkage(); // Create a class linkage

	HRESULT createComputeShaders(); // Create a compute shader

	HRESULT createShaders(); // Create effects
	//
	// Create methods

	// Get methods
	//

	IDXGIFactory *getFactory() const; // Get the factory handle

	IDXGIAdapter *getAdapter() const; // Get the adapter handle

	ID3D11Device *getDevice() const; // Get the device handle

	ID3D11DeviceContext *getImmediateDeviceContext() const; // Get the immediate device context handle

	ID3D11DeviceContext *getDeferredDeviceContext() const; // Get the deferred device context handle

	ID3D11RenderTargetView *getRenderTargetView() const; // Get the render target view

	ID3D11DepthStencilView *getDepthStencilView() const; // Get the depth-stencil view

	ID3DX11ThreadPump *getThreadPump() const; // Get the thread pump handle

	IDXGIKeyedMutex *getKeyedMutex() const; // Get the keyed mutex handle

	HANDLE getSharedResourceHandle() const; // Get the shared resource handle

	HRESULT getDisplaySurfaceData() const; // Get the display surface data

	BOOL getFullscreenState() const; // Get the fullscreen state

	//
	// Get methods

	// Set methods
	//

	// Rasterizer states
	HRESULT setDefaultRasterizerState(ID3D11DeviceContext *pD3DDeviceContext); // Set the default rasterizer state
	HRESULT setSolidFillMode(ID3D11DeviceContext *pD3DDeviceContext); // Set solid fill mode
	HRESULT setWireFrameFillMode(ID3D11DeviceContext *pD3DDeviceContext); // Set wire frame fill mode

	// Depth-stencil states
	HRESULT setDefaultDSState(ID3D11DeviceContext *pD3DDeviceContext); // Set the default depth-stencil state
	HRESULT setDisabledDBDSState(ID3D11DeviceContext *pD3DDeviceContext); // Set the depth-stencil state where depth buffer is disabled

	// Sampler states

	// Blend states
	HRESULT setDefaultBlendState(ID3D11DeviceContext *pD3DDeviceContext); // Set the default blend state--blending disabled
	HRESULT setSpriteBlendState(ID3D11DeviceContext *pD3DDeviceContext); // Set blend state for the sprite

	//
	// Set methods

	HRESULT addSupportForD2D(); // Add support for Direct2D

	// Enable methods
	//

	void enableDepthBufer(); // Enable depth buffer
	void enableAlphaBlending(); // Enable alpha blending
	void enableBackfaceCulling(); // Enable backface culling

	//
	// Enable methods

	// Disable methods
	//

	void disableDepthBuffer(); // Disable depth buffer
	void disableAlphaBlending(); // Disable alpha blending
	void disableBackfaceCulling(); // Disable backface culling

	//
	// Disable methods

	// Queries methods
	//

	// Occlusion query
	void beginOcclusionQuery(); // Begins occlusion query
	void endOcclusionQuery(); // End occlusion query
	HRESULT getOcclusionQueryDataAsync(UINT64 &ruiNumOfSamplesPassed); // Get occlusion query data asynchronously
	UINT64 endAndGetOcclusionQueryData(); // End the occlusion query and retrieve the occlusion query data
	UINT64 getOcclusionQueryData(); // Retrieve the occlusion query data

	// Pipeline stats query
	void beginPipelineStatsQuery(); // Begin pipeline statistics query
	void endPipelineStatsQuery(); // End pipeline statistics query
	HRESULT getPipelineStatsQueryDataAsync(D3D11_QUERY_DATA_PIPELINE_STATISTICS &rD3DQueryDataPipelineStats); // Get pipeline stats data asynchronously
	D3D11_QUERY_DATA_PIPELINE_STATISTICS *getPipelineStatsQueryData(); // Get the pipeline statistics query data
	D3D11_QUERY_DATA_PIPELINE_STATISTICS *endAndGetPipelineStatsQueryData(); // End and get the result of the pipeline statistics query

	// Stream output stats query
	void beginStreamOutputStatsQuery(); // Begin stream output statistics query
	void endStreamOutputStatsQuery(); // End stream output statistics query
	HRESULT getStreamOutputStatsQueryDataAsync(D3D11_QUERY_DATA_SO_STATISTICS &rD3DQueryDataSOStatistics); // Get stream output stats data asynchronously
	D3D11_QUERY_DATA_SO_STATISTICS *getStreamOutputStatsQueryData(); // Get the stream output statistics query data
	D3D11_QUERY_DATA_SO_STATISTICS *endAndGetStreamOutputStatsQueryData(); // End and get the result of the streaming output statistics query data

	//
	// Queries methods

	HRESULT toggleFullscreenState(); // Toggle fullscreen state
	HRESULT toggleFullscreenState(bool bFullScreen); // Toggle fullscreen state
	void toggleFillMode(ID3D11DeviceContext *pD3DDeviceContext); // Toggle fill mode

	HRESULT initCoreEngine(); // Initialize the core 3D graphics engine
	HRESULT initGameEngine(); // Initialize the game engine graphics

	void clearRenderTargetAndDepthStencilViews(); // Clear the render target and depth-stencil views

	HRESULT render(); // Render game data
	HRESULT renderPrimitive(CShader *pShader, ID3D11Buffer *pD3DVertexBuffer, UINT uiStride, UINT uiOffset); // Render primitive
	HRESULT renderIndexedPrimitive(ID3D11DeviceContext *pD3DDeviceContext, CShader *pShader, ID3D11Buffer *pD3DVertexBuffer, ID3D11Buffer *pD3DIndexBuffer, UINT uiStride, UINT uiOffset, UINT uiTotalIndices); // Render indexed primitive using immediate context
	HRESULT renderIndexedInstancedPrimitive(ID3D11DeviceContext *pD3DDeviceContext, CShader *pShader, ID3D11Buffer **ppD3DVertexBuffer, UINT uiNumOfVertexBuffers, ID3D11Buffer *pD3DIndexBuffer, UINT uiTotalIndices, UINT *puiStride, UINT *puiOffset, UINT uiNumOfInstances); // Render indexed instanced primitive

	void recordAndExecuteCommands(); // Record the graphics commands into a command list and execute them

	void present(); // Present the back buffer onto the screen

private: // Private attributes

	// DXGI
	//
	IDXGIFactory *m_pDXGIFactory; // Factory

	IDXGISwapChain *m_pDXGISwapChain; // Swap chain

	IDXGIAdapter *m_pDXGIAdapter; // Adapter

	IDXGIOutput *m_pDXGIOutput; // Output

	IDXGIKeyedMutex *m_pDXGIScreenAlignedQuadKeyedMutex; // Keyed mutex

	IDXGIResource *m_pDXGIResource; //

	//
	// DXGI

	// Direct3D 11
	//
	ID3D11Device *m_pD3DDevice; // Device
	ID3D11DeviceContext *m_pD3DImmDevContext, *m_pD3DDefDevContext; // Device contexts

	// Views
	ID3D11RenderTargetView *m_pD3DRTView; // Render target view
	ID3D11DepthStencilView *m_pD3DDSView; // Depth stencil view

	// States
	ID3D11RasterizerState *m_pD3DDefRState, *m_pD3DWireFrameRState, *m_pD3DCullingDisabledRState; // Rasterizer states

	ID3D11DepthStencilState *m_pD3DDefDSState, *m_pD3DDepthDisabledDSState; // Depth-stencil states

	ID3D11SamplerState *m_pD3DDefSamplerState, *m_pD3DWrapSamplerState, *m_pD3DMirrorSamplerState; // Sampler states

	ID3D11BlendState *m_pD3DDefBlendState, *m_pD3DTransAlphaBlendState; // Blend states
	// End states

	ID3D11Query *m_pD3DOcclusionQuery, *m_pD3DEventQuery, *m_pD3DPipelineStatsQuery; // Queries

	ID3D11Predicate *m_pD3DOccPredicate; // Occlusion predicate

	ID3D11CommandList *m_pD3DCommandList; // Command list which encapsulates rendering commands

	ID3D11Counter *m_pD3DCounter; // Counter

	ID3D11Asynchronous *m_pD3DAsynchronous; // For asynchronous GPU operations

	ID3D11ComputeShader *m_pD3DComputeShader; // Compute shader

	ID3D11ClassLinkage *m_pD3DClassLinkage; // Class linkage

	ID3D11Texture2D *m_pD3DSharedTexture; // Offscreen texture which D2D will render onto

	ID3D11ShaderResourceView *m_pD3DSRV; // SRV for 2D data

#ifdef _DEBUG // Debug version

	// Debugging layer
	ID3D11Debug *m_pD3DDebug; // Debug

	ID3D11InfoQueue *m_pD3DInfoQueue; // Information queue

#endif // _DEBUG

	DXGI_ADAPTER_DESC m_oDXGIAdapterDesc; // Will hold the description of an adapter

	DXGI_OUTPUT_DESC m_oDXGIOutputDesc; // Output description

	D3D11_QUERY_DATA_PIPELINE_STATISTICS m_oD3DQueryDataPipelineStats; // Graphics pipeline stats

	//
	// Direct3D 11

	std::mutex m_oMultithreadedRenderMutex; // Mutex for the synchronization of multi-threaded rendering

	HANDLE m_hSharedResource; // Handle to shared resource

	float m_fRenderTargetColor[4]; // Render target color

	WCHAR m_szAdapterDesc[MAX_PATH]; // Will hold the adapter description

	UINT64 m_uiNumOfSamplesPassed; // Will hold a value specifying the number of samples passed the tests

	BOOL m_bFullscreenState; // Will hold the current fullscreen state
	bool m_bSolidFillMode; // Will hold a boolean value indicating the current fill mode

	bool m_bExitThread; // Will hold a value indicating if a thread should be exi

	HRESULT m_hResult; // Used for checking errors
};

extern CD3DGraphics *g_pD3DGraphics;

#endif // D3DGRAPHICS_H