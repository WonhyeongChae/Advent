#include "pch.h"
#include "D12CommandQueue.h"

namespace Engine
{
	D12CommandQueue::~D12CommandQueue()
	{
		Release();
	}

	void D12CommandQueue::Initialize(ID3D12Device* pDevice)
	{
		//Create the resources needed:
		//The queue itself
		//The fence

		//Direct commandqueue 
		D3D12_COMMAND_QUEUE_DESC description = {};
		description.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		description.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
		description.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		description.NodeMask = 0;

		MY_EVAL_HR(pDevice->CreateCommandQueue(&description, IID_PPV_ARGS(GetAddressOf())), "Error creating command queue");

		MY_EVAL_HR(pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(mFence.GetAddressOf())), "Error creating the fence");
	}

	void D12CommandQueue::Release()
	{
		if (Get())
		{
			Reset();
		}

		if (mFence.Get())
		{
			mFence.Reset();
		}
	}

}