#include "framework.h"
#include "Player.h"
#include "../Weapon/ShortSword.h"
#include "Player_Ani.h"

Player::Player()
	:Creature(27.0f)
{
	_slot = make_shared<Transform>();
	_slot->SetParent(_transform);

	_ani = make_shared<Player_Ani>();
	_ani->SetParent(_collider->GetTransform());

	_hp = 1000;

	_footHold = make_shared<RectCollider>(Vector2(27.0f, 10.0f));
	_footHold->SetParent(_collider->GetTransform());
	_footHold->SetPosition(Vector2(0.0f, -24.0f));

	//나중에 함수 새로 만들어서 생성자에서 꺼낼 부분
	_shortSword = make_shared<ShortSword>();
	_shortSword->GetTransform()->SetParent(_slot);
	_shortSword->GetTransform()->SetPosition(Vector2(50, 0));

	SetAtkSpeed(_shortSword->GetAtkPerSec());
}

Player::~Player()
{
}

void Player::Update()
{
	Input();
	SetWeaponDir();

	Creature::Update();
	_slot->Update();
	_shortSword->Update();
	_ani->Update();
	_footHold->Update();
}

void Player::Render()
{
	Creature::Render();
	_slot->SetBuffer(0);
	_shortSword->Render();
	_ani->Render();
	_footHold->Render();
}

void Player::PostRender()
{
}

void Player::Damaged(int damge)
{
	damge -= _def;
	if (damge <= 0)
		return;
	Creature::Damaged(damge);
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
		if(_time < 0.1f)
			_slot->AddAngle(-20.0f * DELTA_TIME);
		if (_time > 0.1f)
			_shortSword->SetIsActive(false);

		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}
		
		return;
	}

	if (KEY_PRESS(VK_LBUTTON))
	{
		_atkCool = true;
		_shortSword->SetIsActive(true);
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
		_ani->SetIsGround(false);
	}
}

int Player::CheckAttack(shared_ptr<Collider> enemy)
{
	if (!_shortSword->IsAtcive())
		return 0;

	if (!_shortSword->GetCollider()->IsCollision(enemy))
		return 0;

	return GetAtk();
}

float Player::GetAtk()
{
	return _shortSword->GetAtk();
}

void Player::SetWeaponDir()
{
	if (_time < 0.1f && _time > 0.0f)
		return;
	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
	Vector2 Dir = W_MOUSE_POS - startPos;
	float angle = atan(Dir.y / Dir.x);
	if (Dir.x < 0)
		angle += PI;
	_slot->SetAngel(angle);
	
}

void Player::IsGround()
{
	_jumpCount = 0;
	
	if (!_ani->GetISGround() && _jumpPower < 0.0f)
	{
		_ani->SetIsGround(true);
		_ani->SetStateIdle();
	}
}
