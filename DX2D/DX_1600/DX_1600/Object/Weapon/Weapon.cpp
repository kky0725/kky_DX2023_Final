#include "framework.h"
#include "Weapon.h"

Weapon::Weapon()
{
	_type = WeaponType::GUN;
	_collider = make_shared<CircleCollider>(1.0f);
}

Weapon::Weapon(Vector2 size)
{
	_quad = nullptr;

	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(size);

	_transform->SetParent(_collider->GetTransform());
}

Weapon::Weapon(wstring string, Vector2 size)
{
	_quad = make_shared<Quad>(string);
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(size);

	_transform->SetParent(_collider->GetTransform());
}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	if(_quad != nullptr)
		_transform->Update();

	_collider->Update();
}

void Weapon::Render()
{
	if (_quad != nullptr)
	{
		_transform->SetBuffer(0);
		_quad->Render();
	}
	_collider->Render();
}

bool Weapon::WTIsSword()
{
	if (_type == WeaponType::SWORD)
		return true;

	return false;
}
