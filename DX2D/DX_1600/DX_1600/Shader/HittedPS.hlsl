Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int	   isRight;
	int	   padding;
}

cbuffer HpBarBuffer : register(b1)
{
	int hitted;
	int padding2[3];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	if (isRight == 0)
		input.uv.x = 1 - input.uv.x;
	//intput.uvx : 0~1;
	input.uv.x = (startPos.x / imageSize.x) + (size.x / imageSize.x) * input.uv.x;
	input.uv.y = (startPos.y / imageSize.y) + (size.y / imageSize.y) * input.uv.y;


	float4 color = map.Sample(samp, input.uv);
	
	if (hitted == 1)
		color += float4 (1, 0, 0, 0);
	
	return color;
}