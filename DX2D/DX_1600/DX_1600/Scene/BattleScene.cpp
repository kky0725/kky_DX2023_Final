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

	_quad = make_shared<Quad>(L"Resource/UI/Screen.png");
	_transform = make_shared<Transform>();
	_transform->SetScale(Vector2(100.0f, 100.0f));
	_floatBuffer = make_shared<FloatBuffer>();
	_quad->SetPS(ADD_PS(L"Shader/ScreenPS.hlsl"));
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	if (_loading)
	{
		Loading();
		return;
	}

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
	ReturnHome();
}

void BattleScene::Render()
{
	if (_loading)
	{
		_floatBuffer->SetPsBuffer(0);
		_transform->SetBuffer(0);
		_quad->Render();
	}

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
				if (creature->IsAtcive())
					tileMap->Block(creature->GetCollider());
				else
				{
					for (auto coin : creature->GetCoins())
					{
						if (!coin->IsActive())
							continue;
						tileMap->Block(coin->GetCollider());
					}
				}

			}
		}
	}

	for (auto creature : _creatures)
	{
		if (creature->IsAtcive())
			continue;

		for (auto coin : creature->GetCoins())
		{
			if (coin->IsCollison(_player->GetCollider()))
				Inventory::GetInstance()->GetCoin();
		}
	}

	for (auto portal : _portals)
	{
		portal->Block(_player->GetFootHold());

		for (auto creature : _creatures)
		{
			if (!creature->IsAtcive())
				continue;

			portal->Block(creature->GetCollider());
		}
	}
}

void BattleScene::CheckAttack()
{
	for (auto creature : _creatures)
	{
		if (creature->IsAtcive() && _player->IsAtcive())
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
	CAMERA->SetLeftBottom(Vector2(-CORRECTION_VALUE_WIDTH -20.0f, -CORRECTION_VALUE_HEIGHT -20.0f));
	CAMERA->SetRightTop(Vector2(MAP_SIZE_X * 40.0f -CORRECTION_VALUE_WIDTH - 20.0f, MAP_SIZE_Y * 40.0f -CORRECTION_VALUE_HEIGHT -20.0f));

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
			_player->SetPosition(Vector2(120.0f -CORRECTION_VALUE_WIDTH, 120.0f - CORRECTION_VALUE_HEIGHT));
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

void BattleScene::InitBoss()
{
	End();

	CAMERA->SetTarget(_player->GetTransform());

	_player->UpdateWeapon();

	wstring filePath = L"MapInfo/4 - 1.map";
	BinaryReader reader = BinaryReader(filePath);

	for (int i = 0; i < 4; i++)
	{
		Vector2 pos;
		pos.x = reader.Float();
		pos.y = reader.Float();

		_portals[i]->SetPosition(pos);
		if (!_cleared[_curIndex_x - 1][_curIndex_y - 1])
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
		}
	}

	shared_ptr<Creature> creature = make_shared<SkelBoss>();
	_creatures.push_back(creature);

	_player->RestJump();

	if (_curIndex_x == _oldIndex_x && _curIndex_y == _oldIndex_y)
	{
		if (_curIndex_x == 1 && _curIndex_y == 1)
			_player->SetPosition(Vector2(0.0f, 0.0f));
		return;
	}

	if (_curIndex_x - _oldIndex_x == 1)
		_player->SetPosition(_portals[Portal::PortalDir::LEFT]->GetPos() + Vector2(80.0f, 0.0f));
	else if (_curIndex_x - _oldIndex_x == -1)
		_player->SetPosition(_portals[Portal::PortalDir::RIGHT]->GetPos() + Vector2(-80.0f, 0.0f));
	else if (_curIndex_y - _oldIndex_y == 1)
		_player->SetPosition(_portals[Portal::PortalDir::DOWN]->GetPos() + Vector2(0.0f, 80.0f));
	else if (_curIndex_y - _oldIndex_y == -1)
		_player->SetPosition(_portals[Portal::PortalDir::UP]->GetPos() + Vector2(0.0f, -80.0f));

}

void BattleScene::End()
{
	_creatures.resize(0);
	_player->DeleteBullet();
	//_loading = true;
}

void BattleScene::Rest()
{
	for (int i = 0; i < 4; i++)
	{
		vector<bool> clearedY;
		for (int j = 0; j < 4; j++)
		{
			_cleared[i][j] = false;
		}
	}

	_curIndex_x = 1;
	_curIndex_y = 1;
	_oldIndex_x = 1;
	_oldIndex_y = 1;

	_player->Rest();

	Init(L"1 - 1.map");
}

void BattleScene::ChangeScene()
{
	if (_curIndex_y == _oldIndex_y && _curIndex_x == _oldIndex_x)
		return;

	wstring filePath = L"";
	filePath = filePath + to_wstring(_curIndex_x) + L" - " + to_wstring(_curIndex_y) + L".map";

	if (_curIndex_x == 4 && _curIndex_y == 1)
		InitBoss();
	else
		Init(filePath);

	_oldIndex_y = _curIndex_y;
	_oldIndex_x = _curIndex_x;
}

void BattleScene::ClearCheck()
{
	if (_curIndex_x == 4 && _curIndex_y == 1)
		return;
	
	for (auto creature : _creatures)
	{
		if (creature->GetHp() > 0)
			return;
	}

	_cleared[_curIndex_x-1][_curIndex_y-1] = true;
	for (auto portal : _portals)
		portal->ClearScene();
}

void BattleScene::ReturnHome()
{
	if (_curIndex_x == 4 && _curIndex_y == 1)
		if (!_creatures[0]->IsAtcive())
			_time += DELTA_TIME;

	if (_player->GetHp() < 1)
		_time += DELTA_TIME;

	if (_time > 5.0f)
	{
		Rest();
		_time = 0.0f;
	}
}

void BattleScene::Loading()
{
	_time += DELTA_TIME;
	_floatBuffer->_data.value1 = _time;
	_transform->Update();
	if (_time > 5.0f)
	{
		_time = 0.0f;
		_loading = false;
	}

}
