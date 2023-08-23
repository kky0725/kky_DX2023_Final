#pragma once
class ShaderManager : public Singleton<ShaderManager>
{
public:
	shared_ptr<VertexShader> AddVS(wstring path);
	shared_ptr<PixelShader> AddPS(wstring path);

private:
	ShaderManager();
	~ShaderManager();

	static ShaderManager* _instance;

	unordered_map<wstring, shared_ptr<Shader>> _shaderMap;
};

