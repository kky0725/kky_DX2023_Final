#pragma once
class NumFont
{
public:
	NumFont(Vector2 size);
	~NumFont();

	void Render();

	void SetNumber(UINT value);
	void SetPosition(Vector2 pos);

private:
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Transform>> _transforms;
	vector<int> _num;
	int length = 0;
};