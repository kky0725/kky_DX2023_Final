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

	_maxHpFont = make_shared<NumFont>(_fontSize);
	_curHpFont = make_shared<NumFont>(_fontSize);

	_maxHpFont->SetPosition(Vector2(-540.0f + 30.0f, 340.0f));
	_curHpFont->SetPosition(Vector2(-540.0f - 20.0f, 340.0f));

	_slice = make_shared<Quad>(L"Resource/UI/slice.png", _fontSize);
	_sliceTransform = make_shared<Transform>();
	_sliceTransform->SetPosition(Vector2(-540.0f - 10.0f, 340.0f));
	_sliceTransform->SetScale(Vector2(0.8f, 1.2f));
	_sliceTransform->Update();
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

	_maxHpFont->Render();
	_curHpFont->Render();

	_sliceTransform->SetBuffer(0);
	_slice->Render();
}

void PlayerHpBar::SetNumber()
{
	_maxHpFont->SetNumber(_maxHP);
	_curHpFont->SetNumber(_curHP);
}
