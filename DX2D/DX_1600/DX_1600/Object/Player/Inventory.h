#pragma once
class Inventory
{
	Inventory();
	~Inventory();
public:

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Inventory* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new Inventory;
		return _instance;
	}


	void Update();
	void PostRender();

	void CreateQuad();
	void Open();

private:
	static Inventory* _instance;
	int _curWeapon = 0;
	bool _opened = false;
	shared_ptr<Weapon> _weaponSlot1 = nullptr;
	shared_ptr<Weapon> _weaponSlot2 = nullptr;

	int _curCoin = 0;

	shared_ptr<Quad> _base;
	shared_ptr<Quad> _accessory;
	shared_ptr<Quad> _select0;
	shared_ptr<Quad> _select1;
	shared_ptr<Quad> _icon;//vector�� ��ȯ ����
	shared_ptr<Quad> _selectedIcon;//vector�� ��ȯ ����

	shared_ptr<Transform> _baseTransform;
	shared_ptr<Transform> _accessoryTransform;
	shared_ptr<Transform> _select0Transform;
	shared_ptr<Transform> _select1Transform;
	shared_ptr<Transform> _iconTransform;
	shared_ptr<Transform> _selectedIconTransform;//�����ص� ��� ���� ����?
	//vector ����ؼ� �Ǽ��縮 ���� ���� ����

	//���߿� ���� �Ǹ� ���콺 ����ؼ� inventoryâ ���� �� �ְ� ���鿹��
	Vector2 aa;
};
