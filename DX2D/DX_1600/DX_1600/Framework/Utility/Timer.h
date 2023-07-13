#pragma once
class Timer
{
	Timer();
	~Timer();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Timer();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Timer* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();
	void SetLockFPS(float value) { _lockFPS = value; }

	int GetFPS() { return _frameRate; }
	float GetDeltaTime() { if (_deltaTime > 1.0f) return 0.016666f; return _deltaTime; }
	float GetRunTime() { return _runTime; }

private:
	static Timer* _instance;

	float _timeScale = 0.0;
	float _deltaTime = 0.0; // 1번 업데이트하는데 걸리는 시간

	unsigned __int64 _curTime = 0;
	unsigned __int64 _lastTime = 0;
	unsigned __int64 _periodFrequency = 0;

	unsigned __int64 _frameRate = 0;
	unsigned __int64 _frameCount = 0;

	float _oneSecCount = 0.0;
	float _runTime = 0.0;
	float _lockFPS = 0.0;

};


