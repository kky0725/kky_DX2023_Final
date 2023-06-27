#include "framework.h"
#include "Creature.h"

Creature::Creature(wstring string, Vector2 size, float radius)
{
	_quad = make_shared<Quad>(string, size);
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);
}

Creature::Creature(wstring string, float radius)
{
	_quad = make_shared<Quad>(string);
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);
}

Creature::~Creature()
{
}

void Creature::Update()
{
	_transform->Update();
	_collider->Update();
}

void Creature::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}

void Creature::PostRender()
{
}

void Creature::Damaged(int damgae)
{
	if (!_isActive)
		return;
	_hp -= damgae;

	if (_hp < 1)
	{
		_hp = 0;
	}
}
