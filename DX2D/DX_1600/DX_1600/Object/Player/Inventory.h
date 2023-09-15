#pragma once
class Inventory : public Singleton<Inventory>
{
	friend class Singleton;

	Inventory();
	~Inventory();
public:
	void Update();
	void PostRender();
	void WeaponRender();

	void CreateQuad();
	void Open();

	void SetWeapon(shared_ptr<Weapon> weapon, int slot = 0);
	void ChangeWeapon();

	shared_ptr<Weapon> CurWeapon();
	shared_ptr<Weapon> AnotherWeapon();

	void GetCoin() { _curCoin++; }

	//icon ���Կ� ���� �� �Ǽ��縮 ���� �� �ִ� ��� �����, �������� ���� �� �׼������� ������ ���Կ� �ִ� ������ ��ȯ �ϴ� ��� �߰� ����

private:
	//static Inventory* _instance;
	int _curWeapon = 0;
	bool _opened = false;
	shared_ptr<Weapon> _weaponSlot0 = nullptr;
	shared_ptr<Weapon> _weaponSlot1 = nullptr;
	//vector ����ؼ� �Ǽ��縮 ���� ���� ����

	UINT _curCoin = 0;
	shared_ptr<NumFont> _curCoinFont;

	//�κ��丮 �̹���
	shared_ptr<Quad> _base;
	shared_ptr<Quad> _accessory;
	shared_ptr<Quad> _select0;
	shared_ptr<Quad> _select1;
	shared_ptr<Quad> _icon;
	shared_ptr<Quad> _selectedIcon;

	shared_ptr<Transform> _baseTransform;
	shared_ptr<Transform> _accessoryTransform;
	shared_ptr<Transform> _select0Transform;
	shared_ptr<Transform> _select1Transform;
	vector<shared_ptr<Transform>> _iconTransforms;

	shared_ptr<Transform> _weaponIcon0;
	shared_ptr<Transform> _weaponIcon1;

	//���߿� ���� �Ǹ� ���콺 ����ؼ� inventoryâ ���� �� �ְ� ���鿹��
	Vector2 aa;
};
