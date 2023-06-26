Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer HpBarBuffer : register(b0)
{
	int maxHp;
	int curHp;
	int padding[2];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp, input.uv);
	float ratio = (float)curHp / (float)maxHp;
	if (ratio > 1)
		ratio = 1;
	if (input.uv.x > ratio)
		return float4 (0, 0, 0, 0);

	return color;
}