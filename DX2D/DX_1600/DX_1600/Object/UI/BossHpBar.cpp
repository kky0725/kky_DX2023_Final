#include "framework.h"
#include "BossHpBar.h"

BossHpBar::BossHpBar()
	:HpBar(Vector2(100.0f, 20.0f))
{
	_base = make_shared<Quad>(L"Resource/UI/BossLifeBase.png");
	_life = make_shared<Quad>(L"Resource/UI/LifeBar.png", _size);
	_life->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_baseTransform->SetPosition(Vector2(0.0f, -280.0f));
	_lifeTransform->SetPosition(Vector2(+10.0f, 0.0f));

	_baseTransform->SetScale(Vector2(4.0f, 3.0f));
	_lifeTransform->SetScale(Vector2(1.01f, 0.75f));

	_baseTransform->SetParent(nullptr);

	_portait = make_shared<Quad>(L"Resource/UI/BossSkellPortrait.png");
	_portaitTransform = make_shared<Transform>();

	_portaitTransform->SetParent(_baseTransform);
	_portaitTransform->SetPosition(Vector2(-51.0f, 0.0f));
	_portaitTransform->Update();
}

BossHpBar::~BossHpBar()
{
}

void BossHpBar::Update()
{
	HpBar::Update();
}

void BossHpBar::PostRender()
{
	_intBuffer->SetPsBuffer(0);
	_baseTransform->SetBuffer(0);
	_back->Render();

	_lifeTransform->SetBuffer(0);
	_life->Render();

	_portaitTransform->SetBuffer(0);
	_portait->Render();

	_baseTransform->SetBuffer(0);
	_base->Render();

}
