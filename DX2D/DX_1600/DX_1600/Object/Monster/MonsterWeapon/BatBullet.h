#pragma once
class BatBullet : public Bullet
{
public:
	BatBullet();
	virtual ~BatBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Summon(const Vector2 startPos, Vector2 dir);
	void Shoot();

private:

};
