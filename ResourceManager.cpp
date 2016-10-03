#include "DXUT.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() : mSoundManager()
{
}


ResourceManager::~ResourceManager()
{
}

shared_ptr<AudioClip> ResourceManager::LoadAudioClip(const wstring& path)
{
	HRESULT hr;
	CSound *soundPTR = nullptr;
	V(mSoundManager.Create(&soundPTR, (LPWSTR)path.c_str()));

	auto audioClipPTR = make_shared<AudioClip>();
	audioClipPTR->Set(soundPTR);

	return audioClipPTR;
}

HRESULT ResourceManager::Initialize()
{
	HRESULT hr;
	V_RETURN(mSoundManager.Initialize(DXUTGetHWND(), DSSCL_EXCLUSIVE));
	return S_OK;
}