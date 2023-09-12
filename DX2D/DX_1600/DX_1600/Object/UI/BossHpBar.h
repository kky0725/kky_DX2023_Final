#pragma once
class BossHpBar : public HpBar
{
public:
	BossHpBar();
	virtual ~BossHpBar();

	virtual void Update();
	virtual void PostRender();

private:
	shared_ptr<Quad> _portait;
	shared_ptr<Transform> _portaitTransform;
};