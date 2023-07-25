#include "framework.h"
#include "SkelSword.h"

SkelSword::SkelSword()
	:Weapon(L"Resource/Monster/SkelSword.png", Vector2(60.0f, 20.0f))
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;

	_transform->SetScale(Vector2(5.0f, 5.0f));
	_collider->SetPosition(Vector2(2.5f, 0.0f));
}

SkelSword::~SkelSword()
{
}

void SkelSword::Update()
{
	Weapon::Update();
}

void SkelSword::Render()
{
	Weapon::Render();
}
