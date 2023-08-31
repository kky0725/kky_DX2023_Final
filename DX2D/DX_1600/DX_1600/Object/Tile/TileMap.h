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

	enum BackGroundImage
	{
		BASIC
	};

	enum GroundImage
	{
		NOGROUND,
		PASSABLE_WIDTH,
		IMPASSABLE_WIDTH,
		IMPASSABLE_HEIGHT,
		IMPASSABLE_BOTH
	};

	enum CreatureType
	{
		NONE,
		BAT,
		REDBAT,
		GAINTBAT,
		REDGAINTBAT,
		SKELSWORD,
		SKELBOW
	};

	struct TileInfo
	{
		BackGroundImage _backGroundImage = BASIC;
		GroundImage _groundImage = NOGROUND;
		CreatureType _CreatureType = NONE;
	};

	TileMap();
	TileMap(float size, Vector2 pos);
	~TileMap();

	void Update();
	void Render();

	void Set(ObjectType objectType, int type);
	void CreateBackGround(Tile::TileImage tileImage);
	void CreateGround(Tile::TileImage tileImage);
	void CreateCreature(CreatureType type);

	shared_ptr<Collider> GetCollider() { return _collider; }
	TileInfo GetTileInfo() { return _tileInfo; }

private:
	shared_ptr<Collider>	_collider	= nullptr;
	BackGroundImage			_backGroundType	= BackGroundImage::BASIC;
	GroundImage				_groundType = GroundImage::NOGROUND;
	CreatureType			_creatureType	= CreatureType::NONE;

	shared_ptr<Tile>		_backGround = nullptr;
	shared_ptr<Tile>		_ground = nullptr;

	shared_ptr<Sprite>		_creatureSprite = nullptr;
	shared_ptr<Transform>	_creatureTransform = nullptr;

	float _size = 5.0f;

	Vector2 _pos = {};
	TileInfo _tileInfo;
};