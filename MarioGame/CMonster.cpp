#include "CMonster.h"
#include "CStage.h"
#include "CMapManager.h"

CMonster::CMonster()
	:m_tPos(POINT{ 0,0 }), //���� ó�� ��ġ
	m_iDir(MON_DIR_LEFT) //���� ����
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
	// ������ ����ĭ �Ʒ���(��, ������ ĭ�� �߹�) �������� ���̶��
	// ������ �ٲ��ش�.
	CStage* pStage = CMapManager::GetInst()->GetSelectStage();

	if (pStage->GetBlockByXY(m_tPos.x + m_iDir, m_tPos.y + 1) != eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		// ������ �ݴ�������� �ٲ��ֵ��� �Ѵ�.
		m_iDir *= -1;
	}
	else if (pStage->GetBlockByXY(m_tPos.x + m_iDir, m_tPos.y) == eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		m_iDir *= -1;
	}

	// ���� �����̱�
	m_tPos.x += m_iDir;
}
