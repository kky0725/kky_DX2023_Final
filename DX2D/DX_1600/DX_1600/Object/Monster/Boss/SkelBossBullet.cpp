#include "framework.h"
#include "SkelBossBullet.h"

SkelBossBullet::SkelBossBullet()
	:Bullet(20.0f)
{
	_ani = make_shared<Animation>();
	_ani->CreateAction(L"Resource/Monster/SkelBoss/BossBullet.png", "Resource/Monster/SkelBoss/BossBullet.xml", "Idle", Vector2(10, 10));
	_ani->SetScale(Vector2(4.0f,4.0f));

	_ani->SetParent(_collider->GetTransform());
	_speed = 200.0f;
}

SkelBossBullet::~SkelBossBullet()
{
}

void SkelBossBullet::Update()
{
	Bullet::Update();
	_ani->Update();
}

void SkelBossBullet::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
	_ani->Render();
}

void SkelBossBullet::Shoot(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_collider->GetTransform()->SetPosition(startPos);
	_direction = dir;
}

