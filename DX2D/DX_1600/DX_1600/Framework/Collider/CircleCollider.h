#pragma once
class RectCollider;

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual~CircleCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	void SetScale(float value) { _transform->SetScale({ value, value }); }
	
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> col, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> col, bool isObb = false) override;


	//Matrix ��� �ɷ��ִ� �������� Block X
	virtual bool Block(shared_ptr<CircleCollider> moveable) override;
	virtual bool Block(shared_ptr<RectCollider> moveable) override;

private:
	virtual bool AABB_Collision(shared_ptr<RectCollider> col) override final;
	virtual bool AABB_Collision(shared_ptr<CircleCollider> col) override final;

	virtual bool OBB_Collision(shared_ptr<CircleCollider> col) override final;
	virtual bool OBB_Collision(shared_ptr<RectCollider> col) override final;

	float _radius;
};

