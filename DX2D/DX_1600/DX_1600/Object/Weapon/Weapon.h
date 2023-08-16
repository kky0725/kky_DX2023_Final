#pragma once
class Weapon
{
public:
	enum WeaponType
	{
		SWORD,
		GUN
	};

	Weapon();
	Weapon(Vector2 size);
	Weapon(wstring string, Vector2 size);
	virtual ~Weapon();

	virtual void Update() abstract;
	virtual void Render() abstract;
	
	const float& GetAtkPerSec() { return _atkPerSec; }
	const int& GetAtk() {return MyMath::RandomInt(_minAtk, _maxAtk);}
	virtual shared_ptr<Transform> GetTransform() { return _transform; }
	virtual shared_ptr<Collider> GetCollider() { return _collider; }

	bool IsAtcive() { return _isActive; }
	void SetIsActive(bool value) { _isActive = value; }

	bool WTIsSword();

protected:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<Collider> _collider;

	int _maxAtk = 2;
	int _minAtk = 1;
	float _atkPerSec = 1.0f;

	bool _isActive = true;

	WeaponType _type = WeaponType::SWORD;
};

