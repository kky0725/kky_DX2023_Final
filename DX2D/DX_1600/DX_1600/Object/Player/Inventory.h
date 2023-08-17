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

private:
	static Inventory* _instance;
	shared_ptr<Weapon> _weaponSlot1 = nullptr;
	shared_ptr<Weapon> _weaponSlot2 = nullptr;



	//vector ����ؼ� �Ǽ��縮 ���� ���� ����
};
