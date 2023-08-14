#pragma once
class SkelBossSword : public Bullet
{
public:
	SkelBossSword();
	~SkelBossSword();

	virtual void Update() override;
	virtual void Render() override;

	void Summon(Vector2 startPos);
	void Shoot();
	void Charge(Vector2 dir);

	int GetAtk();

	bool IsAttack() { return _isAttack; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _maxAtk = 10;
	int _minAtk = 8;
	//float _atkPerSec = 1.0f;

	bool _isAttack = false; // ���󰡴� ���� ����Ʈ shader ���� ���� ����
	bool _isGround = false; // ���� ������ ����Ʈ �߰� ���ҰŸ� ���� ����
	bool _isCharge = false; // ���� ����Ʈ �߰� ���ҰŸ� ���� ����

	//���� �浹���� �� ���߱� ���� �ݶ��̴� �߰� ���� ground�� block�뵵�� ���
};
