#pragma once
namespace Engine
{
	class BaseShader
	{
	public:
		BaseShader(const TCHAR* filename, const char* entryFunction, const char* profile);
		virtual ~BaseShader();
		bool compilationSuccessful() { return mShaderBytecode != nullptr; }
		LPVOID getShaderByteCode() const { return mShaderBytecode->GetBufferPointer(); }
		SIZE_T getShaderByteCodeSize() const { return mShaderBytecode->GetBufferSize(); }
	protected:
		ID3DBlob* mShaderBytecode;

	private:
		BaseShader();
		BaseShader(BaseShader&);
	};

	class VertexShader : public BaseShader
	{
	public:
		VertexShader(const TCHAR* filename, const char* entryFunction);
		virtual ~VertexShader();
	};

	class PixelShader : public BaseShader
	{
	public:
		PixelShader(const TCHAR* filename, const char* entryFunction);
		virtual ~PixelShader();
	};
}