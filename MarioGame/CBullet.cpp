#include "CBullet.h"
#include "CPlayer.h"
#include "CObjectManager.h"
#include "CStage.h"
#include "CMonster.h"
#include "CMapManager.h"

CBullet::CBullet()
	:m_iDamage(0),m_iRange(g_iBULLET_RANGE_DEFAULT),m_tBulletPos(POINT{0,0}),m_bOnFire(false)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	return true;
}

void CBullet::Update()
{
	//���������� ���´�.
	CStage* pStage = CMapManager::GetInst()->GetSelectStage();

	// �Ѿ��� �̵��� ��ġ�� �����ش�.
	POINT	tNextPos = m_tBulletPos;
	tNextPos.x++;

	bool IsOverlapMonster = NULL;
	bool IsOverlapMonster_next = NULL;
	// ���� ����ִ� ���͸� ���ͼ� ��ġ�� ������ üũ�Ѵ�.
	for (int i = 0; i < pStage->GetMonsterCount(); ++i)
	{
		CMonster* pMonster = pStage->GetMonster(i);

		POINT tMonsterPos = pMonster->GetPos();
		bool IsOverlapMonster = tMonsterPos.x == m_tBulletPos.x && tMonsterPos.y == m_tBulletPos.y;
		bool IsOverlapMonster_next = tMonsterPos.x == tNextPos.x && tMonsterPos.y == tNextPos.y;
		
		if (IsOverlapMonster || IsOverlapMonster_next)
		{
			//���͸� ��Ͽ��� �����Ѵ�.
			pStage->DeleteMonster(i);

			// �Ѿ��� �����Ÿ��� 0���� ���� �����ǵ��� �Ѵ�.
			m_iRange = 0;
			return;
		}
	}


	// �Ѿ��� ��ĭ ������ ���ư��� ���� ���� �Ѿ� ��ġ�� ����ĭ �� �Ѿ���
	// ���ư����� ��ġ�� ���� ���� �ִٸ� �� �̻� ������ ���ϰ� �Ѿ���
	// �����ϰ� �Ѵ�.
	if (pStage->GetBlockByXY(m_tBulletPos.x + 1, m_tBulletPos.y) != eSTAGE_BLOCK_TYPE::SBT_WALL) // ���� �ƴҰ��
	{
		//�Ź� �Ѿ��� ���������� ��ĭ �̵���Ŵ
		m_iRange--;
		m_tBulletPos.x++;
	}
	else //���� ���
	{
		m_iRange = 0;
	}

}

int CBullet::GetRange(void) const
{
	return m_iRange;
}

void CBullet::SetRange(int _iRange)
{
	m_iRange = _iRange;
}

POINT CBullet::GetBulletPos(void) const
{
	return m_tBulletPos;
}

void CBullet::SetBulletPos(const POINT& _tBulletPos)
{
	m_tBulletPos = _tBulletPos;
}

void CBullet::SetBulletByXY(LONG _x, LONG _y)
{
	m_tBulletPos.x = _x;
	m_tBulletPos.y = _y;
}

int CBullet::GetDamage(void) const
{
	return m_iDamage;
}

void CBullet::SetDamage(int _iDamage)
{
	m_iDamage = _iDamage;
}

void CBullet::SetOnFire(bool _bOnFire)
{
	m_bOnFire = _bOnFire;
}

bool CBullet::GetOnFire(void) const
{
	return m_bOnFire;
}

bool CBullet::GetEnable(void) const
{
	//0�� �ƴ� ���� ���� �Ѿ��� �� ���ư� �� �ִ� �����̱� ������
	//true�� �����ϰ� 0�� ���� �Ѿ��� ���� �� �ִ� �����Ÿ� ����
	//��� ������ ������ false�� �����Ͽ� �Ѿ��� �������ش�.
	return m_iRange != 0;
}
