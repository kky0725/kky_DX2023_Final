#pragma once
class Player_Ani : public Animation
{
public:
	Player_Ani();
	virtual ~Player_Ani();

	virtual void Render() override;
	virtual void Update() override;

	void StateControl();

private:
};

