#include "DXUT.h"
#include "Monster.h"
#include "SpriteRenderer.h"
#include "Define.h"

Monster::Monster(D3DXVECTOR3 pos, CharacterInfo* _info, wstring sprite, BulletPattern ptr, float size, wstring music) : Object(GameManager::Get().EnemyList), renderer(new SpriteRenderer()), HPrenderer(new SpriteRenderer()), info(_info), SpriteName(sprite), MusicName(music), Pattern(ptr)
{
	if (info->Name != "temp") GameManager::Get().MobCount++;
	start = pos;
	mPosition = pos;
	GameManager::print("보스 : %s 생성됨\n", info->Name.c_str());
	scale = size;
	IsMove = (info->Speed != 0.f && info->Name != "Boss");

	InitMonster();
	Load();
}

void Monster::InitMonster()
{
}

HRESULT Monster::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(SpriteName));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("보스 텍스쳐 로드됨\n");
	HpTexture = make_shared<Texture>();
	V_RETURN(HpTexture->Load(L"Resources/Debug/HP.png"));
	HPrenderer->SetTexture(HpTexture);
	GameManager::print("HP 텍스쳐 로드됨\n");
	return S_OK;
}

void Monster::Update()
{
	//IsMove = (info->Speed == 0);
	if (info->Name == "temp")
	{
		rc.top = 0;
		rc.bottom = 0;
		rc.right = 0;
		rc.left = 0;
		return;
	}
	ShootCoolDown -= 1.f;

	if (IsMove)
	{
		if (!IntersectRect(new RECT(), &DXUTGetWindowClientRect(), &GetRect()))
		{
			mPosition = start;
			info->NowHP = info->MaxHP;
			return;
		}

		direction = D3DXVECTOR3(0, 1, 0);
		D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
		mPosition += direction * (info->Speed);
	}

	if (IsHit(GameManager::Get().BulletList))
	{
		info->NowHP -= GameManager::Get().mPlayerPtr->info->DMG;
		if (info->NowHP <= 0)
		{
			if (info->Name == "Boss")
				GameManager::Get().mBossPtr = new Monster(D3DXVECTOR3(0, 0, 0), new CharacterInfo{ "temp", 0.f, 1, 1, 0, 0 }, L"Resources/Debug/enemy.png");
			delete this;
			return;
		}
		else if (info->Name == "Boss" && info->NowHP <= info->MaxHP / 10 && !HP_IS_LOW)
		{
			HP_IS_LOW = true;
			HRESULT hr;
			V(ResourceManager::Get().Initialize());
			GameManager::Get().clip = ResourceManager::Get().LoadAudioClip(MusicName);
			GameManager::Get().clip->Play(true);
		}
	}

	if (ShootCoolDown <= 0) Fire();
}

void Monster::Render()
{
	if (info->Name == "temp")
	{
		rc.top = 0;
		rc.bottom = 0;
		rc.right = 0;
		rc.left = 0;
		return;
	}
	D3DXMATRIX s, r, t;
	D3DXMatrixScaling(&s, scale, scale, scale);
	D3DXMatrixRotationZ(&r, D3DXToRadian(90.f));
	D3DXMatrixTranslation(&t, mPosition.x, mPosition.y, mPosition.z);
	r *= mRotationMatrix;
	mWorldTM = s * t;
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();

	D3DXMatrixScaling(&s, 50.f * ((float)info->NowHP/(float)info->MaxHP), 3.f, 1.f);
	D3DXMatrixTranslation(&t, mPosition.x, mPosition.y, mPosition.z);
	mWorldTM = s * t;
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	HPrenderer->Render();
}

void Monster::Fire()
{
	ShootCoolDown = info->ShootInterval;
	switch (Pattern)
	{
	case None:
		break;
	case Straight:
		new EnemyBullet(mPosition, D3DXVECTOR3(0, 1, 0));
		break;
	case FourWay:
		new EnemyBullet(mPosition, D3DXVECTOR3(0, -1, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(0, 1, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(1, 0, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(-1, 0, 0.f));
		break;
	case Xross:
		new EnemyBullet(mPosition, D3DXVECTOR3(1, -1, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(-1, -1, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(1, 1, 0));
		new EnemyBullet(mPosition, D3DXVECTOR3(-1, 1, 0));
		break;
	case FourWayToXross:
		shot_cnt++;
		shot_cnt %= 12;
		if (shot_cnt < 3)
		{
			new EnemyBullet(mPosition, D3DXVECTOR3(0, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(0, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, 0, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, 0, 0.f));
		}
		else if (shot_cnt < 6)
		{
			new EnemyBullet(mPosition, D3DXVECTOR3(1, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, 1, 0));
		}
		else
		{
			new EnemyBullet(mPosition, D3DXVECTOR3(0, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(0, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, 0, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, 0, 0.f));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, -0.5, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, -0.5, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, 0.5, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, 0.5, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(1, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-1, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(0.5, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-0.5, -1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(0.5, 1, 0));
			new EnemyBullet(mPosition, D3DXVECTOR3(-0.5, 1, 0));
			new EnemyBullet(mPosition, GameManager::Get().mPlayerPtr->mPosition - mPosition);
		}
		break;
	default:
		break;
	}
}

void * Monster::operator new(size_t n)
{
	return GameManager::Get().EnemyList->New(n);
}

void Monster::operator delete(void * p)
{
	return GameManager::Get().EnemyList->Delete(p);
}

void Monster::DeleteMonster()
{
	
}

Monster::~Monster()
{
	if (info->Name != "temp") GameManager::Get().MobCount--;
	DeleteMonster();
	GameManager::print("보스 : %s 제거됨\n", info->Name.c_str());
	SAFE_DELETE(info);
	SAFE_DELETE(renderer);
	SAFE_DELETE(HPrenderer);
}
