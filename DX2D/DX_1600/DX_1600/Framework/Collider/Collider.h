#pragma once
class CircleCollider;
class RectCollider;

class Collider
{
public:
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider(ColliderType type);
	virtual~Collider();

	virtual void Update();
	virtual void Render();

	void CreateData();
	virtual void CreateVertices() abstract;

	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

	bool IsCollision(shared_ptr<Collider> col, bool isObb = false);
	bool Block(shared_ptr<Collider> other);

	virtual bool Block(shared_ptr<CircleCollider> moveable) abstract;
	virtual bool Block(shared_ptr<RectCollider> moveable) abstract;

	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> col, bool isObb = false) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> col, bool isObb = false) abstract;


	static bool _isDebug;
protected:
	virtual bool AABB_Collision(shared_ptr<RectCollider> col) abstract;
	virtual bool AABB_Collision(shared_ptr<CircleCollider> col) abstract;

	virtual bool OBB_Collision(shared_ptr<CircleCollider> col) abstract;
	virtual bool OBB_Collision(shared_ptr<RectCollider> col) abstract;

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;

	ColliderType _type = ColliderType::NONE;
};

