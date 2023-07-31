#pragma once
class Bullet
{
public:
	Bullet();
	Bullet(float size);
	virtual ~Bullet();

	virtual void Update() abstract;
	virtual void Render() abstract;

	void SetPos(const Vector2& pos) { _collider->SetPosition(pos); }

	bool IsActive() { return _isActive; }
	void SetActive(bool value) { _isActive = value; }
	void SetAngle(float value) { _collider->GetTransform()->SetAngel(value); }

	const shared_ptr<CircleCollider>& GetCollider() { return _collider; }

	void LifeTime();

protected:
	bool _isActive = false;
	float _speed = 300.0f;
	Vector2 _direction = Vector2(0.0f, 0.0f);

	shared_ptr<CircleCollider> _collider;

	float _time = 0.0f;
	float _lifeTime = 15.0f;
};

