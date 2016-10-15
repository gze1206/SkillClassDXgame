#include "DXUT.h"
#include "SpriteRenderer.h"
#include "Texture.h"

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Render()
{
	if (SUCCEEDED(sD3DxSpritePtr->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		sD3DxSpritePtr->Draw(mTexturePtr->Get(), nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255,255,255));
		sD3DxSpritePtr->End();
	}
}

void SpriteRenderer::Render(const RECT * pSrcRect, const D3DXVECTOR3 * pCenter, const D3DXVECTOR3 * pPosition)
{
	if (SUCCEEDED(sD3DxSpritePtr->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		sD3DxSpritePtr->Draw(mTexturePtr->Get(), pSrcRect, pCenter, pPosition, D3DCOLOR_XRGB(255, 255, 255));
		sD3DxSpritePtr->End();
	}
}
