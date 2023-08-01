#pragma once
class SkelBoss : public Creature
{
public:
	enum BossState
	{
		IDLE,
		ATKP1,
		ATKP2,
		ATKP3
	};

	SkelBoss();
	~SkelBoss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void EndAttack1();

	void BossAtk();
	void AttackP1();
	void AttackP2();
	void AttackP3();

	virtual int CheckAttack(shared_ptr<Collider> col) override;

private:
	shared_ptr<Animation> _body;
	shared_ptr<Animation> _back;

	shared_ptr<class SkelBossHand> _leftHand;
	shared_ptr<class SkelBossHand> _rightHand;

	vector<shared_ptr<class SkelBossBullet>> _bullets;
	int _bulletCount = 0;
	int _poolCount = 25;
	BossState _bossState = BossState::IDLE;

	weak_ptr<Collider> _target;
};
