#include "framework.h"
#include "Sword.h"

Sword::Sword(ItemType type, string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, int atkPerSec, wstring string, Vector2 size)
	:Weapon(type, name, price, itmeDesc, iconSrvfile, ID, minAtk, maxAtk, atkPerSec, string, size)
	//Weapon(L"Resource/Weapon/ShortSword.png", Vector2(65.0f, 18.0f))
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;

	_transform->SetScale(Vector2(5.0f, 5.0f));
	_collider->SetPosition(Vector2(2.5f, 0.0f));
	
	_isActive = false;
}

Sword::~Sword()
{
}

void Sword::Update()
{
	Weapon::Update();
}

void Sword::Render()
{
	Weapon::Render();
}
