#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0);
	~VertexBuffer();

	void CreateVertexBuffer();

	void Set(int slot = 0);


private:
	ComPtr<ID3D11Buffer> vertexBuffer; // �������� ��Ƴ��� ����

	void* _data = nullptr; //vertices �迭�� ����Ű�� ������

	UINT _stride = 0;
	UINT _offset = 0;
	UINT _count = 0;

};

