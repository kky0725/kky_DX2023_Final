#pragma once
class Sound : public Singleton<Sound>
{
	struct SoundInfo
	{
		FMOD::Sound* _sound = nullptr;
		FMOD::Channel* _channel = nullptr;

		SoundInfo() {}
		~SoundInfo() {}
	};

	Sound();
	~Sound();
public:
	void Update();
	void Add(string key, string file, bool bgm = false);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	void SetVolume(string key, float volume);
	
	bool IsPlaySound(string key);

private:
	static Sound* _instance;

	FMOD::System* _soundSysyetm = nullptr;

	unordered_map<string, SoundInfo> _soundMap;
	const int MAX_CHANNEL = 15;
};

