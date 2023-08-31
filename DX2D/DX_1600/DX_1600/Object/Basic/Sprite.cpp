#include "framework.h"
#include "Sprite.h"

using namespace tinyxml2;

Sprite::Sprite(wstring path, string xmlPath, Vector2 size)
	: _maxFrame(nullptr), Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionPS.hlsl");

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _srv.lock()->GetImageSize();

	CreateClips(path, xmlPath);
}

Sprite::Sprite(wstring path, Vector2 size)
	:_maxFrame(nullptr), Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionPS.hlsl");

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _srv.lock()->GetImageSize();
}

Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
	: _maxFrame(nullptr), Quad(path, size)
{
	_maxFrame = make_shared<Vector2>(maxFrame);

	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionPS.hlsl");

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _srv.lock()->GetImageSize();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	_actionBuffer->Update();
}

void Sprite::Render()
{
	_actionBuffer->SetPsBuffer(0);
	Quad::Render();
}

void Sprite::SetCurClip(Vector2 frame)
{
	if (_maxFrame == nullptr)
		return;

	Vector2 size;
	size.x = _actionBuffer->_data.imageSize.x / (*_maxFrame).x;
	size.y = _actionBuffer->_data.imageSize.y / (*_maxFrame).y;
	_actionBuffer->_data.startPos.x = frame.x * size.x;
	_actionBuffer->_data.startPos.y = frame.y * size.y;
	_actionBuffer->_data.size = size;
}

void Sprite::SetCurClip(Action::Clip clip)
{
	_actionBuffer->_data.startPos = clip._startPos;
	_actionBuffer->_data.size = clip._size;
}

void Sprite::SetCurClip(UINT index)
{
	if (index >= _clips.size())
		return;

	_actionBuffer->_data.startPos = _clips[index]._startPos;
	_actionBuffer->_data.size = _clips[index]._size;
}

void Sprite::CreateClips(wstring srvPath, string xmlPath)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	XMLElement* texturAtlas = document->FirstChildElement();
	XMLElement* row = texturAtlas->FirstChildElement();

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		_clips.push_back(clip);

		row = row->NextSiblingElement();
	}
}
