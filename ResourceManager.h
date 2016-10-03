#pragma once
#include "Singleton.h"
#include "AudioClip.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	shared_ptr<AudioClip> LoadAudioClip(const wstring& path);
	HRESULT Initialize();

private:
	CSoundManager mSoundManager;
};