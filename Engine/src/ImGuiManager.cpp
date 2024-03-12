#include "pch.h"
#include "ImGuiManager.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx12.h"

namespace Engine
{
	auto ImGuiManager::Initialize(HWND handle) -> void
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

		ImGui_ImplWin32_Init(handle);
		// ImGui_ImplDX12_Init();
	}
	auto ImGuiManager::SetImguiContext() -> void
	{}
	auto ImGuiManager::StartFrame() -> void
	{}
	auto ImGuiManager::EndFrame() -> void
	{}
}