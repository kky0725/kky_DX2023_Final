#include "framework.h"
#include "Skel.h"

#include "MonsterWeapon/SkelSword.h"
#include "MonsterWeapon/SkelBow.h"

Skel::Skel(bool basic)
    :Creature(25.0f), _basic(basic)
{
	_ani = make_shared<Animation>();
	_isActive = true;

	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Idle", Vector2(50, 50));
	_ani->CreateAction(L"Resource/Monster/SkelWalk.png", "Resource/Monster/SkelWalk.xml", "Walk", Vector2(50, 50));
	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Jump", Vector2(50, 50));
	_ani->CreateAction(L"Resource/Monster/GraySkelIdle.png", "Atk", Vector2(50, 50));
	_ani->CreateAction(L"Resource/Monster/GraySkelDie.png", "Die", Vector2(50, 50));

	_slot = make_shared<Transform>();
	_slot->SetParent(_collider->GetTransform());

	if (_basic)//검
	{
		_maxHp = 56;//수정예정
		_curHp = _maxHp;

		_weapon = make_shared<SkelSword>();
		_ani->SetState(Animation::State::RUN);
		_ani->SetEndEvent(Animation::State::ATK, std::bind(&Skel::EndAttack, this));
	}
	else//활
	{
		_maxHp = 56;//수정예정
		_curHp = _maxHp;

		_weapon = make_shared<SkelBow>();
		_ani->SetState(Animation::State::IDLE);
		_ani->SetEndEvent(Animation::State::ATK, std::bind(&Skel::TargetOff, this));
		_atkSpeed = 3.0f;
		_slot->SetPosition(Vector2(-10.0f, 0.0f));
	}

	_weapon->GetCollider()->SetParent(_slot);
	_ani->SetParent(_collider->GetTransform());
	_speed = 100.0f;
}

Skel::~Skel()
{
}

void Skel::Update()
{
	for (auto coin : _coins)
	{
		coin->Update();
	}
	if (!_isActive)
		return;
	Gravity();
	Move();
	Chase();
	SwordAttack();
	BowAttack();
	_ani->Update();
	_slot->Update();
	_weapon->Update();
	Creature::Update();
}

void Skel::Render()
{
	for (auto coin : _coins)
	{
		coin->Render();
	}
	if (!_isActive)
		return;
	_slot->SetBuffer(0);
	_ani->Render();
	_weapon->Render();
	Creature::Render();
}

void Skel::TargetOn(Vector2 playerPos)
{
	if (_targetOn)
		return;
	_dir = playerPos - _collider->GetTransform()->GetWorldPosition();
	if (_dir.Length() < _range)
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
}

int Skel::CheckAttack(shared_ptr<Collider> col)
{
	TargetOn(col->GetTransform()->GetWorldPosition());
	Vector2 pos = col->GetTransform()->GetWorldPosition();
	_target = col;

	if (_basic)
		return CheckAttackSword(col);
	else
		return CheckAttackBow(col);
}

int Skel::CheckAttackSword(shared_ptr<Collider> col)
{
	if (!_weapon->IsAtcive())
		return 0;

	if (!_weapon->GetCollider()->IsCollision(col))
		return 0;

	return _weapon->GetAtk();
}

int Skel::CheckAttackBow(shared_ptr<Collider> col)
{
	return dynamic_pointer_cast<SkelBow>(_weapon)->CheckAttack(col);
}

void Skel::SwordAttack()
{
	if (!_basic)
		return;

	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time < 0.1f)
		{
			if (_dir.x > 0.0f)
				_slot->AddAngle(-25.0f * DELTA_TIME);
			else
				_slot->AddAngle(25.0f * DELTA_TIME);
		}
		if (_time > 0.1f)
		{
			_weapon->SetIsActive(false);
			_ani->SetState(Animation::State::RUN);
			if (_dir.x > 0.0f)
				_slot->SetAngel(PI / 4.0f);
			else
				_slot->SetAngel(PI / 4.0f * 3.0f);
		}

		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}

		return;
	}

	if (_ani->GetState() == Animation::State::ATK)
	{
		_atkCool = true;
		_weapon->SetIsActive(true);
	}
}

void Skel::BowAttack()
{
	if (_basic)
		return;
	if (_atkCool)
	{
		_time += DELTA_TIME;

		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}

		return;
	}

	if (_ani->GetState() == Animation::State::ATK)
	{
		_atkCool = true;
		//_dir = _target.lock()->GetPos() - _slot->GetWorldPosition();
		dynamic_pointer_cast<SkelBow>(_weapon)->Attack(_dir);
		_slot->SetAngel(_dir.Angle() + PI);

		if (_dir.x > 0.0f)
		{
			_ani->SetRight();
			_slot->SetPosition(Vector2(10.0f, 0.0f));
		}
		if (_dir.x < 0.0f)
		{
			_ani->SetLeft();
			_slot->SetPosition(Vector2(-10.0f, 0.0f));
		}
	}
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

	float distanceX = _target.lock()->GetTransform()->GetWorldPosition().x - _collider->GetTransform()->GetWorldPosition().x;
	float distanceY = _target.lock()->GetTransform()->GetWorldPosition().y - _collider->GetTransform()->GetWorldPosition().y;
	if (distanceX > 0.0f)
		_dir.x = 1.0f;
	else if (distanceX < 0.0f)
		_dir.x = -1.0f;

	if (_dir.x > 0.0f)//검 위치 정해주는 식 추가
	{
		_ani->SetRight();
		_slot->SetAngel(PI / 4.0f);
	}
	if (_dir.x < 0.0f)
	{
		_ani->SetLeft();
		_slot->SetAngel(PI / 4.0f * 3.0f);
	}

	if (abs(distanceX) < 60.0f && abs(distanceY) < 60.0f)
	{
		_ani->SetState(Animation::State::ATK);
		return;
	}

	_collider->GetTransform()->AddVector2(Vector2(_dir.x, 0.0f) * DELTA_TIME * _speed);
}

void Skel::EndAttack()
{
	_ani->SetState(Animation::State::RUN);
}

void Skel::Gravity()
{
	_jumpPower -= 15.0f;
	if (_jumpPower < -600.0f)
		_jumpPower = -600.0f;
	_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
}
