#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
    _vs = ADD_VS(L"Shader/TextureVS.hlsl");
    _ps = ADD_PS(L"Shader/TexturePS.hlsl");
    CreateNoneImgVertices(Vector2(500,10));
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());

    //랜더링 할 때 srv가 필요한데 없어서 실행 안되는 문제 해결 예정
}

Quad::Quad(wstring srvfile)
{
    _vs = ADD_VS(L"Shader/TextureVS.hlsl");
    _ps = ADD_PS(L"Shader/TexturePS.hlsl");

    _srv = ADD_SRV(srvfile);

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

Quad::Quad(wstring srvfile, Vector2 size)
{
    _vs = ADD_VS(L"Shader/TextureVS.hlsl");
    _ps = ADD_PS(L"Shader/TexturePS.hlsl");

    _srv = ADD_SRV(srvfile);
    _halfSize = size * 0.5f;

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

Quad::~Quad()
{
}


void Quad::Render()
{
    _vertexBuffer->Set(0);
    _indexBuffer->Set();

    _vs.lock()->Set();

    _srv.lock()->Set(0);
    SAMPLER->Set(0);

    _ps.lock()->Set();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::CreateVertices()
{
    if (_halfSize.x == 0.0f && _halfSize.y == 0.0f)
    {
    _halfSize.x = _srv.lock()->GetImageSize().x * 0.5f;
    _halfSize.y = _srv.lock()->GetImageSize().y * 0.5f;
    }

    Vertex_Texture temp;

    temp.pos = { XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f) };
    temp.uv = { 0.0f, 0.0f };
    _vertices.push_back(temp);// 왼쪽 위

    temp.pos = { XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f) };
    temp.uv = { 1.0f, 0.0f };
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = { XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f) };
    temp.uv = { 1.0f, 1.0f };
    _vertices.push_back(temp);// 오른쪽 아래=> 시계방향// 방향도 중요하다.

    temp.pos = { XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f) };
    temp.uv = { 0.0f, 1.0f };
    _vertices.push_back(temp); // 왼쪽 아래 => 시계방향// 방향도 중요하다.

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}

void Quad::CreateNoneImgVertices(Vector2 halfSize)
{
    Vertex_Texture temp;
    
    temp.pos = { XMFLOAT3(-halfSize.x, halfSize.y, 0.0f) };
    temp.uv = { 0.0f, 0.0f };
    _vertices.push_back(temp);// 왼쪽 위

    temp.pos = { XMFLOAT3(halfSize.x, halfSize.y, 0.0f) };
    temp.uv = { 1.0f, 0.0f };
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = { XMFLOAT3(halfSize.x, -halfSize.y, 0.0f) };
    temp.uv = { 1.0f, 1.0f };
    _vertices.push_back(temp);// 오른쪽 아래=> 시계방향// 방향도 중요하다.

    temp.pos = { XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f) };
    temp.uv = { 0.0f, 1.0f };
    _vertices.push_back(temp); // 왼쪽 아래 => 시계방향// 방향도 중요하다.

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}
