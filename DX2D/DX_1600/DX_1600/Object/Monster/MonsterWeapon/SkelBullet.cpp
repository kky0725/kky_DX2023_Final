#include "framework.h"
#include "SkelBullet.h"

SkelBullet::SkelBullet()
	:Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Monster/Arrow00.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
	_transform->SetAngel(-PI / 2);
}

SkelBullet::~SkelBullet()
{
}

void SkelBullet::Update()
{
	Bullet::Update();
	_transform->Update();
}

void SkelBullet::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

void SkelBullet::Shoot(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_collider->GetTransform()->SetPosition(startPos);
	_direction = dir;
	_collider->GetTransform()->SetAngel(_direction.Angle());
}
