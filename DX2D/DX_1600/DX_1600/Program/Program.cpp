#include "framework.h"
#include "Program.h"

Program::Program()
{
	srand((unsigned int)time(nullptr));

	Timer::GetInstance()->SetLockFPS(60.0);
}

Program::~Program()
{
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	Sound::GetInstance()->Update();
	CAMERA->Update();

	SCENE->Update();

	EffectManager::GetInstance()->Update();

	if (KEY_DOWN(VK_F1))
	{
		Collider::_isDebug = !Collider::_isDebug;
	}
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CAMERA->SetCameraBuffer();
	CAMERA->SetProjectionBuffer();

	Font::GetInstance()->GetDC()->BeginDraw();

	ALPHA->SetState();

	SCENE->Render();
	EffectManager::GetInstance()->Render();

	//ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());

	CAMERA->SetUICameraBuffer();
	CAMERA->PostRender();
	SCENE->PostRender();

	Font::GetInstance()->GetDC()->EndDraw();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
