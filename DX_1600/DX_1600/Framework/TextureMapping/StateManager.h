#pragma once
class StateManager
{
	StateManager();
	~StateManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new StateManager();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static StateManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	shared_ptr<SampleState> GetSampler() { return _sampler; }
	shared_ptr<BlendState> GetAlpha() { return _alpha; }
	shared_ptr<BlendState> GetAdditive() { return _additive; }
	shared_ptr<BlendState> GetBlendState() { return _blendState; }

private:
	static StateManager* _instance;

	shared_ptr<SampleState> _sampler;
	shared_ptr<BlendState> _alpha;
	shared_ptr<BlendState> _additive;
	shared_ptr<BlendState> _blendState;
};

