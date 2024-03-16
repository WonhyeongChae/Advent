#pragma once

namespace Engine
{
	class DX12PipelineState
	{
	public:
		DX12PipelineState(DX12RootSignature& rootSignature, InputLayout& layout, VertexShader& vs, PixelShader& ps);
		~DX12PipelineState();

		ID3D12PipelineState* getPso() const { return mPso; }
	private:
		DX12PipelineState();
		DX12PipelineState(DX12PipelineState&);

		ID3D12PipelineState* mPso;
	};
}