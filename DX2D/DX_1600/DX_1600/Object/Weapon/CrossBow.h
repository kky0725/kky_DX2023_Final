#pragma once
class CrossBow : public Weapon
{
public:
	CrossBow();
	~CrossBow();

	virtual void Update() override;
	virtual void Render() override;

	virtual shared_ptr<Transform> GetTransform() { return _ani->GetTransform(); }
	virtual shared_ptr<Collider> GetCollider() { return nullptr; }

private:
	shared_ptr<Animation> _ani;

	vector<shared_ptr<Bullet>> _bullets;
};