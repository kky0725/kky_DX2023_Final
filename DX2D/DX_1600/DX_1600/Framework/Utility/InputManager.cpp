#include "framework.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(_oldState, _curState, sizeof(_oldState));

	GetKeyboardState(_curState);

	for (int i = 0; i < KEY_MAX; i++)
	{
		byte key = _curState[i] & 0x80;
		_curState[i] = (key ? 1 : 0); // 삼항조건 연산자 a ? b : c  // a가 ture면 b 실행 flase면 c실행

		int old = _oldState[i];
		int cur = _curState[i];

		if (old == 0 && cur == 1)
		{
			_stateMap[i] = State::DOWN;
		}
		else if (old == 1 && cur == 0)
		{
			_stateMap[i] = State::UP;
		}
		else if (old == 1 && cur == 1)
		{
			_stateMap[i] = State::PRESS;
		}
		else
		{
			_stateMap[i] = State::NONE;
		}
	}
}
