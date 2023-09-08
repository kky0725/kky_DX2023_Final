#pragma once
class Portal
{
public:
	enum PortalDir
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	Portal(PortalDir type);
	~Portal();

	void Update();
	void Render();

	void ClearScene();
	void SetIdle();

	void OnActive();
	void OffActive();
	void Collison(shared_ptr<Collider> col, int& curIndex_x, int& curIndex_y);

	void SetPosition(Vector2 pos) {	_col->SetPosition(pos);	}
	Vector2 GetPos() { return _col->GetPos(); }

private:
	//shared_ptr<Transform> _transform;
	shared_ptr<Animation> _ani;
	shared_ptr<Collider> _col;

	enum PortalDir _type;

	bool _isActive = false;
	bool _isOpen = false;
};