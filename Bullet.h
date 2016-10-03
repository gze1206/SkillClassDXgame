#pragma once

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Render() override;
	virtual HRESULT Load() override;
	virtual void Update() override;

	void fire(const D3DXVECTOR3& start, const D3DXVECTOR3& direction);

	SpriteRenderer *renderer;
	RECT rc;

public:
	float Speed = NULL;
	D3DXVECTOR3 direction;
	bool IsFlight;
};

