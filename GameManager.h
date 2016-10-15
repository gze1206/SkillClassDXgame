#pragma once
#include "Singleton.h"
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "Monster.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "ResourceManager.h"

class Player;
class Item;
class Monster;
class Bullet;

struct CharacterInfo
{
	string Name;
	float Speed;
	int MaxHP, NowHP;
	int DMG;
	int ShootInterval;
};

enum Rotate
{
	Left = 0,
	Right,
	Up,
	Down,
};

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();
	
public:
	void Initialize();
	HRESULT Reset();
	void OnLostDevice();
	void Update();
	void Render();
	void Destroy();
	void GameOver();
	void TaskUpdate(TaskList* list);
	void TaskRender(TaskList* list);
	void TaskDelete(TaskList* list);
	void CheckStage();
	static int print(_In_z_ _Printf_format_string_ char const* const _Format, ...)
	{
#if DEBUG
		va_list arg;
		int cnt = 0;

		va_start(arg, _Format);
		cnt = vprintf(_Format, arg);
		va_end(arg);

		return cnt;
#else
		return NULL;
#endif
	}

public:
	Player *mPlayerPtr;
	Item *mItemPtr;
	RECT ClientRect;
	Monster *mBossPtr;
	shared_ptr<AudioClip> clip = nullptr;
	TaskList *PlayerList, *EnemyList, *BulletList, *ItemList, *EBulletList;
	wstring BGM_Path;
	int Stage = -1, MobCount = 0;
};