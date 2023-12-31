#pragma once
class Coin
{
public:
	Coin();
	~Coin();

	void Update();
	void Render();

	bool IsCollison(shared_ptr<Collider> col);
	void AppearCoin(Vector2 value);
	shared_ptr<Collider> GetCollider() { return _col; }

	bool IsActive() { return _isActive; }

private:
	shared_ptr<Animation> _ani;
	shared_ptr<Collider> _col;

	bool _isActive = false;

	float _gravity = 0.0f;
};