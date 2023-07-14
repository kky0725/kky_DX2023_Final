#include "framework.h"
#include "GaintBat.h"

#include "BatBullet.h"

GaintBat::GaintBat(bool basic)
	:Creature(5.0f)
{
	_ani = make_shared<Animation>();
	_isActive = true;

	if (basic)
	{
		_hp = 46;
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBatAtk.png", "Resource/Monster/GaintBatAtk.xml", "Atk", Vector2(10, 10), Action::END, 0.1f, std::bind(&GaintBat::TargetOff, this));
	}
	else
	{
		_hp = 44;
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBatAtk.png", "Resource/Monster/GaintRedBatAtk.xml", "Atk", Vector2(10, 10), Action::END, 0.1f, std::bind(&GaintBat::TargetOff, this));
		_basic = false;
	}

	_ani->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetScale(Vector2(10.0f, 10.0f));

	_speed = 100.0f;

	for (int i = 0; i < 9; i++)
	{
		shared_ptr<BatBullet> bullet = make_shared<BatBullet>();
		_bullets.push_back(bullet);
	}
}

GaintBat::~GaintBat()
{

}

void GaintBat::Update()
{
	if (!_isActive)
		return;
	Move();
	Attack();
	_ani->Update();
	Creature::Update();
}

void GaintBat::Render()
{
	if (!_isActive)
		return;
	_ani->Render();
	Creature::Render();
}

void GaintBat::Attack()
{
	if (!_targetOn)
		return;

	if (_basic)
	{
		//3개씩 3줄로 공격
	}
	else
		RedAttack();
}

void GaintBat::RedAttack()
{
	//원 형 공격
}

void GaintBat::TargetOn(Vector2 playerPos)
{
	Vector2 dir = playerPos-_collider->GetTransform()->GetWorldPosition();
	if (dir.Length() < _range)
	{
		_ani->SetState(Animation::State::ATK);
		_targetOn = true;
	}
}

void GaintBat::TargetOff()
{
	_ani->SetState(Animation::State::IDLE);
	_targetOn = false;
}


void GaintBat::Move()
{
	if (_targetOn)
		return;
	_time += DELTA_TIME;
	if (_time > 0.5f)
	{
		_time = 0.0f;
		_dir.x = MyMath::RandomInt(-1, 1);
		_dir.y = MyMath::RandomInt(-1, 1);
	}

	_collider->GetTransform()->AddVector2(_dir * DELTA_TIME * _speed);

	if (_dir.x == 1)
		_ani->SetRight();
	if (_dir.x == -1)
		_ani->SetLeft();
}
