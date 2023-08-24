#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;

	Camera();
	~Camera();
public:
	void Update();
	void PostRender();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 1.0f);

	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetCameraBuffer() { _view->SetBuffer(1); }
	void SetUICameraBuffer() { _uiView->SetBuffer(1); }
	void SetProjectionBuffer() { _projection->SetVSBuffer(2); }

	void AddAngle(float angle) { _view->AddAngle(-angle); }
	void AddScale(const Vector2& scale) { _view->AddScale(scale) ; }
	void AddVector2(const Vector2& pos);

	void SetAngle(float angle) { _view->SetAngel(-angle); }
	void SetScale(const Vector2& scale) { _view->SetScale(scale); }
	void SetPosition(const Vector2& pos);

	void SetTarget(shared_ptr<Transform> target) { _target = target; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }
	void SetOffSet(Vector2 value) { _offset = value; }

	const Vector2 GetWorldMousePos();

private:
	void FollowMode();
	void FreeMode();
	void Shake();

	//static Camera* _instance;

	shared_ptr<Transform>		_view;
	shared_ptr<Transform>		_uiView;
	shared_ptr<MatrixBuffer>	_projection;

	// FollowMode
	weak_ptr<Transform> _target;
	Vector2 _offset;
	Vector2 _leftBottom = Vector2(-10000.0f, -10000.0f);
	Vector2 _rightTop = Vector2(10000.0f, 10000.0f);

	//FreeMode
	float _speed = 500.0f;

	float _duration = 0.0f;
	float _magnitude = 0.0f;
	float _reduceDamping = 0.0f;

	Vector2 _originPos;
};

