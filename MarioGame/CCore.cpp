#include "CCore.h"
#include "CMapManager.h"
#include "CObjectManager.h"
#include "CStateManager.h"
#include "CPlayer.h"
#include <conio.h>

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

	//���� ������Ʈ ������ �ʱ�ȭ
	if (!CStateManager::GetInst()->Init())
	{
		return false;
	}

	return true;
}

void CCore::Run()
{
	bool bSystemLoop = true;
	bool bPlayLoop = true;
	while (bSystemLoop)
	{
		system("cls");
		int iInput = 0;
		std::cout << "Stage Select" << std::endl;
		std::cout << "1. Stage1" << std::endl;
		std::cout << "2. Stage2" << std::endl;
		std::cout << "3. Stage3" << std::endl;
		std::cout << "0. Quit" << std::endl << ">>";
		std::cin >> iInput;

		if (iInput > 3)
		{
			continue;
		}

		if (iInput == 0)
		{
			break;
		}


		--iInput; //���������� �����ִ� �迭�� 0������ �����ϹǷ�, 1 ����
		CMapManager::GetInst()->SetSelectStage(iInput);
		CObjectManager::GetInst()->InitPlayerStartPos();
		CStateManager::GetInst()->ResetGameState();
		bPlayLoop = true;
		while (bPlayLoop)
		{
			CStateManager::GetInst()->Update();
			eGAME_STATE gameState = CStateManager::GetInst()->GetGameState();
			system("cls");
			if (gameState == eGAME_STATE::GAME_OVER)
			{
				CStateManager::GetInst()->Render();
				break;
			}
			else if (gameState == eGAME_STATE::GAME_STAGECLEAR)
			{
				CStateManager::GetInst()->Render();
				break;
			}
			else if (gameState == eGAME_STATE::GAME_RETRY)
			{
				CMapManager::GetInst()->Render();
				CObjectManager::GetInst()->Update();
				CObjectManager::GetInst()->Render();
			}
			Sleep(100); //Sleep(�и�������) �и������� ��ŭ ����
		}
		CStateManager::GetInst()->ResetGameState();
	}

}