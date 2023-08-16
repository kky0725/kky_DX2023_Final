#pragma once
#include "../Creature.h"
class Creature;
class ShortSword;

class Player : public Creature
{
public:
	Player();
	virtual ~Player();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	
	virtual void Damaged(int damge);
	void SetAtkSpeed(float atkPerSec) { _atkSpeed =  1/atkPerSec; }

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }
	void Input();
	void Fire();
	void Jump();

	void SwordAtk();
	void BowAtk();

	void SwapWeapon();

	virtual int CheckAttack(shared_ptr<Collider> enemy)  override;
	int CheckAttackSword(shared_ptr<Collider> enemy);
	int CheckAttackBow(shared_ptr<Collider> enemy);

	float GetAtk();

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

	shared_ptr<Weapon> _weapon1 = nullptr;
	shared_ptr<Weapon> _weapon2 = nullptr;
	int _curIndex = 0;

	float _jumpPower = 0.0f;
	int _jumpCount = 0;

	bool _end = false;
};