#pragma once
class Tile
{
public:
	enum TileType
	{
		IMPASSABLE,
		PASSABLE,
		BACKGROUND
	};

	enum TileDir
	{
		NONE,
		WIDTH,
		HEIGHT,
		BOTH
	};

	enum TileImage
	{
		WALL_BASIC0,
		WALL_BASIC1,
		WALL_BASIC2,
		WALL_BASIC3,
		WALL_BASIC4,
		WALL_BASIC5,
		WALL_BASIC6,
		WALL_BASIC7,
		WALL_BASIC8,
		WALL_BASIC9,
		WALL_BASIC10,
		WALL_BASIC11,
		WALL_BASIC12,
		WALL_BASIC13,
		WALL_BASIC14,
		WALL_BASIC15,
		WALL_BASIC16,
		WALL_BASIC_CEILING0,
		WALL_BASIC_CEILING1,
		WALL_BASIC_CEILING2,
		WALL_BASIC_CEILING3,
		WALL_BASIC_CEILING4,
		WALL_BASIC_CEILING5,
		WALL_BASIC_CEILING6,
		WALL_BASIC_STATUE_BOTTOM,
		WALL_BASIC_STATUE_MIDLE,
		WALL_BASIC_STATUE_TOP,
		WALL_CHAIN,

		ONE_WAY0,
		ONE_WAY1,
		ONE_WAY2,
		ONE_WAY3,
		H0, H1, H2, H3, H4, H5,
		H6, H7, H8, H9, H10, H11,
		H12, H13, H14, H15,
		STAIR_BOTTOM_LEFT,
		STAIR_BOTTOM_RIGHT,
		STAIR_TOP_LEFT,
		STAIR_TOP_RIGHT,
		NOGROUND
	};

	Tile(TileImage tileImage, Vector2 pos);
	~Tile();

	void Update();
	void Render();

	bool Block(shared_ptr<Collider> collider);
	bool PassableBlock(shared_ptr<Collider> collider);
	bool TileBlock(shared_ptr<Collider> collider);

	
private:
	void SetTileDir(TileImage tileImage);

	shared_ptr<Collider> _collider;
	shared_ptr<Sprite> _ground;
	shared_ptr<Transform> _transform;

	Vector2 _colSize = Vector2(16.0f, 16.0f);

	TileType _tileType = TileType::IMPASSABLE;
	TileDir _tileDir = TileDir::NONE;
};