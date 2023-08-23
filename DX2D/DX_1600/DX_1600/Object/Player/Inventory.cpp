#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
	CreateQuad();
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	for (int i = 0; i < 15; i++)
	{
		_iconTransforms[i]->Update();
	}
}

void Inventory::PostRender()
{
	if (!_opened)
		return;

	_baseTransform			->SetBuffer(0);
	_base->Render();
	_accessoryTransform		->SetBuffer(0);
	_accessory->Render();
	if (_curWeapon == 0)
	{
		_select0Transform->SetBuffer(0);
		_select0->Render();
	}
	else
	{
		_select1Transform->SetBuffer(0);
		_select1->Render();
	}


	for (int i = 0; i < 15; i++)
	{
		_iconTransforms[i]->SetBuffer(0);
		_icon->Render();
		//_selectedIcon->Render();
	}

	

	ImGui::SliderFloat2("invetory", &aa.x, -50.0f, 70.0f);
	//_iconTransform->SetPosition(aa);
}

void Inventory::CreateQuad()
{
	_base			= make_shared<Quad>(L"Resource/Player/Inventory/InventoryBase2.png");
	_accessory		= make_shared<Quad>(L"Resource/Player/Inventory/InventoryBase.png");
	_select0		= make_shared<Quad>(L"Resource/Player/Inventory/WeaponSelect0.png");
	_select1		= make_shared<Quad>(L"Resource/Player/Inventory/WeaponSelect1.png");
	_icon			= make_shared<Quad>(L"Resource/Player/Inventory/IconGray.png");
	_selectedIcon	= make_shared<Quad>(L"Resource/Player/Inventory/IconWhite_Equip.png");

	_baseTransform			= make_shared<Transform>();
	_accessoryTransform		= make_shared<Transform>();
	_select0Transform		= make_shared<Transform>();
	_select1Transform		= make_shared<Transform>();

	_accessoryTransform		 ->SetParent(_baseTransform);
	_select0Transform		 ->SetParent(_baseTransform);
	_select1Transform		 ->SetParent(_baseTransform);

	for (int i = 0; i < 15; i++)
	{
		shared_ptr<Transform> iconTransform = make_shared<Transform>();
		iconTransform->SetParent(_baseTransform);

		Vector2 pos;
		pos.x = -40.0f + i % 5 * 21.0f;
		pos.y = -9.0f - i / 5 * 21.0f;
		iconTransform->SetPosition(pos);

		_iconTransforms.push_back(iconTransform);
		_iconTransforms[i]->Update();
	}

	_baseTransform->SetScale(Vector2(3.63f, 3.63f));
	_baseTransform->SetPosition(Vector2(405.5f,16.5f));

	_select0Transform->SetPosition(Vector2(-25.0f, 52.0f));
	_select1Transform->SetPosition(Vector2(+29.0f, 52.0f));

	_accessoryTransform->SetPosition(Vector2(2.4f, 21.0f));

	_baseTransform->Update();
	_accessoryTransform->Update();
	_select0Transform->Update();
	_select1Transform->Update();
}

void Inventory::Open()
{
	if (KEY_DOWN('I'))
	{
		_opened = !_opened;
	}
}

void Inventory::SetWeapon(shared_ptr<Weapon> weapon, int slot)
{
	if (slot != 0 && slot != 1)
		return;

	if (slot == 0)
		_weaponSlot0 == weapon;
	else
		_weaponSlot1 == weapon;
}

void Inventory::ChangeWeapon()
{
	if (_curWeapon == 0)
		_curWeapon = 1;
	else
		_curWeapon = 0;
}

shared_ptr<Weapon> Inventory::CurWeapon()
{
	if (_curWeapon == 0)
		return _weaponSlot0;
	else
		return _weaponSlot1;
}
