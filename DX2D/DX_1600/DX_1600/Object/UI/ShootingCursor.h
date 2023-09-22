#pragma once
class ShootingCursor
{
public:
	ShootingCursor();
	~ShootingCursor();

	void Update();
	void PostRender();

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};