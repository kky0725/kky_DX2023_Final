#include "framework.h"
#include "Tile.h"
#include "../Player/Player.h"

Tile::Tile(TileImage tileImage, Vector2 pos)
{
	_ground = make_shared<Sprite>(Vector2(40.0f,40.0f));//여기 채워야함
	_transform = make_shared<Transform>();

	if(_tileType == TileType::BACKGROUND)
		_collider = nullptr;
	else
	{
		_collider = make_shared<RectCollider>(_colSize);
		_collider->SetParent(_transform);
	}

	_transform->SetPosition(pos);

	_ground->SetCurClip(tileImage);

	SetTileType();
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

bool Tile::Block(shared_ptr<Collider> collider)
{
	if (_tileType == TileType::BACKGROUND)
		return false;
	else if (_tileType == TileType::IMPASSABLE)
		return TileBlock(collider);
	else if (_tileType == TileType::PASSABLE)
		return PassableBlock(collider);
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

void Tile::SetTileType()
{
	_tileType = TileType::IMPASSABLE;
	_tileDir = TileDir::NONE;
}
