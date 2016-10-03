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
	GameManager::print("CSound ���� �Ϸ�\n");
}

void AudioClip::Play(bool loop)
{
	clip->Play(0, loop);
}

void AudioClip::Stop()
{
	clip->Stop();
}