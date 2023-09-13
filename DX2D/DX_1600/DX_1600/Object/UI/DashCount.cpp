#include "framework.h"
#include "DashCount.h"

DashCount::DashCount()
{
	for (int i = 0; i < 5;i++)
	{
		shared_ptr<Transform> base = make_shared<Transform>();
		base->SetPosition(Vector2(-600.0f + i * 18.0f, 300.0f));
		base->SetScale(Vector2(2.0f, 2.0f));
		_baseTransform.push_back(base);
	}
	_dashCountTransform = make_shared<Transform>();

	_baseLeft = make_shared<Quad>(L"Resource/UI/DashBase_0.png");
	_baseMiddle = make_shared<Quad>(L"Resource/UI/DashBase.png");
	_dashCount = make_shared<Quad>(L"Resource/UI/DashCount.png");

	for (int i = 0; i < _maxCount; i++)
	{
		_baseTransform[i]->Update();
	}
}

DashCount::~DashCount()
{
}

void DashCount::Update()
{
	for (int i = 0; i < _maxCount; i++)
	{
		_baseTransform[i]->Update();
	}
}

void DashCount::PostRender()
{
	_baseTransform[0]->SetBuffer(0);
	_baseLeft->Render();

	if (_maxCount > 2)
	{
		for (int i = 1; i < _maxCount - 1; i++)
		{
			_baseTransform[i]->SetBuffer(0);
			_baseMiddle->Render();
		}
	}

	_baseTransform[_maxCount - 1]->SetScale(Vector2(-2.0f, 2.0f));
	_baseTransform[_maxCount - 1]->SetBuffer(0);
	_baseLeft->Render();

	for (int i = 0; i < _curCount; i++)
	{
		_baseTransform[i]->SetBuffer(0);
		_dashCount->Render();
	}

}

