#include "framework.h"
#include "TileMap.h"

#include "../../Object/Monster/Bat.h"
#include "../../Object/Monster/GaintBat.h"
#include "../../Object/Monster/Skel.h"

TileMap::TileMap()
{
	_collider = make_shared<RectCollider>(Vector2(_size, _size));
	_creatureSprite = make_shared<Sprite>(L"Resource/Monster/Monsters.png", "Resource/Monster/Monsters.xml", Vector2(50.0f, 50.0f));
	_creatureTransform = make_shared<Transform>();
}

TileMap::TileMap(float size, Vector2 pos)
	:_size(size), _pos(pos)
{
	_collider = make_shared<RectCollider>(Vector2(_size, _size));
	_creatureSprite = make_shared<Sprite>(L"Resource/Monster/Monsters.png", "Resource/Monster/Monsters.xml", Vector2(50.0f, 50.0f));
	_creatureTransform = make_shared<Transform>();

	CreateBackGround(Tile::TileImage::WALL_BASIC4);
	_backGround->Update();
}

TileMap::~TileMap()
{
}

void TileMap::Update()
{
	_collider->Update();
}

void TileMap::Render()
{
	_collider->Render();

	if (_backGround)
		_backGround->Render();

	if (_ground && _tileInfo._groundImage != Tile::TileImage::NOGROUND)
		_ground->Render();

	if (_tileInfo._CreatureType != CreatureType::NONE)
	{
		_creatureTransform->SetBuffer(0);
		_creatureSprite->Render();
	}
}

void TileMap::Set(ObjectType objectType, int type)
{
	switch (objectType)
	{
	case TileMap::BACKGROUND:
	{
		CreateBackGround((Tile::TileImage)type);
		_backGround->Update();

		break;
	}
	case TileMap::GROUND:
	{
		CreateGround((Tile::TileImage)type);
		_ground->Update();

		break;
	}
	case TileMap::CREATURE:
	{
		_creatureType = (CreatureType)type;
		CreateCreature(_creatureType);
		break;
	}
	default:
		break;
	}
}

void TileMap::CreateBackGround(Tile::TileImage tileImage)
{
	_tileInfo._backGroundImage = tileImage;
	_backGround = make_shared<Tile>(tileImage, _pos);
}

void TileMap::CreateGround(Tile::TileImage tileImage)
{
	_tileInfo._groundImage = tileImage;
	_ground = make_shared<Tile>(tileImage, _pos);
}

void TileMap::CreateCreature(CreatureType type)
{
	_tileInfo._CreatureType = type;
	if (type != CreatureType::NONE)
	{
		_creatureSprite->SetCurClip(type - 1);
		_creatureTransform->SetScale({ 1.0f, 1.0f });
	}

	if (type == CreatureType::GAINTBAT || type == CreatureType::REDGAINTBAT)
		_creatureTransform->SetScale({2.0f, 2.0f});

	_creatureTransform->SetPosition(_pos);
	_creatureSprite->Update();
	_creatureTransform->Update();
}

