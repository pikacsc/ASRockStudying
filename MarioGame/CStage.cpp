#include "CStage.h"
#include "CFileStream.h"
#include "CPlayer.h"
#include "CObjectManager.h"

enum eSTAGE_BLOCK_TYPE
{
	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4'
};

CStage::CStage()
	:m_cStage{ 0 }
{
}

CStage::~CStage()
{
	printf("\nCStage() : Destroyed\n");
}

bool CStage::Init()
{
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


static void ApplyGravity(const char(*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer);
static void ApplyPhysics(const char(*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer);
static void UpdateCoin(char(*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer);

void CStage::Update()
{
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	ApplyGravity(m_cStage, pPlayer);
	ApplyPhysics(m_cStage, pPlayer);
	UpdateCoin(m_cStage, pPlayer);


}

//중력작용, 땅위에 있는지 체크
static void ApplyGravity(const char (*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer)
{

	//플레이어의 x,y 좌표를 얻어온뒤 바로 밑에 땅인지, 허공인지 체크
	int player_iX = _pPlayer->GetX();
	int player_Bottom = _pPlayer->GetY() + 1;
	if (_cStage[player_Bottom][player_iX] != SBT_WALL)
	{
		_pPlayer->SetOnGround(false);
	}
	else
	{
		_pPlayer->SetOnGround(true);
	}
}

//물리 적용, 벽에 못통과 하게 만들기
void ApplyPhysics(const char(*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer)
{

	int player_Left = _pPlayer->GetX() - 1;
	int player_Right = _pPlayer->GetX() + 1;

	int player_iY = _pPlayer->GetY();

	if (_cStage[player_iY][player_Left] == SBT_WALL)
	{
		_pPlayer->SetLeftBlock(true);
	}
	else
	{
		_pPlayer->SetLeftBlock(false);
	}

	if (_cStage[player_iY][player_Right] == SBT_WALL)
	{
		_pPlayer->SetRightBlock(true);
	}
	else
	{
		_pPlayer->SetRightBlock(false);
	}
}

void UpdateCoin(char(*_cStage)[g_iMAP_WIDTH], CPlayer* _pPlayer)
{

	int player_iX = _pPlayer->GetX();
	int player_iY = _pPlayer->GetY();

	//코인먹었는지 체크
	if (_cStage[player_iY][player_iX] == SBT_COIN)
	{
		_cStage[player_iY][player_iX] = SBT_ROAD;
		_pPlayer->PlusCoin();
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

	//플레이어의 x,y 좌표를 얻어온다
	int player_iX = pPlayer->GetX();
	int player_iY = pPlayer->GetY();

	// 맵의 출력은 플레이어의 위치를 중심으로 출력
	// 세로는 플레이어 2칸위부터 한칸 아래까지 출력
	// 총 4줄이 출력되는것이다
	// 가로는 플레이어 위치부터 오른쪽 10칸 까지 출력함
	constexpr int iClientPadding_left		= 0;
	constexpr int iClientPadding_Top		= -2;
	constexpr int iClientPadding_Right		= 9;
	constexpr int iClientPadding_Bottom		= 1;

	int iClientHeight_start = player_iY + iClientPadding_Top;
	int iClientHeight_end = player_iY + iClientPadding_Bottom;
	int iClientWidth_start = player_iX + iClientPadding_left;
	int iClientWidth_end = player_iX + iClientPadding_Right;


	for (int i = iClientHeight_start; i <= iClientHeight_end; ++i)
	{
		for (int j = iClientWidth_start; j < iClientWidth_end; ++j)
		{
			if (i == player_iY  && j == player_iX)
			{
				std::cout << "§";
			}
			else if (m_cStage[i][j] == SBT_WALL)
			{
				std::cout << "■";
			}
			else if (m_cStage[i][j] == SBT_ROAD)
			{
				std::cout << "  ";
			}
			else if (m_cStage[i][j] == SBT_START)
			{
				std::cout << "☆";
			}
			else if (m_cStage[i][j] == SBT_END)
			{
				std::cout << "★";
			}
			else if (m_cStage[i][j] == SBT_COIN)
			{
				std::cout << "◎";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "coin : "<< player_Coin << std::endl;
}

