#include "framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
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
}

MapEditor::~MapEditor()
{
}

void MapEditor::Update()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			if (tileMap->GetCollider()->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_LBUTTON))
				tileMap->Set(_objectType, _type);
		}
	}

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Update();
	}

}

void MapEditor::Render()
{
	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
			tileMap->Render();
	}
}

void MapEditor::PostRender()
{
	Create();
}

void MapEditor::Init()
{

}

void MapEditor::End()
{
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
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H13);//midle //tile 이 한줄 밀린듯
		if (ImGui::Button("MT", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, Tile::TileImage::H14);//left
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

	if (ImGui::BeginMenu("Save"))
	{
		if (ImGui::Button("1-1", { 50.0f,50.0f }))
			Save(L"1 - 1.map");
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Load"))
	{
		if (ImGui::Button("1-1", { 50.0f,50.0f }))
			Load(L"1 - 1.map");
		ImGui::Button("1-2", { 50.0f,50.0f });
		ImGui::Button("1-3", { 50.0f,50.0f });
		ImGui::Button("1-4", { 50.0f,50.0f });
		ImGui::Button("2-1", { 50.0f,50.0f });
		ImGui::Button("2-2", { 50.0f,50.0f });
		ImGui::Button("2-3", { 50.0f,50.0f });
		ImGui::Button("2-4", { 50.0f,50.0f });
		ImGui::EndMenu();
	}
}

void MapEditor::Save(wstring file)
{
	wstring filePath = L"MapInfo/" + file;
	BinaryWriter writer = BinaryWriter(filePath);

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			TileMap::TileInfo tileInfo = tileMap->GetTileInfo();
			writer.Byte(&tileInfo, sizeof(TileMap::TileInfo));
		}
	}
}

void MapEditor::Load(wstring file)
{
	wstring filePath = L"MapInfo/" + file;
	BinaryReader reader = BinaryReader(filePath);

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
}

