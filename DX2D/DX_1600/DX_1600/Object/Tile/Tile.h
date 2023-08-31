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
		BASIC
	};

	Tile(TileImage tileImage, Vector2 pos);
	~Tile();

	void Update();
	void Render();

	bool Block(shared_ptr<Collider> collider);
	bool PassableBlock(shared_ptr<Collider> collider);
	bool TileBlock(shared_ptr<Collider> collider);
	
private:
	void SetTileType();

	shared_ptr<Collider> _collider;
	shared_ptr<Sprite> _ground;
	shared_ptr<Transform> _transform;

	Vector2 _colSize = Vector2(16.0f, 16.0f);

	TileType _tileType = TileType::IMPASSABLE;
	TileDir _tileDir = TileDir::NONE;
};