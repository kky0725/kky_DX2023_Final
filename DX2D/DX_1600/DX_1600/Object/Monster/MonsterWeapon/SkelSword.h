#pragma once
class SkelSword : public Weapon
{
public:
	SkelSword();
	virtual ~SkelSword();

	virtual void Update() override;
	virtual void Render() override;

private:

};

