#pragma once
#include "TaskList.h"

class Bullet : public Object
{
public:
	Bullet(const D3DXVECTOR3& start, const D3DXVECTOR3& direction);
	virtual ~Bullet();

public:
	void Render() override;
	virtual HRESULT Load() override;
	virtual void Update() override;

	void fire(const D3DXVECTOR3& start, const D3DXVECTOR3& direction);

	void * operator new(size_t n);
	void operator delete(void* p);

	SpriteRenderer *renderer;
	RECT rc;

public:
	float Speed = NULL;
	D3DXVECTOR3 direction;
	bool IsFlight;
};
