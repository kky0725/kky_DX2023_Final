#include "framework.h"
#include "Player.h"
#include "Player_Ani.h"

Player::Player()
	:Creature(27.0f)
{
	_slot = make_shared<Transform>();
	_slot->SetParent(_collider->GetTransform());

	_ani = make_shared<Player_Ani>();
	_ani->SetParent(_collider->GetTransform());

	_hp = 100000;

	_footHold = make_shared<RectCollider>(Vector2(27.0f, 10.0f));
	_footHold->SetParent(_collider->GetTransform());
	_footHold->SetPosition(Vector2(0.0f, -24.0f));

	//나중에 함수 새로 만들어서 생성자에서 꺼낼 부분
	//_weapon0 = ItemList::GetInstance()->GetWeapon(0);
	//_weapon1 = ItemList::GetInstance()->GetWeapon(1);
	//_weapon = _weapon0;
	_weapon = Inventory::GetInstance()->CurWeapon();
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
	BulletUpdate();

	Inventory::GetInstance()->Update();
}

void Player::Render()
{
	if (_end)
		return;
	Creature::Render();
	_slot->SetBuffer(0);
	_ani->Render();
	_weapon->Render();
	BulletRender();

	_footHold->Render();
}

void Player::PostRender()
{
	ImGui::Text("PlayerDashCount : %d", _dashCount);

	Inventory::GetInstance()->PostRender();
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
			//_speed = 200.0f;
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

	//if (KEY_DOWN(VK_RBUTTON) && !_dashCool)
	if (KEY_DOWN(VK_XBUTTON2) && !_dashCool)
	{
		_dashCool = true;
		//_speed = _dashSpeed;
		_dashCount--;
	}
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
	}
}

void Player::SwapWeapon()
{
	//if (_weapon0 == nullptr || _weapon1 == nullptr)
	//	return;

	if (KEY_DOWN(VK_XBUTTON1))
	{
		Inventory::GetInstance()->ChangeWeapon();
		_weapon = Inventory::GetInstance()->CurWeapon();
		//if (_weapon == _weapon0)
		//	_weapon = _weapon1;
		//else
		//	_weapon = _weapon0;

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
	return dynamic_pointer_cast<Gun>(_weapon)->CheckAttack(enemy);
}

int Player::GetAtk()
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
