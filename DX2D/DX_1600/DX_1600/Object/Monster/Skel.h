#pragma once
class Skel : public Creature
{
public:
	Skel();
	virtual ~Skel();

	virtual void Update() override;
	virtual void Render() override;

	void TargetOn(Vector2 playerPos);

	virtual int CheckAttack(shared_ptr<Collider> col) override;
	void Attack();
	void Move();


private:
	shared_ptr<Animation> _ani;
	Vector2 _dir = { 1.0f,0.0f };
	shared_ptr<Transform> _slot;

	bool _basic = true;
	bool _targetOn = false;
	float _range = 200.0f;
	int _atk = 10;

};
