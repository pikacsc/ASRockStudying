#pragma once
#include "value.h"
class CStage;
class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	static CObjectManager* m_pInst;

public:
	static CObjectManager* GetInst();

	static void DestroyInst();

private:
	// ���� ���� �ϴ°��� �ƴ� �ش� Ÿ���� ����ϰ��� �Ҷ� ���漱����
	// ���� ���� �ִ�.
	class CPlayer* m_pPlayer;
	class CBullet* m_pBullet[g_iBULLET_COUNT_MAX];
	int			   m_iCurBulletCount;

public:
	class CPlayer* GetPlayer() const;

public:
	bool Init();
	void Update();
	void Render();
	
	void InitPlayerStartPos(void);
	bool CreateBullet(POINT tPos);
	bool CheckBullet(int x, int y);
};

