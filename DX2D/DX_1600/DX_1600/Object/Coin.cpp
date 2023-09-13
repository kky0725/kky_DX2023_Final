#include "framework.h"
#include "Coin.h"

Coin::Coin()
{
	_ani = make_shared<Animation>();
	_col = make_shared<CircleCollider>(2.0f);

	_ani->CreateAction(L"Resource/Coin.png", "Resource/Coin.xml", Vector2(2.0f, 2.0f));
	_ani->SetParent(_col->GetTransform());
}

Coin::~Coin()
{
}

void Coin::Update()
{
	_ani->Update();
	_col->Update();

	_gravity -= 15.0f;

	if (_gravity < -300.0f)
		_gravity = -300.0f;

	_col->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _gravity * DELTA_TIME);
}

void Coin::Render()
{
	_ani->Render();
	_col->Render();
}

bool Coin::IsCollison(shared_ptr<Collider> col)
{
	if (!_isActive)
		return false;

	if (_col->IsCollision(col))
	{
		_isActive = false;
		return true;
	}

	return false;
}

void Coin::AppearCoin(Vector2 value)
{
	Vector2 rand = Vector2(0.0f, 0.0f); // ·£´ý float Ãß°¡
	_col->SetPosition(value + rand);
	_isActive = true;
}

