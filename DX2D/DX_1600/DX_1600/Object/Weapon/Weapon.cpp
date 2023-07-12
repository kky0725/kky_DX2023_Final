#include "framework.h"
#include "Weapon.h"

Weapon::Weapon(wstring string)
{
	_quad = make_shared<Quad>(string);
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(Vector2(10,10));

	_collider->GetTransform()->SetParent(_transform);
}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
	_transform->Update();
	_collider->Update();
}

void Weapon::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}