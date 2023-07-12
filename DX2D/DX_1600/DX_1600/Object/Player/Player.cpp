#include "framework.h"
#include "Player.h"
#include "../Weapon/ShortSword.h"
#include "Player_Ani.h"

//Player::Player(wstring string, Vector2 size, float radius)
//	:Creature(string, size, radius)
//{
//	_slot = make_shared<Transform>();
//	_slot->SetParent(_transform);
//	_isActive = true;
//
//	_hp = 80;
//}

Player::Player(wstring string, float radius)
	:Creature(radius)
{
	_slot = make_shared<Transform>();
	_slot->SetParent(_transform);
	_isActive = true;

	_ani = make_shared<Player_Ani>();
	_ani->SetParent(_collider->GetTransform());

	_hp = 80;

	_shortSword = make_shared<ShortSword>(L"Resource/UI/Button.png");
	_shortSword->GetTransform()->SetParent(_slot);
	_shortSword->GetTransform()->SetPosition(Vector2(100, 0));
	//_slot->AddAngle(2.0f);
	//_slot->AddVector2(Vector2(10, 0));
	//_slot->SetScale(Vector2(2.0f, 2.0f));
	//_shortSword->GetTransform()->AddAngle(1.0f);
	//_shortSword->GetTransform()->SetScale(Vector2(2.0f, 2.0f));
}

Player::~Player()
{
}

void Player::Update()
{
	Input();

	Creature::Update();
	_slot->Update();
	_shortSword->Update();
	_ani->Update();
}

void Player::Render()
{
	Creature::Render();
	_slot->SetBuffer(0);
	_shortSword->Render();
	_ani->Render();
}

void Player::PostRender()
{
}

void Player::Damged(int damge)
{
	if (!_isActive)
		return;
	damge -= def;
	if (damge <= 0)
		return;

	_hp -= damge;

	if (_hp < 1)
	{
		_hp = 0;
	}
}

void Player::Input()
{
	if (!_isActive)
		return;

	{
		_jumpPower -= 15.0f;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	Fire();

	Jump();
}

void Player::Fire()
{
	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}
		return;
	}
}

void Player::Jump()
{
	if (_jumpCount > 0)
		return;

	if (KEY_DOWN('W') || KEY_DOWN(VK_SPACE))
	{
		_jumpPower = 600.0f;
		_jumpCount++;
	}
}
