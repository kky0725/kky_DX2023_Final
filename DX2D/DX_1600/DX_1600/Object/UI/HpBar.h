#pragma once
class HpBar
{
public:
	HpBar(Vector2 size);
	virtual ~HpBar();

	virtual void Update();
	virtual void PostRender();

	void SetPosition(Vector2 pos) { _baseTransform->SetPosition(pos); }
	void SetMaxHp(int value) { _maxHP = value; _intBuffer->_data.value1 = value;}
	void SetCurHp(int value) { _curHP = value; _intBuffer->_data.value2 = value;}

	void SetParent(shared_ptr<Transform> parent) { _baseTransform->SetParent(parent); }

protected:
	shared_ptr<Transform> _baseTransform;
	shared_ptr<Transform> _lifeTransform;
	shared_ptr<Quad> _base;
	shared_ptr<Quad> _back;
	shared_ptr<Quad> _life;

	shared_ptr<IntBuffer> _intBuffer;

	UINT _maxHP = 100;
	UINT _curHP = 100;

	Vector2 _size = Vector2(1.0f, 1.0f);
};

