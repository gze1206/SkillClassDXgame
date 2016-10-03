#include "DXUT.h"
#include "AudioClip.h"

AudioClip::AudioClip()
{
}


AudioClip::~AudioClip()
{
}


void AudioClip::Set(CSound* sound)
{
	clip = sound;
	GameManager::print("CSound 설정 완료\n");
}

void AudioClip::Play(bool loop)
{
	clip->Play(0, loop);
}

void AudioClip::Stop()
{
	clip->Stop();
}