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

	enum BackGroundType
	{
		BASIC
	};

	enum GroundType
	{
		NOGROUND
	};

	enum CreatureType
	{
		NONE,
		BAT,
		REDBAT,
		GAINTBAT,
		REDGAINTBAT
	};

	TileMap();
	TileMap(float size, Vector2 pos);
	~TileMap();

	void Update();
	void Render();

	void Set(ObjectType objectType, int type);
	void CreateCreature(CreatureType type);

	shared_ptr<Collider> GetCollider() { return _collider; }


private:
	shared_ptr<Collider>	_collider	= nullptr;
	BackGroundType			_backGroundType	= BackGroundType::BASIC;
	GroundType				_groundType = GroundType::NOGROUND;
	CreatureType			_creatureType	= CreatureType::NONE;

	shared_ptr<Tile>		_backGround = nullptr;
	shared_ptr<Tile>		_ground = nullptr;
	shared_ptr<Creature>	_creature = nullptr;

	float _size = 5.0f;

	Vector2 _pos;
};