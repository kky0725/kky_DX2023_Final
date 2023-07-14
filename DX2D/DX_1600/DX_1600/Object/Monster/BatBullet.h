#pragma once
class BatBullet
{
public:
	BatBullet();
	~BatBullet();

	void Update();
	void Render();

	void SetPos(const Vector2& pos) { _collider->SetPosition(pos); }
	void Summon(const Vector2 startPos);
	void Shoot(const Vector2& dir);

	bool IsActive() { return _isActive; }
	void SetActive(bool value) { _isActive = value; }
	void SetAngle(float value) { _collider->GetTransform()->SetAngel(value); }

	const shared_ptr<CircleCollider>& GetCollider() { return _collider; }

	void LifeTime();

private:
	bool _isActive = false;
	float _speed = 300.0f;
	Vector2 _direction = Vector2(0.0f, 0.0f);

	shared_ptr<CircleCollider> _collider;
	
	shared_ptr<Animation> _ani;

	float _time = 0.0f;
	float _lifeTime = 5.0f;
};
