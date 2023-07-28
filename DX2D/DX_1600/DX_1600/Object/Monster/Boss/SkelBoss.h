#pragma once
class SkelBoss : public Creature
{
public:
	SkelBoss();
	~SkelBoss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void EndAttack1();

	virtual int CheckAttack(shared_ptr<Collider> col) override;

private:
	shared_ptr<Animation> _body;
	shared_ptr<Animation> _back;
};
