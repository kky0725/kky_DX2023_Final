#pragma once
#include "../Creature.h"

class Bat : Creature
{
public:
	Bat(wstring string);
	virtual ~Bat();

	virtual void Update() override;
	virtual void Render() override;

	void move();

private:
	shared_ptr<Animation> _ani;

};

