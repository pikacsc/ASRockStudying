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
	//스테이지를 얻어온다.
	CStage* pStage = CMapManager::GetInst()->GetSelectStage();

	// 총알이 이동할 위치를 구해준다.
	POINT	tNextPos = m_tBulletPos;
	tNextPos.x++;

	bool IsOverlapMonster = NULL;
	bool IsOverlapMonster_next = NULL;
	// 현재 살아있는 몬스터를 얻어와서 위치가 같은지 체크한다.
	for (int i = 0; i < pStage->GetMonsterCount(); ++i)
	{
		CMonster* pMonster = pStage->GetMonster(i);

		POINT tMonsterPos = pMonster->GetPos();
		bool IsOverlapMonster = tMonsterPos.x == m_tBulletPos.x && tMonsterPos.y == m_tBulletPos.y;
		bool IsOverlapMonster_next = tMonsterPos.x == tNextPos.x && tMonsterPos.y == tNextPos.y;
		
		if (IsOverlapMonster || IsOverlapMonster_next)
		{
			//몬스터를 목록에서 삭제한다.
			pStage->DeleteMonster(i);

			// 총알의 남은거리를 0으로 만들어서 삭제되도록 한다.
			m_iRange = 0;
			return;
		}
	}


	// 총알이 한칸 앞으로 나아가기 전에 현재 총알 위치의 다음칸 즉 총알이
	// 나아가야할 위치에 만약 벽이 있다면 더 이상 나가지 못하고 총알을
	// 삭제하게 한다.
	if (pStage->GetBlockByXY(m_tBulletPos.x + 1, m_tBulletPos.y) != eSTAGE_BLOCK_TYPE::SBT_WALL) // 벽이 아닐경우
	{
		//매번 총알을 오른쪽으로 한칸 이동시킴
		m_iRange--;
		m_tBulletPos.x++;
	}
	else //벽일 경우
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
	//0이 아닌 경우는 아직 총알이 더 나아갈 수 있는 상태이기 때문에
	//true를 리턴하고 0일 경우는 총알이 나갈 수 있는 사정거리 까지
	//모두 나갔기 때문에 false를 리턴하여 총알을 삭제해준다.
	return m_iRange != 0;
}
