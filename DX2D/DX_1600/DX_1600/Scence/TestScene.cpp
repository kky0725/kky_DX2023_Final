#include "framework.h"
#include "TestScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Monster/Bat.h"
#include "../Object/Monster/GaintBat.h"

TestScene::TestScene()
{
	_player = make_shared<Player>();
	
	_ground = make_shared<RectCollider>(Vector2(1280, 50));
	_ground->GetTransform()->SetPosition(Vector2(0.0f, -250.0f));

	_gaintBat = make_shared<GaintBat>(true);
	_bat = make_shared<Bat>(true);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	CheckAttack();

	_bat->Update();
	_gaintBat->Update();
	_player->Update();

	_ground->Update();

	if (_ground->Block(_player->GetCollider()))
		_player->IsGround();
}

void TestScene::Render()
{
	_bat->Render();
	_gaintBat->Render();
	_player->Render();

	_ground->Render();
}

void TestScene::PostRender()
{
	ImGui::Text("W_M.x : %f, W_M.y : %f", W_MOUSE_POS.x, W_MOUSE_POS.y);

	ImGui::Text("BatHp : %d", _bat->GetHp());
	ImGui::Text("GBatHp : %d", _gaintBat->GetHp());
}

void TestScene::CheckAttack()
{
	int damage = _player->IsCollisionEnemy(_bat->GetCollider());
	_bat->Damaged(damage);
	dynamic_pointer_cast<GaintBat>(_gaintBat)->TargetOn(_player->GetTransform()->GetWorldPosition());
}
