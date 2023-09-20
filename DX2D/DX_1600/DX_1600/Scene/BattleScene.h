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
	void InitBoss();
	void End();
	void Rest();

	void ChangeScene();
	void ClearCheck();

	void ReturnHome();

	void Loading();
private:
	vector<vector<shared_ptr<TileMap>>> _tileMaps;

	vector<shared_ptr<Creature>> _creatures;
	shared_ptr<Player> _player;

	vector<shared_ptr<Portal>> _portals;

	int _curIndex_x = 1;
	int _curIndex_y = 1;
	int _oldIndex_x = 1;
	int _oldIndex_y = 1;

	vector<vector<bool>> _cleared;

	float _time = 0.0f;

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<FloatBuffer> _floatBuffer;
	bool _loading = false;
};