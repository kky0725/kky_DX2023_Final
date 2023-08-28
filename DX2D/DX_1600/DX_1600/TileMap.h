#pragma once
class TileMap
{
public:
	enum ObjectType
	{
		BACKGROUND,
		GROUND,
		CREATURE
	};

	TileMap();
	~TileMap();

private:
	shared_ptr<Collider>	_collider	= nullptr;
	shared_ptr<Tile>		_backGround	= nullptr;
	shared_ptr<Tile>		_ground		= nullptr;
	shared_ptr<Creature>	_creature	= nullptr;
};