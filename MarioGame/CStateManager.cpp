#include "CStateManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CMapManager.h"

CStateManager* CStateManager::m_pInst = nullptr;

CStateManager::CStateManager()
	:m_eGameSate(eGAME_STATE::GAME_RETRY)
{
}

CStateManager::~CStateManager()
{
}

CStateManager* CStateManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CStateManager;
	}
	return m_pInst;
}

void CStateManager::DestroyInst()
{
	if (!m_pInst)
	{
		return;
	}
	delete m_pInst;
	m_pInst = nullptr;
}

bool CStateManager::Init()
{
	return true;
}

void CStateManager::Update()
{
	POINT playerPos = CObjectManager::GetInst()->GetPlayer()->GetPos();
	CStage* cStage = CMapManager::GetInst()->GetSelectStage();
	POINT goalPos = cStage->GetGoalPos();
	CPlayer* player = CObjectManager::GetInst()->GetPlayer();

	//game over check
	if (playerPos.y >= g_iMAP_HEIGHT)
	{
		if (player->GetLifeCount() > 0)
		{
			player->MinusLife();
			player->ResetToStart();
			m_eGameSate = eGAME_STATE::GAME_RETRY;
			return;
		}
		else
		{
			player->ResetToStart();
			m_eGameSate = eGAME_STATE::GAME_OVER;
			return;
		}
	}

	//player win check
	if (playerPos.x == goalPos.x && playerPos.y == goalPos.y)
	{
		m_eGameSate = eGAME_STATE::GAME_STAGECLEAR;
		printf("\nGoal!!!!\n");
	}

}

static void RenderStageClear(void);
static void RenderGameOver(void);


void CStateManager::Render()
{
	if (m_eGameSate == eGAME_STATE::GAME_STAGECLEAR)
	{
		int sec = g_iLoadingSec;
		while (sec > 0)
		{
			system("cls");
			RenderStageClear();
			Sleep(1000);
			--sec;
		}
	}
	else if (m_eGameSate == eGAME_STATE::GAME_OVER)
	{
		int sec = g_iLoadingSec;
		while (sec > 0)
		{
			system("cls");
			RenderGameOver();
			Sleep(1000);
			--sec;
		}
	}
}


void CStateManager::Run()
{
	Update();
	Render();
}


eGAME_STATE CStateManager::GetGameState(void) const
{
	return m_eGameSate;
}

void CStateManager::SetGameState(const eGAME_STATE& _eGameState)
{
	m_eGameSate = _eGameState;
}

void CStateManager::ResetGameState()
{
	m_eGameSate = eGAME_STATE::GAME_RETRY;
}

static void RenderStageClear(void)
{
	std::cout << "Goal! next stage!" << std::endl;
}

static void RenderGameOver(void)
{
	std::cout << "Game Over" << std::endl;
}
