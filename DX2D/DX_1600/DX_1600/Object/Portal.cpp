#include "framework.h"
#include "Portal.h"

Portal::Portal(PortalDir type)
	:_type(type)
{
	_ani = make_shared<Animation>();
	_col = make_shared<RectCollider>(Vector2(40.0f, 80.0f));

	//_ani->CreateAction();

	_ani->SetParent(_col->GetTransform());

	_col->SetPosition(Vector2(-1000.0f, -1000.0f));

	switch (_type)
	{
	case Portal::UP:
		_col->GetTransform()->SetAngel(PI / 2);
		break;
	case Portal::DOWN:
		_col->GetTransform()->SetAngel(-PI / 2);
		break;
	case Portal::RIGHT:
		_col->GetTransform()->SetAngel(0.0f);
		break;
	case Portal::LEFT:
		_col->GetTransform()->SetAngel(PI);
		break;
	default:
		break;
	}
}

Portal::~Portal()
{
}

void Portal::Update()
{
	//_ani->Update();
	_col->Update();
}

void Portal::Render()
{
	//_ani->Render();
	_col->Render();
}

void Portal::OnActive()
{
	_isActive = true;
	//애니메이션 실행
}

void Portal::Collison(shared_ptr<Collider> col, Vector2& curIndex)
{

	if(_col->IsCollision(col))
	{
		if (!_isActive)
			return;

		switch (_type)
		{
		case Portal::UP:
		{
			curIndex.y += 1;
			break;
		}
		case Portal::DOWN:
		{
			curIndex.y -= 1;
			break;
		}
		case Portal::RIGHT:
		{
			curIndex.x += 1;
			break;
		}
		case Portal::LEFT:
		{
			curIndex.x -= 1;
			break;
		}
		default:
			break;
		}
	}
}