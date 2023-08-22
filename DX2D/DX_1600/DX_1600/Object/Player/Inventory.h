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

	void SetWeapon(shared_ptr<Weapon> weapon, int slot = 0);
	void ChangeWeapon();

	shared_ptr<Weapon> CurWeapon();

private:
	static Inventory* _instance;
	int _curWeapon = 0;
	bool _opened = false;
	shared_ptr<Weapon> _weaponSlot0 = nullptr;
	shared_ptr<Weapon> _weaponSlot1 = nullptr;
	//vector 사용해서 악세사리 슬롯 생성 예정

	UINT _curCoin = 0;

	//인벤토리 이미지
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

	//나중에 여유 되면 마우스 사용해서 inventory창 닫을 수 있게 만들예정
	Vector2 aa;
};
