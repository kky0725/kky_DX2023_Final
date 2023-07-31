#pragma once
class SkelBossBullet : public Bullet
{
public:
	SkelBossBullet();
	~SkelBossBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Shoot(Vector2 startPos, Vector2 dir);

private:
	shared_ptr<Animation> _ani;

};
