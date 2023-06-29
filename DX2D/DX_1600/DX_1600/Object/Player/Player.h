#pragma once
#include "../Creature.h"
class Creature;
class ShortSword;

class Player : public Creature
{
public:
	//Player(wstring string, Vector2 size, float radius);
	Player(wstring string, float radius);
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
private:
	shared_ptr<Transform> _slot;
	//to do 발판 콜라이더 추가

	int def = 0;
	shared_ptr<ShortSword> _shortSword;
};

