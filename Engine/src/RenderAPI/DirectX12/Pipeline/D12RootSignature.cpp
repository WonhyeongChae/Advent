#include "pch.h"
#include "D12RootSignature.h"

namespace Engine
{
	D12RootSignature::~D12RootSignature()
	{
		Release();
	}

	void D12RootSignature::Initialize(ID3D12Device* pDevice)
	{
		//b0 (t0) registerspace for a ConstantBuffer
		D3D12_ROOT_PARAMETER rootParameter[2];
		rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[0].Descriptor.ShaderRegister = 0;
		rootParameter[0].Descriptor.RegisterSpace = 0;
		rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[1].Descriptor.ShaderRegister = 1;
		rootParameter[1].Descriptor.RegisterSpace = 0;
		rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		D3D12_VERSIONED_ROOT_SIGNATURE_DESC rsDesc = { };
		rsDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_0;
		rsDesc.Desc_1_0.pParameters = rootParameter;
		rsDesc.Desc_1_0.NumParameters = 2;
		rsDesc.Desc_1_0.NumStaticSamplers = 0;
		rsDesc.Desc_1_0.pStaticSamplers = 0;
		rsDesc.Desc_1_0.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* pSerializedRS = nullptr;
		ID3DBlob* pErrorBlob = nullptr;

		MY_EVAL_HR(D3D12SerializeVersionedRootSignature(&rsDesc, &pSerializedRS, &pErrorBlob), "Error serializing the root signature");

		if (pErrorBlob)
		{
			PRINT_N("Rootsignature serialization error: " << (const char*)pErrorBlob->GetBufferPointer());
		}

		MY_EVAL_HR(pDevice->CreateRootSignature(0, pSerializedRS->GetBufferPointer(), pSerializedRS->GetBufferSize(), IID_PPV_ARGS(GetAddressOf())), "Error creating the root signature");
	}

	void D12RootSignature::Release()
	{
		if (Get())
		{
			Reset();
		}
	}
}
