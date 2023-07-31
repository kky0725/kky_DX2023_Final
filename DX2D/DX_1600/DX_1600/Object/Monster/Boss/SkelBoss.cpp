#include "framework.h"
#include "SkelBoss.h"
#include "SkelBossBullet.h"

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

	for (int i = 0; i < _poolCount * 4; i++)
	{
		shared_ptr<SkelBossBullet> bullet = make_shared<SkelBossBullet>();
		_bullets.push_back(bullet);
	}
	_atkSpeed = 0.2f;

	_bossState = ATKP1;
}

SkelBoss::~SkelBoss()
{
}

void SkelBoss::Update()
{
	Creature::Update();
	BossAtk();
	_body->Update();
	_back->Update();
	for (auto bullet : _bullets)
		bullet->Update();
}

void SkelBoss::Render()
{
	if (!_isActive)
		return;
	_back->Render();
	_body->Render();
	for (auto bullet : _bullets)
		bullet->Render();
	_collider->Render();
}

void SkelBoss::PostRender()
{
	if (ImGui::Button("ATK1", ImVec2(100, 100)))
		_bossState = ATKP1;
}

void SkelBoss::EndAttack1()
{
	_body->SetState(Animation::State::ATK2);
}

void SkelBoss::BossAtk()
{
	switch (_bossState)
	{
	case SkelBoss::IDLE:
		break;
	case SkelBoss::ATKP1:
	{
		AttackP1();
		break;
	}
	case SkelBoss::ATKP2:
	{
		AttackP2();
		break;
	}
	case SkelBoss::ATKP3:
	{
		AttackP3();
		break;
	}
	default:
		break;
	}
}

void SkelBoss::AttackP1()
{
	_time += DELTA_TIME;
	if (_time > _atkSpeed)
	{
		for (int i = 0; i < 4; i++)
		{
			Vector2 StartPos = _back->GetWorldPosition();
			Vector2 Dir = Vector2{ 1.0f, 0.0f };
			_bullets[i + 4 * _bulletCount]->Shoot(StartPos, Dir.Rotation(PI / 2 * i + PI / 24 * _bulletCount));
		}
		_bulletCount++;
		_time = 0.0f;
	}
	if (_bulletCount >= _poolCount)
	{
		_bossState = BossState::IDLE;
		_bulletCount = 0;
	}
}

void SkelBoss::AttackP2()
{
}

void SkelBoss::AttackP3()
{
}

int SkelBoss::CheckAttack(shared_ptr<Collider> col)
{
	return 0;
}
