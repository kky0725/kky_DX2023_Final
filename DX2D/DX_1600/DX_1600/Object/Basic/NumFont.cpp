#include "framework.h"
#include "NumFont.h"

NumFont::NumFont(Vector2 size)
{
	_sprite = make_shared<Sprite>(L"Resource/UI/NumFont.png", "Resource/UI/NumFont.xml", size);
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		_transforms.push_back(transform);
	}
}

NumFont::~NumFont()
{
}

void NumFont::Render()
{

	//_transform->SetBuffer(0);
	_sprite->Render();
}

void NumFont::SetNumber(UINT value)
{
	if (value <= 9)
	{
		_isNumber = true;
		_sprite->SetCurClip(value);
		_transform->Update();
		_sprite->Update();
	}
	else
		_isNumber = false;
}

