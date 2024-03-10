#include "pch.h"
#include "RenderAPI.h"

#include <vector>

#include "DirectX12/DXGI/DXGIFactory.h"
#include "DirectX12/DXGI/DXGIAdapter.h"

#include "DirectX12/Debug/D12Debug.h"

#include "../Utilities/Utilities.h"

namespace Engine
{
	using namespace Render;

	RenderAPI::~RenderAPI()
	{
		Release();
	}

	void RenderAPI::Initialize(HWND hwnd, const UINT width, const UINT height)
	{
		mWidth = width;
		mHeight = height;

		DXGIFactory factory;
		DXGIAdapter adapter = factory.GetAdapter();
#ifdef _DEBUG
		D12Debug::Get().Enable();

		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		PRINT_W_N("Selected device " << desc.Description);

#endif // _DEBUG

		mDevice.Init(adapter.Get());
		mDevice->SetName(L"Main virtual device");

		mCommandQueue.Initialize(mDevice.Get());
		mCommandList.Initialize(mDevice.Get());

		mSwapChain.Initialize(mDevice.Get(), factory.Get(), mCommandQueue.Get(), hwnd, mWidth, mHeight);

		mDynamicVertexBuffer.Initialize(mDevice.Get(), KBs(16), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
		mDynamicVertexBuffer.Get()->SetName(L"Dynamic vertex buffer");

		std::vector<Vertex> vertices;

		for (int i = 0; i < 3; i++)
		{
			Vertex vertexData;
			vertexData.color = { 0.0f,1.0f,0.0f,1.0f };

			if (i == 0)
			{
				vertexData.position = { -1.0f, -1.0f, 0.0f };
			}
			else if (i == 1)
			{
				vertexData.position = { 0.0f, 1.0f, 0.0f };
			}
			else
			{
				vertexData.position = { 1.0f, -1.0f, 0.0f };
			}
			vertices.push_back(vertexData);
		}

		memcpy(mDynamicVertexBuffer.GetCPUMemory(), vertices.data(), sizeof(Vertex) * vertices.size());
		
		mDynamicVBView.BufferLocation = mDynamicVertexBuffer.Get()->GetGPUVirtualAddress();
		mDynamicVBView.StrideInBytes = sizeof(Vertex);
		mDynamicVBView.SizeInBytes = KBs(16);

		/*
		//ONLY CPU = default ram / cache
		//ONLY GPU = default heap on GPU (VRAM)
		//Shared CPU and GPU = with read/write for all - it's stored on the GPU
		//Readback memory on GPU (With Read from the CPU)
		*/

		mBasePipeline.Initialize(mDevice.Get());

		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mViewport.Width = static_cast<FLOAT>(mWidth);
		mViewport.Height = static_cast<FLOAT>(mHeight);
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		mSRRect.left = 0;
		mSRRect.right = static_cast<LONG>(mViewport.Width);
		mSRRect.top = 0;
		mSRRect.bottom = static_cast<LONG>(mViewport.Height);

		DirectX::XMMATRIX viewMatrix;
		viewMatrix = DirectX::XMMatrixLookAtLH({ 0.0f,1.0f,-3.0f,0.0f }, { 0.0f,0.0f,0.0f,0.0f }, { 0.0f,1.0f,0.0f,0.0f });
		DirectX::XMMATRIX projectionMatrix;
		projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.2217304764f, 16.0f / 9.0f, 1.0f, 50.0f);
		mViewProjectionMatrix = viewMatrix * projectionMatrix;

		mCBPassData.Initialize(mDevice.Get(), Utils::CalculateConstantbufferAlignment(sizeof(PassData)), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
		/*
		1 Video:
		Math/Coordinate system: Some DirectXMath functions to setup our 3d world.

		Discuss a bit about the view and the projection matrix

		2 Video:

		Uploading the "camera"/viewpoint matrix that helps translate from 3D space into 2D screen space
		- Constantbuffer
		- Bind that to the pipeline

		3 Video:
		Rendering a 3D box -creating the vertices and uploading
		Depth buffering

		4 Video:
		- "uploading" data to the default heap
		- resource barriers

		Define a 3D space, with 3 axes
		Define the coordinate system axes in relation to each other...
		- I.E. Which axis is up? Which is forward? Which the right axis?

		Define a camera/eye position with a looking direction

		Define a 3D object at the origin (0,0,0)
		Offset the camera and set it to look at the origin

		Adress the math and the actual shader computations that translate from 3D world space into 2d "clipspace"/"screenspace"

		Lastly we'll probably need an episode on the depth buffer
		*/
	}

	void RenderAPI::UpdateDraw()
	{
		memcpy(mCBPassData.GetCPUMemory(), &mViewProjectionMatrix, sizeof(PassData));
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);

		const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = mSwapChain.GetCurrentRTVHandle();
		mCommandList.GFXCmd()->ClearRenderTargetView(rtvHandle, clearColor, 0, 0);
		mCommandList.GFXCmd()->OMSetRenderTargets(1, &rtvHandle, false, 0);

		mCommandList.GFXCmd()->RSSetViewports(1, &mViewport);
		mCommandList.GFXCmd()->RSSetScissorRects(1, &mSRRect);

		mCommandList.GFXCmd()->SetGraphicsRootSignature(mBasePipeline.GetRS());
		mCommandList.GFXCmd()->SetPipelineState(mBasePipeline.Get());
		mCommandList.GFXCmd()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mCommandList.GFXCmd()->IASetVertexBuffers(0, 1, &mDynamicVBView);
		mCommandList.GFXCmd()->SetGraphicsRootConstantBufferView(0, mCBPassData.Get()->GetGPUVirtualAddress());
		mCommandList.GFXCmd()->DrawInstanced(3, 1, 0, 0);

		barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = mSwapChain.GetCurrentRenderTarget();
		barrier.Transition.Subresource = 0;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		mCommandList.GFXCmd()->ResourceBarrier(1, &barrier);


		mCommandList.GFXCmd()->Close();
		mCommandQueue.M_ExecuteCommandList(mCommandList.Get());

		mSwapChain.Present();

		while (mCommandQueue.GetFence()->GetCompletedValue() < mCommandQueue.M_GetCurrentFenceValue())
		{
			_mm_pause();
		}

		mCommandList.ResetCommandList();
	}

	void RenderAPI::Release()
	{
		mDynamicVertexBuffer.Release();

		mCommandQueue.FlushQueue();

		mSwapChain.Release();

		mCommandList.Release();
		mCommandQueue.Release();

		if (mDevice.Get())
		{
			mDevice.Reset();
		}
	}
}