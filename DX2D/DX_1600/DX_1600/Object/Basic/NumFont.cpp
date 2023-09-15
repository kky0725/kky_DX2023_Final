#include "framework.h"
#include "NumFont.h"

NumFont::NumFont(Vector2 size, float spacing)
	:_spacing(spacing)
{
	_sprite = make_shared<Sprite>(L"Resource/UI/NumFont.png", "Resource/UI/NumFont.xml", size);
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		_transforms.push_back(transform);
	}

	_num.resize(4);
}

NumFont::~NumFont()
{
}

void NumFont::Render()
{
	for (int i = 0; i < _length; i++)
	{
		_transforms[i]->SetBuffer(0);
		_sprite->SetCurClip(_num[i]);
		_sprite->Update();
		_sprite->Render();
	}
}

void NumFont::SetNumber(UINT value)
{
	if (value == 0)
	{
		_length = 1;
		_sprite->SetCurClip(0);
		_sprite->Update();
		return;
	}

	_length = to_string(value).length();
	for (int i = 0; i < _length; i++)
	{
		if (value / 10 == 0 && value % 10 == 0)
			continue;
		_num[i] = value % 10;
		value /= 10;
	}
}

void NumFont::SetPosition(Vector2 pos)
{
	for (int i = 0; i < 4; i++)
	{
		_transforms[i]->SetPosition(pos - Vector2(_spacing * i, 0.0f));
		_transforms[i]->Update();
	}
}

