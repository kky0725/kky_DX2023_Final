#include "framework.h"
#include "ShortSword.h"

ShortSword::ShortSword()
	:Weapon(L"Resource/Weapon/ShortSword.png", Vector2(65.0f, 18.0f))
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;

	_transform->SetScale(Vector2(5.0f, 5.0f));
	_collider->SetPosition(Vector2(2.5f, 0.0f));
	
	_isActive = false;
}

ShortSword::~ShortSword()
{
}

void ShortSword::Update()
{
	Weapon::Update();
}

void ShortSword::Render()
{
	Weapon::Render();
}
