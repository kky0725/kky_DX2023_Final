#include "framework.h"
#include "TestScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Monster/Bat.h"
#include "../Object/Monster/GaintBat.h"
#include "../Object/Monster/Skel.h"

TestScene::TestScene()
{
	_player = make_shared<Player>();
	
	_ground = make_shared<RectCollider>(Vector2(1280, 50));
	_ground->GetTransform()->SetPosition(Vector2(0.0f, -250.0f));

	shared_ptr<Creature> gaintBat = make_shared<GaintBat>(false);
	shared_ptr<Creature> bat = make_shared<Bat>(true);
	shared_ptr<Creature> skel = make_shared<Skel>(false);

	_creatures.push_back(gaintBat);
	_creatures.push_back(bat);
	_creatures.push_back(skel);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	CheckAttack();

	for (auto creature : _creatures)
	{
		creature->Update();
		_ground->Block(creature->GetCollider());
	}
	_player->Update();

	_ground->Update();

	if (_ground->Block(_player->GetCollider()))
		_player->IsGround();

	
}

void TestScene::Render()
{
	for (auto creature : _creatures)
		creature->Render();
	_player->Render();

	_ground->Render();
}

void TestScene::PostRender()
{
	ImGui::Text("W_M.x : %f, W_M.y : %f", W_MOUSE_POS.x, W_MOUSE_POS.y);

	ImGui::Text("PlayerHp : %d", _player->GetHp());
	ImGui::Text("BatHp : %d", _creatures[0]->GetHp());
	ImGui::Text("GBatHp : %d", _creatures[1]->GetHp());
}

void TestScene::CheckAttack()
{
	for (auto creature : _creatures)
		creature->Damaged(_player->CheckAttack(creature->GetCollider()));

	for (auto creature : _creatures)
		_player->Damaged(creature->CheckAttack(_player->GetCollider()));
		
}
