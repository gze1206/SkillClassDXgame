#include "DXUT.h"
#include "GameManager.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include <conio.h>

wstring Paths[2] = { L"Resources/Debug/Dopamine.wav", L"Resources/Debug/tjfsus.wav" };

GameManager::GameManager()
{
	PlayerList = new TaskList(sizeof(Player), 1);
	EnemyList = new TaskList(sizeof(Monster), 22);
	BulletList = new TaskList(sizeof(Bullet), 5000);
	EBulletList = new TaskList(sizeof(EnemyBullet), 5000);
	ItemList = new TaskList(sizeof(Item), 1);
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
	//mBossPtr = new Monster(
	//	"Boss", 
	//	D3DXVECTOR3(WINDOW_WIDTH/2, 0, 0.0f), 
	//	1.f, 
	//	222, 
	//	1, 
	//	L"Resources/Debug/boss.png", 
	//	L"Resources/Debug/lachryma.wav");
	//mBossPtr->Load();
	//mBossPtr->GetInfo()->ShootInterval = 12;
	//mBossPtr->ShootCoolDown = 64;
	//mBossPtr->scale = 0.25f;
	//mBossPtr->Pattern = BulletPattern::Straight;
	mBossPtr = new Monster(D3DXVECTOR3(0, 0, 0), new CharacterInfo{ "temp", 0.f, 1, 1, 0, 0 }, L"Resources/Debug/enemy.png");

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

	TaskUpdate(PlayerList);
	TaskUpdate(ItemList);
	TaskUpdate(EnemyList);
	TaskUpdate(BulletList);
	TaskUpdate(EBulletList);

	if (mPlayerPtr->IsHit(mItemPtr))
	{
		print("ÇÃ·¹ÀÌ¾î¿Í ¾ÆÀÌÅÛ Ãæµ¹ÇÔ\n");
		mItemPtr->Respawn();
		mPlayerPtr->info->Speed += 0.22f;
		mPlayerPtr->info->DMG++;
		mPlayerPtr->info->NowHP = mPlayerPtr->info->MaxHP;
		mPlayerPtr->GotItem++;
		print("ÇöÀç ¼Óµµ : %.2f\n", mPlayerPtr->info->Speed);
		clip = ResourceManager::Get().LoadAudioClip(L"Resources/Debug/SE.wav");
		clip->Play(false);
	}
	if (mBossPtr != nullptr)
	{
		if (mPlayerPtr->IsHit(mBossPtr))
		{
			print("º¸½º¿Í ÇÃ·¹ÀÌ¾î Ãæµ¹ÇÔ\n");
			mPlayerPtr->info->NowHP -= mBossPtr->GetInfo()->DMG;
			print("ÇöÀç Ã¼·Â : %d\n", mPlayerPtr->info->NowHP);
			mPlayerPtr->Respawn();
			if (mPlayerPtr->info->NowHP <= 0)
			{
				GameOver();
			}
		}
	}

	CheckStage();
}

void GameManager::GameOver()
{
	HRESULT hr;
	V(ResourceManager::Get().Initialize());
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

void GameManager::TaskUpdate(TaskList * list)
{
	for (TaskIter i(list); i.HasNext(); )
	{
		Object* obj = static_cast<Object*>(i.Next());
		obj->Update();
	}
}

void GameManager::TaskRender(TaskList * list)
{
	for (TaskIter i(list); i.HasNext(); )
	{
		Object* obj = static_cast<Object*>(i.Next());
		obj->Render();
	}
}

void GameManager::TaskDelete(TaskList * list)
{
	for (TaskIter i(list); i.HasNext(); i.Next(), i.Remove());
}

void GameManager::CheckStage()
{
	if (MobCount == 0)
	{
		HRESULT hr;
		V(ResourceManager::Get().Initialize());
		BGM_Path = Paths[rand() % 2];
		clip = ResourceManager::Get().LoadAudioClip(BGM_Path);
		clip->Play(true);
		Stage++;
		switch (Stage)
		{
		case 0:
			mBossPtr = new Monster(
				D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f),
				new CharacterInfo{"Boss", 0.f, 22, 22, 1, 12},
				L"Resources/Debug/boss.png",
				BulletPattern::Straight,
				0.25f,
				L"Resources/Debug/lachryma.wav");
			mBossPtr->ShootCoolDown = 64;
			new Monster(D3DXVECTOR3(100, 0, 0.0f), new CharacterInfo{"Àâ¸÷", 1.f, 2, 2, 1, 24}, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			break;
		case 1:
			mBossPtr = new Monster(
				D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f),
				new CharacterInfo{ "Boss", 0.f, 22, 22, 1, 6 },
				L"Resources/Debug/boss.png",
				BulletPattern::FourWay,
				0.25f,
				L"Resources/Debug/lachryma.wav");
			mBossPtr->ShootCoolDown = 64;
			new Monster(D3DXVECTOR3(100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 2, 2, 1, 24 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			new Monster(D3DXVECTOR3(WINDOW_WIDTH - 100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 2, 2, 1, 24 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			break;
		case 2:
			mBossPtr = new Monster(
				D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f),
				new CharacterInfo{ "Boss", 0.f, 222, 222, 1, 6 },
				L"Resources/Debug/boss.png",
				BulletPattern::Xross,
				0.25f,
				L"Resources/Debug/lachryma.wav");
			mBossPtr->ShootCoolDown = 64;
			new Monster(D3DXVECTOR3(100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			new Monster(D3DXVECTOR3(WINDOW_WIDTH - 100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			new Monster(D3DXVECTOR3(150, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			new Monster(D3DXVECTOR3(WINDOW_WIDTH - 150, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::Straight);
			break;
		case 3:
			mBossPtr = new Monster(
				D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f),
				new CharacterInfo{ "Boss", 0.f, 222, 222, 1, 3 },
				L"Resources/Debug/boss.png",
				BulletPattern::FourWayToXross,
				0.25f,
				L"Resources/Debug/lachryma.wav");
			mBossPtr->ShootCoolDown = 64;
			new Monster(D3DXVECTOR3(100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::FourWay);
			new Monster(D3DXVECTOR3(WINDOW_WIDTH - 100, 0, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::FourWay);
			new Monster(D3DXVECTOR3(150, 50, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::FourWay);
			new Monster(D3DXVECTOR3(WINDOW_WIDTH - 150, 50, 0.0f), new CharacterInfo{ "Àâ¸÷", 1.f, 4, 4, 1, 12 }, L"Resources/Debug/enemy.png", BulletPattern::FourWay);
			break;
		default:
			//GameOver();
			break;
		}
	}
}

void GameManager::Render()
{
	TaskRender(PlayerList);
	TaskRender(ItemList);
	TaskRender(EnemyList);
	TaskRender(BulletList);
	TaskRender(EBulletList);
}

void GameManager::Destroy()
{
	SAFE_DELETE(mPlayerPtr);
	SAFE_DELETE(mItemPtr);
	SAFE_DELETE(mBossPtr);
	TaskDelete(PlayerList);
	TaskDelete(ItemList);
	TaskDelete(EnemyList);
	TaskDelete(BulletList);
	TaskDelete(EBulletList);
	
#if DEBUG
	FreeConsole();
#endif
	Renderer::Release();
}