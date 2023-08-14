#include "framework.h"
#include "CrossBowArrow.h"

CrossBowArrow::CrossBowArrow()
	:Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Weapon/CrossBowArrow.png");
	_transform = make_shared<Transform>();
	
	_transform->SetScale(Vector2(3.0f, 3.0f));
	_transform->SetPosition(Vector2(0.0f, -20.0f));

	_transform->SetParent(_collider->GetTransform());

	_lifeTime = 15.0f;
}

CrossBowArrow::~CrossBowArrow()
{
}

void CrossBowArrow::Update()
{
	if (!_isActive)
		return;
	_collider->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);
	_collider->Update();
	_transform->Update();
}

void CrossBowArrow::Render()
{
	if (!_isActive)
		return;
	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}

