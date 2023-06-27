#pragma once
class Creature
{
public:
	Creature(wstring string, Vector2 size, float radius);
	Creature(wstring string, float radius);
	virtual ~Creature();

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender();

	const int& GetHp() const { return _hp; }

	Vector2 GetPosition() { return _collider->GetTransform()->GetWorldPosition(); }
	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	shared_ptr<Collider> GetCollider() { return _collider; }

	void Damaged(int damgae);

	bool IsAtcive() { return _isActive; }

protected:
	shared_ptr<Quad>		_quad;
	shared_ptr<Transform>	_transform;
	shared_ptr<Collider>	_collider;

	int _hp = 10;
	bool _isActive = false;

	float _speed = 200.0f;
	float _time = 0.0f;
	float _atkSpeed = 0.5f;
	bool _atkCool = false;
};

