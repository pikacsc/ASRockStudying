#pragma once
#include "value.h"

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

public:
	class CPlayer* GetPlayer() const;

public:
	bool Init();
};

