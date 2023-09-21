#include "framework.h"
#include "Portal.h"

Portal::Portal(PortalDir type)
	:_type(type)
{
	_ani = make_shared<Animation>();

	_ani->CreateAction(L"Resource/Portal/portalIdle.png", "Resource/Portal/portalIdle.xml", "idle", Vector2(80.0f, 40.0f), Action::Type::LOOP, 0.2f);
	_ani->CreateAction(L"Resource/Portal/portalStart.png", "Resource/Portal/portalStart.xml", "start", Vector2(80.0f, 40.0f), Action::Type::END, 0.2f, std::bind(&Portal::SetIdle, this));
	_ani->CreateAction(L"Resource/Portal/portalEnd.png", "Resource/Portal/portalEnd.xml", "end", Vector2(80.0f, 40.0f), Action::Type::END, 0.2f, std::bind(&Portal::OnActive, this));

	switch (_type)
	{
	case Portal::UP:
	case Portal::DOWN:
;		_col = make_shared<RectCollider>(Vector2(80.0f, 40.0f));
		break;
	case Portal::RIGHT:
		_col = make_shared<RectCollider>(Vector2(40.0f, 80.0f));
		_ani->GetTransform()->SetAngel(PI/2);
		break;
	case Portal::LEFT:
		_col = make_shared<RectCollider>(Vector2(40.0f, 80.0f));
		_ani->GetTransform()->SetAngel(-PI/2);
		break;
	default:
		break;
	}

	_ani->SetParent(_col->GetTransform());

	_col->SetPosition(Vector2(-10000.0f, -10000.0f));

}

Portal::~Portal()
{
}

void Portal::Update()
{
	_ani->Update();
	_col->Update();
}

void Portal::Render()
{
	if(!_isOpen)
		_ani->Render();
	_col->Render();
}

void Portal::ClearScene()
{
	_ani->SetState((Animation::State)2);
}

void Portal::SetIdle()
{
	_ani->SetStateIdle();
}

void Portal::OnActive()
{
	_isActive = true;
	_isOpen = true;
}

void Portal::OffActive()
{
	_isActive = false;
	_isOpen = false;
	_ani->SetState((Animation::State)1);
}

void Portal::Collison(shared_ptr<Collider> col, int& curIndex_x, int& curIndex_y)
{

	if(_col->IsCollision(col))
	{
		if (!_isActive)
			return;

		switch (_type)
		{
		case Portal::UP:
		{
			curIndex_y += 1;
			break;
		}
		case Portal::DOWN:
		{
			curIndex_y -= 1;
			break;
		}
		case Portal::RIGHT:
		{
			curIndex_x += 1;
			break;
		}
		case Portal::LEFT:
		{
			curIndex_x -= 1;
			break;
		}
		default:
			break;
		}
	}
}

void Portal::Block(shared_ptr<Collider> col)
{
	if (_isActive)
		return;

	_col->Block(col);
}
