#pragma once
#include "TaskList.h"

class EnemyBullet : public Object
{
public:
	EnemyBullet(const D3DXVECTOR3& start, const D3DXVECTOR3& direction);
	virtual ~EnemyBullet();

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
