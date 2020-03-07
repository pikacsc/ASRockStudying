#include "CMapManager.h"
#include "CStateManager.h"
#include "CStage.h"

CMapManager* CMapManager::m_pInst = nullptr;
const char CMapManager::m_StageNameArr[][g_iSTAGENAME_MAX] = { "Stage1.txt", "Stage2.txt", "Stage3.txt" };

CMapManager::CMapManager()
	:m_pStage{},m_iSelectStageNum(0)
{
	for (int i = 0; i < g_iSTAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = nullptr;
	}
}

CMapManager::~CMapManager()
{
	//스테이지 메모리 해제
	for (int i = 0; i < g_iSTAGE_MAX_COUNT; ++i)
	{
		delete m_pStage[i];
		m_pStage[i] = nullptr;
	}
	printf("\nCMapManager() : Destroyed\n");
}

CMapManager* CMapManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CMapManager;
	}
	return m_pInst;
}

void CMapManager::DestroyInst()
{
	if (!m_pInst)
	{
		return;
	}

	delete m_pInst;
	m_pInst = nullptr;
}


bool CMapManager::Init()
{
	//모든맵 초기화
	for (int i = 0; i < g_iSTAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = new CStage;
		
		if (!m_pStage[i]->ReadFile(m_StageNameArr[i]))
		{
			printf("\nMapManager::init() failed\n");
			return false;
		}
		m_pStage[i]->Init();
	}
	
	return true;
}

void CMapManager::Update()
{
	//m_pStage[m_iSelectStageNum]->Update();
}

void CMapManager::Render()
{
	if (CStateManager::GetInst()->GetGameState() == eGAME_STATE::GAME_OVER)
	{
		return;
	}
	if (CStateManager::GetInst()->GetGameState() == eGAME_STATE::GAME_STAGECLEAR)
	{
		return;
	}
	m_pStage[m_iSelectStageNum]->Render();
}

void CMapManager::Run()
{
}

void CMapManager::SetSelectStage(int _iStageNum)
{
	m_iSelectStageNum = _iStageNum;
}

CStage* CMapManager::GetSelectStage(void) const
{
	return m_pStage[m_iSelectStageNum];
}
