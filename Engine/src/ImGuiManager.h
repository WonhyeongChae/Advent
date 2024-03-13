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

		auto Initialize(HWND hwnd, RenderAPI& renderer) -> void;
		auto Update() -> void;
	private:
		int num = 0;
		enum ImGuiId
		{
			COUNT = 4000
		};
		
	};
}