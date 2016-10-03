/*
Copyright (c) 2011 by Chrles Kelly
C++�� DirectX�� ���� ������ �����ϸ� ���� 2D ���� ���α׷��� ����
*/

#pragma once
#include <xact3.h>

class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();
	HRESULT initAudio();
	void Update();
	void Play(const char cue[]);
	void Stop(const char cue[]);

private:
	IXACT3Engine *engine;
	IXACT3WaveBank *wave;
	IXACT3SoundBank *sound;
	XACTINDEX cueI;
	void *mapWaveBank;
	void *soundBankData;
	bool initialized;
};

