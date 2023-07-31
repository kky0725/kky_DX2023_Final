#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_collider = make_shared<CircleCollider>(5.0f);
	_collider->SetPosition(Vector2(-1000, -1000));
}

Bullet::Bullet(float size)
{
	_collider = make_shared<CircleCollider>(size);
	_collider->SetPosition(Vector2(-1000, -1000));
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	LifeTime();
	if (!_isActive)
		return;
	_collider->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);
	_collider->Update();
}

void Bullet::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
}

void Bullet::LifeTime()
{
	if (!_isActive)
	{
		_time = 0.0f;
		return;
	}
	_time += DELTA_TIME;
	if (_time > _lifeTime)
		_isActive = false;
}
