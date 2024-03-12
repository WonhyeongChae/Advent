#pragma once

namespace Engine
{
	class ImGuiManager 
	{
	public:
		ImGuiManager() = default;
		~ImGuiManager()
		{};

		auto Initialize(HWND handle) -> void;
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