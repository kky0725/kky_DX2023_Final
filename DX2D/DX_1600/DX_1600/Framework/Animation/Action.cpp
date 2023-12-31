#include "framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, string name, Type type, float speed)
	: _clips(clips), _name(name), _repeatType(type) ,_speed(speed)
{
}

Action::~Action()
{
}

void Action::Update()
{
	if (_isPlay == false)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;

		switch (_repeatType)
		{
		case Action::END:
		{
			_curClipIndex++;
			if (_curClipIndex >= _clips.size() - 2)
			{
				if (_almostEnd != nullptr)
					_almostEnd();
			}

			if (_curClipIndex == _eventNumber)
			{
				if (_numberEvent != nullptr)
					_numberEvent();
			}

			if (_curClipIndex >= _clips.size())
				Stop();
			break;
		}
		case Action::LOOP:
		{
			_curClipIndex++;
			_curClipIndex %= _clips.size();
			break;
		}
		case Action::PINGPONG:
		{
			if (_isRevers)
			{
				_curClipIndex--;
				if (_curClipIndex <= 0)
					_isRevers = false;
			}
			else
			{
				_curClipIndex++;
				if (_curClipIndex >= _clips.size() - 1)
					_isRevers = true;
			}
			break;
		}
		default:
			break;
		}
	}
}

void Action::Play()
{
	_isPlay = true;
	_isRevers = false;
	_time = 0.0f;
	_curClipIndex = 0;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Stop()
{
	_isPlay = false;
	_curClipIndex = 0;

	if (_endEvent != nullptr)
		_endEvent();
}

void Action::Reset()
{
	_isPlay = false;
	_curClipIndex = 0;
	_time = 0.0f;
}
