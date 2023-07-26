#include "framework.h"
#include "SkelSword.h"

SkelSword::SkelSword()
	:Weapon(L"Resource/Monster/SkelSword.png", Vector2(50.0f, 15.0f))
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;

	_transform->SetScale(Vector2(3.0f, 3.0f));
	_transform->SetPosition(Vector2(-10.0f, 0.0f));
	_collider->SetPosition(Vector2(40.0f, 0.0f));
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
