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

	void ChangeScene();

private:
	vector<vector<shared_ptr<TileMap>>> _tileMaps;

	vector<shared_ptr<Creature>> _creatures;
	shared_ptr<Player> _player;

	vector<shared_ptr<Portal>> _portals;

	int _curIndex_x = 1;
	int _curIndex_y = 1;
	int _oldIndex_x = 1;
	int _oldIndex_y = 1;
};