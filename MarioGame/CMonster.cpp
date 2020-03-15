#include "CMonster.h"
#include "CStage.h"
#include "CMapManager.h"

CMonster::CMonster()
	:m_tPos(POINT{ 0,0 }), //몬스터 처음 위치
	m_iDir(MON_DIR_LEFT) //몬스터 방향
{
}

CMonster::~CMonster()
{
}

void CMonster::SetPos(const POINT& _pos)
{
	m_tPos = _pos;
}

void CMonster::SetPosByXY(int _iX, int _iY)
{
	m_tPos.x = _iX;
	m_tPos.y = _iY;
}

void CMonster::SetX(int _iX)
{
	m_tPos.x = _iX;
}

void CMonster::SetY(int _iY)
{
	m_tPos.y = _iY;
}

POINT CMonster::GetPos(void) const
{
	return m_tPos;
}

int CMonster::GetX(void) const
{
	return m_tPos.x;
}

int CMonster::GetY(void) const
{
	return m_tPos.y;
}

bool CMonster::Init(void)
{

	return true;
}

void CMonster::Update(void)
{
	// 움직일 다음칸 아래가(즉, 움직인 칸의 발밑) 떨어지는 곳이라면
	// 방향을 바꿔준다.
	CStage* pStage = CMapManager::GetInst()->GetSelectStage();

	if (pStage->GetBlockByXY(m_tPos.x + m_iDir, m_tPos.y + 1) != eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		// 방향을 반대방향으로 바꿔주도록 한다.
		m_iDir *= -1;
	}
	else if (pStage->GetBlockByXY(m_tPos.x + m_iDir, m_tPos.y) == eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		m_iDir *= -1;
	}

	// 몬스터 움직이기
	m_tPos.x += m_iDir;
}
