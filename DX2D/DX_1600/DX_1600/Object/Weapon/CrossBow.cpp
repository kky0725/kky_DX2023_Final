#include "framework.h"
#include "CrossBow.h"
#include "CrossBowArrow.h"

CrossBow::CrossBow()
	:Weapon()
{
	_ani = make_shared<Animation>();
	_ani->CreateAction(L"Resource/Weapon/CrossBow.png", "Resource/Weapon/CrossBow.xml", "Bow", Vector2(14, 11), Action::Type::END, 0.2f, std::bind(&CrossBow::Fire, this));
	_ani->Reset();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<CrossBowArrow>();
		_bullets.push_back(bullet);
	}

	_ani->SetParent(_collider->GetTransform());
	_ani->SetScale(Vector2(2.0f, 2.0f));
	_ani->SetAngle(PI);
	
	_maxAtk = 13;
	_minAtk = 11;
	_atkPerSec = 2.38f;
}

CrossBow::~CrossBow()
{
}

void CrossBow::Update()
{

	if (!_isActive)
		return;
	_ani->Update();
	_collider->Update();
	BulletUpdate();
}

void CrossBow::Render()
{

	if (!_isActive)
		return;
	_ani->Render();
	BulletRender();
}

void CrossBow::BulletUpdate()
{
	for (auto bullet : _bullets)
		bullet->Update();
}

void CrossBow::BulletRender()
{
	for (auto bullet : _bullets)
		bullet->Render();
}

void CrossBow::Attack(Vector2 dir)
{
	_ani->Play();
	_direction = dir.NormalVector2();
}

void CrossBow::Fire()
{
	_ani->Reset();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Bullet>& obj)-> bool {return !obj->IsActive(); });

	if (bulletIter == _bullets.end())
		return;

	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();

	dynamic_pointer_cast<CrossBowArrow>(*bulletIter)->Shoot(startPos, _direction);
}

int CrossBow::CheckAttack(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (!bullet->IsActive())
			continue;
		if (col->IsCollision(bullet->GetCollider()))
		{
			bullet->SetActive(false);
			return GetAtk();
		}
	}
	return 0;
}
