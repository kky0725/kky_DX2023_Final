#pragma once
#define KEY_MAX 255

class InputManager : public Singleton<InputManager>
{
	friend class Singleton;

	enum State
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager();

public:
	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

	void SetMousePos(const Vector2& pos) { _mousePos = pos; }
	const Vector2& GetMousePos() { return _mousePos; }

private:
	static InputManager* _instance;

	byte _curState[KEY_MAX] = {};
	byte _oldState[KEY_MAX] = {};
	byte _stateMap[KEY_MAX] = {};

	Vector2 _mousePos;
};

