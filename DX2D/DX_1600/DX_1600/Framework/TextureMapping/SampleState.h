#pragma once
class SampleState
{
public:
	SampleState();
	~SampleState();

	void Set(int slot = 0);

private:
	ComPtr<ID3D11SamplerState> samplerState;
};

