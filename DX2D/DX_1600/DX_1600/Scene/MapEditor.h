#pragma once
class MapEditor : public Scene
{
public:
	MapEditor();
	~MapEditor();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Init();
	virtual void End();

	void Create();

	void SetCurType(TileMap::ObjectType objectType, int type) { _objectType = objectType; _type = type; };

	void Save(wstring file);
	void Load(wstring file);

private:
	vector<vector<shared_ptr<TileMap>>> _tileMaps;

	int _poolCountX = 10;
	int _poolCountY = 10;

	TileMap::ObjectType _objectType = TileMap::ObjectType::BACKGROUND;
	int _type = 0;
};