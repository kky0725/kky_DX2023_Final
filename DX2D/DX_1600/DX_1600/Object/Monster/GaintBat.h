#pragma once
class GaintBat : public Creature
{
public:
	GaintBat(bool basic);
	~GaintBat();

	virtual void Update() override;
	virtual void Render() override;

	void Attack();
	void SummonBullets(Vector2 direction);
	void TargetOn(Vector2 playerPos);
	void AttackStart();
	virtual int CheckAttack(shared_ptr<Collider> player) override;

	void Move();
	void TargetOff();

private:
	bool _basic = true;
	bool _targetOn = false;
	float _range = 200.0f;
	int _atk = 10;

	shared_ptr<Animation> _ani;

	float _time = 0.0f;
	Vector2 _dir = { 1.0f,1.0f };

	vector<shared_ptr<class BatBullet>> _bullets;
};
