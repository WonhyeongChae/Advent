#pragma once

constexpr unsigned int INPUT_LAYOUT_MAX_ELEMENT_COUNT = 8;

namespace Engine
{
	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();
		auto AppendSimpleVertexDataToInputLayout() -> void;
		auto GetLayoutDesc() const -> D3D12_INPUT_LAYOUT_DESC*;

	private:
		InputLayout(InputLayout&);

		D3D12_INPUT_ELEMENT_DESC	mInputLayoutElements[INPUT_LAYOUT_MAX_ELEMENT_COUNT];
		D3D12_INPUT_LAYOUT_DESC		mInputLayout;
	};
}