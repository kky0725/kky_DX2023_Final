#include "framework.h"
#include "HpBar.h"

HpBar::HpBar(Vector2 size)
	:_size(size)
{
	_baseTransform = make_shared<Transform>();
	_lifeTransform = make_shared<Transform>();
	_base = nullptr;
	_back = make_shared<Quad>(L"Resource/UI/BossLifeBack.png");
	_life = make_shared<Quad>(L"Resource/UI/LifeBar.png", size);
	_life->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_intBuffer = make_shared<IntBuffer>();

	_baseTransform->SetPosition(Vector2(0.0f, -10.0f));
	_lifeTransform->SetPosition(Vector2(0.0f, 0.0f));

	_baseTransform->SetScale(Vector2(2.0f, 2.0f));

	_lifeTransform->SetParent(_baseTransform);
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
	_baseTransform->Update();
	_lifeTransform->Update();
		_intBuffer->Update();
}

void HpBar::PostRender()
{
	if (_maxHP == _curHP)
		return;

	_intBuffer->SetPsBuffer(0);
	_baseTransform->SetBuffer(0);
	_back->Render();

	_lifeTransform->SetBuffer(0);
	_life->Render();
}
