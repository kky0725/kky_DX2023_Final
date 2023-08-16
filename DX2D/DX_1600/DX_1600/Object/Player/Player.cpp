#include "framework.h"
#include "Player.h"
#include "../Weapon/ShortSword.h"
#include "../Weapon/CrossBow.h"
#include "Player_Ani.h"

Player::Player()
	:Creature(27.0f)
{
	_slot = make_shared<Transform>();
	_slot->SetParent(_collider->GetTransform());

	_ani = make_shared<Player_Ani>();
	_ani->SetParent(_collider->GetTransform());

	_hp = 10;

	_footHold = make_shared<RectCollider>(Vector2(27.0f, 10.0f));
	_footHold->SetParent(_collider->GetTransform());
	_footHold->SetPosition(Vector2(0.0f, -24.0f));

	//나중에 함수 새로 만들어서 생성자에서 꺼낼 부분
	_weapon1 = make_shared<ShortSword>();
	_weapon2 = make_shared<CrossBow>();
	_weapon = _weapon1;
	_weapon->GetCollider()->SetParent(_slot);
	_weapon->GetCollider()->GetTransform()->SetPosition(Vector2(50, 0));

	SetAtkSpeed(_weapon->GetAtkPerSec());
}

Player::~Player()
{
}

void Player::Update()
{
	if (_end)
		return;
	Die();
	Input();
	SetWeaponDir();

	Creature::Update();
	_slot->Update();
	_ani->Update();
	_weapon->Update();
	_footHold->Update();
}

void Player::Render()
{
	if (_end)
		return;
	Creature::Render();
	_slot->SetBuffer(0);
	_ani->Render();
	_weapon->Render();
	_footHold->Render();
}

void Player::PostRender()
{
}

void Player::Damaged(int damge)
{
	damge -= _def;
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
	SwapWeapon();

}

void Player::Fire()
{
	if (_weapon->WTIsSword())
		SwordAtk();
	else
		BowAtk();
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

void Player::SwordAtk()
{
	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time < 0.1f)
			_slot->AddAngle(-20.0f * DELTA_TIME);
		if (_time > 0.1f)
			_weapon->SetIsActive(false);

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
		_weapon->SetIsActive(true);
	}
}

void Player::BowAtk()
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

	if (KEY_PRESS(VK_LBUTTON))
	{
		_atkCool = true;
		Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
		Vector2 dir = W_MOUSE_POS - startPos;
		dynamic_pointer_cast<CrossBow>(_weapon)->Attack(dir);
	}
}

void Player::SwapWeapon()
{
	if (_weapon1 == nullptr || _weapon2 == nullptr)
		return;

	if (KEY_DOWN(VK_XBUTTON1))
	{
		if (_weapon == _weapon1)
			_weapon = _weapon2;
		else
			_weapon = _weapon1;

		SetAtkSpeed(_weapon->GetAtkPerSec());
		_weapon->GetCollider()->SetParent(_slot);
		_weapon->GetCollider()->GetTransform()->SetPosition(Vector2(50, 0));
	}
}

int Player::CheckAttack(shared_ptr<Collider> enemy)
{
	if (_weapon->WTIsSword())
		return CheckAttackSword(enemy);
	else
		return CheckAttackBow(enemy);
}

int Player::CheckAttackSword(shared_ptr<Collider> enemy)
{
	if (!_weapon->IsAtcive())
		return 0;

	if (!_weapon->GetCollider()->IsCollision(enemy))
		return 0;

	return GetAtk();
}

int Player::CheckAttackBow(shared_ptr<Collider> enemy)
{
	return dynamic_pointer_cast<CrossBow>(_weapon)->CheckAttack(enemy);
}

float Player::GetAtk()
{
	return _weapon->GetAtk();
}

void Player::SetWeaponDir()
{
	if (_time < 0.1f && _time > 0.0f)
		return;
	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
	Vector2 dir = W_MOUSE_POS - startPos;
	float angle = atan(dir.y / dir.x);
	if (dir.x < 0)
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

void Player::Die()
{
	if (_isActive)
		return;

	_ani->SetState(Animation::State::END);

	_time += DELTA_TIME;

	if (_time > 5.0f)
		_end = true;
}
