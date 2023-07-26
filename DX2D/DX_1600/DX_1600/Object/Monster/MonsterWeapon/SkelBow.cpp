#include "framework.h"
#include "SkelBow.h"

SkelBow::SkelBow()
	: Weapon(Vector2(10.0f,10.0f))
{
	_ani = make_shared<Animation>();
	_ani->CreateAction(L"Resource/Monster/SkelBow.png", "Resource/Monster/SkelBow.xml", "BOW", Vector2(10.0f, 10.0f), Action::Type::END);
}

SkelBow::~SkelBow()
{
}

void SkelBow::Update()
{
	_ani->Update();
	Weapon::Update();
}

void SkelBow::Render()
{
	_ani->Render();
	Weapon::Render();
}
