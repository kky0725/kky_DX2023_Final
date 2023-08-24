#pragma once
class SkelSword : public Weapon//Sword 상속으로 수정예정
{
public:
	SkelSword();
	virtual ~SkelSword();

	virtual void Update() override;
	virtual void Render() override;

private:

};

