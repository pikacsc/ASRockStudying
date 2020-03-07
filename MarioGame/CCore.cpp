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
	// 맵 관리자를 초기화 한다. 실패시 false 를 리턴함
	if (!CMapManager::GetInst()->Init())
	{
		return false;
	}

	//오브젝트 관리자 초기화
	if(!CObjectManager::GetInst()->Init())
	{
		return false;
	}

	//게임 스테이트 관리자 초기화
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


		--iInput; //스테이지를 갖고있는 배열은 0번부터 시작하므로, 1 빼기
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
			Sleep(100); //Sleep(밀리세컨드) 밀리세컨드 만큼 쉬기
		}
		CStateManager::GetInst()->ResetGameState();
	}

}