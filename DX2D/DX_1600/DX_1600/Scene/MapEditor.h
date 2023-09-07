#pragma once
class MapEditor : public Scene
{
public:
	MapEditor();
	~MapEditor();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Create();

	void SetCurType(TileMap::ObjectType objectType, int type) { _objectType = objectType; _type = type; };

	void Save(wstring file);
	void Load(wstring file);

	void SetPortal(Vector2 pos);

private:
	vector<vector<shared_ptr<TileMap>>> _tileMaps;

	TileMap::ObjectType _objectType = TileMap::ObjectType::BACKGROUND;
	int _type = 0;

	vector<shared_ptr<Portal>> _portals;
};