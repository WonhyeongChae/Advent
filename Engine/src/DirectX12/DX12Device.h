#pragma once

using namespace Microsoft::WRL;

static constexpr UINT FRAME_BUFFER_COUNT = 3;

namespace Engine
{
	class DX12Device
	{
	public:
		auto GetInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = std::make_shared<DX12Device>(DX12Device());
			}
			return mInstance;
		}

	public:
		static void Initialize(const HWND& hWnd);
		static void Shutdown();

		inline auto GetDevice() -> ID3D12Device* { return mDevice; }
		inline auto GetSwapChain() -> IDXGISwapChain3* { return mSwapChain; }

		inline auto GetBackBuffer() -> ID3D12Resource* { return mBackBuffeRtv[mFrameIndex]; }
		inline auto	GetBackBufferDescriptor() -> D3D12_CPU_DESCRIPTOR_HANDLE
		{
			auto handle(mBackBuffeRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
			handle.ptr += mFrameIndex * mRtvDescriptorSize;
			return handle;
		}

		inline auto GetFrameCommandList() -> ID3D12GraphicsCommandList* { return mCommandList[0]; }

		void BeginFrame();
		void EndFrameAndSwap(bool vsyncEnabled);
		void CloseBufferedFramesBeforeShutdown();


	private:
		DX12Device() = default;
		DX12Device(DX12Device&);
		//Dx12Device(const Dx12Device&);
		~DX12Device();

		void EnableShaderBasedValidation();

		void internalInitialise(const HWND& hWnd);
		void internalShutdown();

		void waitForPreviousFrame(int frameIndex = -1);

#ifdef _DEBUG
		ComPtr<ID3D12Debug>					mDebugController0;
		ComPtr<ID3D12Debug1>				mDebugController1;
#endif

		ID3D12Device* mDevice;									// the pointer to our Direct3D device interface
		IDXGISwapChain3* mSwapChain;									// the pointer to the swap chain interface
		int									mFrameIndex;								// Current swap chain frame index (back buffer)
		ID3D12CommandQueue* mCommandQueue;								// command list container

		ID3D12DescriptorHeap* mBackBuffeRtvDescriptorHeap;				// a descriptor heap to hold back buffers ressource descriptors (equivalent to views)
		ID3D12Resource* mBackBuffeRtv[FRAME_BUFFER_COUNT];			// back buffer render target view
		ID3D12CommandAllocator* mCommandAllocator[FRAME_BUFFER_COUNT];		// Command allocator in GPU memory. Need a many as frameCount as cannot rest while in use by GPU
		ID3D12GraphicsCommandList* mCommandList[1];							// A command list to record commands into. No multi-thread so only one is needed

		ID3D12Fence* mFrameFence[FRAME_BUFFER_COUNT];			// locked while commandlist is being executed by the gpu.
		HANDLE								mFrameFenceEvent;							// a handle to an event when our fence is unlocked by the gpu
		UINT64								mFrameFenceValue[FRAME_BUFFER_COUNT];		// Incremented each frame. each fence will have its own value

		// GPU information
		IDXGIAdapter3* mAdapter;									// Current device adapter
		DXGI_ADAPTER_DESC2					mAdapterDesc;								// Adapter information
		DXGI_QUERY_VIDEO_MEMORY_INFO		mVideoMemInfo;								// Last sampled video memory usage (allocations, etc)
		int									mCsuDescriptorSize;							// CBV SRV UAV descriptor size for the selected GPU device
		int									mRtvDescriptorSize;							// RTV descriptor size for the selected GPU device
		int									mSamDescriptorSize;							// Sampler descriptor size for the selected GPU device
		int									mDsvDescriptorSize;							// DSV descriptor size for the selected GPU device

		static std::shared_ptr<DX12Device>	mInstance;
	};
}
