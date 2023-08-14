#include "framework.h"
#include "CrossBow.h"
#include "CrossBowArrow.h"

CrossBow::CrossBow()
{
	_ani = make_shared<Animation>();
	_ani->CreateAction(L"Resource/Weapon/CrossBow.png", "Resource/Weapon/CrossBow.xml", "Bow", Vector2(14, 11), Action::Type::END);

	for (int i = 0; i < 20; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<CrossBowArrow>();
		_bullets.push_back(bullet);
	}
	
	_maxAtk = 13;
	_minAtk = 11;
	_atkPerSec = 2.38;
}

CrossBow::~CrossBow()
{
}

void CrossBow::Update()
{
	if (!_isActive)
		return;
	_ani->Update();
		
	for (auto bullet : _bullets)
		bullet->Update();
}

void CrossBow::Render()
{
	if (!_isActive)
		return;
	_ani->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}