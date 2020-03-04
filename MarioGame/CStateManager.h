#pragma once
#include "value.h"

class CStateManager
{
private:
	CStateManager();
	~CStateManager();

private:
	static CStateManager* m_pInst;
	
	bool	m_bPlayerWin;
	bool	m_bGameOver;
public:
	static CStateManager* GetInst();
	static void DestroyInst();

public:
	bool Init();
	void Update();
	void Render();
	void Run();

	bool IsPlayerWin();
	bool IsGameOver();

	void ResetGameState();
};

