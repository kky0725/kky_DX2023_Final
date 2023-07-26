#include "framework.h"
#include "SkelBullet.h"

SkelBullet::SkelBullet()
	:Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Monster/ã�Ƽ� ���� ����");
	_transform = make_shared<Transform>();
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
	Bullet::Render();
	_transform->SetBuffer(0);
	_quad->Render();
}
