#include "DXUT.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Define.h"
#include <comdef.h>
#include <CRTDBG.H>
#include <atlconv.h>

Player::Player() : Object(), renderer(new SpriteRenderer()), info(new CharacterInfo{ "PLAYER", 3.0f, 10, 10, 1 })
{
	mPosition = D3DXVECTOR3(100, 100, 0);
	GameManager::print("�÷��̾� : %s ������\n", info->Name.c_str());
	
	//GameError �׽�Ʈ
	//try { throw(GameError(GameErrorDefine::FATAL_ERROR, "test")); }
	//catch (GameError ex)
	//{
	//	string temp = "";
	//	if (ex.GetCode() == -1) temp = "ġ������ ����!";
	//	MessageBoxA(DXUTGetHWND(), ex.GetErrorMessage(), temp.c_str(), NULL);
	//}
}


Player::~Player()
{
	GameManager::print("�÷��̾� : %s ���ŵ�\n", info->Name.c_str());
	SAFE_DELETE(info);
	SAFE_DELETE(renderer);
}

HRESULT Player::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/player.png"));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("�÷��̾� �ؽ��� �ε��\n");
	return S_OK;
}

void Player::Respawn()
{
	mPosition = D3DXVECTOR3(100, 100, 0);
	GameManager::print("�÷��̾� : %s �������\n", info->Name.c_str());
}

void Player::Update()
{
	if ((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) && rc.top > GameManager::Get().ClientRect.top)
	{
		mPosition.y -= info->Speed;
		rot = Up;
	}
	if ((GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) && rc.bottom < GameManager::Get().ClientRect.bottom)
	{
		mPosition.y += info->Speed;
		rot = Down;
	}
	if ((GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) && rc.left > GameManager::Get().ClientRect.left)
	{
		mPosition.x -= info->Speed;
		rot = Left;
	}
	if ((GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) && rc.right < GameManager::Get().ClientRect.right)
	{
		mPosition.x += info->Speed;
		rot = Right;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (GameManager::Get().A[0] != nullptr)
		{
			for (char i = 0; i < 3; i++)
			{
				GameManager::Get().A[i]->~Bullet();
			}
		}
		for (char i = 0; i < 3; i++)
		{
			GameManager::Get().A[i] = new Bullet();
			GameManager::Get().A[i]->Load();
		}
		switch (rot)
		{
		case Right:
			GameManager::Get().A[0]->fire(mPosition, D3DXVECTOR3(1, 0, 0));
			GameManager::Get().A[1]->fire(mPosition, D3DXVECTOR3(1, -1, 0));
			GameManager::Get().A[2]->fire(mPosition, D3DXVECTOR3(1, 1, 0));
			break;
		case Left:
			GameManager::Get().A[0]->fire(mPosition, D3DXVECTOR3(-1, 0, 0));
			GameManager::Get().A[1]->fire(mPosition, D3DXVECTOR3(-1, -1, 0));
			GameManager::Get().A[2]->fire(mPosition, D3DXVECTOR3(-1, 1, 0));
			break;
		case Up:
			GameManager::Get().A[0]->fire(mPosition, D3DXVECTOR3(0, 1, 0));
			GameManager::Get().A[1]->fire(mPosition, D3DXVECTOR3(1, 1, 0));
			GameManager::Get().A[2]->fire(mPosition, D3DXVECTOR3(-1, 1, 0));
			break;
		case Down:
			GameManager::Get().A[0]->fire(mPosition, D3DXVECTOR3(0, -1, 0));
			GameManager::Get().A[1]->fire(mPosition, D3DXVECTOR3(1, -1, 0));
			GameManager::Get().A[2]->fire(mPosition, D3DXVECTOR3(-1, -1, 0));
			break;
		default:
			break;
		}
	}
}

void Player::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}