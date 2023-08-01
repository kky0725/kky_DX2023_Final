#pragma once
class BatBullet : public Bullet
{
public:
	BatBullet();
	virtual ~BatBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Summon(Vector2 startPos, Vector2 dir);
	void Shoot();
	

private:
	shared_ptr<Animation> _ani;
};
