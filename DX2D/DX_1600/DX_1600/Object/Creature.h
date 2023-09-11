#pragma once
class Creature
{
public:
	Creature(wstring string, float radius);
	Creature(float radius);
	virtual ~Creature();

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender();

	const int& GetHp() const { return _hp; }
	void SetHpBar();


	Vector2 GetPosition() { return _collider->GetTransform()->GetWorldPosition(); }
	virtual void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

	virtual void Damaged(int damge);
	virtual int CheckAttack(shared_ptr<Collider> col) abstract;
	void CheckDamaged();

	bool IsAtcive() { return _isActive; }
	void SetIsActive(bool value) { _isActive = value; }


protected:
	shared_ptr<Quad>		_quad;
	shared_ptr<Transform>	_transform;
	shared_ptr<Collider>	_collider;

	shared_ptr<class HpBar> _hpBar;

	UINT _maxHp = 10;
	UINT _hp = 10;

	bool _isActive = true;

	float _speed = 200.0f;
	float _time = 0.0f;
	float _atkSpeed = 0.5f;
	bool _atkCool = false;

	float _DCtime = 0.0f;
	bool _damaged = false;
};

