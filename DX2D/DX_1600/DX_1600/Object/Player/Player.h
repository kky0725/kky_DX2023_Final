#pragma once
#include "../Creature.h"
class Creature;

class Player : public Creature
{
public:
	Player(wstring string, Vector2 size, float radius);
	Player(wstring string, float radius);
	virtual ~Player();

	virtual void Update() override;
	virtual void Render() override;
private:

};

