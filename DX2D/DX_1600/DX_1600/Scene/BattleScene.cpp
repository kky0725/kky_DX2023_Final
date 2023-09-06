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
			shared_ptr<TileMap> tileMap = make_shared<TileMap>(40.0f, Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
			tileMap->GetCollider()->GetTransform()->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
			tileMapY.push_back(tileMap);
		}
		_tileMaps.push_back(tileMapY);
	}

	_portals.resize(4);

	_portals[Portal::PortalDir::UP] = make_shared<Portal>();
	_portals[Portal::PortalDir::DOWN] = make_shared<Portal>();
	_portals[Portal::PortalDir::RIGHT] = make_shared<Portal>();
	_portals[Portal::PortalDir::LEFT] = make_shared<Portal>();

	_player = make_shared<Player>();
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
		portal->Update();

	_player->Update();

	Block();
	CheckAttack();
	ChangeScene();
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
	{
		_player = make_shared<Player>();
		Init(L"1 - 1.map");
	}

	if (ImGui::Button("End", { 50.0f,50.0f }))
	{
		End();
	}

	ImGui::Text("PlayerHp : %d", _player->GetHp());
	ImGui::Text("PlayerPos : %f, %f", _player->GetPosition().x, _player->GetPosition().y);
}

void BattleScene::Block()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			if (tileMap->Block(_player->GetFootHold()))
				_player->IsGround();
			for (auto creature : _creatures)
			{
				tileMap->Block(creature->GetCollider());
			}
		}
	}
}

void BattleScene::CheckAttack()
{
	for (auto creature : _creatures)
		creature->Damaged(_player->CheckAttack(creature->GetCollider()));

	for (auto creature : _creatures)
		_player->Damaged(creature->CheckAttack(_player->GetCollider()));
}

void BattleScene::Init(wstring file)
{
	End();

	wstring filePath = L"MapInfo/" + file;
	BinaryReader reader = BinaryReader(filePath);

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			TileMap::TileInfo tileInfo;
			TileMap::TileInfo* ptr = &tileInfo;
			reader.Byte((void**)&ptr, sizeof(TileMap::TileInfo));

			_tileMaps[i][j]->Set(TileMap::ObjectType::BACKGROUND, tileInfo._backGroundImage);
			_tileMaps[i][j]->Set(TileMap::ObjectType::GROUND, tileInfo._groundImage);

			switch (tileInfo._creatureType)
			{
			case TileMap::CreatureType::BAT:
			{
				shared_ptr<Creature> creature = make_shared<Bat>(true);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::REDBAT:
			{
				shared_ptr<Creature> creature = make_shared<Bat>(false);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::GAINTBAT:
			{
				shared_ptr<Creature> creature = make_shared<GaintBat>(true);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::REDGAINTBAT:
			{
				shared_ptr<Creature> creature = make_shared<GaintBat>(false);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::SKELSWORD:
			{
				shared_ptr<Creature> creature = make_shared<Skel>(true);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			case TileMap::CreatureType::SKELBOW:
			{
				shared_ptr<Creature> creature = make_shared<Skel>(false);
				creature->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
				_creatures.push_back(creature);
				break;
			}
			default:
				break;
			}
		}
	}

	for (auto portal : _portals)
	{
		Vector2 pos;
		Vector2* ptr = &pos;
		reader.Byte((void**)ptr, sizeof(Vector2));

		portal->SetPosition(pos);
	}

	if (_curIndex == _oldIndex && _curIndex == Vector2(1, 1))
	{
		_player->SetPosition(Vector2(0.0f, 0.0f));
		return;
	}

	if (_curIndex.x - _oldIndex.x == 1)
		_player->SetPosition(_portals[Portal::PortalDir::LEFT]->GetPos() + Vector2(40.0f, 0.0f));
	else if(_curIndex.x - _oldIndex.x == -1)
		_player->SetPosition(_portals[Portal::PortalDir::RIGHT]->GetPos() + Vector2(-40.0f, 0.0f));
	else if(_curIndex.y - _oldIndex.y == 1)
		_player->SetPosition(_portals[Portal::PortalDir::DOWN]->GetPos() + Vector2(0.0f, 40.0f));
	else if(_curIndex.y - _oldIndex.y == -1)
		_player->SetPosition(_portals[Portal::PortalDir::UP]->GetPos() + Vector2(0.0f, -40.0f));

}

void BattleScene::End()
{
	_creatures.resize(0);
	_player->DeleteBullet();
}

void BattleScene::ChangeScene()
{
	if (_curIndex == _oldIndex)
		return;

	_oldIndex = _curIndex;

	wstring filePath = L"MapInfo/";
	filePath = filePath + to_wstring(_curIndex.x) + L"-" + to_wstring(_curIndex.y);

	Init(filePath);
}
