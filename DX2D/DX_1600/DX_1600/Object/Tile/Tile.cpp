#include "framework.h"
#include "Tile.h"
#include "../Player/Player.h"

Tile::Tile(TileImage tileImage, Vector2 pos)
{
	_ground = make_shared<Sprite>(L"Resource/Ground/tileSprite.png", "Resource/Ground/tileSprite.xml", Vector2(40.0f, 40.0f));
	_transform = make_shared<Transform>();

	if (tileImage <= TileImage::WALL_CHAIN)
		_tileType = TileType::BACKGROUND;
	else if (tileImage <= TileImage::ONE_WAY3)
		_tileType = TileType::PASSABLE;
	else
		_tileType = TileType::IMPASSABLE;

	SetTileDir(tileImage);

	if(_tileType == TileType::BACKGROUND)
		_collider = nullptr;
	else
	{
		_collider = make_shared<RectCollider>(_colSize);
		_collider->SetParent(_transform);
	}

	_transform->SetPosition(pos);

	_ground->SetCurClip(tileImage);

	_ground->Update();
}

Tile::~Tile()
{
}

void Tile::Update()
{
	if (_tileType != TileType::BACKGROUND)
		_collider->Update();

	_transform->Update();
}

void Tile::Render()
{
	_transform->SetBuffer(0);
	_ground->Render();

	if (_tileType != TileType::BACKGROUND)
		_collider->Render();
}

bool Tile::Block(shared_ptr<Collider> collider, bool monster)
{
	if (_tileType == TileType::BACKGROUND)
		return false;
	else if (_tileType == TileType::IMPASSABLE)
		return TileBlock(collider);
	else if (_tileType == TileType::PASSABLE)
	{
		if (monster)
			return TileBlock(collider);//여기 문제 있음
		else
			return PassableBlock(collider);
	}
}

bool Tile::PassableBlock(shared_ptr<Collider> collider)
{
	if (KEY_PRESS('S'))
		return false;

	if (KEY_PRESS('W') || KEY_PRESS(VK_SPACE))
		return false;

	return TileBlock(collider);
}

bool Tile::TileBlock(shared_ptr<Collider> collider)
{
	if (_tileDir == TileDir::NONE)
		return false;

	if (!_collider->IsCollision(collider))
		return false;

	shared_ptr<CircleCollider> moveable = dynamic_pointer_cast<CircleCollider>(collider);

	Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
	Vector2 blockCenter = _collider->GetTransform()->GetWorldPosition();
	Vector2 virtuaHalfSize = Vector2(moveable->GetWorldRadius(), moveable->GetWorldRadius());
	Vector2 sum = dynamic_pointer_cast<RectCollider>(_collider)->GetWorldSize() * 0.5f + virtuaHalfSize;
	Vector2 dir = moveableCenter - blockCenter;
	Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

	Vector2 fixedPos = moveable->GetTransform()->GetPos();

	switch (_tileDir)
	{
	case Tile::NONE:
	{
		break;
	}
	case Tile::WIDTH:
	{
		float scalar = overlap.y;
		if (_tileType != TileType::PASSABLE && dir.y < 0)
		{
			scalar *= -1;
		}

		fixedPos.y += scalar;
		break;
	}
	case Tile::HEIGHT:
	{
		float scalar = overlap.x;
		if (dir.x < 0)
			scalar *= -1;

		fixedPos.x += scalar;
		break;
	}
	case Tile::BOTH:
	{
		if (overlap.x < overlap.y)
		{
			float scalar = overlap.x;
			if (dir.x < 0)
				scalar *= -1;

			fixedPos.x += scalar;
		}
		else
		{
			float scalar = overlap.y;
			if (dir.y < 0)
				scalar *= -1;
			fixedPos.y += scalar;
		}
		break;
	}
	default:
		break;
	}

	moveable->SetPosition(fixedPos);

	return true;
}

void Tile::SetTileDir(TileImage tileImage)
{
	switch (tileImage)
	{
	case Tile::ONE_WAY0: case Tile::ONE_WAY1: case Tile::ONE_WAY2: case Tile::ONE_WAY3:
		_tileDir = TileDir::WIDTH;
		break;
	case Tile::H0:	case Tile::H1:	case Tile::H2:	case Tile::H4: case Tile::H6:
	case Tile::H7:	case Tile::H8:	case Tile::H9:	case Tile::H10:	case Tile::H11:	case Tile::H12:
		_tileDir = TileDir::BOTH;
		break;
	case Tile::H3: case Tile::H5:
		_tileDir = TileDir::HEIGHT;
		break;
	case Tile::H13:	case Tile::H14:	case Tile::H15:
		_tileDir = TileDir::WIDTH;
		break;
	case Tile::STAIR_BOTTOM_LEFT:
		_tileDir = TileDir::WIDTH;
		break;
	case Tile::STAIR_BOTTOM_RIGHT:
		_tileDir = TileDir::WIDTH;
		break;
	case Tile::STAIR_TOP_LEFT:
		_tileDir = TileDir::WIDTH;
		break;
	case Tile::STAIR_TOP_RIGHT:
		_tileDir = TileDir::WIDTH;
		break;
	default:
		_tileDir = TileDir::NONE;
		break;
	}
}
