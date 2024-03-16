#include "pch.h"

#include "DX12Shader.h"

namespace Engine
{
	BaseShader::BaseShader(const TCHAR* filename, const char* entryFunction, const char* profile)
	{
	}
	BaseShader::~BaseShader()
	{
	}
	BaseShader::BaseShader()
	{
	}
	BaseShader::BaseShader(BaseShader&)
	{
	}
	VertexShader::VertexShader(const TCHAR* filename, const char* entryFunction)
	{
	}
	VertexShader::~VertexShader()
	{
	}
	PixelShader::PixelShader(const TCHAR* filename, const char* entryFunction)
	{
	}
	PixelShader::~PixelShader()
	{
	}
}