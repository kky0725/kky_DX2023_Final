#include "framework.h"
#include "Bat.h"

Bat::Bat(bool basic)
	:Creature(5.0f)
{
	_ani = make_shared<Animation>();

	if (basic) 
	{
		_hp = 6;
		_ani->CreateAction(L"Resource/Monster/Bat.png", "Resource/Monster/Bat.xml", "Idle", Vector2(10, 10));
	}
	else
	{
		_hp = 16;
		_ani->CreateAction(L"Resource/Monster/RedBat.png", "Resource/Monster/RedBat.xml", "Idle", Vector2(10, 10));
	}

	_ani->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetScale(Vector2(5.0f, 5.0f));

	_speed = 100.0f;
}

Bat::~Bat()
{
}

void Bat::Update()
{
	if (!_isActive)
		return;
	Move();
	_ani->Update();
	Creature::Update();
}

void Bat::Render()
{
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
