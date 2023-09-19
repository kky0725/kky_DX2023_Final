#include "framework.h"
#include "Bat.h"

Bat::Bat(bool basic)
	:Creature(25.0f)
{
	_ani = make_shared<Animation>();

	if (basic) 
	{
		_maxHp = 6;
		_curHp = _maxHp;
		_ani->CreateAction(L"Resource/Monster/Bat.png", "Resource/Monster/Bat.xml", "Idle", Vector2(50, 50));
	}
	else
	{
		_maxHp = 16;
		_curHp = _maxHp;
		_ani->CreateAction(L"Resource/Monster/RedBat.png", "Resource/Monster/RedBat.xml", "Idle", Vector2(50, 50));
	}

	_ani->SetParent(_collider->GetTransform());

	_speed = 100.0f;
}

Bat::~Bat()
{
}

void Bat::Update()
{
	for (auto coin : _coins)
	{
		coin->Update();
	}
	if (!_isActive)
		return;
	Move();
	_ani->Update();
	Creature::Update();
}

void Bat::Render()
{
	for (auto coin : _coins)
	{
		coin->Render();
	}
	if (!_isActive)
		return;
	_ani->Render();
	Creature::Render();
}

void Bat::Move()
{
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

int Bat::CheckAttack(shared_ptr<Collider> col)
{
	return 0;
}
