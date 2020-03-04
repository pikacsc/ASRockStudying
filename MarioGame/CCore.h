#pragma once

#include "value.h"

class CCore
{
private:
	CCore();
	~CCore();

private:
	static CCore* m_pInst;

public:
	static CCore* GetInst();
	static void DestroyInst();

public:

	//��ü ������ �ʱ�ȭ �ϴ� ����
	bool Init();

	void Run();
};

