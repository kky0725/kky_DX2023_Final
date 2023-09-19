#pragma once
class SkelBoss : public Creature
{
public:
	enum BossState
	{
		IDLE,
		ATKP1,
		ATKP2L,
		ATKP2R,
		ATKP3,
	};

	SkelBoss();
	~SkelBoss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void EndAttack1();

	void BossAtk();
	void IdleTime();
	void AttackP1();
	void AttackP2L();
	void AttackP2R();
	void AttackP3();

	vector<shared_ptr<class SkelBossSword>> GetSkelBossSword() { return _swords; }

	virtual int CheckAttack(shared_ptr<Collider> col) override;

	void Hitted();

private:
	shared_ptr<Animation> _body;
	shared_ptr<Animation> _back;

	shared_ptr<class SkelBossHand> _leftHand;
	shared_ptr<class SkelBossHand> _rightHand;

	vector<shared_ptr<class SkelBossSword>> _swords;

	vector<shared_ptr<class SkelBossBullet>> _bullets;
	int _bulletAtk = 10;
	int _bulletCount = 0;
	int _poolCount = 25;
	BossState _bossState = BossState::IDLE;

	weak_ptr<Collider> _target;
	Vector2 _targetPos;

	float _idleTime = 1.0f;
	int count = 0;

	bool _atkP3SummonPase = true;

	shared_ptr<IntBuffer> _intBuffer;
};
