#include "CStage.h"
#include "CFileStream.h"
#include "CPlayer.h"
#include "CObjectManager.h"


CStage::CStage()
	:m_cStage{ 0 }, m_startPOS(POINT{ 0,0 }), m_goalPOS(POINT{ 0,0 })
{
	Init();
}

CStage::~CStage()
{
	printf("\nCStage() : Destroyed\n");
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
