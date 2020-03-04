#include "CStateManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CMapManager.h"

CStateManager* CStateManager::m_pInst = nullptr;

CStateManager::CStateManager()
	:m_bGameOver(false),m_bPlayerWin(false)
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

	//game over check
	if (playerPos.y >= g_iMAP_HEIGHT)
	{
		m_bGameOver = true;
	}

	//player win check
	if (playerPos.x == goalPos.x && playerPos.y == goalPos.y)
	{
		m_bPlayerWin = true;
	}

}

static void RenderPlayerWin(void);
static void RenderGameOver(void);


void CStateManager::Render()
{
	if (IsPlayerWin())
	{
		RenderPlayerWin();
	}
	if (IsGameOver())
	{
		RenderGameOver();
	}
}


void CStateManager::Run()
{
}

bool CStateManager::IsPlayerWin()
{
	return m_bPlayerWin;
}

bool CStateManager::IsGameOver()
{
	return m_bGameOver;
}

void CStateManager::ResetGameState()
{
	m_bGameOver = false;
	m_bPlayerWin = false;
}

void RenderPlayerWin(void)
{
	std::cout << "Goal!!!!" << std::endl;
}

void RenderGameOver(void)
{
	std::cout << "Game Over" << std::endl;
}
