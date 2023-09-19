#include "framework.h"
#include "BatBullet.h"

BatBullet::BatBullet()
	:Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Monster/BatBullet.png");
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());
}

BatBullet::~BatBullet()
{
}

void BatBullet::Update()
{
	Bullet::Update();
	_transform->Update();
}

void BatBullet::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

void BatBullet::Summon(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_collider->GetTransform()->SetPosition(startPos);
	_direction = dir;
	_speed = 0.0f;
}

void BatBullet::Shoot()
{
	_speed = 200.0f;
}