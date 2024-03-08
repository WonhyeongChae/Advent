#include "pch.h"
#include "Application.h"
//#include <windowsx.h>

#include "RenderAPI/DirectX12/Debug/DXGIDebug.h"

namespace Engine
{
	LRESULT CALLBACK WindProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_NCCREATE:
		{
			LPCREATESTRUCT param = reinterpret_cast<LPCREATESTRUCT>(lparam);
			Application* pApplication = reinterpret_cast<Application*>(param->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApplication));
			std::cout << "Create process started..." << std::endl;
			break;
		}
		case WM_CREATE:
		{
			Application* pApplication = reinterpret_cast<Application*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			pApplication->OnCreate(hwnd);
			break;
		}
		case WM_DESTROY:
		{
			Application* pApplication = reinterpret_cast<Application*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			pApplication->OnDestroy();
			PostQuitMessage(0);
			break;
		}
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}


	bool Application::Initialize()
	{
		RECT windowRect = { 0, 0, static_cast<LONG>(1280), static_cast<LONG>(720) };
		::AdjustWindowRect(&windowRect, WS_TILEDWINDOW, FALSE);

		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		int windowX = std::max<int>(0, (mScreenInfo.first - windowWidth) / 2);
		int windowY = std::max<int>(0, (mScreenInfo.second - windowHeight) / 2);

		WNDCLASS wndClass = {};
		wndClass.lpszClassName = L"BaseWindowClass";
		wndClass.style = 0;
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(BIBOO_ICON));
		wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
		wndClass.lpszMenuName = 0;
		wndClass.hInstance = 0;
		wndClass.lpfnWndProc = WindProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;

		RegisterClass(&wndClass);

		mWindowHandle = CreateWindow(L"BaseWindowClass", L"BIBOO", WS_TILEDWINDOW, windowX, windowY, windowWidth, windowHeight, 0, 0, 0, this); //refer back to the lParam stuff later

		if (!mWindowHandle)
		{
			return false;
		}

		ShowWindow(mWindowHandle, SW_SHOW);
		UpdateWindow(mWindowHandle);

		mIsRunning = true;

		return mIsRunning;
	}

	void Application::OnCreate(HWND hwnd)
	{
		std::cout << "Created window" << std::endl;
		mRenderer.Initialize(hwnd);
	}

	void Application::Update()
	{
		MSG message;

		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	void Application::OnDestroy()
	{
		std::cout << "Closed the window - shutting down application" << std::endl;
#ifdef _DEBUG || DEBUG
		DXGIDebug::Get().GetLiveObjects();
#endif // _DEBUG || DEBUG
		mIsRunning = false;
	}

}