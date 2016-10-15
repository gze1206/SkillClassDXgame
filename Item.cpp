#include "DXUT.h"
#include "Item.h"
#include "SpriteRenderer.h"
#include <time.h>

Item::Item() : renderer(new SpriteRenderer()), Object(GameManager::Get().ItemList)
{
	mPosition = D3DXVECTOR3(100, 100, 0);
	srand(time(NULL));
	GameManager::print("������ ������\n");
}


Item::~Item()
{
	SAFE_DELETE(renderer);
	GameManager::print("������ ���ŵ�\n");
}

Item* Item::Respawn()
{
	float x = ((float)rand() / RAND_MAX) * 1000.f + 100.f;
	float y = ((float)rand() / RAND_MAX) * 900.f + 100.f;
	mPosition = D3DXVECTOR3(x, y, 0);
	GameManager::print("������ ������ ��\n");
	return this;
}

void Item::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}

HRESULT Item::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/item.png"));
	renderer->SetTexture(mTexturePtr);
	Respawn();
	GameManager::print("������ �ؽ��� �ε��\n");
	return S_OK;
}

void Item::Update()
{

}

void * Item::operator new(size_t n)
{
	return GameManager::Get().ItemList->New(n);
}

void Item::operator delete(void * p)
{
	return GameManager::Get().ItemList->Delete(p);
}
