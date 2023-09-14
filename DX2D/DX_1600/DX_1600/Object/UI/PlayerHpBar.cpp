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

	_maxTen = make_shared<NumFont>(_fontSize);
	_maxOne = make_shared<NumFont>(_fontSize);
	_curTen = make_shared<NumFont>(_fontSize);
	_curOne = make_shared<NumFont>(_fontSize);

	_maxTen->SetPosition(Vector2(-540.0f - 50.0f, 340.0f));
	_maxOne->SetPosition(Vector2(-540.0f - 40.0f, 340.0f));
	_curTen->SetPosition(Vector2(-540.0f - 10.0f, 340.0f));
	_curOne->SetPosition(Vector2(-540.0f -  0.0f, 340.0f));
}

PlayerHpBar::~PlayerHpBar()
{
}

void PlayerHpBar::Update()
{
	HpBar::Update();
	SetNumber();
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

	_maxTen->Render();
	_maxOne->Render();
	_curTen->Render();
	_curOne->Render();
}

void PlayerHpBar::SetNumber()
{
	_maxTen->SetNumber(0);
	_maxOne->SetNumber(0);
	_curTen->SetNumber(0);
	_curOne->SetNumber(0);
}
