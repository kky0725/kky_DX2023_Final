#pragma once
#include "Weapon.h"

class ShortSword : public Weapon
{
public:
	ShortSword(wstring string);
	virtual ~ShortSword();
	
	virtual void Update() override;
	virtual void Render() override;

private:

};

