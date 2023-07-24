#include "framework.h"
#include "Animation.h"

using namespace tinyxml2;

Animation::Animation()
{
	//CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Idle", Vector2(10.0f, 10.0f));
	//CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Run", Vector2(10.0f, 10.0f));
	//CreateAction(L"Resource/Player/~~.png", "Resource/Player/~~.xml", "Atk", Vector2(10.0f, 10.0f));

	_transform = make_shared<Transform>();
}

Animation::~Animation()
{
}

void Animation::Update()
{
	_transform->Update();

	_actions[_curState]->Update();
	_sprites[_curState]->Update();
}

void Animation::Render()
{
	_transform->SetBuffer(0);

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void Animation::PostRender()
{
}


void Animation::SetState(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Animation::CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, float speed, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	XMLElement* texturAtlas = document->FirstChildElement();
	XMLElement* row = texturAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type, speed);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Animation::CreateAction(wstring srvPath, string actionName, Vector2 size)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);
	Vector2 imageSize = srv->GetImageSize();
	vector<Action::Clip> clips;
	clips.push_back(Action::Clip(0, 0, imageSize.x, imageSize.y, srv));
	shared_ptr<Action> action = make_shared<Action>(clips, actionName, Action::Type::LOOP, 1.0f);
	action->Play();

	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Animation::SetLeft()
{
	for (auto sprite : _sprites)
	{
		//_transform->SetScale(Vector2(-1.0f, 1.0f));
		sprite->SetLeft();
	}
}

void Animation::SetRight()
{
	for (auto sprite : _sprites)
	{
		//_transform->SetScale(Vector2(1.0f,1.0f));
		sprite->SetRight();
	}
}
