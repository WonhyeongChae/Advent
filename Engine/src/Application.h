#pragma once
#include "EngineMin.h"

#include <Windows.h>
#include <utility>

#include "RenderAPI/RenderAPI.h"

struct WindowSetup
{
	RECT windowRect = { 0, 0, static_cast<LONG>(1280), static_cast<LONG>(720) };

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	int windowX = std::max<int>(0, (screenX - windowWidth) / 2);
	int windowY = std::max<int>(0, (screenY - windowHeight) / 2);
};

namespace Engine
{
	class MY_API Application
	{
	public:
		Application() = default;

		bool Initialize();

		void OnCreate(HWND hwnd);


		void Update();


		void OnDestroy();

		inline bool IsRunning() const { return mIsRunning; }

	private: //subsystems:

		RenderAPI mRenderer;

	private: //variables:
		HWND mWindowHandle = nullptr;
		bool mIsRunning = false;

		WindowSetup mWindowSetup;
	};
}
