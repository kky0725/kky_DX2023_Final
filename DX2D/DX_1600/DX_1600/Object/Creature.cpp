#include "framework.h"
#include "Creature.h"

Creature::Creature(wstring string, Vector2 size, float radius)
{
	_quad = make_shared<Quad>(string, size);
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);

	_transform->SetParent(_collider->GetTransform());
}

Creature::Creature(wstring string, float radius)
{
	_quad = make_shared<Quad>(string);
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);

	_transform->SetParent(_collider->GetTransform());
}

Creature::Creature(float radius)
{
	_quad == nullptr;
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);

	_transform->SetParent(_collider->GetTransform());
}

Creature::~Creature()
{
}

void Creature::Update()
{
	if (!_isActive)
		return;
	_transform->Update();
	_collider->Update();
}

void Creature::Render()
{
	if (!_isActive)
		return;
	if (_quad != nullptr)
	{
		_transform->SetBuffer(0);
		_quad->Render();
	}
	_collider->Render();
}

void Creature::PostRender()
{
}

void Creature::Damaged(int damge)
{
	if (!_isActive)
		return;
	_hp -= damge;

	if (_hp < 1)
	{
		_hp = 0;
		_isActive = false;
	}
}
