#pragma once
class PlayerHpBar : public HpBar
{
public:
	PlayerHpBar();
	virtual ~PlayerHpBar();

	virtual void Update();
	virtual void PostRender();

	void SetNumber();

private:
	shared_ptr<NumFont> _maxTen;
	shared_ptr<NumFont> _maxOne;
	shared_ptr<NumFont> _curTen;
	shared_ptr<NumFont> _curOne;

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	Vector2 _fontSize = Vector2(10.0f, 10.0f);
};