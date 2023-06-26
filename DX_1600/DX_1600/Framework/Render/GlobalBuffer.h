#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	// 상수 버퍼를 이용할 때 한가지 규칙
	// 16바이트 배수를 무조건 지켜야 한다. 24 x
	struct Data
	{
		XMMATRIX matirx = XMMatrixIdentity();//단위 행렬
	};

	MatrixBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		value = XMMatrixTranspose(value);
		_data.matirx = value;
	}

	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~ColorBuffer() {}

	void SetColor(XMFLOAT4 value) { _data.color = value; }

private:
	Data _data;
};

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 maxFrame = { 0.0f, 0.0f };
		XMFLOAT2 curFrame = { 0.0f, 0.0f };
	};

	FrameBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~FrameBuffer() {}

	void SetMaxFrame(Vector2 value)
	{
		_data.maxFrame = value;

	}
	void SetCurFrame(Vector2 value)
	{
		_data.curFrame = value;
	}

private:
	Data _data;
};

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 imageSize;
		int		isRight = 0;
		int		padding;
	};

	ActionBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~ActionBuffer() {}

	Data _data;
private:
};

class FilterBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		int value1 = 1;
		int value2 = 0;
		int value3 = 0;

		Vector2 imageSize = { 0,0 };
		Vector2 radialCenter = { 0,0 };
	};

	FilterBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~FilterBuffer() {}

	Data _data;
private:
};

class IntBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int	value1 = 0;
		int	value2 = 0;
		int	value3 = 0;
		int	value4 = 0;
	};

	IntBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~IntBuffer() {}

	Data _data;
private:
};

class ButtonBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int		state = 0;
		float	hovered = 0.0f;
		float	clicked = 0.0f;
		float	padding = 0.0f;
	};

	ButtonBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~ButtonBuffer() {}

	Data _data;
private:
};