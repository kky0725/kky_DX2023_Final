#include "framework.h"
#include "Player.h"


Player::Player(wstring string, Vector2 size, float radius)
	:Creature(string, size, radius)
{
}

Player::Player(wstring string, float radius)
	: Creature(string, radius)

{
}

Player::~Player()
{
}

void Player::Update()
{
	Creature::Update();
}

void Player::Render()
{
	Creature::Render();
}
