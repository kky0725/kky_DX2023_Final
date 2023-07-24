#include "framework.h"
#include "Skel.h"

Skel::Skel()
    :Creature(25.0f)
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

	if (_basic)
	{

	}
	else
	{

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
}

int Skel::CheckAttack(shared_ptr<Collider> col)
{
	TargetOn(col->GetTransform()->GetWorldPosition());



    return 0;
}

void Skel::Attack()
{
	if (!_targetOn)
		return;

}

void Skel::Move()
{
	if (!_targetOn)
		return;


}
