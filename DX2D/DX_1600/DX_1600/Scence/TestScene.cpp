#include "framework.h"
#include "TestScene.h"

#include "../Object/Player/Player.h"

TestScene::TestScene()
{
	_player = make_shared<Player>(L"Resource/Player/Player.png", 50.0f);
	
	_ground = make_shared<RectCollider>(Vector2(1280, 50));
	_ground->GetTransform()->SetPosition(Vector2(0.0f, -250.0f));

}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();

	_ground->Update();

	if (_ground->Block(_player->GetCollider()))
		_player->RestJumpCount();
}

void TestScene::Render()
{
	_player->Render();

	_ground->Render();
}

void TestScene::PostRender()
{
}
