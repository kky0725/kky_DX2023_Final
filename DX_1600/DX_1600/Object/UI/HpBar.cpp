#include "framework.h"
#include "HpBar.h"

HpBar::HpBar(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_intBuffer = make_shared<IntBuffer>();
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
	_transform->Update();
	_intBuffer->Update();
}

void HpBar::PostRender()
{
	_intBuffer->SetPsBuffer(0);
	_transform->SetBuffer(0);
	_quad->Render();
}
