#pragma once
#include "Texture.h"
#include "TaskIter.h"

class Object : public Task
{
public:
	Object(TaskList* list);
	virtual ~Object();

public:
	virtual HRESULT Load()
	{
		return S_OK;
	}

	virtual void Update()
	{

	}

	virtual void Render()
	{

	}

	const RECT& GetRect()
	{
		rc = { 0, 0, (LONG)(mTexturePtr->GetInfo().Width * scale), (LONG)(mTexturePtr->GetInfo().Height * scale) };
		rc.top += mPosition.y;
		rc.left += mPosition.x;
		rc.bottom += mPosition.y;
		rc.right += mPosition.x;
		return rc;
	}

	bool IsHit(Object* obj);
	bool IsHit(TaskList* list);

	D3DXVECTOR3 mPosition;
	float scale = 1.f;

protected:
	D3DXMATRIX mWorldTM;
	D3DXMATRIX mRotationMatrix;
	RECT rc;
	shared_ptr<Texture> mTexturePtr;
};

