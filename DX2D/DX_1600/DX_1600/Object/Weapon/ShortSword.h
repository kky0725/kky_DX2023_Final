#pragma once

class ShortSword : public Weapon
{
public:
	ShortSword();
	virtual ~ShortSword();
	
	virtual void Update() override;
	virtual void Render() override;

private:
};

