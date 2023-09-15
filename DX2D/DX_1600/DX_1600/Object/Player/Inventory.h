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

	//icon 슬롯에 무기 및 악세사리 넣을 수 있는 기능 만들고, 장착중인 무기 및 액세서리와 아이콘 슬롯에 있는 아이템 교환 하는 기능 추가 예정

private:
	//static Inventory* _instance;
	int _curWeapon = 0;
	bool _opened = false;
	shared_ptr<Weapon> _weaponSlot0 = nullptr;
	shared_ptr<Weapon> _weaponSlot1 = nullptr;
	//vector 사용해서 악세사리 슬롯 생성 예정

	UINT _curCoin = 0;
	shared_ptr<NumFont> _curCoinFont;

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

	shared_ptr<Transform> _weaponIcon0;
	shared_ptr<Transform> _weaponIcon1;

	//나중에 여유 되면 마우스 사용해서 inventory창 닫을 수 있게 만들예정
	Vector2 aa;
};
