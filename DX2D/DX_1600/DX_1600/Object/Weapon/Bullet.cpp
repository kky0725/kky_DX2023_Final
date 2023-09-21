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
	DeleteBullet();
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

void Bullet::DeleteBullet()
{
	if (_collider->GetPos().x < -CORRECTION_VALUE_WIDTH - 20.0f + 120.0f ||
		_collider->GetPos().x > MAP_SIZE_X * 40.0f - CORRECTION_VALUE_WIDTH - 20.0f - 120.0f||
		_collider->GetPos().y < -CORRECTION_VALUE_HEIGHT - 20.0f + 120.0f ||
		_collider->GetPos().y > MAP_SIZE_Y * 40.0f - CORRECTION_VALUE_HEIGHT - 20.0f - 120.0f)
		_isActive = false;
}
