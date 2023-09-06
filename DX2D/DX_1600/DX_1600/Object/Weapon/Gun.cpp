#include "framework.h"
#include "Gun.h"
#include "CrossBowArrow.h"

Gun::Gun(ItemType type, string name, int price, string itemDesc, wstring iconSrvFile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring srvFile, string xmlFile)
	:Weapon(type, name, price, itemDesc, iconSrvFile, ID, minAtk, maxAtk, atkPerSec)
{
	_ani = make_shared<Animation>();
	//_ani->CreateAction(L"Resource/Weapon/CrossBow.png", "Resource/Weapon/CrossBow.xml", "Bow", Vector2(14, 11), Action::Type::END, 0.2f, std::bind(&Gun::Fire, this));
	_ani->CreateAction(srvFile, xmlFile, "Bow", Vector2(14, 11), Action::Type::END, 0.2f, std::bind(&Gun::Fire, this));
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

Gun::~Gun()
{
}

void Gun::Update()
{

	if (!_isActive)
		return;
	_ani->Update();
	_collider->Update();
	BulletUpdate();
}

void Gun::Render()
{

	if (!_isActive)
		return;
	_ani->Render();
	BulletRender();
}

void Gun::BulletUpdate()
{
	for (auto bullet : _bullets)
		bullet->Update();
}

void Gun::BulletRender()
{
	for (auto bullet : _bullets)
		bullet->Render();
}

void Gun::DeleteBullet()
{
	for (auto bullet : _bullets)
		bullet->SetActive(false);
}

void Gun::Attack(Vector2 dir)
{
	_ani->Play();
	_direction = dir.NormalVector2();
}

void Gun::Fire()
{
	_ani->Reset();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Bullet>& obj)-> bool {return !obj->IsActive(); });

	if (bulletIter == _bullets.end())
		return;

	Vector2 startPos = _collider->GetTransform()->GetWorldPosition();

	dynamic_pointer_cast<CrossBowArrow>(*bulletIter)->Shoot(startPos, _direction);
}

int Gun::CheckAttack(shared_ptr<Collider> col)
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
