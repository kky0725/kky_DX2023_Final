#include "framework.h"
#include "BatBullet.h"

BatBullet::BatBullet()
	:Bullet()
{
	_ani = make_shared<Animation>();
	//_ani->CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Idle", Vector2(10.0f, 10.0f));
}

BatBullet::~BatBullet()
{
}

void BatBullet::Update()
{
	Bullet::Update();
}

void BatBullet::Render()
{
	Bullet::Render();
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