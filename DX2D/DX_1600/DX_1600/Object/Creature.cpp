#include "framework.h"
#include "Creature.h"

#include "UI/HpBar.h"
#include "Coin.h"

Creature::Creature(wstring string, float radius)
{
	_quad = make_shared<Quad>(string);
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(radius);

	_transform->SetParent(_collider->GetTransform());

	_hpBar = make_shared<HpBar>(Vector2(50.0f, 10.0f));

	_hpBar->SetParent(_collider->GetTransform());
}

Creature::Creature(float radius)
{
	_quad = nullptr;
	_collider = make_shared<CircleCollider>(radius);

	_hpBar = make_shared<HpBar>(Vector2(50.0f, 10.0f));

	_hpBar->SetParent(_collider->GetTransform());

	int count = MyMath::RandomInt(1, 3);
	for (int i = 0; i < count; i++)
	{
		shared_ptr<Coin> coin = make_shared<Coin>();
		_coins.push_back(coin);
	}
}

Creature::~Creature()
{
}

void Creature::Update()
{
	if (!_isActive)
		return;
	if (_quad != nullptr)
	{
		_transform->Update();
	}
	_collider->Update();
	CheckDamaged();

	SetHpBar();
	_hpBar->Update();
}

void Creature::Render()
{
	if (!_isActive)
		return;
	if (_quad != nullptr)
	{
		_transform->SetBuffer(0);
		_quad->Render();
	}
	_collider->Render();
	_hpBar->PostRender();
}

void Creature::PostRender()
{
}

void Creature::SetHpBar()
{
	_hpBar->SetMaxHp(_maxHp);
	_hpBar->SetCurHp(_curHp);
}

void Creature::Damaged(int damge)
{
	if (!_isActive)
		return;
	if (_damaged)
		return;
	if (damge <= 0)
		return;
	_curHp -= damge;
	_damaged = true;

	if (_curHp < 1)
	{
		_curHp = 0;
		_isActive = false;

		for (auto coin : _coins)
		{
			coin->AppearCoin(_collider->GetPos());
		}
	}
}

void Creature::CheckDamaged()
{
	if (!_damaged)
		return;

	_DCtime += DELTA_TIME;
	if (_DCtime > 0.1f)
	{
		_damaged = false;
		_DCtime = 0.0f;
	}
}
