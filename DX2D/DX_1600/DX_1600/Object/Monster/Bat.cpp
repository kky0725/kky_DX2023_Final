#include "framework.h"
#include "Bat.h"

Bat::Bat(wstring string)
	:Creature(5.0f)
{
	_ani = make_shared<Animation>();


	if (string == L"puple") // 수정 예정
	{
		_hp = 6;
		_ani->CreateAction(string, "pupleBat.xml", "Idle", Vector2(10, 10));
	}
	else
	{
		_hp = 16;
		_ani->CreateAction(string, "redBat.xml", "Idle", Vector2(10, 10));
	}

	_ani->SetParent(_collider->GetTransform());

	_speed = 10.0f; // 수정 예정
}

Bat::~Bat()
{
}

void Bat::Update()
{
	move();
	Creature::Update();
}

void Bat::Render()
{
	Creature::Render();
}

void Bat::move()
{
	Vector2 dir;
	dir.x = MyMath::RandomInt(-1, 1);
	dir.y = MyMath::RandomInt(-1, 1);

	_collider->GetTransform()->AddVector2(dir * DELTA_TIME * _speed);

	if (dir.x == 1)
		_ani->SetRight();
	if (dir.x == -1)
		_ani->SetLeft();
}
