#pragma once
#include "../Creature.h"

class Player : public Creature
{
public:
	Player();
	virtual ~Player();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void BulletUpdate();
	void BulletRender();
	
	virtual void Damaged(int damge);
	void SetAtkSpeed(float atkPerSec) { _atkSpeed =  1/atkPerSec; }

	void Move(Vector2 movePos) { _footHold->GetTransform()->AddVector2(movePos); }
	void Input();
	void Fire();
	void Jump();
	void Dash();

	void SwordAtk();
	void BowAtk();

	void SwapWeapon();

	virtual int CheckAttack(shared_ptr<Collider> enemy)  override;
	int CheckAttackSword(shared_ptr<Collider> enemy);
	int CheckAttackBow(shared_ptr<Collider> enemy);

	int GetAtk();

	void SetWeaponDir();

	void IsGround();

	void Die();
	bool End() { return _end; }

	shared_ptr<Collider> GetFootHold() { return _footHold; }
private:
	shared_ptr<Transform> _slot;
	shared_ptr<class Player_Ani> _ani;
	shared_ptr<Collider> _footHold;

	int _def = 0;
	shared_ptr<Weapon> _weapon;

	shared_ptr<Weapon> _weapon0 = nullptr;
	shared_ptr<Weapon> _weapon1 = nullptr;
	int _curIndex = 0;

	float _jumpPower = 0.0f;
	int _jumpCount = 0;

	float _dashSpeed = 600.0f;
	float _dashTime = 0.0f; //0.5f
	float _dashCT = 0.0f; //2.0f
	int _dashCount = 2;
	int _maxDashCount = 2;
	bool _dashCool = false;

	bool _end = false;
};