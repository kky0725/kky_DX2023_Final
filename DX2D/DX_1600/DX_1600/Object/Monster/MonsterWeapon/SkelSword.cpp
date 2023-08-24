#include "framework.h"
#include "SkelSword.h"

SkelSword::SkelSword()
	:Weapon(Item::ItemType::WEAPON, "해골검", 0, "해골 병사가 들고다니는 검", L"Resource/Monster/SkelSword.png", 101, 8, 10, 3.03f, L"Resource/Monster/SkelSword.png", Vector2(50.0f, 15.0f))
{
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
