#include "framework.h"
#include "ItemList.h"

ItemList::ItemList()
{
	
}

ItemList::~ItemList()
{
}

void ItemList::CreateSword(string name, int price, string itemDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, int atkPerSec, wstring string, Vector2 size)
{
	shared_ptr<Item> item = make_shared<Sword>(Item::WEAPON, name, price, itemDesc, iconSrvfile, ID, minAtk, maxAtk, atkPerSec, string, size);
	_items.push_back(item);
}
