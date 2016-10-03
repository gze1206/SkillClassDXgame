#include "DXUT.h"
#include "GameManager.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include <conio.h>

wstring Paths[2] = { L"Resources/Debug/Dopamine.wav", L"Resources/Debug/tjfsus.wav" };

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	mPlayerPtr = new Player();
	mPlayerPtr->Load();
	mItemPtr = new Item();
	mItemPtr->Load();
	mBossPtr = new Monster("Boss", D3DXVECTOR3(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0.0f), 0.0f, 22, 1, L"Resources/Debug/player.png", L"Resources/Debug/lachryma.wav");
	mBossPtr->Load();
	HRESULT hr;
	V(ResourceManager::Get().Initialize());
	clip = ResourceManager::Get().LoadAudioClip(Paths[rand()%2]);
	clip->Play(true);

#if DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	print("start : %.2f\n", mPlayerPtr->info->Speed);
}

HRESULT GameManager::Reset()
{
	HRESULT hr;
	V_RETURN(Renderer::CreateSprite());
	return S_OK;
}

void GameManager::OnLostDevice()
{
	Renderer::Release();
}

void GameManager::Update()
{
	ClientRect = DXUTGetWindowClientRect();

	mPlayerPtr->Update();
	mItemPtr->Update();
	mBossPtr->Update();
	for (char i = 0; i < 3; i++)
	{
		if (A[i] != nullptr)
		{
			A[i]->Update();
		}
	}

	if (IsTriggerOn(mPlayerPtr->GetRect(), mItemPtr->GetRect()))
	{
		print("플레이어와 아이템 충돌함\n");
		mItemPtr->Respawn();
		mPlayerPtr->info->Speed+=0.22f;
		mPlayerPtr->info->DMG++;
		mPlayerPtr->GotItem++;
		mBossPtr->GetInfo()->Speed *= 1.5;
		mBossPtr->GetInfo()->DMG += 1;
		print("현재 속도 : %.2f\n", mPlayerPtr->info->Speed);
		clip = ResourceManager::Get().LoadAudioClip(L"Resources/Debug/SE.wav");
		clip->Play(false);
		if (mPlayerPtr->info->Speed > 22)
		{
			GameOver();
		}
	}
	if (IsTriggerOn(mBossPtr->GetRect(), mPlayerPtr->GetRect()))
	{
		print("보스와 플레이어 충돌함\n");
		mPlayerPtr->info->NowHP -= mBossPtr->GetInfo()->DMG;
		print("현재 체력 : %d\n", mPlayerPtr->info->NowHP);
		mPlayerPtr->Respawn();
		if (mPlayerPtr->info->NowHP <= 0)
		{
			GameOver();
		}
	}
	
	for (char i = 0; i < 3; i++)
	{
		if (A[i] != nullptr)
		{
			if (IsTriggerOn(mBossPtr->GetRect(), A[i]->GetRect()))
			{
				print("보스와 탄환 충돌함\n");
				mBossPtr->GetInfo()->NowHP -= mPlayerPtr->info->DMG;
				print("보스 체력 : %d\n", mBossPtr->GetInfo()->NowHP);
				if (mBossPtr->GetInfo()->NowHP <= 0)
				{
					mBossPtr->~Monster();
					GameOver();
				}
				else if (mBossPtr->GetInfo()->NowHP - mPlayerPtr->info->DMG <= mBossPtr->GetInfo()->MaxHP / 10)
				{
					clip->Stop();
					clip = ResourceManager::Get().LoadAudioClip(mBossPtr->MusicName);
					clip->Play(true);
				}
				A[i]->~Bullet();
				A[i] = NULL;
			}
		}
	}
}

void GameManager::GameOver()
{
	mPlayerPtr->~Player();
	mItemPtr->~Item();
	mBossPtr->~Monster();
	
	for (char i = 0; i < 3; i++)
	{
		if (A[i] != nullptr)
		{
			A[i]->~Bullet();
		}
	}
	print("Game Over\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			DXUTShutdown();
			return;
		}
	}
}

void GameManager::Render()
{
	mPlayerPtr->Render();
	mItemPtr->Render();
	mBossPtr->Render();
	for (char i = 0; i < 3; i++)
	{
		if (A[i] != nullptr)
		{
			A[i]->Render();
		}
	}
}

void GameManager::Destroy()
{
	SAFE_DELETE(mPlayerPtr);
	SAFE_DELETE(mItemPtr);
	SAFE_DELETE(mBossPtr);
	for (char i = 0; i < 3; i++)
	{
		if (A[i] != nullptr)
		{
			A[i]->~Bullet();
		}
	}
	SAFE_DELETE(A[0]);
	SAFE_DELETE(A[1]);
	SAFE_DELETE(A[2]);
#if DEBUG
	FreeConsole();
#endif
	Renderer::Release();
}

//렉트 두 개를 인자로 받아 충돌체크를 한다
bool GameManager::IsTriggerOn(const RECT& a, const RECT& b)
{
	return (a.left <= b.right && a.right >= b.left && a.top <= b.bottom && a.bottom >= b.top);
}