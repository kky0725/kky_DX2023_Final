#include "framework.h"
#include "SkelBossHand.h"

SkelBossHand::SkelBossHand(bool isLeft)
	: _isLeft(isLeft)
{
	_hand = make_shared <Animation>();
	_hand->CreateAction(L"Resource/Monster/SkelBoss/SkelBossLeftHandIdle.png", "Resource/Monster/SkelBoss/SkelBossLeftHandIdle.xml", "Idle", Vector2(150.0f, 150.0f));
	_hand->CreateAction(L"Resource/Monster/SkelBoss/SkelBossLeftHandAttack.png", "Resource/Monster/SkelBoss/SkelBossLeftHandAttack.xml", "Atk", Vector2(150.0f, 150.0f), Action::Type::END, 0.2f);
	
	_head = make_shared <Animation>();
	_head->CreateAction(L"Resource/Monster/SkelBoss/SkelBossLaserHead.png", "Resource/Monster/SkelBoss/SkelBossLaserHead.xml", "Head", Vector2(100.0f, 100.0f), Action::Type::END, 0.2f, std::bind(&SkelBossHand::EndLaser, this));

	_head->SetParent(_hand->GetTransform());


	if (_isLeft)
	{
		_hand->SetRight();
		_head->SetRight();
		_head->SetPosition(Vector2(50.0f, -10.0f));
	}
	else
	{
		_hand->SetLeft();
		_head->SetLeft();
		_head->SetPosition(Vector2(-50.0f, -10.0f));
	}

	for (int i = 0; i < 10; i++)
	{
		shared_ptr<Animation> body = make_shared <Animation>();
		body->CreateAction(L"Resource/Monster/SkelBoss/SkelBossLaserbody.png", "Resource/Monster/SkelBoss/SkelBossLaserbody.xml", "body", _bodySize, Action::Type::END, 0.2f);
		_bodys.push_back(body);
	}

	_collider = make_shared<RectCollider>(Vector2(_bodySize.x * 10.0f, _bodySize.y - 30.0f));
	_collider->SetParent(_hand->GetTransform());

	
	//delete
	_hand->SetState((Animation::State)1);
	_isActive = true;
}

SkelBossHand::~SkelBossHand()
{
}

void SkelBossHand::Update()
{
	_hand->Update();
	if (_isActive)
	{
		_head->Update();
		for (auto body : _bodys)
			body->Update();
		_collider->Update();
	}
}

void SkelBossHand::Render()
{
	_hand->Render();
	if (_isActive)
	{
		_head->Render();
		for (auto body : _bodys)
			body->Render();
		_collider->Render();
	}
}

void SkelBossHand::Shoot()
{
	_isActive = true;
	if (_isLeft)
	{
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = _head->GetWorldPosition() + Vector2(_bodySize.x * i + 90.0f, 0.0f);
			_bodys[i]->SetPosition(startPos);
		}
		_collider->SetPosition(Vector2(_bodySize.x * 5.0f, -10.0f));
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = _head->GetWorldPosition() - Vector2(_bodySize.x * i + 90.0f, 0.0f);
			_bodys[i]->SetPosition(startPos);
		}
		_collider->SetPosition(Vector2(-_bodySize.x * 5.0f, -10.0f));
	}
	
}

void SkelBossHand::EndLaser()
{
	_isActive = false;
}

void SkelBossHand::Attack()
{
	
}

void SkelBossHand::EndAttack()
{
}
