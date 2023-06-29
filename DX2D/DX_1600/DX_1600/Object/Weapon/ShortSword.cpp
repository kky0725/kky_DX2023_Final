#include "framework.h"
#include "ShortSword.h"

ShortSword::ShortSword(wstring string)
	:Weapon(string)
{
	_maxAtk = 10;
	_minAtk = 8;
	_atkPerSec = 3.03f;
}

ShortSword::~ShortSword()
{
}

void ShortSword::Update()
{
	Weapon::Update();
}

void ShortSword::Render()
{
	Weapon::Render();
}
