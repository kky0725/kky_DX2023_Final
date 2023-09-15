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
	shared_ptr<NumFont> _maxHpFont;
	shared_ptr<NumFont> _curHpFont;

	shared_ptr<Quad> _slice;
	shared_ptr<Transform> _sliceTransform;

	Vector2 _fontSize = Vector2(10.0f, 10.0f);
};