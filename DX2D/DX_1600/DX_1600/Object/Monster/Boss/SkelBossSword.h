#pragma once
class SkelBossSword : public Bullet
{
public:
	SkelBossSword();
	~SkelBossSword();

	virtual void Update() override;
	virtual void Render() override;

	void Summon(Vector2 startPos);
	void Shoot();
	void Charge(Vector2 dir);

	int GetAtk();

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _maxAtk = 10;
	int _minAtk = 8;
	float _atkPerSec = 1.0f;

	bool _isActive = false;
	bool _isAttack = false;
	bool _isGround = false;
	bool _isCharge = false;
};
