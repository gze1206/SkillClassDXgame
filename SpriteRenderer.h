#pragma once
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();

	virtual void Render() override;
	virtual void Render(const RECT *pSrcRect, const D3DXVECTOR3 *pCenter, const D3DXVECTOR3 *pPosition = nullptr);

public:
	
};

