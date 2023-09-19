#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
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
}

MapEditor::~MapEditor()
{
}

void MapEditor::Update()
{
	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
		{
			for (shared_ptr<TileMap> tileMap : tileMapY)
			{
				if (tileMap->GetCollider()->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_LBUTTON))
				{
					if (_objectType == TileMap::ObjectType::PORTAL)
					{
						Vector2 pos = tileMap->GetCollider()->GetPos();
						SetPortal(pos);
					}
					else
						tileMap->Set(_objectType, _type);
				}
			}
		}
	}
	

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Update();
	}


	for (auto portal : _portals)
		portal->Update();

}

void MapEditor::Render()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Render();
	}

	for (auto portal : _portals)
		portal->Render();
}

void MapEditor::PostRender()
{
	Create();
}

void MapEditor::Create()
{
	if (ImGui::BeginMenu("BackGround"))
	{
		if (ImGui::Button("LT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC0);
		if (ImGui::Button("MT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC1);
		if (ImGui::Button("RT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC2);
		if (ImGui::Button("LM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC3);
		if (ImGui::Button("MM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC4);
		if (ImGui::Button("RM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC5);
		if (ImGui::Button("LB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC12);
		if (ImGui::Button("MB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC13);
		if (ImGui::Button("RB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC14);
		if (ImGui::Button("BLACK", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC11);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Ground"))
	{
		if (ImGui::Button("DELETE_GROUND", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::NOGROUND);
		if (ImGui::Button("LT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H0);
		if (ImGui::Button("MT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H1);
		if (ImGui::Button("RT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H2);
		if (ImGui::Button("LM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H3);
		if (ImGui::Button("MM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H4);
		if (ImGui::Button("RM", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H5);
		if (ImGui::Button("LB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H6);
		if (ImGui::Button("MB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H7);
		if (ImGui::Button("RB", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H8);
		if (ImGui::Button("LT_CORNER", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H9);
		if (ImGui::Button("RT_CORNER", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H10);
		if (ImGui::Button("LB_CORNER", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H11);
		if (ImGui::Button("RB_CORNER", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H12);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("FootHoldGround"))
	{
		if (ImGui::Button("DELETE_GROUND", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::NOGROUND);
		if (ImGui::Button("ONEWAY_L", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::ONE_WAY0);
		if (ImGui::Button("ONEWAY_M1", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::ONE_WAY1);
		if (ImGui::Button("ONEWAY_M2", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::ONE_WAY2);
		if (ImGui::Button("ONEWAY_R", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::ONE_WAY3);
		if (ImGui::Button("LT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H13);
		if (ImGui::Button("MT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H14);
		if (ImGui::Button("RT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H15);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Creature"))
	{
		if (ImGui::Button("DELETE_CREATURE", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::NONE);
		if (ImGui::Button("BAT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::BAT);
		if (ImGui::Button("REDBAT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::REDBAT);
		if (ImGui::Button("GAINTBAT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::GAINTBAT);
		if (ImGui::Button("GATINREDBAT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::REDGAINTBAT);
		if (ImGui::Button("SEKLSWORD", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::SKELSWORD);
		if (ImGui::Button("SKELBOW", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::CREATURE, TileMap::CreatureType::SKELBOW);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Portal"))
	{
		if (ImGui::Button("Up", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::PORTAL, Portal::PortalDir::UP);
		if (ImGui::Button("Down", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::PORTAL, Portal::PortalDir::DOWN);
		if (ImGui::Button("Right", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::PORTAL, Portal::PortalDir::RIGHT);
		if (ImGui::Button("Left", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::PORTAL, Portal::PortalDir::LEFT);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("DeletePortal"))
	{
		if (ImGui::Button("Up", { 50.0f,50.0f }))
		{
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC4);
			_portals[Portal::PortalDir::UP]->SetPosition(Vector2(-10000.0f, -10000.0f));
		}
		if (ImGui::Button("Down", { 50.0f,50.0f }))
		{
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC4);
			_portals[Portal::PortalDir::DOWN]->SetPosition(Vector2(-10000.0f, -10000.0f));
		}
		if (ImGui::Button("Right", { 50.0f,50.0f }))
		{
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC4);
			_portals[Portal::PortalDir::RIGHT]->SetPosition(Vector2(-10000.0f, -10000.0f));
		}
		if (ImGui::Button("Left", { 50.0f,50.0f }))
		{
			SetCurType(TileMap::ObjectType::BACKGROUND, Tile::TileImage::WALL_BASIC4);
			_portals[Portal::PortalDir::LEFT]->SetPosition(Vector2(-10000.0f, -10000.0f));
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Save"))
	{
		if (ImGui::Button("1-1", { 50.0f,50.0f }))
			Save(L"1 - 1.map");
		if (ImGui::Button("2-1", { 50.0f,50.0f }))
			Save(L"2 - 1.map");
		if (ImGui::Button("3-1", { 50.0f,50.0f }))
			Save(L"3 - 1.map");
		if (ImGui::Button("4-1", { 50.0f,50.0f }))
			Save(L"4 - 1.map");
		if (ImGui::Button("3-2", { 50.0f,50.0f }))
			Save(L"3 - 2.map");
		if (ImGui::Button("TEST", { 50.0f,50.0f }))
			Save(L"test.map");
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Load"))
	{
		if (ImGui::Button("1-1", { 50.0f,50.0f }))
			Load(L"1 - 1.map");
		if (ImGui::Button("2-1", { 50.0f,50.0f }))
			Load(L"2 - 1.map");
		if (ImGui::Button("3-1", { 50.0f,50.0f }))
			Load(L"3 - 1.map");
		if (ImGui::Button("4-1", { 50.0f,50.0f }))
			Load(L"4 - 1.map");
		if (ImGui::Button("3-2", { 50.0f,50.0f }))
			Load(L"3 - 2.map");
		if (ImGui::Button("TEST", { 50.0f,50.0f }))
			Load(L"test.map");
		ImGui::EndMenu();
	}
}

void MapEditor::Save(wstring file)
{
	wstring filePath = L"MapInfo/" + file;
	BinaryWriter writer = BinaryWriter(filePath);


	for (int i = 0; i < 4; i++)
	{
		Vector2 pos = _portals[i]->GetPos();
		writer.Float(pos.x);
		writer.Float(pos.y);
	}

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			TileMap::TileInfo tileInfo = tileMap->GetTileInfo();
			writer.Byte(&tileInfo, sizeof(TileMap::TileInfo));
		}
	}

	//for (auto portal : _portals)
	//{
	//	Vector2 pos = portal->GetPos();
	//	writer.Byte(&pos, sizeof(Vector2));
	//}

}

void MapEditor::Load(wstring file)
{
	wstring filePath = L"MapInfo/" + file;
	BinaryReader reader = BinaryReader(filePath);

	for (int i = 0; i < 4; i++)
	{
		Vector2 pos;
		pos.x = reader.Float();
		pos.y = reader.Float();

		_portals[i]->SetPosition(pos);
	}

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			TileMap::TileInfo tileInfo;
			TileMap::TileInfo* ptr = &tileInfo;
			reader.Byte((void**)&ptr, sizeof(TileMap::TileInfo));

			tileMap->Set(TileMap::ObjectType::BACKGROUND, tileInfo._backGroundImage);
			tileMap->Set(TileMap::ObjectType::GROUND, tileInfo._groundImage);
			tileMap->Set(TileMap::ObjectType::CREATURE, tileInfo._creatureType);
		}
	}

	//for (auto portal : _portals)
	//{
	//	Vector2 pos;
	//	Vector2* ptr = &pos;
	//	reader.Byte((void**)ptr, sizeof(Vector2));

	//	portal->SetPosition(pos);
	//}



}

void MapEditor::SetPortal(Vector2 pos)//ÀÛ¼ºÁß
{
	switch (_type)
	{
	case Portal::UP:
		_portals[Portal::PortalDir::UP]->SetPosition(pos + Vector2(20.0f, 0.0f));
		break;
	case Portal::DOWN:
		_portals[Portal::PortalDir::DOWN]->SetPosition(pos + Vector2(20.0f, 0.0f));
		break;
	case Portal::RIGHT:
		_portals[Portal::PortalDir::RIGHT]->SetPosition(pos + Vector2(0.0f, 20.0f));
		break;
	case Portal::LEFT:
		_portals[Portal::PortalDir::LEFT]->SetPosition(pos + Vector2(0.0f, 20.0f));
		break;
	default:
		break;
	}
}

void MapEditor::Init()
{
	CAMERA->SetTarget(nullptr);
}

