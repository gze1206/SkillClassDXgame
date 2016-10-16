#include "DXUT.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Define.h"
#include <comdef.h>
#include <CRTDBG.H>
#include <atlconv.h>

Player::Player() : Object(GameManager::Get().PlayerList), renderer(new SpriteRenderer()),HPrenderer(new SpriteRenderer), info(new CharacterInfo{ "PLAYER", 1.5f, 10, 10, 1, 6 })
{
	mPosition = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100, 0);
	GameManager::print("플레이어 : %s 생성됨\n", info->Name.c_str());
	scale = 0.25f;
	
	//GameError 테스트
	//try { throw(GameError(GameErrorDefine::FATAL_ERROR, "test")); }
	//catch (GameError ex)
	//{
	//	string temp = "";
	//	if (ex.GetCode() == -1) temp = "치명적인 오류!";
	//	MessageBoxA(DXUTGetHWND(), ex.GetErrorMessage(), temp.c_str(), NULL);
	//}
}


Player::~Player()
{
	GameManager::print("플레이어 : %s 제거됨\n", info->Name.c_str());
	SAFE_DELETE(info);
	SAFE_DELETE(renderer);
	SAFE_DELETE(HPrenderer);
}

HRESULT Player::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/player.png"));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("플레이어 텍스쳐 로드됨\n");
	HpTexture = make_shared<Texture>();
	V_RETURN(HpTexture->Load(L"Resources/Debug/HP.png"));
	HPrenderer->SetTexture(HpTexture);
	GameManager::print("HP 텍스쳐 로드됨\n");
	return S_OK;
}

void Player::Respawn()
{
	mPosition = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100, 0);
	GameManager::print("플레이어 : %s 재생성됨\n", info->Name.c_str());
	scale = 0.25f;
}

void * Player::operator new(size_t n)
{
	return GameManager::Get().PlayerList->New(n);
}

void Player::operator delete(void * p)
{
	return GameManager::Get().PlayerList->Delete(p);
}

void Player::Update()
{
	ShootCoolDown -= 1.f;

	if (IsHit(GameManager::Get().EBulletList))
	{
		info->NowHP -= GameManager::Get().mBossPtr->GetInfo()->DMG;
		Respawn();
		if (info->NowHP <= 0)
		{
			GameManager::Get().clip->Stop();
			DXUTShutdown();
		}
	}

	D3DXVECTOR3 direction(0,0,0);
	if ((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) && rc.top > GameManager::Get().ClientRect.top)
	{
		mPosition.y -= info->Speed;
		rot = Up;
		direction.y -= info->Speed;
		D3DXVec3Normalize(&this->direction, &direction);
		D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
	}
	if ((GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) && rc.bottom < GameManager::Get().ClientRect.bottom)
	{
		mPosition.y += info->Speed;
		rot = Down;
		direction.y += info->Speed;
		D3DXVec3Normalize(&this->direction, &direction);
		D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
	}
	if ((GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) && rc.left > GameManager::Get().ClientRect.left)
	{
		mPosition.x -= info->Speed;
		rot = Left;
		direction.x -= info->Speed;
		D3DXVec3Normalize(&this->direction, &direction);
		D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
	}
	if ((GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) && rc.right < GameManager::Get().ClientRect.right)
	{
		mPosition.x += info->Speed;
		rot = Right;
		direction.x += info->Speed;
		D3DXVec3Normalize(&this->direction, &direction);
		D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (ShootCoolDown <= 0)
		{
			ShootCoolDown = info->ShootInterval;
			switch (rot)
			{
			case Right:
				new Bullet(mPosition, D3DXVECTOR3(1, 0, 0));
				new Bullet(mPosition, D3DXVECTOR3(1, -1, 0));
				new Bullet(mPosition, D3DXVECTOR3(1, 1, 0));
				break;
			case Left:
				new Bullet(mPosition, D3DXVECTOR3(-1, 0, 0));
				new Bullet(mPosition, D3DXVECTOR3(-1, -1, 0));
				new Bullet(mPosition, D3DXVECTOR3(-1, 1, 0));
				break;
			case Up:
				new Bullet(mPosition, D3DXVECTOR3(0, 1, 0));
				new Bullet(mPosition, D3DXVECTOR3(1, 1, 0));
				new Bullet(mPosition, D3DXVECTOR3(-1, 1, 0));
				break;
			case Down:
				new Bullet(mPosition, D3DXVECTOR3(0, -1, 0));
				new Bullet(mPosition, D3DXVECTOR3(1, -1, 0));
				new Bullet(mPosition, D3DXVECTOR3(-1, -1, 0));
				break;
			default:
				break;
			}
		}
	}
}

void Player::Render()
{
	D3DXMATRIX s, r, t;
	D3DXMatrixScaling(&s, scale, scale, scale);
	D3DXMatrixTranslation(&t, mPosition.x, mPosition.y, mPosition.z);
	D3DXMatrixRotationZ(&r, D3DXToRadian(90.f));
	r *= mRotationMatrix;
	mWorldTM = s * r * t;
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render(nullptr, &D3DXVECTOR3(mTexturePtr->GetInfo().Width/2.f, mTexturePtr->GetInfo().Height / 2.f, 0.f));

	D3DXMatrixScaling(&s, 50.f * ((float)info->NowHP / (float)info->MaxHP), 3.f, 1.f);
	D3DXMatrixTranslation(&t, mPosition.x, mPosition.y - 22, mPosition.z);
	mWorldTM = s * t;
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	HPrenderer->Render();
}