#pragma once

class Sword : public Weapon
{
public:
	Sword(ItemType type, string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring string, Vector2 size);
	virtual ~Sword();
	
	virtual void Update() override;
	virtual void Render() override;


private:
};

