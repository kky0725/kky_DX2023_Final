#pragma once
class SRVManager : public Singleton<SRVManager>
{
	friend class Singleton;

	SRVManager();
	~SRVManager();
public:
	shared_ptr<SRV> Add_SRV(wstring path);

private:
	//static SRVManager* _instance;

	unordered_map<wstring, shared_ptr<SRV>> _srvMap;

};

