#include "framework.h"
#include "ShortSword.h"

ShortSword::ShortSword()
	:Weapon(L"Resource/Weapon/ShortSword.png")
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;

	_transform->SetScale(Vector2(5.0f, 5.0f));
	_collider->GetTransform()->SetScale(Vector2(1.3f, 0.5f));
	_collider->SetPosition(Vector2(2.5f, 0.0f));
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
