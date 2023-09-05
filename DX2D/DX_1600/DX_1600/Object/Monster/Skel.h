#pragma once
class Skel : public Creature
{
public:
	Skel(bool basic);
	virtual ~Skel();

	virtual void Update() override;
	virtual void Render() override;

	void TargetOn(Vector2 playerPos);
	void TargetOff();

	virtual int CheckAttack(shared_ptr<Collider> col) override;
	int CheckAttackSword(shared_ptr<Collider> col);
	int CheckAttackBow(shared_ptr<Collider> col);
	void SwordAttack();
	void BowAttack();
	void Move();
	void Chase();
	void EndAttack();

	void Gravity();

private:
	shared_ptr<Animation> _ani;
	Vector2 _dir = { 1.0f,0.0f };
	shared_ptr<Transform> _slot;

	bool _basic = true;
	bool _targetOn = false;
	float _range = 500.0f;
	int _atk = 10;

	float _jumpPower = 0.0f;

	weak_ptr<Collider> _target;
	shared_ptr<Weapon> _weapon;
};

