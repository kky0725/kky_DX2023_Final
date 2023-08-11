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
	//float _atkPerSec = 1.0f;

	bool _isActive = false;
	bool _isAttack = false; // 날라가는 동안 이펙트 shader 만들어서 변경 예정
	bool _isGround = false; // 땅에 박히는 이펙트 추가 안할거면 삭제 예정
	bool _isCharge = false; // 차지 이펙트 추가 안할거면 삭제 예정
};
