#include "ImGuiManager.h"

#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx12.h"


namespace Engine
{
	auto ImGuiManager::Initialize(HWND hwnd, RenderAPI& renderer) -> void
	{
		IMGUI_CHECKVERSION();
		auto context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.Colors[ImGuiCol_WindowBg].w = 0.f;
			style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
		}

		if (ImGui_ImplWin32_Init(hwnd))
			std::cout << "ImGui: Win32 Init success!\n";

		if (ImGui_ImplDX12_Init(renderer.GetDevice(), 3, DXGI_FORMAT_R8G8B8A8_UNORM, renderer.GetDescHeap(), renderer.GetDescHeap()->GetCPUDescriptorHandleForHeapStart(), renderer.GetDescHeap()->GetGPUDescriptorHandleForHeapStart()))
			std::cout << "ImGui: DX12 Init success!\n";

		if (ImGui_ImplDX12_CreateDeviceObjects())
			std::cout << "ImGui: CreateDeviceObjects success!\n";		
	}

	auto ImGuiManager::Update() -> void
	{
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX12_NewFrame();
		ImGui::NewFrame();

		auto show_demo = true;
		ImGui::ShowDemoWindow(&show_demo);
		
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), nullptr);
	}
}
