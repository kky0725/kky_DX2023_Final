#include "framework.h"
#include "BattleScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Monster/Bat.h"
#include "../Object/Monster/GaintBat.h"
#include "../Object/Monster/Skel.h"
#include "../Object/Monster/Boss/SkelBoss.h"

BattleScene::BattleScene()
{
	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		vector<shared_ptr<TileMap>> tileMapY;
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			shared_ptr<TileMap> tileMap = make_shared<TileMap>(40.0f, Vector2(i * 40.0f - CORRECTION_VALUE_WIDTH, j * 40.0f - CORRECTION_VALUE_HEIGHT));
			tileMapY.push_back(tileMap);
		}
		_tileMaps.push_back(tileMapY);
	}

	_portals.resize(4);

	_portals[Portal::PortalDir::UP] = make_shared<Portal>(Portal::PortalDir::UP);
	_portals[Portal::PortalDir::DOWN] = make_shared<Portal>(Portal::PortalDir::DOWN);
	_portals[Portal::PortalDir::RIGHT] = make_shared<Portal>(Portal::PortalDir::RIGHT);
	_portals[Portal::PortalDir::LEFT] = make_shared<Portal>(Portal::PortalDir::LEFT);

	_player = make_shared<Player>();

	//CAMERA->SetTarget(_player->GetTransform());
	//CAMERA->SetRightTop()
	//CAMERA->SetLeftBottom()

	for (int i = 0; i < 4; i++)
	{
		vector<bool> clearedY;
		for (int j = 0; j < 4; j++)
		{
			bool cleared = false;
			clearedY.push_back(cleared);
		}
		_cleared.push_back(clearedY);
	}

	Init(L"1 - 1.map");
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	for (auto creature : _creatures)
		creature->Update();

	for (auto portal : _portals)
	{
		portal->Update();
		portal->Collison(_player->GetCollider(), _curIndex_x, _curIndex_y);
	}

	_player->Update();

	Block();
	CheckAttack();

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Update();
	}
	ChangeScene();
	ClearCheck();
}

void BattleScene::Render()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Render();
	}

	for (auto creature : _creatures)
		creature->Render();
	for (auto portal : _portals)
		portal->Render();

	_player->Render();
}

void BattleScene::PostRender()
{
	if (ImGui::Button("1-1", { 50.0f,50.0f }))
		Init(L"1 - 1.map");
	if (ImGui::Button("1-2", { 50.0f,50.0f }))
		Init(L"1 - 2.map");

	if (ImGui::Button("1-1 => 1-2", { 50.0f,50.0f }))
	{
		_curIndex_y = 2;
	}
	if (ImGui::Button("1-2 => 1-1", { 50.0f,50.0f }))
	{
		_curIndex_y = 1;
	}

	if (ImGui::Button("End", { 50.0f,50.0f }))
	{
		End();
	}

	ImGui::Text("PlayerHp : %d", _player->GetHp());
	ImGui::Text("PlayerPos : %f, %f", _player->GetPosition().x, _player->GetPosition().y);

	/////////////////////

	for (auto creature : _creatures)
		creature->PostRender();
	_player->PostRender();
}

void BattleScene::Block()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			if (tileMap->Block(_player->GetFootHold(), false))
				_player->IsGround();
			for (auto creature : _creatures)
			{
				tileMap->Block(creature->GetCollider());
			}
		}
	}

	for (auto portal : _portals)
	{
		portal->Block(_player->GetFootHold());

		for (auto creature : _creatures)
		{
			portal->Block(creature->GetCollider());
		}

	}


}

void BattleScene::CheckAttack()
{
	for (auto creature : _creatures)
	{
		if (creature->IsAtcive())
		{
			creature->Damaged(_player->CheckAttack(creature->GetCollider()));
			_player->Damaged(creature->CheckAttack(_player->GetCollider()));
		}
	}
}

void BattleScene::Init(wstring file)
{
	End();

	CAMERA->SetTarget(_player->GetTransform());

	_player->UpdateWeapon();

	wstring filePath = L"MapInfo/" + file;
	BinaryReader reader = BinaryReader(filePath);

	for (int i = 0; i < 4; i++)
	{
		Vector2 pos;
		pos.x = reader.Float();
		pos.y = reader.Float();

		_portals[i]->SetPosition(pos);
		if(!_cleared[_curIndex_x-1][_curIndex_y-1])
			_portals[i]->OffActive();
	}

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			TileMap::TileInfo tileInfo;
			TileMap::TileInfo* ptr = &tileInfo;
			reader.Byte((void**)&ptr, sizeof(TileMap::TileInfo));

			_tileMaps[i][j]->Set(TileMap::ObjectType::BACKGROUND, tileInfo._backGroundImage);
			_tileMaps[i][j]->Set(TileMap::ObjectType::GROUND, tileInfo._groundImage);

			Vector2 pos = Vector2(i * 40.0f - CORRECTION_VALUE_WIDTH, j * 40.0f - CORRECTION_VALUE_HEIGHT);

			if (_cleared[_curIndex_x-1][_curIndex_y-1])
				continue;

			switch (tileInfo._creatureType)
			{
			case TileMap::CreatureType::BAT:
			{
				shared_ptr<Creature> creature = make_shared<Bat>(true);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::REDBAT:
			{
				shared_ptr<Creature> creature = make_shared<Bat>(false);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::GAINTBAT:
			{
				shared_ptr<Creature> creature = make_shared<GaintBat>(true);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::REDGAINTBAT:
			{
				shared_ptr<Creature> creature = make_shared<GaintBat>(false);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::SKELSWORD:
			{
				shared_ptr<Creature> creature = make_shared<Skel>(true);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::SKELBOW:
			{
				shared_ptr<Creature> creature = make_shared<Skel>(false);
				creature->SetPosition(pos);
				_creatures.push_back(creature);
				break;
			}
			default:
				break;
			}
		}
	}

	_player->RestJump();

	if (_curIndex_x == _oldIndex_x && _curIndex_y == _oldIndex_y)
	{
		if (_curIndex_x == 1 && _curIndex_y == 1)
			_player->SetPosition(Vector2(0.0f, 0.0f));
		return;
	}

	if (_curIndex_x - _oldIndex_x == 1)
		_player->SetPosition(_portals[Portal::PortalDir::LEFT]->GetPos() + Vector2(80.0f, 0.0f));
	else if(_curIndex_x - _oldIndex_x == -1)
		_player->SetPosition(_portals[Portal::PortalDir::RIGHT]->GetPos() + Vector2(-80.0f, 0.0f));
	else if(_curIndex_y - _oldIndex_y == 1)
		_player->SetPosition(_portals[Portal::PortalDir::DOWN]->GetPos() + Vector2(0.0f, 80.0f));
	else if(_curIndex_y - _oldIndex_y == -1)
		_player->SetPosition(_portals[Portal::PortalDir::UP]->GetPos() + Vector2(0.0f, -80.0f));

}

void BattleScene::End()
{
	_creatures.resize(0);
	_player->DeleteBullet();
}

void BattleScene::ChangeScene()
{
	if (_curIndex_y == _oldIndex_y)
		return;

	wstring filePath = L"";
	filePath = filePath + to_wstring(_curIndex_x) + L" - " + to_wstring(_curIndex_y) + L".map";

	Init(filePath);

	_oldIndex_y = _curIndex_y;
}

void BattleScene::ClearCheck()
{
	for (auto creature : _creatures)
	{
		if (creature->GetHp() > 0)
			return;
	}

	_cleared[_curIndex_x-1][_curIndex_y-1] = true;
	for (auto portal : _portals)
		portal->ClearScene();
}
