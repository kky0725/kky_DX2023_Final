#pragma once
class Creature
{
public:


private:
	shared_ptr<Sprite>		_sprite;
	shared_ptr<Transform>	_transform;
	shared_ptr<Collider>	_collider;
};

