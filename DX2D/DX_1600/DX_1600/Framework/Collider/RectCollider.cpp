#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	: _size(size), Collider(ColliderType::RECT)
{
    CreateVertices();
    Collider::CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::Render()
{
    Collider::Render();
}

void RectCollider::CreateVertices()
{
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = _size.x * 0.5f;
    halfSize.y = _size.y * 0.5f;

    temp.pos = { XMFLOAT3(-halfSize.x, halfSize.y, 0.0f) };
    _vertices.push_back(temp);

    temp.pos = { XMFLOAT3(halfSize.x, halfSize.y, 0.0f) };

    _vertices.push_back(temp);

    temp.pos = { XMFLOAT3(halfSize.x, -halfSize.y, 0.0f) };
    _vertices.push_back(temp);

    temp.pos = { XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f) };
    _vertices.push_back(temp);

    temp.pos = { XMFLOAT3(-halfSize.x, halfSize.y, 0.0f) };
    _vertices.push_back(temp);
}

RectCollider::AABBRectInfo RectCollider::GetAABBInfo()
{
    AABBRectInfo result;
    result.left     = _transform->GetWorldPosition().x - GetWorldSize().x * 0.5f;
    result.right    = _transform->GetWorldPosition().x + GetWorldSize().x * 0.5f;
    result.top      = _transform->GetWorldPosition().y + GetWorldSize().y * 0.5f;
    result.bottom   = _transform->GetWorldPosition().y - GetWorldSize().y * 0.5f;

    return result;
}

RectCollider::OBBRectInfo RectCollider::GetOBBInfo()
{
    OBBRectInfo info;

    info.worldPos = _transform->GetWorldPosition();

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, _transform->GetMartix());
    info.direction[0] = {matrix._11, matrix._12};
    info.direction[1] = {matrix._21, matrix._22};

    info.direction[0].Normallize();
    info.direction[1].Normallize();

    info.lenght[0] = GetWorldSize().x * 0.5f;
    info.lenght[1] = GetWorldSize().y * 0.5f;

    return info;
}

bool RectCollider::IsCollision(const Vector2& pos)
{
    AABBRectInfo info = GetAABBInfo();

    if (pos.x < info.left || pos.x > info.right)
        return false;
    else if (pos.y > info.top || pos.y < info.bottom)
        return false;
    return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> col, bool isObb)
{
    if (isObb)
        return OBB_Collision(col);
    return AABB_Collision(col);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> col, bool isObb)
{
    if (isObb)
        return OBB_Collision(col);
    return AABB_Collision(col);
}

bool RectCollider::AABB_Collision(shared_ptr<RectCollider> col)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = col->GetTransform()->GetWorldPosition();
    Vector2 distance = (this->GetWorldSize() + col->GetWorldSize()) * 0.5f;
    if (abs(center1.x - center2.x) > distance.x)
        return false;
    else if (abs(center1.y - center2.y) > distance.y)
        return false;
    else
        return true;
}

bool RectCollider::AABB_Collision(shared_ptr<CircleCollider> col)
{
    AABBRectInfo info = GetAABBInfo();

    Vector2 leftTop = Vector2(info.left, info.top);
    Vector2 rightTop = Vector2(info.right, info.top);
    Vector2 leftBottom = Vector2(info.left, info.bottom);
    Vector2 rightBottom = Vector2(info.right, info.bottom);
    if (col->IsCollision(leftTop) || col->IsCollision(rightTop) || col->IsCollision(leftBottom) || col->IsCollision(rightBottom))
        return true;

    if (info.right > col->GetTransform()->GetWorldPosition().x && info.left < col->GetTransform()->GetWorldPosition().x)
    {
        if (info.top + col->GetWorldRadius() > col->GetTransform()->GetWorldPosition().y
            && info.bottom - col->GetWorldRadius() < col->GetTransform()->GetWorldPosition().y)
            return true;
    }
    if (info.bottom < col->GetTransform()->GetWorldPosition().y && info.top > col->GetTransform()->GetWorldPosition().y)
    {
        if (info.left - col->GetWorldRadius() < col->GetTransform()->GetWorldPosition().x
            && info.right + col->GetWorldRadius() > col->GetTransform()->GetWorldPosition().x)
            return true;
    }
    return false;
}

bool RectCollider::OBB_Collision(shared_ptr<RectCollider> col)
{
    OBBRectInfo infoA = GetOBBInfo();
    OBBRectInfo infoB = col->GetOBBInfo();

    Vector2 aToB = infoB.worldPos - infoA.worldPos;

    // n : normal... 길이가 1인 벡터
    // e : edge... 모서리
    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.lenght[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.lenght[1];

    Vector2 neb1 = infoB.direction[0];
    Vector2 eb1 = infoB.direction[0] * infoB.lenght[0];
    Vector2 neb2 = infoB.direction[1];
    Vector2 eb2 = infoB.direction[1] * infoB.lenght[1];

    // nea1 축으로 투영
    float length = abs(nea1.Dot(aToB));
    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1, eb1, eb2);
    if (length > lengthA + lengthB)
        return false;

    // nea2 축으로 투영
    length = abs(nea2.Dot(aToB));
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);
    if (length > lengthA + lengthB)
        return false;

    // neb1 축으로 투영
    length = abs(neb1.Dot(aToB));
    lengthA = SeparateAxis(neb1, ea1, ea2);
    lengthB = eb1.Length();
    if (length > lengthA + lengthB)
        return false;

    // neb2 축으로 투영
    length = abs(neb2.Dot(aToB));
    lengthA = SeparateAxis(neb2, ea1, ea2);
    lengthB = eb2.Length();
    if (length > lengthA + lengthB)
        return false;

    return true;
}

bool RectCollider::OBB_Collision(shared_ptr<CircleCollider> col)
{
    OBBRectInfo infoA = GetOBBInfo();

    Vector2 aToB = col->GetPos() - infoA.worldPos;

    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.lenght[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.lenght[1];

    //Vector2 leftTop     = infoA.worldPos - ea1 + ea2;
    //Vector2 rightTop    = infoA.worldPos + ea1 + ea2;
    //Vector2 leftBottom  = infoA.worldPos - ea1 - ea2;
    //Vector2 rightBottom = infoA.worldPos + ea1 - ea2;
    //if (col->IsCollision(leftTop) || col->IsCollision(rightTop) || col->IsCollision(leftBottom) || col->IsCollision(rightBottom))
    //    return true;

    //float corner1 = abs(nea1.Dot(aToB)) - ea1.Length();
    //float corner2 = abs(nea2.Dot(aToB)) - ea2.Length();
    //if (pow(corner1, 2) + pow(corner2, 2) > pow(col->GetWorldRadius(), 2))
    //    return false;

    // nea1 축으로 투영
    float length = abs(nea1.Dot(aToB));
    float lengthA = ea1.Length();
    float lengthB = col->GetWorldRadius();
    if (length > lengthA + lengthB)
        return false;

    // nea2 축으로 투영
    length = abs(nea2.Dot(aToB));
    lengthA = ea2.Length();
    lengthB = col->GetWorldRadius();
    if (length > lengthA + lengthB)
        return false;

    float d = sqrt(pow(infoA.lenght[0], 2) + pow(infoA.lenght[1], 2)) + col->GetWorldRadius();
    if (aToB.Length() > d)
        return false;

    return true;
}


bool RectCollider::Block(shared_ptr<RectCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;

    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 sum = (this->GetWorldSize() + moveable->GetWorldSize()) * 0.5f;
    Vector2 dir = moveableCenter - blockCenter;
    Vector2 overlap = Vector2(sum.x - abs(dir.x) , sum.y - abs(dir.y));

    Vector2 fixedPos = moveable->GetTransform()->GetPos();

    if (overlap.x < overlap.y )
    {
        float scalar = overlap.x;
        if (dir.x < 0)
            scalar *= -1;

        fixedPos.x += scalar;

        moveable->GetTransform()->AddVector2(Vector2(scalar, 0.0f));
    }
    else
    {
        float scalar = overlap.y;
        if (dir.y < 0)
            scalar *= -1;
        fixedPos.y += scalar;

        moveable->GetTransform()->AddVector2(Vector2(0.0f, scalar));
    }
    //moveable->SetPosition(fixedPos);

    return true;
}

bool RectCollider::Block(shared_ptr<CircleCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;

    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 virtuaHalfSize = Vector2(moveable->GetWorldRadius(), moveable->GetWorldRadius());
    Vector2 sum = this->GetWorldSize() * 0.5f + virtuaHalfSize;
    Vector2 dir = moveableCenter - blockCenter;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = moveable->GetTransform()->GetPos();

    if (overlap.x < overlap.y)
    {
        float scalar = overlap.x;
        if (dir.x < 0)
            scalar *= -1;

        fixedPos.x += scalar;

       // moveable->GetTransform()->AddVector2(Vector2(scalar, 0.0f));
    }
    else
    {
        float scalar = overlap.y;
        if (dir.y < 0)
            scalar *= -1;
        fixedPos.y += scalar;

       // moveable->GetTransform()->AddVector2(Vector2(0.0f, scalar));
    }
    moveable->SetPosition(fixedPos);

    return true;
}
