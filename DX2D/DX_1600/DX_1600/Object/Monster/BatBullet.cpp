#include "framework.h"
#include "BatBullet.h"

BatBullet::BatBullet()
{
	_collider = make_shared<CircleCollider>(5.0f);
	_collider->SetPosition(Vector2(-1000, -1000));

	_ani = make_shared<Animation>();
	//_ani->CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Idle", Vector2(10.0f, 10.0f));
}

BatBullet::~BatBullet()
{
}

void BatBullet::Update()
{
	LifeTime();
	if (!_isActive)
		return;
	_collider->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);
	_collider->Update();
}

void BatBullet::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
}

void BatBullet::Summon(const Vector2 startPos)
{
	_isActive = true;
	_collider->GetTransform()->SetPosition(startPos);
	_direction = Vector2(0.0f, 0.0f);
}

void BatBullet::Shoot(const Vector2& dir)
{
	_direction = dir.NormalVector2();
}

void BatBullet::LifeTime()
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
