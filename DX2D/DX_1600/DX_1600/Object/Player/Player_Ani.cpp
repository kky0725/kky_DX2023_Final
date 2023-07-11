#include "framework.h"
#include "Player_Ani.h"

Player_Ani::Player_Ani()
	: Animation()
{
	CreateAction(L"Resource/Player/PlayerIdle.png", "Resource/PlayerPlayerIdle.xml", "Idle", Vector2(10.0f, 10.0f));
	CreateAction(L"Resource/PlayerPlayerRun.png", "Resource/Player/PlayerIRun.xml", "Run", Vector2(10.0f, 10.0f));
	//CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Atk", Vector2(10.0f, 10.0f));

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
