#include "framework.h"
#include "SkelBossSword.h"

SkelBossSword::SkelBossSword()
{
	_collider = make_shared<RectCollider>(Vector2(80.0f, 50.0f));
	_quad = make_shared<Quad>(L"Resource/Monster/SkelBoss/BossSword.png");
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());

	_lifeTime = 30.0f;

	//delet
	_isActive = true;
}

SkelBossSword::~SkelBossSword()
{
}

void SkelBossSword::Update()
{
	Bullet::Update();
	_transform->Update();
}

void SkelBossSword::Render()
{
	if (!_isActive)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

void SkelBossSword::Summon(Vector2 startPos, Vector2 dir)
{
	if (_isGround)
		return;


	if (!_isActive)
	{
		_collider->GetTransform()->SetPosition(startPos);
		_speed = 0.0f;
		_isActive = true;
		_isAttack = false;
		_isCharge = true;
	}
	if(_isCharge)
	{
		_direction = dir;
		float angle = atan(dir.y / dir.x);
		SetAngle(angle);
	}
}

void SkelBossSword::Shoot()
{
	_isAttack = true;
	_isCharge = false;
	_speed = 200.0f;
}

int SkelBossSword::GetAtk()
{
	if (!_isAttack)
		return 0;
	else
	{
		_isAttack = false;
		return MyMath::RandomInt(_minAtk, _maxAtk);
	}
}

