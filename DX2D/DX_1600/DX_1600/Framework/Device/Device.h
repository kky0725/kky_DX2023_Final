#pragma once
class Device
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Device* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDC() { return _deviceContext; }
	ComPtr< IDXGISwapChain> GetSwapChain() {return _swapChain; }

	void Clear();
	void Present();

private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateDoubleBuffer();

	static Device* _instance;

	ComPtr<ID3D11Device>			_device; // 컴퓨터의 하드웨어 기능 점검, 리소스 할당(하드웨어에 접근할 수 있게 도와주는 얘.
	ComPtr<ID3D11DeviceContext>		_deviceContext; // 렌더링할 대상을 결정(어따가 그릴지 결정)
	ComPtr<IDXGISwapChain>			_swapChain; // 각각의 표면(버퍼, 텍스쳐)을 출력하기 전에 데이터를 보관하다.
	ComPtr<ID3D11RenderTargetView>	_renderTargetView; // 지금 당장 그릴 곳(후면 버퍼)을 가리키는 포인터


};

