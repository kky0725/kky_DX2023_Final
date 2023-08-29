#include "framework.h"
#include "TileMap.h"

#include "../../Object/Monster/Bat.h"
#include "../../Object/Monster/GaintBat.h"
#include "../../Object/Monster/Skel.h"

TileMap::TileMap()
{
	_collider = make_shared<RectCollider>(Vector2(_size, _size));
}

TileMap::TileMap(float size, Vector2 pos)
	:_size(size), _pos(pos)
{
	_collider = make_shared<RectCollider>(Vector2(_size, _size));

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

	if (_ground)
		_ground->Render();

	if (_creature)
		_creature->Render();
}

void TileMap::Set(ObjectType objectType, int type)
{
	switch (objectType)
	{
	case TileMap::BACKGROUND:
	{
		_backGroundType = (BackGroundType)type;
		break;
	}
	case TileMap::GROUND:
	{
		_groundType = (GroundType)type;
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

void TileMap::CreateCreature(CreatureType type)
{
	switch (type)
	{
	case TileMap::NONE:
	{
		_creature = nullptr;
		return;
	}
	case TileMap::BAT:
	{
		_creature = make_shared<Bat>(true);
		break;
	}
	case TileMap::REDBAT:
	{
		_creature = make_shared<Bat>(false);
		break; 
	}
	case TileMap::GAINTBAT:
	{
		_creature = make_shared<GaintBat>(true);
		break;
	}
	case TileMap::REDGAINTBAT:
	{
		_creature = make_shared<GaintBat>(true);
		break;
	}
	default:
		break;
	}
	_creature->SetPosition(_pos);
	_creature->Update();
}

