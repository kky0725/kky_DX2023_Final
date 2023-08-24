#pragma once
class SkelBow : public Weapon//weapon말고 Gun으로 수정 예정
{
public:
	SkelBow();
	~SkelBow();

	virtual void Update() override;
	virtual void Render() override;

	void Attack(Vector2 dir);
	void Fire();

	int CheckAttack(shared_ptr<Collider> col);

private:
	shared_ptr<Animation> _ani;
	vector<shared_ptr<class SkelBullet>> _bullets;

	Vector2 _direction;
	int _atk = 5;
};
