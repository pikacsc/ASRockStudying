#pragma once
#include "value.h"

class CStateManager
{
private:
	CStateManager();
	~CStateManager();

private:
	static CStateManager* m_pInst;
	eGAME_STATE m_eGameSate;
public:
	static CStateManager* GetInst();
	static void DestroyInst();

public:
	bool Init();
	void Update();
	void Render();
	void Run();

	eGAME_STATE GetGameState(void) const;
	void SetGameState(const eGAME_STATE& _eGameState);

	void ResetGameState();

};

