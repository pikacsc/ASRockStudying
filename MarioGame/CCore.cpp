#include "CCore.h"
#include "CMapManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"

CCore* CCore::m_pInst = NULL;

CCore::CCore()
{
}

CCore::~CCore()
{
	CMapManager::DestroyInst();
	CObjectManager::DestroyInst();
	if (!m_pInst)
	{
		printf("\nCCore : Destroyed\n");
	}
}

CCore* CCore::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CCore;
	}
	return m_pInst;
}

void CCore::DestroyInst()
{
	if (!m_pInst)
	{
		return;
	}

	delete m_pInst;
	m_pInst = nullptr;
}

bool CCore::Init()
{
	// �� �����ڸ� �ʱ�ȭ �Ѵ�. ���н� false �� ������
	if (!CMapManager::GetInst()->Init())
	{
		return false;
	}

	//������Ʈ ������ �ʱ�ȭ
	if(!CObjectManager::GetInst()->Init())
	{
		return false;
	}

	return true;
}

void CCore::Run()
{
	//CMapManager::GetInst()->Render();
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	while (true)
	{
		system("cls");

		pPlayer->Update();

		CMapManager::GetInst()->Update();
		CMapManager::GetInst()->Render();
		Sleep(100); //Sleep(�и�������) �и������� ��ŭ ����
	}
}