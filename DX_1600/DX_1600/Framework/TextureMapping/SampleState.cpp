#include "framework.h"
#include "SampleState.h"

SampleState::SampleState()
{
    D3D11_SAMPLER_DESC sampleDesc = {};
    sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampleDesc.MinLOD = 0;
    sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;

    DEVICE->CreateSamplerState(&sampleDesc, samplerState.GetAddressOf());
}

SampleState::~SampleState()
{
}

void SampleState::Set(int slot)
{
	DC->PSSetSamplers(slot, 1, samplerState.GetAddressOf());
}
