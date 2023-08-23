#include "framework.h"
#include "Item.h"

Item::Item(ItemType type, string name, int price, string itmeDesc, wstring srvfile, int ID)
	:_type(type), _name(name), _price(price), _itemDesc(itmeDesc), _ID(ID)
{
	_icon = make_shared<Quad>(srvfile);
}

Item::~Item()
{
}

void Item::RenderIcon()
{
	_icon->Render();
}

