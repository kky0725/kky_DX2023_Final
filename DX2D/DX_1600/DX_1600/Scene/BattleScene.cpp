#include "framework.h"
#include "BattleScene.h"

#include "../Object/Player/Player.h"
#include "../Object/Monster/Bat.h"
#include "../Object/Monster/GaintBat.h"
#include "../Object/Monster/Skel.h"
#include "../Object/Monster/Boss/SkelBoss.h"

BattleScene::BattleScene()
{
	for (int i = 0; i < _poolCountX; i++)
	{
		vector<shared_ptr<TileMap>> tileMapY;
		for (int j = 0; j < _poolCountY; j++)
		{
			shared_ptr<TileMap> tileMap = make_shared<TileMap>(40.0f, Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
			tileMap->GetCollider()->GetTransform()->SetPosition(Vector2(i * 40.0f - 60.0f, j * 40.0f - 60.0f));
			tileMapY.push_back(tileMap);
		}
		_tileMaps.push_back(tileMapY);
	}

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

	_player->Update();

	Block();
	CheckAttack();
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

	_player->Render();
}

void BattleScene::PostRender()
{
	if (ImGui::Button("1-1", { 50.0f,50.0f }))
	{
		_player = make_shared<Player>();
		Init(L"1 - 1.map");
	}
}

void BattleScene::Block()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			if (tileMap->GetTileCollider())
			{
				if (tileMap->GetTileCollider()->Block(_player->GetFootHold()))
					_player->IsGround();

				for (auto creature : _creatures)
				{
					tileMap->GetTileCollider()->Block(creature->GetCollider());
				}
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
	wstring filePath = L"MapInfo/" + file;
	BinaryReader reader = BinaryReader(filePath);

	for (int i = 0; i < _poolCountX; i++)
	{
		for (int j = 0; j < _poolCountY; j++)
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
}

void BattleScene::End()
{
}

