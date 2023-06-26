#pragma once
class RectCollider : public Collider
{
	struct AABBRectInfo
	{
		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
	};

	struct OBBRectInfo
	{
		Vector2 worldPos;
		Vector2 direction[2]; // 가로 세로 벡터
		float lenght[2]; // 가로 세로 길이
	};

public:
	RectCollider(Vector2 size);
	virtual~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }
	Vector2 GetWorldSize() const { return Vector2(_transform->GetWorldScale().x * _size.x, _transform->GetWorldScale().y * _size.y); }

	AABBRectInfo GetAABBInfo();
	OBBRectInfo GetOBBInfo();

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> col, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> col, bool isObb = false) override;


	//Matrix 상속 걸려있는 구조에선 Block X
	virtual bool Block(shared_ptr<RectCollider> moveable) override;
	virtual bool Block(shared_ptr<CircleCollider> moveable) override;

private:
	virtual bool AABB_Collision(shared_ptr<RectCollider> col) override final;
	virtual bool AABB_Collision(shared_ptr<CircleCollider> col) override final;

	virtual bool OBB_Collision(shared_ptr<CircleCollider> col) override final;
	virtual bool OBB_Collision(shared_ptr<RectCollider> col) override final;

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
	{
		float r1 = abs(separate.Dot(e1));
		float r2 = abs(separate.Dot(e2));

		return r1 + r2;
	}

	Vector2 _size;


};

