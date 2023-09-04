#include "framework.h"
#include "TestScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Monster/Bat.h"
#include "../Object/Monster/GaintBat.h"
#include "../Object/Monster/Skel.h"
#include "../Object/Monster/Boss/SkelBoss.h"

TestScene::TestScene()
{
	_player = make_shared<Player>();
	
	_ground = make_shared<RectCollider>(Vector2(1280, 50));
	_ground->GetTransform()->SetPosition(Vector2(0.0f, -250.0f));

	_ground2 = make_shared<RectCollider>(Vector2(1280, 50));
	_ground2->GetTransform()->SetPosition(Vector2(640.0f, -50.0f));

	shared_ptr<Creature> skelBoss = make_shared<SkelBoss>();
	shared_ptr<Creature> gaintBat = make_shared<GaintBat>(false);
	//shared_ptr<Creature> bat = make_shared<Bat>(true);
	//shared_ptr<Creature> skel = make_shared<Skel>(false);
	//shared_ptr<Creature> skel2 = make_shared<Skel>(true);

	_creatures.push_back(skelBoss);
	_creatures.push_back(gaintBat);
	//_creatures.push_back(bat);
	//_creatures.push_back(skel);
	//_creatures.push_back(skel2);

}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	if (_player->End()) // 여기서 삭제하고 각 크리쳐 별로 공격 부분에 넣어줄지 고민중
		return;

	CheckAttack();

	for (auto creature : _creatures)
	{
		creature->Update();
		_ground->Block(creature->GetCollider());
	}
	_player->Update();

	_ground->Update();

	if (_ground->Block(_player->GetFootHold()))
		_player->IsGround();
	
	_ground2->Update();
	if (_ground2->Block(_player->GetFootHold()))
		_player->IsGround();

}

void TestScene::Render()
{
	for (auto creature : _creatures)
		creature->Render();
	_player->Render();

	_ground->Render();
	_ground2->Render();

}

void TestScene::PostRender()
{
	ImGui::Text("W_M.x : %f, W_M.y : %f", W_MOUSE_POS.x, W_MOUSE_POS.y);

	ImGui::Text("PlayerHp : %d", _player->GetHp());
	ImGui::Text("BossHp : %d", _creatures[0]->GetHp());

	_player->PostRender();
}

void TestScene::CheckAttack()
{
	for (auto creature : _creatures)
		creature->Damaged(_player->CheckAttack(creature->GetCollider()));

	for (auto creature : _creatures)
		_player->Damaged(creature->CheckAttack(_player->GetCollider()));
		
}
