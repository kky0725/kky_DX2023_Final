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

	bool IsAttack() { return _isAttack; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _maxAtk = 10;
	int _minAtk = 8;
	//float _atkPerSec = 1.0f;

	bool _isAttack = false; // 날라가는 동안 이펙트 shader 만들어서 변경 예정
	bool _isGround = false; // 땅에 박히는 이펙트 추가 안할거면 삭제 예정
	bool _isCharge = false; // 차지 이펙트 추가 안할거면 삭제 예정

	//땅에 충돌했을 때 멈추기 위한 콜라이더 추가 예정 ground와 block용도로 사용
};
