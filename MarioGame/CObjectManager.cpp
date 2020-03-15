#include "value.h"
#include "CStage.h"
#include "CMapManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CBullet.h"

CObjectManager* CObjectManager::m_pInst = nullptr;

CObjectManager::CObjectManager()
	:m_pPlayer(nullptr)
{
}

CObjectManager::~CObjectManager()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;

	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		delete m_pBullet[i];
		m_pBullet[i] = nullptr;
	}

}

CObjectManager* CObjectManager::GetInst()
{
	if (!m_pInst)
	{
		m_pInst = new CObjectManager;
	}
	return m_pInst;
}

void CObjectManager::DestroyInst()
{
	if (!m_pInst)
	{
		return;
	}

	delete m_pInst;
	m_pInst = nullptr;
}

CPlayer* CObjectManager::GetPlayer() const
{
	return m_pPlayer;
}


bool CObjectManager::Init()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
	}
	m_pPlayer->Init();

	/*
	1�� ���ڿ� ���� ������ �޸� �ּҸ� �־��ش�.
	3�� ���ڴ� ���� ������ �޸� ũ�⸦ �־��ش�.
	�̷��� ���ָ� 1���� �־��� �ּҺ��� 3���� �־��� �޸� ũ�⸸ŭ
	2�����ڿ� �� ������ �޸𸮸� �ʱ�ȭ ���ش�.
	*/
	memset(m_pBullet, 0, sizeof(CBullet*) * g_iBULLET_COUNT_MAX);
	m_iCurBulletCount = 0;

	return true;
}

void CObjectManager::Update()
{
	m_pPlayer->Update();

	for (int i = 0; i < m_iCurBulletCount;++i)
	{
		m_pBullet[i]->Update();
	}

	for (int i = 0; i < m_iCurBulletCount;)
	{
		if (m_pBullet[i] == nullptr)
		{
			continue;
		}

		//�Ѿ��� �����Ǿ�� �� ���
		if (!m_pBullet[i]->GetEnable())
		{
			delete m_pBullet[i];
			for (int j = i; j < m_iCurBulletCount - 1; ++j)
			{
				m_pBullet[j] = m_pBullet[j + 1];
			}

			m_pBullet[m_iCurBulletCount - 1] = NULL;
			--m_iCurBulletCount;
		}
		// �Ѿ��� �������� ���� ��� i�� ���� ��Ų��.
		else
		{
			++i;
		}
	}

}

void CObjectManager::Render()
{
	m_pPlayer->Render();
}

void CObjectManager::InitPlayerStartPos(void)
{
	CStage* selectStage = CMapManager::GetInst()->GetSelectStage();
	m_pPlayer->SetPos(selectStage->GetStartPos());
	m_pPlayer->SetLifeCount(g_iLIFE_DEFAULT);
}

bool CObjectManager::CreateBullet(POINT tPos)
{
	// �Ѿ� ������ ������ �Ѿ��� �̹� �ִ�ġ��� ���̻� �������� �ʴ´�.
	if (m_iCurBulletCount == g_iBULLET_COUNT_MAX)
	{
		return false;
	}

	// �Ѿ� ����
	CBullet* pBullet = new CBullet;

	// �Ѿ� �ʱ�ȭ, �ʱ�ȭ ���н� ������ �Ѿ��� �����
	// false�� ��ȯ
	if (!pBullet->Init())
	{
		delete pBullet;
		pBullet = nullptr;
		return false;
	}

	// ���ڷ� ���� ��ġ�� �Ѿ��� ��ġ�� �����Ѵ�.
	pBullet->SetBulletPos(tPos);

	m_pBullet[m_iCurBulletCount] = pBullet;
	++m_iCurBulletCount;

	return true;
}

// �ش� ��ġ�� �Ѿ��� �ִ����� �Ѿ� ��Ͽ��� �˻����ش�. 
// ������ true, ������ false�� ��ȯ�ϰ� �Ͽ� �ش���ġ�� �Ѿ��� �ִ����� �Ǵ��Ѵ�
bool CObjectManager::CheckBullet(int _iX, int _iY)
{
	//���� �Ѿ��� �߰��� ����ŭ �ݺ��ϸ� �� �Ѿ˵��� ��ġ�� üũ�Ѵ�.
	for (int i = 0; i < m_iCurBulletCount; ++i)
	{
		//�Ѿ��� ��ġ�� ���ڷ� ���� ��ġ�� ���ٸ� �Ѿ��̹Ƿ�, true�� �����Ѵ�.
		if ((m_pBullet[i]->GetBulletPos().x == _iX) && m_pBullet[i]->GetBulletPos().y == _iY)
		{
			return true;
		}
	}

	return false;
}
