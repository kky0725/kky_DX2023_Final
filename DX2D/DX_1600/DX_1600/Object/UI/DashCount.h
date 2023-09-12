#pragma once
class DashCount
{
public:
	DashCount();
	~DashCount();

	void Update();
	void PostRender();

	void SetCount(int max, int cur) { _maxCount = max; _curCount = cur; }

private:
	shared_ptr<Transform> _baseLeft;
	vector<shared_ptr<Transform>> _baseMiddles;
	shared_ptr<Transform> _baseRight;

	shared_ptr<Quad> _baseLeft;
	shared_ptr<Quad> _basMiddle;

	int _maxCount = 2;
	int _curCount = 2;
};