#pragma once
#include "Weapon.h"

class ShortSword : public Weapon
{
public:
	ShortSword();
	virtual ~ShortSword();
	
	virtual void Update() override;
	virtual void Render() override;

	bool IsAtcive() { return _isActive; }
	void SetIsActive(bool value) { _isActive = value; }

private:
	bool _isActive = false;
};

