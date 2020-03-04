#include "value.h"
#include "CStage.h"
#include "CMapManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"

CObjectManager* CObjectManager::m_pInst = nullptr;

CObjectManager::CObjectManager()
	:m_pPlayer(nullptr)
{
}

CObjectManager::~CObjectManager()
{
}

CObjectManager* CObjectManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CObjectManager;
	}
	return m_pInst;
}

void CObjectManager::DestroyInst()
{
	if (!m_pInst)
	{
		return;
	}

	delete m_pInst;
	m_pInst = nullptr;
}

CPlayer* CObjectManager::GetPlayer() const
{
	return m_pPlayer;
}

bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();

	return true;
}

void CObjectManager::Update()
{
	m_pPlayer->Update();
}

void CObjectManager::InitPlayerStartPos(void)
{
	CStage* selectStage = CMapManager::GetInst()->GetSelectStage();
	m_pPlayer->SetPos(selectStage->GetStartPos());
}
