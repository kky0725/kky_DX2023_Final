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
	vector<shared_ptr<Transform>> _baseTransform;
	shared_ptr<Transform> _dashCountTransform;

	shared_ptr<Quad> _baseLeft;
	shared_ptr<Quad> _baseMiddle;
	shared_ptr<Quad> _dashCount;

	int _maxCount = 2;
	int _curCount = 2;
};