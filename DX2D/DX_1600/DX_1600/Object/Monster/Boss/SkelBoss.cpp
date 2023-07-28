#include "framework.h"
#include "SkelBoss.h"

SkelBoss::SkelBoss()
	:Creature(90.0f)
{
	_hp = 5000;//수치 수정 예정

	_body = make_shared<Animation>();
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossIdle.png", "Resource/Monster/SkelBoss/SkelBossIdle.xml", "Idle", Vector2(20.0f, 20.0f));
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossIdle.png", "Resource/Monster/SkelBoss/SkelBossIdle.xml", "None", Vector2(20.0f, 20.0f));
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossIdle.png", "Resource/Monster/SkelBoss/SkelBossIdle.xml", "None", Vector2(20.0f, 20.0f));
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossAtk1.png", "Resource/Monster/SkelBoss/SkelBossAtk1.xml", "Atk1", Vector2(20.0f, 20.0f), Action::Type::END, 0.1f, std::bind(&SkelBoss::EndAttack1,this));
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossAtk2.png", "Resource/Monster/SkelBoss/SkelBossAtk2.xml", "Atk2", Vector2(20.0f, 28.0f), Action::Type::LOOP);
	_body->SetScale(Vector2(12.0f, 12.f));
	_body->SetParent(_collider->GetTransform());
	_body->SetPosition(Vector2(25.0f, 16.0f));


	_back = make_shared<Animation>();
	_back->CreateAction(L"Resource/Monster/SkelBoss/SkelBossBack.png", "Resource/Monster/SkelBoss/SkelBossBack.xml", "Idle", Vector2(10.0f, 10.0f));
	_back->SetScale(Vector2(16.0f, 16.0f));
	_back->SetParent(_collider->GetTransform());
	_back->SetPosition(Vector2(0.0f, -45.0f));

}

SkelBoss::~SkelBoss()
{
}

void SkelBoss::Update()
{
	Creature::Update();
	_body->Update();
	_back->Update();
}

void SkelBoss::Render()
{
	if (!_isActive)
		return;
	_back->Render();
	_body->Render();
	_collider->Render();
}

void SkelBoss::PostRender()
{

}

void SkelBoss::EndAttack1()
{
	_body->SetState(Animation::State::ATK2);
}

int SkelBoss::CheckAttack(shared_ptr<Collider> col)
{
	return 0;
}
