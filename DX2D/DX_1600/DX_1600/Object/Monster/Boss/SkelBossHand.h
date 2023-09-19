#pragma once
class SkelBossHand
{
public:
	SkelBossHand(bool isLeft);
	~SkelBossHand();

	void Update();
	void Render();
	
	void Shoot();
	void EndLaser();
	void Attack();
	void EndAttack();
	bool Attacking() { return _attacking; }
	bool IsActive() { return _isActive; }

	shared_ptr<Transform> GetTransform() { return _hand->GetTransform(); }
	shared_ptr<Collider> GetCollider() { return _collider; }

private:
	shared_ptr<Animation> _hand;

	shared_ptr<Animation> _head;
	vector<shared_ptr<Animation>> _bodys;
	shared_ptr<Collider> _collider;
	Vector2 _bodySize = Vector2(120.0f, 120.0f);

	bool _attacking = false;
	bool _isActive = false;

	bool _isLeft;
};
