#pragma once
class CrossBowArrow : public Bullet
{
public:
	CrossBowArrow();
	~CrossBowArrow();

	virtual void Update() override;
	virtual void Render() override;

	void Shoot(Vector2 startPos, Vector2 dir);

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};
