#include "framework.h"
#include "SkelBullet.h"

SkelBullet::SkelBullet()
	:Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Monster/찾아서 넣을 예정");
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
