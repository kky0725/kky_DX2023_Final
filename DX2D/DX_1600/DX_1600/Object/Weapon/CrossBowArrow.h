#pragma once
class CrossBowArrow : public Bullet
{
public:
	CrossBowArrow();
	~CrossBowArrow();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};
