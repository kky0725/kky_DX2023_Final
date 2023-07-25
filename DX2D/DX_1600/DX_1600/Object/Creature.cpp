#include "framework.h"
#include "Creature.h"

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
	CheckDamaged();
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
	if (_damaged)
		return;
	_hp -= damge;
	_damaged = true;

	if (_hp < 1)
	{
		_hp = 0;
		_isActive = false;
	}
}

void Creature::CheckDamaged()
{
	if (!_damaged)
		return;

	_DCtime += DELTA_TIME;
	if (_DCtime > 0.1f)
	{
		_damaged = false;
		_DCtime = 0.0f;
	}
}
