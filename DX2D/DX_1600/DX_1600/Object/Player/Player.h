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
	
	virtual void Damged(int damge);
	void SetAtkSpeed(float atkPerSec) { _atkSpeed =  1/atkPerSec; }

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }
	void Input();
	void Fire();
	void Jump();

	float GetAtk();

	void SetWeaponDir();

	void IsGround();


	shared_ptr<Collider> GetFootHold() { return _footHold; }
private:
	shared_ptr<Transform> _slot;
	shared_ptr<class Player_Ani> _ani;
	shared_ptr<Collider> _footHold;

	int def = 0;
	shared_ptr<ShortSword> _shortSword;

	float _jumpPower = 0.0f;
	int _jumpCount = 0;
};

