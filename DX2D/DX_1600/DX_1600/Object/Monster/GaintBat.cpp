#include "framework.h"
#include "GaintBat.h"

#include "BatBullet.h"

GaintBat::GaintBat(bool basic)
	:Creature(50.0f), _basic(basic)
{
	_ani = make_shared<Animation>();
	_isActive = true;

	if (basic)
	{
		_hp = 46;
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "none", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBat.png", "Resource/Monster/GaintBat.xml", "none", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintBatAtk.png", "Resource/Monster/GaintBatAtk.xml", "Atk", Vector2(10, 10), Action::END, 0.1f, std::bind(&GaintBat::TargetOff, this));
	}
	else
	{
		_hp = 44;
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "Idle", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "none", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBat.png", "Resource/Monster/GaintRedBat.xml", "none", Vector2(10, 10));
		_ani->CreateAction(L"Resource/Monster/GaintRedBatAtk.png", "Resource/Monster/GaintRedBatAtk.xml", "Atk", Vector2(10, 10), Action::END, 0.1f, std::bind(&GaintBat::TargetOff, this));
	}

	_ani->SetParent(_collider->GetTransform());
	_ani->SetScale(Vector2(10.0f, 10.0f));

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
	Attack();
	Move();
	_ani->Update();
	Creature::Update();
	for (auto bullet : _bullets)
		bullet->Update();
}

void GaintBat::Render()
{
	if (!_isActive)
		return;
	_ani->Render();
	Creature::Render();
	for (auto bullet : _bullets)
		bullet->Render();
}

void GaintBat::Attack()
{
	if (!_targetOn)
		return;

	for (int i = 0; i < 9; i++)
	{
		_bullets[i]->Shoot();
	}

}

void GaintBat::SummonBullets(Vector2 direction)
{
	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
	if (_basic)
	{
		for (int i = 0; i < 9; i++)
		{
			_bullets[i]->Summon(startPos + direction.Rotation(PI/6.0f * (-1 + i%3)) * (50.0f +  50.0f * (i/3)), direction.Rotation(PI / 6.0f * (-1 + i % 3)));
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			_bullets[i]->Summon(startPos + direction.Rotation(2.0f * PI/9.0f * i) * 50.0f, direction.Rotation(2.0f * PI / 9.0f * i));
		}
	}
}

void GaintBat::TargetOn(Vector2 playerPos)
{
	if (_targetOn)
		return;
	Vector2 dir = playerPos-_collider->GetTransform()->GetWorldPosition();
	if (dir.Length() < _range)
	{
		_ani->SetState(Animation::State::ATK);
		_targetOn = true;
		SummonBullets(dir.NormalVector2());
	}
}

void GaintBat::TargetOff()
{
	_ani->SetState(Animation::State::IDLE);
	_targetOn = false;
	Attack();
}

int GaintBat::CheckAttack(shared_ptr<Collider> player)
{
	TargetOn(player->GetTransform()->GetWorldPosition());

	for (auto bullet : _bullets)
	{
		if (!bullet->IsActive())
			continue;
		if (player->IsCollision(bullet->GetCollider()))
		{
			bullet->SetActive(false);
			return _atk;
		}
	}
	return 0;
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
