#pragma once
class SkelBullet : public Bullet
{
public:
	SkelBullet();
	~SkelBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Shoot(Vector2 startPos, Vector2 dir);

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};
