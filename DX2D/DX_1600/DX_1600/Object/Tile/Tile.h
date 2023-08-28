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

	Tile(wstring srvFile, TileType type, string name, Vector2 pos ,Vector2 tileSize, TileDir tileDir = NONE, Vector2 colSize = Vector2(1.0f, 1.0f), Vector2 colPos = Vector2(0.0f, 0.0f));
	~Tile();

	void Update();
	void Render();

	bool Block(shared_ptr<Collider> collider);
	bool PassableBlock(shared_ptr<Collider> collider);
	bool TileBlock(shared_ptr<Collider> collider);
	

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	TileType _tileType;
	string _name;

	Vector2 _colSize;
	Vector2 _tileSize;

	TileDir _tileDir;
};