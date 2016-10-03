#pragma once
class Monster : public Object
{
public:
	Monster(string name, D3DXVECTOR3 pos, float speed, int hp, int dmg, wstring sprite, wstring music = L"N/A");
	//�Ͻ��������� ġ�� ������ �Լ����� �༮
	virtual void InitMonster();
	//�Ͻ��������� ġ�� ������ �޾Ƹ����� �༮
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

public:
	wstring MusicName = L"N/A";
	wstring SpriteName = L"N/A";
	bool IsMove = true;
	D3DXVECTOR3 Destination;

protected:
	SpriteRenderer *renderer;
	CharacterInfo *info;
};