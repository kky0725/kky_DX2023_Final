Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ValueBuffer : register(b0)
{
	float value;
	float padding2[3];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, value);

	return color;
}