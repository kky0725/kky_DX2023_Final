#include "framework.h"
#include "SkelBoss.h"
#include "SkelBossBullet.h"
#include "SkelBossHand.h"

SkelBoss::SkelBoss()
	:Creature(90.0f)
{
	_hp = 5000;//수치 수정 예정

	_body = make_shared<Animation>();
	_body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossIdle.png", "Resource/Monster/SkelBoss/SkelBossIdle.xml", "Idle", Vector2(20.0f, 20.0f));
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

	_leftHand = make_shared<SkelBossHand>(true);
	_rightHand = make_shared<SkelBossHand>(false);
	_leftHand->GetTransform()->SetPosition(Vector2(-400.0f, -50.0f));
	_rightHand->GetTransform()->SetPosition(Vector2(400.0f, -100.0f));


	//_bossState = ATKP1;
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
	_leftHand->Update();
	_rightHand->Update();
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
	_leftHand->Render();
	_rightHand->Render();
}

void SkelBoss::PostRender()
{
	if (ImGui::Button("ATK1", ImVec2(50, 20)))
	{
		_bossState = ATKP1;
		_body->SetState((Animation::State)2);
	}

	if (ImGui::Button("ATK2", ImVec2(50, 20)))
	{
		_bossState = ATKP2;
	}

	if (ImGui::Button("ATK2", ImVec2(50, 20)))
	{
		_bossState = ATKP2;
	}
}

void SkelBoss::EndAttack1()
{
	_body->SetState((Animation::State)3);
}

void SkelBoss::BossAtk()
{
	switch (_bossState)
	{
	case SkelBoss::IDLE:
	{
		IdleTime();
		break;
	}
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

void SkelBoss::IdleTime()
{
	_time += DELTA_TIME;
	if (_time > _idleTime)
	{
		_time = 0.0f;
		_bossState = BossState::ATKP2;//랜덤하게 정해지도록 변경 예정

		if (_bossState == BossState::ATKP2)
			_targetPos = _target.lock()->GetPos();
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
		_body->SetStateIdle();
		_bulletCount = 0;
	}
}

void SkelBoss::AttackP2()
{
	_time += DELTA_TIME;
	//왼손과 오른손이 번갈아 가면서 공격하는 코드 구현예정.
	if (_time > _idleTime)
	{
		count++;
		_leftHand->Attack();
		_time = 0.0f;
	}
	if (!_leftHand->Attacking())
	{
		if (count != 0)
		{
			count = 0;
			_bossState = BossState::IDLE;
			return;
		}
		float yy = _leftHand->GetTransform()->GetPos().y;
		float position = LERP(yy, _targetPos.y, 0.05f);
		float distance = position - yy;
		_leftHand->GetTransform()->AddVector2(Vector2(0.0f, distance));
	}
	//_rightHand->Attack();


}

void SkelBoss::AttackP3()
{
}

int SkelBoss::CheckAttack(shared_ptr<Collider> col)
{
	_target = col;
	switch (_bossState)
	{
	case SkelBoss::IDLE:
	{
		return 0;
	}
	case SkelBoss::ATKP1:
	{
		return 0;
	}
	case SkelBoss::ATKP2:
	{
		return 0;
	}
	case SkelBoss::ATKP3:
	{
		return 0;
	}
	default:
	{
		return 0;
	}
	}

}
