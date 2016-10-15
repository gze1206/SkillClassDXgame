#pragma once

enum BulletPattern
{
	None = 0,
	Straight,
	FourWay,
	Xross,
	FourWayToXross,
};

class Monster : public Object
{
public:
	Monster(D3DXVECTOR3 pos, CharacterInfo* _info,wstring sprite, BulletPattern ptr = None,float size = 0.25f, wstring music = L"N/A");
	//하스스톤으로 치면 전투의 함성같은 녀석
	virtual void InitMonster();
	//하스스톤으로 치면 죽음의 메아리같은 녀석
	virtual void DeleteMonster();
	virtual ~Monster();

public:
	virtual HRESULT Load() override;
	virtual void Update() override;
	virtual void Render() override;
	CharacterInfo* GetInfo()
	{
		return info;
	}
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
	void Fire();

	void * operator new(size_t n);
	void operator delete(void* p);

public:
	wstring MusicName = L"N/A";
	wstring SpriteName = L"N/A";
	bool IsMove = true, HP_IS_LOW = false;
	D3DXVECTOR3 direction, start;
	BulletPattern Pattern = BulletPattern::None;
	float ShootCoolDown = 0.f;

protected:
	SpriteRenderer *renderer;
	SpriteRenderer *HPrenderer;
	shared_ptr<Texture> HpTexture;
	CharacterInfo *info;
	int shot_cnt = 0;
};