#pragma once
class SkelBow : public Weapon
{
public:
	SkelBow();
	~SkelBow();

	virtual void Update() override;
	virtual void Render() override;

	void Attack();

private:
	shared_ptr<Animation> _ani;

};
