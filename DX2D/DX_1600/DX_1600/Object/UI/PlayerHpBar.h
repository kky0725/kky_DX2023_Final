#pragma once
class PlayerHpBar : public HpBar
{
public:
	PlayerHpBar();
	virtual ~PlayerHpBar();

	virtual void Update();
	virtual void PostRender();

private:

};