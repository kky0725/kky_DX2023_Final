#pragma once
class Item
{
public:
	enum ItemType
	{
		WEAPON,
		ACCESSORY
	};
	
	Item(ItemType type, string name, int price, string itmeDesc, wstring srvfile, int ID);
	virtual ~Item();

	virtual void RenderIcon() abstract;

protected:
	ItemType _type = WEAPON;
	string _name = "";
	int _price;
	string _itemDesc = "";
	shared_ptr<Quad> _icon = nullptr;
	int _ID;
};
