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

	void OnActive();
	void Collison(shared_ptr<Collider> col, Vector2& curIndex);

	void SetPosition(Vector2 pos) {	_col->SetPosition(pos);	}
	Vector2 GetPos() { return _col->GetPos(); }

private:
	//shared_ptr<Transform> _transform;
	shared_ptr<Animation> _ani;
	shared_ptr<Collider> _col;

	enum PortalDir _type;

	bool _isActive = false;
};