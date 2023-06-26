#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	virtual ~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	virtual void Set() override;

private:
	ComPtr<ID3D11PixelShader>	_pixelShader; // 면에 해당하는 픽셀 계산식
};

