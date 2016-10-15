#include "DXUT.h"
#include "SpriteRenderer.h"
#include "Bullet.h"

Bullet::Bullet(const D3DXVECTOR3& start, const D3DXVECTOR3& direction) : Object(GameManager::Get().BulletList), renderer(new SpriteRenderer())
{
	scale = 0.1f;
	Load();
	fire(start, direction);
}


Bullet::~Bullet()
{
	SAFE_DELETE(renderer);
}

HRESULT Bullet::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/p_bullet.png"));
	renderer->SetTexture(mTexturePtr);
	//GameManager::print("ÅºÈ¯ ÅØ½ºÃÄ ·ÎµåµÊ\n");
	return S_OK;
}

void Bullet::Render()
{
	D3DXMATRIX s, r, t;
	D3DXMatrixScaling(&s, scale, scale, scale);
	D3DXMatrixRotationZ(&r, D3DXToRadian(90.f));
	D3DXMatrixTranslation(&t, mPosition.x, mPosition.y, mPosition.z);
	r *= mRotationMatrix;
	mWorldTM = s * r * t;
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}

void Bullet::Update()
{
	if (IsHit(GameManager::Get().EnemyList))
	{
		delete this;
		return;
	}
	if (!IntersectRect(new RECT(), &DXUTGetWindowClientRect(), &GetRect()))
	{
		GameManager::print("ÅºÈ¯ Á¦°ÅµÊ\n");
		delete this;
		return;
	}
	Speed = GameManager::Get().mPlayerPtr->info->Speed * 200;

	mPosition += D3DXVECTOR3(direction.x, -direction.y, direction.z) * (Speed * DXUTGetElapsedTime());
}

void Bullet::fire(const D3DXVECTOR3& start, const D3DXVECTOR3& direction)
{
	mPosition = start;
	IsFlight = true;
	D3DXVec3Normalize(&this->direction, &direction);
	D3DXMatrixRotationZ(&mRotationMatrix, atan2(direction.y, direction.x));
}

void * Bullet::operator new(size_t n)
{
	return GameManager::Get().BulletList->New(n);
}

void Bullet::operator delete(void * p)
{
	return GameManager::Get().BulletList->Delete(p);
}
