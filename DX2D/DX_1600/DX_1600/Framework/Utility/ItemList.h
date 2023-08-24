#pragma once
class ItemList : public Singleton<ItemList>
{
	friend class Singleton;

	ItemList();
	~ItemList();

	void CreateSword(string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring string, Vector2 size);
	void CreateGun(string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring srvFile, string xmlFile);
	//void CreateAccessory();

	vector<shared_ptr<Item>> _items;

public:
	shared_ptr<Item> GetItem(int index) { return _items[index]; }
	shared_ptr<Weapon> GetWeapon(int index) { return dynamic_pointer_cast<Weapon>(_items[index]); }
};

