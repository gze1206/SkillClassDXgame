#include "DXUT.h"
#include "Monster.h"
#include "SpriteRenderer.h"
#include "Define.h"

Monster::Monster(string name, D3DXVECTOR3 pos, float speed, int hp, int dmg, wstring sprite, wstring music) : Object(), renderer(new SpriteRenderer()), info(new CharacterInfo{ name, speed, hp, hp, dmg }), SpriteName(sprite), MusicName(music)
{
	mPosition = pos;
	GameManager::print("���� : %s ������\n", info->Name.c_str());
	IsMove = (speed != 0);

	InitMonster();
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
	GameManager::print("���� �ؽ��� �ε��\n");
	return S_OK;
}

void Monster::Update()
{
	if (IsMove)
	{
		Destination = GameManager::Get().mPlayerPtr->mPosition;
		float x, y, z;
		(mPosition.x > Destination.x) ? x = mPosition.x - info->Speed : x = mPosition.x + info->Speed;
		(mPosition.y > Destination.y) ? y = mPosition.y - info->Speed : y = mPosition.y + info->Speed;
		(mPosition.z > Destination.z) ? z = mPosition.z - info->Speed : z = mPosition.z + info->Speed;
		mPosition = D3DXVECTOR3(x, y, z);
	}
}

void Monster::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}

void Monster::DeleteMonster()
{
	
}

Monster::~Monster()
{
	DeleteMonster();
	GameManager::print("���� : %s ���ŵ�\n", info->Name.c_str());
	SAFE_DELETE(info);
	SAFE_DELETE(renderer);
}
