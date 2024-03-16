#pragma once

namespace Engine
{
	class DX12RootSignature
	{
	public:
		DX12RootSignature(bool noneOrIA);	// default root signature: empty or using input assembler
		~DX12RootSignature();

		ID3D12RootSignature* getRootsignature() const { return mRootSignature; }
	private:
		DX12RootSignature();
		DX12RootSignature(DX12RootSignature&);

		ID3D12RootSignature* mRootSignature;
	};
}