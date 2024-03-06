#pragma once
#include "EngineMin.h"

#include <Windows.h>

#include "RenderAPI/RenderAPI.h"

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
	};
}
