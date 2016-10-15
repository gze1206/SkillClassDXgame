#pragma once
#include "Object.h"
#include "Texture.h"
#include "Item.h"

class SpriteRenderer;
struct CharacterInfo;
enum Rotate;

class Player :
	public Object
{
public:
	Player();
	virtual ~Player();

public:
	virtual HRESULT Load() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetInfo(CharacterInfo* InfoPtr)
	{
		info = InfoPtr;
	}

	void SwapInfo(CharacterInfo* InfoPtr)
	{
		CharacterInfo* temp = info;
		info = InfoPtr;
		InfoPtr = temp;
		SAFE_DELETE(temp);
	}

	void Respawn();

	void * operator new(size_t n);
	void operator delete(void* p);

public:
	CharacterInfo *info;
	D3DXVECTOR3 direction;
	int GotItem = 0;
	Rotate rot;
	float ShootCoolDown = 0.f;

protected:
	SpriteRenderer *renderer;
	SpriteRenderer *HPrenderer;
	shared_ptr<Texture> HpTexture;
};

