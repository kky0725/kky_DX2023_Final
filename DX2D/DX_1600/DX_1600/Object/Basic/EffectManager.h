#pragma once
class EffectManager : public Singleton<EffectManager>
{
	friend class Singleton;

	EffectManager();
	~EffectManager();
public:
	void Update();
	void Render();

	//vector<shared_ptr<Effect>>& GetEffect(string name) { return ; }

	void AddEffect(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END);

	void Play(string name, Vector2 pos, float angle = 0.0f);

private:
	UINT _poolCount = 30;

	unordered_map<string, vector<shared_ptr<Effect>>> _effectTable;
	static EffectManager* _instance;

};

