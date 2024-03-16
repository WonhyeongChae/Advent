#pragma once

namespace Engine
{
	class DX12RenderBuffer
	{
	public:
		DX12RenderBuffer(unsigned int sizeByte, void* initData = nullptr, bool allowUAV = false);
		~DX12RenderBuffer();
		void resourceTransitionBarrier(D3D12_RESOURCE_STATES newState);
		inline auto getGPUVirtualAddress() -> D3D12_GPU_VIRTUAL_ADDRESS { return mBuffer->GetGPUVirtualAddress(); }
	private:
		DX12RenderBuffer();
		DX12RenderBuffer(DX12RenderBuffer&);

		ID3D12Resource* mBuffer;
		D3D12_RESOURCE_STATES mResourceState;
		ID3D12Resource* mUploadHeap;// private upload heap, TODO: handle that on Dx12Device
	};
}