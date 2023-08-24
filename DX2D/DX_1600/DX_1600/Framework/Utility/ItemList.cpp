#include "framework.h"
#include "ItemList.h"

ItemList::ItemList()
{
	CreateSword("¼ô¼Òµå", 100, "Æò¹üÇÑ °Ë", L"Resource/Weapon/ShortSword.png", 0, 8, 10, 3.03f, L"Resource/Weapon/ShortSword.png", Vector2(65.0f, 18.0f));
	CreateGun("¼Õ¼è³ú", 100, "Æò¹üÇÑ ¼è³ú", L"Resource/Weapon/CrossBow0.png", 1, 11, 13, 2.38f, L"Resource/Weapon/CrossBow.png", "Resource/Weapon/CrossBow.xml");
}

ItemList::~ItemList()
{
}

void ItemList::CreateSword(string name, int price, string itemDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring srvFile, Vector2 size)
{
	shared_ptr<Item> item = make_shared<Sword>(Item::WEAPON, name, price, itemDesc, iconSrvfile, ID, minAtk, maxAtk, atkPerSec, srvFile, size);
	_items.push_back(item);
}

void ItemList::CreateGun(string name, int price, string itemDesc, wstring iconSrvfile, int ID, int minAtk, int maxAtk, float atkPerSec, wstring srvFile, string xmlFile)
{
	shared_ptr<Item> item = make_shared<Gun>(Item::WEAPON, name, price, itemDesc, iconSrvfile, ID, minAtk, maxAtk, atkPerSec, srvFile, xmlFile);
	_items.push_back(item);
}
