#pragma once
#include "Object.h"
#include "Texture.h"

class SpriteRenderer;

class Item :
	public Object
{
public:
	Item();
	virtual ~Item();

public:
	Item* Respawn();
	virtual void Render() override;
	virtual HRESULT Load() override;
	virtual void Update() override;

	void * operator new(size_t n);
	void operator delete(void* p);

	SpriteRenderer *renderer;
	RECT rc;
};

