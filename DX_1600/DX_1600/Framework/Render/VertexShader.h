#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	virtual ~VertexShader();
	
	void CreateBlob(wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	virtual void Set() override;

private:
	ComPtr<ID3D11VertexShader> _vertexShader; // 각 정점에 대응되는 계산식... World, View, Projection
	ComPtr<ID3D11InputLayout> _inputLayout; // 어디서 끊어서 읽어야 할지.. 정보의 배치
	ComPtr<ID3D11ShaderReflection> _reflection;//런타임에서 구조와 행위를 관리
};

