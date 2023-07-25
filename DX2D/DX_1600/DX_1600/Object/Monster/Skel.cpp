#include "framework.h"
#include "Skel.h"

#include "MonsterWeapon/SkelSword.h"
#include "MonsterWeapon/SkelBow.h"

Skel::Skel(bool basic)
    :Creature(25.0f), _basic(basic)
{
	_ani = make_shared<Animation>();
	_isActive = true;

	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Idle", Vector2(10, 10));
	_ani->CreateAction(L"Resource/Monster/SkelWalk.png", "Resource/Monster/SkelWalk.xml", "Walk", Vector2(10, 10));
	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Jump", Vector2(10, 10));
	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Atk", Vector2(10, 10));
	_ani->CreateAction(L"Resource/Monster/GraySkelDie.png", "Die", Vector2(10, 10));

	_slot = make_shared<Transform>();
	_slot->SetParent(_transform);

	if (_basic)//°Ë
	{
		_weapon = make_shared<SkelSword>();
		_ani->SetState(Animation::State::RUN);
		_ani->SetEndEvent(Animation::State::ATK, std::bind(&Skel::EndAttack, this));
	}
	else//È°
	{
		//_weapon = make_shared<SkelBow>();
		_ani->SetState(Animation::State::IDLE);
		_ani->SetEndEvent(Animation::State::ATK, std::bind(&Skel::TargetOff, this));
	}

	

	_ani->SetParent(_collider->GetTransform());
	_ani->SetScale(Vector2(10.0f, 10.0f));
	_speed = 100.0f;
}

Skel::~Skel()
{
}

void Skel::Update()
{
	if (!_isActive)
		return;
	Move();
	Chase();
	_ani->Update();
	Creature::Update();
}

void Skel::Render()
{
	if (!_isActive)
		return;
	_ani->Render();
	Creature::Render();
}

void Skel::TargetOn(Vector2 playerPos)
{
	if (_targetOn)
		return;
	Vector2 dir = playerPos - _collider->GetTransform()->GetWorldPosition();
	if (dir.Length() < _range)
	{
		_targetOn = true;
		if (!_basic)
		{
			_ani->SetState(Animation::State::ATK);
		}
	}
}

void Skel::TargetOff()
{
	_targetOn = false;
	_ani->SetState(Animation::State::IDLE);
	BowAttack();
}

int Skel::CheckAttack(shared_ptr<Collider> col)
{
	TargetOn(col->GetTransform()->GetWorldPosition());
	_target = col;

	if (_basic)
		return CheckAttackSword();
	else
		return CheckAttackBow();
}

int Skel::CheckAttackSword()
{
	return 0;
}

int Skel::CheckAttackBow()
{
	return 0;
}

void Skel::SwordAttack()
{
}

void Skel::BowAttack()
{
}

void Skel::Move()
{
	if (_basic)
	{
		if (_targetOn)
			return;

		_time += DELTA_TIME;
		if (_time > 0.5f)
		{
			_time = 0.0f;
			_dir.x *= -1.0f;
		}

		_collider->GetTransform()->AddVector2(_dir * DELTA_TIME * _speed);

		if (_dir.x > 0.0f)
			_ani->SetRight();
		if (_dir.x < 0.0f)
			_ani->SetLeft();
	}
	else
		return;

}

void Skel::Chase()
{
	if (!_basic)
		return;

	if (!_targetOn)
		return;

	if (_ani->GetState() != Animation::State::RUN)
		return;

	float distance = _target.lock()->GetTransform()->GetWorldPosition().x - _collider->GetTransform()->GetWorldPosition().x;
	if (distance > 0.0f)
		_dir.x = 1.0f;
	else if (distance < 0.0f)
		_dir.x = -1.0f;

	if (_dir.x > 0.0f)
		_ani->SetRight();
	if (_dir.x < 0.0f)
		_ani->SetLeft();

	_collider->GetTransform()->AddVector2(_dir * DELTA_TIME * _speed);

	if (abs(distance) < 50.0f)
	{
		_ani->SetState(Animation::State::ATK);
		SwordAttack();
	}

}

void Skel::EndAttack()
{
	_ani->SetState(Animation::State::RUN);

}
