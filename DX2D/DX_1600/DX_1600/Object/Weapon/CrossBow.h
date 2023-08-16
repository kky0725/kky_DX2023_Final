#pragma once
class CrossBow : public Weapon
{
public:
	CrossBow();
	~CrossBow();

	virtual void Update() override;
	virtual void Render() override;

	virtual shared_ptr<Transform> GetTransform() { return _ani->GetTransform(); }
	virtual shared_ptr<Collider> GetCollider() { return _collider; }

	void Attack(Vector2 dir);
	void Fire();
	int CheckAttack(shared_ptr<Collider> col);

private:
	shared_ptr<Animation> _ani;

	vector<shared_ptr<Bullet>> _bullets;
	Vector2 _direction;
};