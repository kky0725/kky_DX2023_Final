#pragma once
class NumFont
{
public:
	NumFont(Vector2 size = Vector2(10.0f, 10.0f), float spacing = 10.0f);
	~NumFont();

	void Render();

	void SetNumber(UINT value);
	void SetPosition(Vector2 pos);

private:
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Transform>> _transforms;
	vector<int> _num;
	float _spacing = 10.0f;
	int _length = 0;
};