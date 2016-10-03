#include "DXUT.h"
#include "SpriteRenderer.h"
#include "Bullet.h"

Bullet::Bullet() : Object(), renderer(new SpriteRenderer())
{
	Load();
}


Bullet::~Bullet()
{
	SAFE_DELETE(renderer);
}

HRESULT Bullet::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/e_bullet.png"));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("ÅºÈ¯ ÅØ½ºÃÄ ·ÎµåµÊ\n");
	return S_OK;
}

void Bullet::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}

void Bullet::Update()
{
	Speed = GameManager::Get().mPlayerPtr->info->Speed * 1.5;

	mPosition = mPosition + D3DXVECTOR3(Speed * direction.x, -Speed * direction.y, Speed * direction.z);
}

void Bullet::fire(const D3DXVECTOR3& start, const D3DXVECTOR3& direction)
{
	mPosition = start;
	IsFlight = true;
	D3DXVec3Normalize(&this->direction, &direction);
}