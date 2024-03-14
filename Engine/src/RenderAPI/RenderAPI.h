#pragma once
#include "EngineMin.h"
#include <Windows.h>
#include <DirectXMath.h>

#include "RenderDataTypes.h"

#include "DirectX12/DXGI/DXGISwapChain.h"

#include "DirectX12/Base/D12Device.h"

#include "DirectX12/Commands/D12CommandQueue.h"
#include "DirectX12/Commands/D12CommandList.h"

#include "DirectX12/Resource/D12Resource.h"

#include "DirectX12/Pipeline/D12PipelineState.h"
#include "DirectX12/Descriptors/D12DescriptorHeap.h"
#include "DirectX12/MemoryManagement/BufferUploader.h"

namespace Engine
{
	class MY_API RenderAPI
	{

	public:
		RenderAPI() = default;
		~RenderAPI();

		void Initialize(HWND hwnd, const UINT width, const UINT height);
		void UpdateDraw();
		void Release();

		auto GetDevice() -> ID3D12Device*
		{
			return mDevice.Get();
		}

		auto GetDescHeap() -> ID3D12DescriptorHeap*
		{
			return mDepthDescHeap.Get();
		}

	private:
		D12Device mDevice;

		D12CommandQueue mCommandQueue;
		D12CommandList mCommandList;

		DXGISwapChain mSwapChain;

		D12PipelineState mBasePipeline;
		D12Resource mDepthBuffer;

		D3D12_VIEWPORT mViewport;
		D3D12_RECT mSRRect;

		D12DescriptorHeap mDepthDescHeap;

		BufferUploader mBufferUploader;

		D12Resource mVertexBuffer;
		D12Resource mIndexBuffer;
		D12Resource mMaterialBuffer1;

		D3D12_VERTEX_BUFFER_VIEW mVBView;
		D3D12_INDEX_BUFFER_VIEW mIBView;

		D12Resource mCBPassData;
		Render::Light mLights[8];

		DirectX::XMMATRIX mViewProjectionMatrix;

	private:
		UINT mWidth = 0;
		UINT mHeight = 0;

	private:
		UINT mCurentidx = 0;
	};
}
