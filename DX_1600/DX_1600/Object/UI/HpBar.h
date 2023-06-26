#pragma once
class HpBar
{
public:
	HpBar(wstring path, Vector2 size);
	~HpBar();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) {_transform->SetPosition(pos); }
	void SetMaxHp(UINT value) { _maxHP = value; _intBuffer->_data.value1 = (int)value; }
	void SetCurHp(UINT value) { _curHP = value; _intBuffer->_data.value2 = (int)value;}

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;

	shared_ptr<IntBuffer> _intBuffer;

	UINT _maxHP = 100;
	UINT _curHP = 100;
};