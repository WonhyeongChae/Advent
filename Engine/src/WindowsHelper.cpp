#include "pch.h"

#include "WindowsHelper.h"
#include "WindowsInput.h"

namespace Engine
{
	WindowsHelper::WindowsHelper(HINSTANCE hInstance, const RECT& clientRect, int nCmdShow, LPCWSTR windowName)
	{
	}
	WindowsHelper::~WindowsHelper()
	{
	}
	void WindowsHelper::ShowWindow()
	{
	}
	bool WindowsHelper::ProcessSingleMessage(MSG& msg)
	{
		return false;
	}
	WindowsHelper::WindowsHelper()
	{
	}
	void WindowsHelper::ProcessMouseMessage(MSG& msg)
	{
	}
	void WindowsHelper::ProcessKeyMessage(MSG& msg)
	{
	}
}