#pragma once

#include <Windows.h>

#include "RenderAPI/RenderAPI.h"

namespace Engine
{
	class ImGuiManager 
	{
	public:
		ImGuiManager() = default;
		~ImGuiManager()
		{};

		auto Initialize(HWND hwnd, const RenderAPI& renderer) -> void;
		auto GuiUpdate() -> void;
		auto SetImguiContext() -> void;
		auto StartFrame() -> void;
		auto EndFrame() -> void;

	private:
		int num = 0;
		enum ImGuiId
		{
			COUNT = 4000
		};
		
	};
}