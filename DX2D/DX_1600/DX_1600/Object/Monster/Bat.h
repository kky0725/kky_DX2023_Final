#pragma once
#include "../Creature.h"

class Bat : public Creature
{
public:
	Bat(bool basic);
	virtual ~Bat();

	virtual void Update() override;
	virtual void Render() override;

	void move();

private:
	shared_ptr<Animation> _ani;

	float _time = 0.0f;
	Vector2 _dir = { 1.0f,1.0f };

};
