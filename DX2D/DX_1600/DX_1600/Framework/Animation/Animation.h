#pragma once
class Animation
{
public:
	enum State
	{
		IDLE,
		RUN,
		JUMP,
		ATK,
		END,
		NONE
	};

	Animation();
	virtual ~Animation();

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	void SetParent(shared_ptr<Transform> parent) { _transform->SetParent(parent); }
	void SetScale(Vector2 value) { _transform->SetScale(value); }
	void SetPosition(Vector2 value) { _transform->SetPosition(value); }
	Vector2 GetWorldPosition() { return _transform->GetWorldPosition(); }
	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetState(State state);
	State GetState() { return _curState; }
	void SetStateIdle() { SetState(IDLE); }

	void SetIsGround(bool value) { _isGround = value; }
	bool GetISGround() const { return _isGround; }
	bool GetIsRight() const { return _isRight; }

	void CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type = Action::Type::LOOP, float speed = 0.1f, CallBack event = nullptr);
	void CreateAction(wstring srvPath, string actionName, Vector2 size);

	void SetEndEvent(State state, CallBack event);
	void SetNumberEvent(State state, CallBack event, int eventNumber);

	void SetLeft();
	void SetRight();

	void Play() { _actions[_curState]->Play(); }
	void Reset() { _actions[_curState]->Reset(); }

protected:
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<class Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	Vector2 _fixedPos;

	bool _isRight = true;
	bool _isGround = false;
};

