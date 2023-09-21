#include "framework.h"
#include "ShootingCursor.h"

ShootingCursor::ShootingCursor()
{
	_quad = make_shared<Quad>(L"Resource/UI/ShootingCursor2.png");
	_transform = make_shared<Transform>();
	_transform->SetScale(Vector2(3.0f, 3.0f));
	ShowCursor(false);
}

ShootingCursor::~ShootingCursor()
{
}

void ShootingCursor::Update()
{
	_transform->SetPosition(MOUSE_POS - CENTER);
	_transform->Update();
}

void ShootingCursor::PostRender()
{
	_transform->SetBuffer(0);
	_quad->Render();
}
