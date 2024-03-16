#pragma once

namespace Engine
{
	class WindowsHelper
	{
	public:
		WindowsHelper(
			HINSTANCE hInstance,
			const RECT& clientRect,
			int nCmdShow,
			LPCWSTR windowName);
		~WindowsHelper();

		void ShowWindow();

		bool ProcessSingleMessage(MSG& msg);

		auto GetInputData() -> const WindowsInputData&
		{
			return mInput;
		}
		void ClearInputEvents()
		{
			mInput.mInputEvents.clear();
		}

		auto GetHwnd() const -> const HWND { return mHWnd; }

	private:
		WindowsHelper();

		void ProcessMouseMessage(MSG& msg);
		void ProcessKeyMessage(MSG& msg);

		HINSTANCE		mHInstance;			/// The application instance
		HWND			mHWnd;				/// The handle for the window, filled by a function
		WNDCLASSEX		mWc;				/// This struct holds information for the window class
		RECT			mClientRect;		/// The client rectangle where we render into
		int				mNCmdShow;			/// Window show cmd

		WindowsInputData mInput;				/// input event and status (mouse, keyboard, etc.)
	};
}