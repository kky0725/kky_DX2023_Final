#include "framework.h"
#include "TestScene.h"

#include "../Object/Player/Player.h"

TestScene::TestScene()
{
	_player = make_shared<Player>(L"Resource/Player/Player.png", 50.0f);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();
}

void TestScene::Render()
{
	_player->Render();
}

void TestScene::PostRender()
{
}
