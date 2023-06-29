#pragma once
class Weapon
{
public:
	Weapon(wstring string);
	virtual ~Weapon();

	virtual void Update() abstract;
	virtual void Render() abstract;
	
	const int& GetAtk() {return MyMath::RandomInt(_minAtk, _maxAtk);}
	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }


protected:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<Collider> _collider;

	int _maxAtk = 2;
	int _minAtk = 1;
	float _atkPerSec = 1.0f;
};

