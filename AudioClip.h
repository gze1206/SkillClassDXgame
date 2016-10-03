#pragma once
#include "Asset.h"

class AudioClip :
	public Asset
{
public:
	AudioClip();
	~AudioClip();
	void Set(CSound* sound);
	void Play(bool loop);
	void Stop();

private:
	CSound *clip;
};

