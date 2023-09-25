#include "framework.h"
#include "Player.h"
#include "Player_Ani.h"

#include "../UI/PlayerHpBar.h"
#include "../UI/DashCount.h"

Player::Player()
	:Creature(27.0f)
{
	_slot = make_shared<Transform>();
	_slot->SetParent(_collider->GetTransform());

	_ani = make_shared<Player_Ani>();
	_ani->SetParent(_collider->GetTransform());

	_hpBar = make_shared<PlayerHpBar>();

	_maxHp = 50;
	_curHp = _maxHp;

	_footHold = make_shared<CircleCollider>(12.0f);
	_collider->SetParent(_footHold->GetTransform());
	_collider->SetPosition(Vector2(0.0f, 5.0f));

	_dashCountUI = make_shared<DashCount>();

	UpdateWeapon();

	_coins.resize(0);


	EffectManager::GetInstance()->AddEffect("Jump", L"Resource/Player/JumpFX.png", Vector2(1, 5), Vector2(30.0f, 30.0f));
	EffectManager::GetInstance()->AddEffect("DoubleJump", L"Resource/Player/DoubleJumpFX.png", Vector2(1, 6), Vector2(30.0f, 30.0f));
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

	SetHpBar();
	_hpBar->Update();
	_collider->Update();
	CheckDamaged();
	_slot->Update();

	_ani->Update();
	_weapon->Update();
	_footHold->Update();
	BulletUpdate();

	Inventory::GetInstance()->Update();

}

void Player::Render()
{
	if (_end)
		return;
	_collider->Render();
	_slot->SetBuffer(0);
	_ani->Render();
	_weapon->Render();
	BulletRender();

	_footHold->Render();
}

void Player::PostRender()
{
	//ImGui::Text("PlayerDashCount : %d", _dashCount);

	Inventory::GetInstance()->PostRender();

	_hpBar->PostRender();
	_dashCountUI->PostRender();
}

void Player::BulletUpdate()
{
	if (Inventory::GetInstance()->CurWeapon()->WTIsSword() && !Inventory::GetInstance()->AnotherWeapon()->WTIsSword())
		dynamic_pointer_cast<Gun>(Inventory::GetInstance()->AnotherWeapon())->BulletUpdate();
}

void Player::BulletRender()
{
	if (Inventory::GetInstance()->CurWeapon()->WTIsSword() && !Inventory::GetInstance()->AnotherWeapon()->WTIsSword())
		dynamic_pointer_cast<Gun>(Inventory::GetInstance()->AnotherWeapon())->BulletRender();
}

void Player::DeleteBullet()
{
	if (!Inventory::GetInstance()->CurWeapon()->WTIsSword())
		dynamic_pointer_cast<Gun>(_weapon)->DeleteBullet();

	if (Inventory::GetInstance()->CurWeapon()->WTIsSword() && !Inventory::GetInstance()->AnotherWeapon()->WTIsSword())
		dynamic_pointer_cast<Gun>(Inventory::GetInstance()->AnotherWeapon())->DeleteBullet();
}

void Player::UpdateWeapon()
{
	_weapon = Inventory::GetInstance()->CurWeapon();
	_weapon->GetCollider()->SetParent(_slot);
	_weapon->GetCollider()->GetTransform()->SetPosition(Vector2(50, 0));

	SetAtkSpeed(_weapon->GetAtkPerSec());
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

		if (_jumpPower < -400.0f)
			_jumpPower = -400.0f;

		//_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
		_footHold->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
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
	Dash();
	SwapWeapon();

	Inventory::GetInstance()->Open();
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
		if (_ani->GetISGround())
		{
			EFFECT_PLAY("Jump", _footHold->GetPos());
			SOUND->Play("Jump");
		}

		if (!_ani->GetISGround())
		{
			EFFECT_PLAY("DoubleJump", _footHold->GetPos());
			SOUND->Play("Jump");
		}

		_jumpPower = 600.0f;
		_jumpCount++;
		_ani->SetIsGround(false);

	}
}

void Player::Dash()
{
	if (_dashCool)
	{
		if (KEY_PRESS('A'))
		{
			Vector2 movePos = Vector2(2.0f * -_speed, 0.0f) * DELTA_TIME;
			Move(movePos);
		}

		if (KEY_PRESS('D'))
		{
			Vector2 movePos = Vector2(2.0f * _speed, 0.0f) * DELTA_TIME;
			Move(movePos);
		}

		if (KEY_PRESS('W'))
		{
			Vector2 movePos = Vector2(0.0f, 2.0f * _speed) * DELTA_TIME;
			Move(movePos);
		}

		if (KEY_PRESS('S'))
		{
			Vector2 movePos = Vector2(0.0f, 2.0f * -_speed) * DELTA_TIME;
			Move(movePos);
		}

		_dashTime += DELTA_TIME;
		if (_dashTime > 0.5f)
		{
			_dashCool = false;
			_dashTime = 0.0f;
		}
	}

	if (_dashCount < _maxDashCount)
	{
		_dashCT += DELTA_TIME;
		if (_dashCT > 2.0f)
		{
			_dashCT = 0.0f;
			_dashCount++;
		}
	}
	else
	{
		_dashCount = _maxDashCount;
		_dashCT = 0.0f;
	}


	if (_dashCount == 0)
		return;

	if (KEY_DOWN(VK_XBUTTON2) && !_dashCool)
	{
		_dashCool = true;
		_dashCount--;
		SOUND->Play("Dash");
	}

	_dashCountUI->SetCount(_maxDashCount, _dashCount);
	_dashCountUI->Update();
}

void Player::SwordAtk()
{
	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time < 0.1f)
		{
			Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
			Vector2 dir = W_MOUSE_POS - startPos;
			if(dir.x >0)
				_slot->AddAngle(-20.0f * DELTA_TIME);
			else
				_slot->AddAngle(+20.0f * DELTA_TIME);
		}
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
		SOUND->Play("Atk");
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
		dynamic_pointer_cast<Gun>(_weapon)->Attack(dir);
		SOUND->Play("Shoot");
	}
}

void Player::SwapWeapon()
{
	//if (_weapon0 == nullptr || _weapon1 == nullptr)
	//	return;

	if (KEY_DOWN(VK_XBUTTON1))
	{
		Inventory::GetInstance()->ChangeWeapon();
		UpdateWeapon();
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
	return dynamic_pointer_cast<Gun>(_weapon)->CheckAttack(enemy);
}

int Player::GetAtk()
{
	return _weapon->GetAtk();
}

void Player::SetWeaponDir()
{
	if (!_isActive)
		return;
	if (_time < 0.1f && _time > 0.0f)
		return;
	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();
	Vector2 dir = W_MOUSE_POS - startPos;
	float angle = atan(dir.y / dir.x);
	if (dir.x < 0)
		angle += PI;
	_slot->SetAngel(angle);

	if (!_weapon->WTIsSword())
	{
		if (dir.x < 0)
			dynamic_pointer_cast<Gun>(_weapon)->SetLeft();
		else
			dynamic_pointer_cast<Gun>(_weapon)->SetRight();
	}
	
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

void Player::Rest()
{
	_curHp = _maxHp;
	_isActive = true;
	_end = false;
	_ani->SetStateIdle();
	_jumpCount = 0;
	_dashCount = 2;
}

void Player::SetIdle()
{
	_ani->SetStateIdle();
}
