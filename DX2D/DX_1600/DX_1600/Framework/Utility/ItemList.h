#pragma once
class ItemList : public Singleton<ItemList>
{
	ItemList();
	~ItemList();

	void CreateSword(string name, int price, string itmeDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, int atkPerSec, wstring string, Vector2 size);
	void CreateGun();
	void CreateAccessory();

	vector<shared_ptr<Item>> _items;
};

