#pragma once
class SkelBossSword : public Bullet
{
public:
	SkelBossSword();
	~SkelBossSword();

	virtual void Update() override;
	virtual void Render() override;

	void Summon(Vector2 startPos, Vector2 dir);
	void Shoot();

	int GetAtk();

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _maxAtk = 10;
	int _minAtk = 8;
	float _atkPerSec = 1.0f;

	bool _isActive = false;
	bool _isAttack = false;
	bool _isGround = true;
	bool _isCharge = false;
};
