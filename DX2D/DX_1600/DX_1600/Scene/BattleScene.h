#pragma once
class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender();

	void Block();
	void CheckAttack();

	void Init(wstring file);
	void End();

private:
	vector<vector<shared_ptr<TileMap>>> _tileMaps;

	int _poolCountX = 10;
	int _poolCountY = 10;

	vector<shared_ptr<Creature>> _creatures;
	shared_ptr<Player> _player;
};