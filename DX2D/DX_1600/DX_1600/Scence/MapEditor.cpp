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
			tileMap->Update();
	}

	for (vector<shared_ptr<TileMap>> tileMapY : _tileMaps)
	{
		for (shared_ptr<TileMap> tileMap : tileMapY)
		{
			if (tileMap->GetCollider()->IsCollision(W_MOUSE_POS) && KEY_PRESS(VK_LBUTTON))
				tileMap->Set(_objectType, _type);
		}
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
		if (ImGui::Button("BASIC", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::BACKGROUND, TileMap::BackGroundImage::BASIC);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Ground"))
	{
		if (ImGui::Button("DELETE_GROUND", { 50.0f,50.0f }))
			SetCurType(TileMap::ObjectType::GROUND, TileMap::GroundImage::NOGROUND);
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
			int i = 1;
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Load"))
	{
		ImGui::Button("1-1", { 50.0f,50.0f });
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

