#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius), Collider(ColliderType::CIRCLE)
{
    CreateVertices();
    Collider::CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    Collider::Update();
}

void CircleCollider::Render()
{
    Collider::Render();
}

void CircleCollider::CreateVertices()
{
    float radian = 2.0f * PI / 36.0f;
    for (int i = 0; i < 37; i++)
    {
        Vertex temp;
        temp.pos = { XMFLOAT3(cos(radian * i) * _radius, sin(radian * i) * _radius, 0.0f) };
        _vertices.push_back(temp);
    }
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
    float distance = (_transform->GetWorldPosition() - pos).Length();
    return distance < GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> col, bool isObb)
{
    if (isObb)
        return OBB_Collision(col);
    return AABB_Collision(col);
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> col, bool isObb)
{
    if (isObb)
        return OBB_Collision(col);
    return AABB_Collision(col);
}

bool CircleCollider::Block(shared_ptr<CircleCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;

    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();

    Vector2 dir = moveableCenter - blockCenter;

    float scalar = abs((moveable->GetWorldRadius() + GetWorldRadius()) - dir.Length());
    dir.Normallize();

    moveable->GetTransform()->AddVector2(dir * scalar * DELTA_TIME);

    return true;
}

bool CircleCollider::Block(shared_ptr<RectCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;

    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 virtuaHalfSize = Vector2(this->GetWorldRadius(), this->GetWorldRadius());
    Vector2 sum = moveable->GetWorldSize() * 0.5f + virtuaHalfSize;
    Vector2 dir = moveableCenter - blockCenter;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = moveable->GetTransform()->GetPos();

    if (overlap.x < overlap.y)
    {
        float scalar = overlap.x;
        if (dir.x < 0)
            scalar *= -1.0f;

        fixedPos.x += scalar;

        // moveable->GetTransform()->AddVector2(Vector2(scalar, 0.0f));
    }
    else
    {
        float scalar = overlap.y;
        if (dir.y < 0)
            scalar *= -1.0f;
        fixedPos.y += scalar;

        // moveable->GetTransform()->AddVector2(Vector2(0.0f, scalar));
    }
    moveable->SetPosition(fixedPos);

    return true;
}

bool CircleCollider::AABB_Collision(shared_ptr<RectCollider> col)
{
    return col->IsCollision(shared_from_this());
}

bool CircleCollider::AABB_Collision(shared_ptr<CircleCollider> col)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = col->_transform->GetWorldPosition();
    float distance = (center1 - center2).Length();
    return distance < GetWorldRadius() + col->GetWorldRadius();
}

bool CircleCollider::OBB_Collision(shared_ptr<RectCollider> col)
{
    return col->IsCollision(shared_from_this(), true);
}

bool CircleCollider::OBB_Collision(shared_ptr<CircleCollider> col)
{
    return AABB_Collision(col);
}
