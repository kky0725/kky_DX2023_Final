#include "framework.h"
#include "SkelBow.h"

#include "SkelBullet.h"

SkelBow::SkelBow()
	: Weapon(Item::ItemType::WEAPON, "해골활", 0, "해골 궁수가 사용하는 활", L"Resource/Monster/SkelBow.png", 100, 5, 6, 2.0f)//생성자 Weapon말고 Gun으로 수정예정
{
	_ani = make_shared<Animation>();
	_ani->CreateAction(L"Resource/Monster/SkelBow.png", "Resource/Monster/SkelBow.xml", "BOW", Vector2(10.0f, 10.0f), Action::Type::END, 0.2f, std::bind(&SkelBow::Fire, this));
	_ani->SetScale(Vector2(2.0f, 2.0f));

	for (int i = 0; i < 20; i++)
	{
		shared_ptr<SkelBullet> bullet = make_shared<SkelBullet>();
		_bullets.push_back(bullet);
	}

	_ani->SetParent(_collider->GetTransform());
}

SkelBow::~SkelBow()
{
}

void SkelBow::Update()
{
	_ani->Update();
	Weapon::Update();
	for (auto& bullet : _bullets)
		bullet->Update();
}

void SkelBow::Render()
{
	_ani->Render();
	Weapon::Render();
	for (auto& bullet : _bullets)
		bullet->Render();
}

void SkelBow::Attack(Vector2 dir)
{
	_ani->Play();
	_direction = dir.NormalVector2();
}

void SkelBow::Fire()
{
	_ani->Reset();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<SkelBullet>& obj)-> bool {return !obj->IsActive(); });

	if (bulletIter == _bullets.end())
		return;

	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(startPos, _direction);
}

int SkelBow::CheckAttack(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (!bullet->IsActive())
			continue;
		if (col->IsCollision(bullet->GetCollider()))
		{
			bullet->SetActive(false);
			return _atk;
		}
	}
	return 0;
}
