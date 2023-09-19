#include "framework.h"
#include "SkelBossSword.h"

SkelBossSword::SkelBossSword()
{
	_collider = make_shared<RectCollider>(Vector2(20.0f, 140.0f));
	_quad = make_shared<Quad>(L"Resource/Monster/SkelBoss/BossSword.png");
	_transform = make_shared<Transform>();
	
	_transform->SetScale(Vector2(3.0f, 3.0f));
	_transform->SetPosition(Vector2(0.0f, -20.0f));

	_transform->SetParent(_collider->GetTransform());

	_lifeTime = 30.0f;
	_speed = 0.0f;
	//delet
	//_isActive = true;
	_collider->SetPosition(Vector2(-100.0f, 50.0f));

	EffectManager::GetInstance()->AddEffect("BossSwordCharge", L"Resource/Monster/SkelBoss/BossSwordChargeFX.png", Vector2(1, 8), Vector2(100.0f, 100.0f));
	EffectManager::GetInstance()->AddEffect("BossSwordHit", L"Resource/Monster/SkelBoss/BossSwordHitFX.png", Vector2(1, 5), Vector2(100.0f, 100.0f));
}

SkelBossSword::~SkelBossSword()
{
}

void SkelBossSword::Update()
{
	//LifeTime();
	if (!_isActive)
		return;
	if (_isGround)
		return;
	_collider->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);
	_collider->Update();
	_transform->Update();
}

void SkelBossSword::Render()
{
	if (!_isActive)
		return;
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}

void SkelBossSword::Summon(Vector2 startPos)
{
	_collider->GetTransform()->SetPosition(startPos);
	_speed = 0.0f;
	_isActive = true;
	_isAttack = false;
	_isCharge = true;
}

void SkelBossSword::Shoot()
{
	_isAttack = true;
	_isCharge = false;
	_speed = 500.0f;
}

void SkelBossSword::Charge(Vector2 dir)
{
	if (!_isCharge)
		return;
	if (_isAttack)
		return;
	_direction = dir.NormalVector2();
	float angle = atan(dir.y / dir.x);
	if (dir.x > 0)
		angle = angle + PI;
	SetAngle(angle + PI/2);
	EffectManager::GetInstance()->Play("BossSwordCharge", _transform->GetWorldPosition(), angle);

}

int SkelBossSword::GetAtk()
{
	if (_isAttack)
	{
		_isAttack = false;
		return MyMath::RandomInt(_minAtk, _maxAtk);
	}

	return 0;
}

void SkelBossSword::IsGround()
{
	if (_isGround)
		return;

	_isGround = true;
	EFFECT_PLAY("BossSwordHit", _transform->GetWorldPosition());
}

