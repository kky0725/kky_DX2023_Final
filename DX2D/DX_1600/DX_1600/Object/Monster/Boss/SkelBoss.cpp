#include "framework.h"
#include "SkelBoss.h"
#include "SkelBossBullet.h"
#include "SkelBossHand.h"
#include "SkelBossSword.h"

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

	_leftHand = make_shared<SkelBossHand>(true);
	_rightHand = make_shared<SkelBossHand>(false);
	_leftHand->GetTransform()->SetPosition(Vector2(-400.0f, -50.0f));
	_rightHand->GetTransform()->SetPosition(Vector2(400.0f, -100.0f));
	_atkSpeed = 0.2f;

	for (int i = 0; i < 6; i++)
	{
		shared_ptr<SkelBossSword> sword = make_shared<SkelBossSword>();
		_swords.push_back(sword);
	}

	//_idleTime = 10.0f // 보스전 도입부가 필요할 경우 생성자에서 idleTime 값을 키우고 주석 해제.

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
	for (auto sword : _swords)
		sword->Update();
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
	for (auto sword : _swords)
		sword->Render();
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
	case SkelBoss::ATKP2L:
	{
		AttackP2L();
		break;
	}
	case SkelBoss::ATKP2R:
	{
		AttackP2R();
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
		int randomInt = MyMath::RandomInt(1, 3);
		//int randomInt = 3;
		if (randomInt == 1)
		{
			_bossState = BossState::ATKP1;
			_body->SetState((Animation::State)2);
		}
		else if (randomInt == 2)
		{
			_bossState = BossState::ATKP2L;
			_idleTime = 1.0f;
		}
		else
		{
			_bossState = BossState::ATKP3;
		}
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
		_idleTime = 4.0f;
		_bulletCount = 0;
	}
}

void SkelBoss::AttackP2L()
{
	_time += DELTA_TIME;
	if (_time > _idleTime)
	{
		count++;
		_leftHand->Attack();

		_targetPos = _target.lock()->GetTransform()->GetWorldPosition();
		_time = 0.0f;
	}

	if (!_leftHand->Attacking())
	{
		float yy = _leftHand->GetTransform()->GetPos().y;
		float position = LERP(yy, _targetPos.y, 0.05f);
		float distance = position - yy;
		_leftHand->GetTransform()->AddVector2(Vector2(0.0f, distance));
	}

	if (!_leftHand->Attacking() && count != 0)
	{
		_bossState = BossState::ATKP2R;
		count = 0;
		_time = 0.0f;
	}

}

void SkelBoss::AttackP2R()
{
	_time += DELTA_TIME;
	if (_time > _idleTime)
	{
		count++;
		_rightHand->Attack();

		_targetPos = _target.lock()->GetTransform()->GetWorldPosition();
		_time = 0.0f;
	}

	if (!_rightHand->Attacking())
	{
		float yy = _rightHand->GetTransform()->GetPos().y;
		float position = LERP(yy, _targetPos.y, 0.05f);
		float distance = position - yy;
		_rightHand->GetTransform()->AddVector2(Vector2(0.0f, distance));
	}

	if (!_rightHand->Attacking() && count != 0)
	{
		_bossState = BossState::IDLE;
		count = 0;
		_time = 0.0f;
	}

}

void SkelBoss::AttackP3()
{
	_time += DELTA_TIME;

	if (_atkP3SummonPase)
	{
		if (_time > 0.2f && count != 6)
		{
			_time = 0.0f;
			Vector2 startPos = Vector2(-500.0f + count * 200.0f, 300.0f);
 			_swords[count]->Summon(startPos);
			count++;
		}
		
		if (count == 6 && _time > 2.0f)
		{
			_atkP3SummonPase = false;
			count = 0;
			_time = 0.0f;
		}
	}
	else
	{
		if (_time > 0.5f && count != 6)
		{
			_time = 0.0f;
			_swords[count]->Shoot();
			count++;
		}

		if (count == 6 && _time > 5.0f)
		{
			_atkP3SummonPase = true;
			count = 0;
			_bossState = BossState::IDLE;
			_idleTime = 2.0f;
		}
	}

	for (auto sword : _swords)
	{
		Vector2 dir = _target.lock()->GetTransform()->GetWorldPosition();
		dir -= sword->GetCollider()->GetPos();
		sword->Charge(dir);
	}
}


int SkelBoss::CheckAttack(shared_ptr<Collider> col)
{
	_target = col;
	switch (_bossState)
	{
	case SkelBoss::IDLE:
	case SkelBoss::ATKP1:
	case SkelBoss::ATKP3:
	{
		for (auto bullet : _bullets)
		{
			if (!bullet->IsActive())
				continue;
			if (col->IsCollision(bullet->GetCollider()))
			{
				bullet->SetActive(false);
				return _bulletAtk;
			}
		}
	}
	{
		for (int i = 0; i < 6; i++)
		{
			if (!_swords[i]->IsActive() || !_swords[i]->IsAttack())
				continue;
			if (col->IsCollision(_swords[i]->GetCollider()))
			{
				return _swords[i]->GetAtk();
			}
		}
		return 0;
	}
	case SkelBoss::ATKP2L:
	{
		if(col->IsCollision(_leftHand->GetCollider()) && _leftHand->IsActive()) //다단히트 문제 해결해야함
			return 10;
		return 0;
	}
	case SkelBoss::ATKP2R:
	{
		if (col->IsCollision(_rightHand->GetCollider()) && _rightHand->IsActive())
			return 10;
		return 0;
	}
	default:
	{
		return 0;
	}
	}

}
