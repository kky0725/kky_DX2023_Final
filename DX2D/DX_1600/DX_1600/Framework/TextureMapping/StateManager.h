#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;

	StateManager();
	~StateManager();
public:
	shared_ptr<SampleState> GetSampler() { return _sampler; }
	shared_ptr<BlendState> GetAlpha() { return _alpha; }
	shared_ptr<BlendState> GetAdditive() { return _additive; }
	shared_ptr<BlendState> GetBlendState() { return _blendState; }

private:
	//static StateManager* _instance;

	shared_ptr<SampleState> _sampler;
	shared_ptr<BlendState> _alpha;
	shared_ptr<BlendState> _additive;
	shared_ptr<BlendState> _blendState;

	ID3D11RasterizerState* rasterizerState = nullptr;
};

