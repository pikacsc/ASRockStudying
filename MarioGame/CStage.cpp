#include "CStage.h"
#include "CFileStream.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CObjectManager.h"
#include "CMonster.h"


CStage::CStage()
	:m_cStage{ 0 }, 
	m_startPOS(POINT{ 0,0 }), 
	m_goalPOS(POINT{ 0,0 }), 
	m_pMonsterArray(nullptr), 
	m_iMonsterCount(0),
	m_iMonsterArrayCount(0)
{
	Init();
}

CStage::~CStage()
{
	printf("\nCStage() : Destroyed\n");
	for (int i = 0; i < m_iMonsterCount; ++i)
	{
		delete m_pMonsterArray[i];
		m_pMonsterArray[i] = nullptr;
	}
	delete[] m_pMonsterArray;
}

bool CStage::Init()
{
	if (m_cStage[0][0] == 0)
	{
		return false;
	}
	for (int i = 0; i < g_iMAP_HEIGHT; ++i)
	{
		for (int j = 0; j < g_iMAP_WIDTH; ++j)
		{
			if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_START))
			{
				m_startPOS = POINT{ j,i };
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_END))
			{
				m_goalPOS = POINT{ j,i };
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_MONSTER))
			{
				CreateMonster(j, i);

				// 몬스터 위치를 체크하여 몬스터 생성만 하고 SBT_ROAD로 실제 맵을 바꿔준다.
				m_cStage[i][j] = static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_ROAD);
			}
		}
	}
	return true;
}

bool CStage::ReadFile(const char* _pFileName)
{
	CFileStream file;

	if (!file.OpenFile(_pFileName, "rt"))
	{
		return false;
	}

	for (int i = 0; i < g_iMAP_HEIGHT; ++i)
	{
		int iSize = 0;
		file.ReadLine(m_cStage[i], iSize);
	}


	return true;
}

void CStage::Update()
{
	for (int i = 0; i < m_iMonsterCount; ++i)
	{
		m_pMonsterArray[i]->Update();
	}

}

void CStage::Render()
{
	/*
	맵은 스크톨 처리하여, 현재 플레이어가 이동한 위치로부터 맵을 출력해줌
	출력 크기는 세로 4칸 가로 10칸으로 해줌
	0 : 벽
	1 : 길
	2 : 시작점
	3 : 도착점
	4 : 코인
	*/
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	
	int player_Coin = pPlayer->GetCoin();
	int player_Life = pPlayer->GetLifeCount();

	//플레이어의 x,y 좌표를 얻어온다
	int player_iX = pPlayer->GetX();
	int player_iY = pPlayer->GetY();

	// 맵의 출력은 플레이어의 위치를 중심으로 출력
	// 세로는 플레이어 2칸위부터 한칸 아래까지 출력
	// 총 4줄이 출력되는것이다
	// 가로는 플레이어 위치부터 오른쪽 10칸 까지 출력함
	constexpr int iClientPadding_left		= -2;
	constexpr int iClientPadding_Top		= -2;
	constexpr int iClientPadding_Right		= 9;
	constexpr int iClientPadding_Bottom		= 1;

	int iClientHeight_start = player_iY + iClientPadding_Top;
	int iClientHeight_end = player_iY + iClientPadding_Bottom;
	int iClientWidth_start = player_iX + iClientPadding_left;
	int iClientWidth_end = player_iX + iClientPadding_Right;


	//맵 끝에 거의 도달했을때 가로 스크롤 멈춤
	if (iClientWidth_start >= g_iMAP_WIDTH - iClientPadding_Right)
	{
		iClientWidth_start = g_iMAP_WIDTH - iClientPadding_Right;
	}

	if (iClientWidth_end > g_iMAP_WIDTH)
	{
		iClientWidth_end = g_iMAP_WIDTH;
	}
	
	//세로 스크롤 멈춤
	if (iClientHeight_start < 0)
	{
		iClientHeight_start = 0;
	}

	if (iClientHeight_end > g_iMAP_HEIGHT)
	{
		iClientHeight_end = g_iMAP_HEIGHT + iClientPadding_Bottom;
	}


	for (int i = iClientHeight_start; i <= iClientHeight_end; ++i)
	{
		for (int j = iClientWidth_start; j < iClientWidth_end; ++j)
		{
			if (i == player_iY  && j == player_iX)
			{
				std::cout << "§";
			}
			// 현재위치에 총알이 있을 경우 총알로 출력한다.
			else if (CObjectManager::GetInst()->CheckBullet(j, i))
			{
				std::cout << "™";
			}
			// 몬스터가 현재 위치에 있다면 몬스터로 출력한다.
			else if (CheckMonster(j, i))
			{
				std::cout << "◆";
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_WALL))
			{
				std::cout << "■";
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_ROAD))
			{
				std::cout << "  ";
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_START))
			{
				std::cout << "☆";
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_END))
			{
				std::cout << "★";
			}
			else if (m_cStage[i][j] == static_cast<char>(eSTAGE_BLOCK_TYPE::SBT_COIN))
			{
				std::cout << "◎";
			}
		}
		std::cout << std::endl;
	}
}

eSTAGE_BLOCK_TYPE CStage::GetBlockByPos(const POINT& _pos) const
{
	return static_cast<eSTAGE_BLOCK_TYPE>(m_cStage[_pos.y][_pos.x]);
}

eSTAGE_BLOCK_TYPE CStage::GetBlockByXY(int _x, int _y) const
{
	eSTAGE_BLOCK_TYPE block = static_cast<eSTAGE_BLOCK_TYPE>(m_cStage[_y][_x]);
	return block;
}

void CStage::SetBlockByPos(const POINT& _pos, const eSTAGE_BLOCK_TYPE& _block)
{
	m_cStage[_pos.y][_pos.x] = static_cast<char>(_block);
}

void CStage::SetBlockByXY(int _x, int _y, const eSTAGE_BLOCK_TYPE& _block)
{
	m_cStage[_y][_x] = static_cast<char>(_block);
}



POINT CStage::GetGoalPos(void) const
{
	return m_goalPOS;
}

POINT CStage::GetStartPos(void) const
{
	return m_startPOS;
}

CMonster* CStage::CreateMonster(int _iX, int _iY)
{
	// 배열이 동적할당 되지 않았을 경우 동적할당 해준다.
	if (!m_pMonsterArray)
	{
		m_iMonsterArrayCount = 3;
		m_pMonsterArray = new CMonster * [m_iMonsterArrayCount];
	}

	// 만약 몬스터가 꽉 차있을 경우 배열을 늘려준다.
	if (m_iMonsterCount == m_iMonsterArrayCount)
	{
		//공간을 늘려서 할당해준다. 2배만큼 공간을 늘려준다.
		m_iMonsterArrayCount *= 2;
		CMonster** ppArray = new CMonster * [m_iMonsterArrayCount];

		// 기존에 있는 주소 정보를 이배열로 옮겨준다.
		// memcpy : 메모리 복사 함수이다.
		//1번인자에 들어간 메모리 주소에 2번인자에 들어간 메모리 주소로부터
		//3번인자에 들어간 바이트 수만큼 메모리를 복사한다.
		//몬스터가 꽉찼다면 기존 배열은 이미 가득 차있다.
		//그래서 위에서 공간을 2배만큼 동적 배열로 할당해주고
		//아래에서 새로 할당한 공간이 예를들어 20개 라면 기존 공간은
		//10개이다. 기존 공간의(2번인자) 동적할당된 메모리 주소들을
		//새로 할당된 공간으로 10개만큼 복사해주는 것이다.
		memcpy(ppArray, m_pMonsterArray, sizeof(CMonster*) * m_iMonsterCount);
		delete[] m_pMonsterArray;
		m_pMonsterArray = ppArray;
	}

	// 실제 몬스터 객체를 할당한다.
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init())
	{
		delete pMonster;
		pMonster = nullptr;
	}

	// 몬스터 위치정보를 설정한다.
	pMonster->SetPosByXY(_iX, _iY);

	// 몬스터 배열에 넣어준다.
	m_pMonsterArray[m_iMonsterCount] = pMonster;
	++m_iMonsterCount;

	return pMonster;
}

bool CStage::CheckMonster(int _iX, int _iY)
{
	for (int i = 0; i < m_iMonsterCount; ++i)
	{
		if (m_pMonsterArray[i]->GetPos().x == _iX &&
			m_pMonsterArray[i]->GetPos().y == _iY)
		{
			return true;
		}
	}

	return false;
}

int CStage::GetMonsterCount(void) const
{
	return m_iMonsterCount;
}

CMonster* CStage::GetMonster(int idx) const
{
	return m_pMonsterArray[idx];
}

void CStage::DeleteMonster(int _idx)
{
	delete m_pMonsterArray[_idx];

	for (int i = _idx; i < m_iMonsterCount - 1; ++i)
	{
		m_pMonsterArray[i] = m_pMonsterArray[i + 1];
	}
	m_pMonsterArray[m_iMonsterCount - 1] = nullptr;

	--m_iMonsterCount;
}
