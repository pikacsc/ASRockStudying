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
	// 가장 위에 하는것이 아닌 해당 타입을 사용하고자 할때 전방선언을
	// 해줄 수도 있다.
	class CPlayer* m_pPlayer;

public:
	class CPlayer* GetPlayer() const;

public:
	bool Init();
};

