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

	//전체 게임을 초기화 하는 역할
	bool Init();

	void Run();
};

