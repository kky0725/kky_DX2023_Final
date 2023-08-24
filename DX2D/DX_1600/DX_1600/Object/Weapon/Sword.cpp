#include "framework.h"
#include "Sword.h"

Sword::Sword(ItemType type, string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring string, Vector2 size)
	:Weapon(type, name, price, itmeDesc, iconSrvfile, ID, minAtk, maxAtk, atkPerSec, string, size)
{
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
