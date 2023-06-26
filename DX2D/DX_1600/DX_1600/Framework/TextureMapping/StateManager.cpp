#include "framework.h"
#include "StateManager.h"

StateManager* StateManager::_instance = nullptr;
StateManager::StateManager()
{
	_sampler = make_shared<SampleState>();

	_alpha = make_shared<BlendState>();
	_alpha->Alpha();

	_additive = make_shared<BlendState>();
	_additive->Additive();

	_blendState = make_shared<BlendState>();
}

StateManager::~StateManager()
{
}
