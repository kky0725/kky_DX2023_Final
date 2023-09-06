#pragma once
class Gun : public Weapon
{
public:
	Gun(ItemType type, string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring srvFile, string xmlFile);
	virtual ~Gun();

	virtual void Update() override;
	virtual void Render() override;
	void BulletUpdate();
	void BulletRender();
	void DeleteBullet();

	virtual shared_ptr<Transform> GetTransform() override { return _ani->GetTransform(); }
	virtual shared_ptr<Collider> GetCollider() override { return _collider; }

	void Attack(Vector2 dir);
	void Fire();
	int CheckAttack(shared_ptr<Collider> col);

	void SetLeft() { _ani->SetScale(Vector2(2.0f, 2.0f)); }
	void SetRight() { _ani->SetScale(Vector2(2.0f, -2.0f)); }

private:
	shared_ptr<Animation> _ani;

	vector<shared_ptr<Bullet>> _bullets;
	Vector2 _direction;
};