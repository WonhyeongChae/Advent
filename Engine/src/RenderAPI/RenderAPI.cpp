#include "pch.h"
#include "RenderAPI.h"

#include "DirectX12/DXGI/DXGIFactory.h"
#include "DirectX12/DXGI/DXGIAdapter.h"

#include "DirectX12/Debug/D12Debug.h"

namespace Engine
{
	RenderAPI::~RenderAPI()
	{
	}

	void RenderAPI::Initialize(HWND hwnd)
	{
#ifdef _DEBUG || DEBUG
		D12Debug::Get().Enable();
#endif // _DEBUG || DEBUG

		DXGIFactory factory;

		DXGIAdapter adapter = factory.GetAdapter();

		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		PRINT_W_N("Selected device " << desc.Description);

		mDevice.Init(adapter.Get());

		mDevice->SetName(L"Main virtual device");

	}
}