#include "framework.h"
#include "Player_Ani.h"

Player_Ani::Player_Ani()
	: Animation()
{
	CreateAction(L"Resource/Player/PlayerIdle.png", "Resource/Player/PlayerIdle.xml", "Idle", Vector2(10.0f, 10.0f), Action::LOOP, 0.2f);
	CreateAction(L"Resource/Player/PlayerRun.png", "Resource/Player/PlayerRun.xml", "Run", Vector2(10.0f, 10.0f));
	CreateAction(L"Resource/Player/PlayerJump.png", "Jump", Vector2(10.0f, 10.0f));

	_transform->SetScale(Vector2(5.0f, 5.0f));
	_transform->SetPosition(Vector2(0.0f, 10.0f));

	SetRight();
}

Player_Ani::~Player_Ani()
{
}

void Player_Ani::Update()
{
	StateControl();
	Animation::Update();
}

void Player_Ani::Render()
{
	Animation::Render();
}

void Player_Ani::StateControl()
{
	if (KEY_PRESS('W') || KEY_PRESS(VK_SPACE))
	{
		SetState(JUMP);
	}

	if (!_isGround)
		return;

	if (KEY_UP('A'))
	{
		SetState(IDLE);
	}
	if (KEY_PRESS('A'))
	{
		SetState(RUN);
		_isRight = false;
		SetLeft();
	}

	if (KEY_UP('D'))
	{
		SetState(IDLE);
	}
	if (KEY_PRESS('D'))
	{
		SetState(RUN);
		_isRight = true;
		SetRight();
	}
}
