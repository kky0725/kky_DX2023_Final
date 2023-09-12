#include "framework.h"
#include "PlayerHpBar.h"

PlayerHpBar::PlayerHpBar()
	:HpBar(Vector2(50.0f, 10.0f))
{
	_base = make_shared<Quad>(L"Resource/UI/PlayerLifeBase.png");
	_back = make_shared<Quad>(L"Resource/UI/PlayerLifeBack.png");
	_life = make_shared<Quad>(L"Resource/UI/LifeBar.png", _size);
	_life->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_baseTransform->SetPosition(Vector2(-560.0f, 340.0f));
	_lifeTransform->SetPosition(Vector2(+10.0f, 0.0f));

	_baseTransform->SetScale(Vector2(2.0f, 2.0f));
	_lifeTransform->SetScale(Vector2(1.0f, 1.0f));

	_baseTransform->SetParent(nullptr);
}

PlayerHpBar::~PlayerHpBar()
{
}

void PlayerHpBar::Update()
{
	HpBar::Update();
}

void PlayerHpBar::PostRender()
{
	_intBuffer->SetPsBuffer(0);
	_baseTransform->SetBuffer(0);
	_back->Render();

	_lifeTransform->SetBuffer(0);
	_life->Render();

	_baseTransform->SetBuffer(0);
	_base->Render();
}