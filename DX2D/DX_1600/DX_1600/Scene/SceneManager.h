#pragma once
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton;

	SceneManager();
	~SceneManager();
public:
	void Update();
	void Render();
	void PostRender();

	void NextScene();
	void PrevScene();
	void SetScene(int number);

private:
	vector<shared_ptr<Scene>> _scenes;
	UINT _curScene = 0;
	
	UINT _test;
};

