#include "CPlayer.h"
#include "value.h"

CPlayer::CPlayer()
	:m_iX(0),m_iY(0),m_bIsOnGround(true),m_iCoin(0),m_bLeftBlock(true),m_bRightBlock(false)
{

}

CPlayer::~CPlayer()
{
}

int CPlayer::GetX() const
{
	return m_iX;
}

void CPlayer::SetX(int _iX)
{
	m_iX = _iX;
}

int CPlayer::GetY() const
{
	return m_iY;
}

void CPlayer::SetY(int _iY)
{
	m_iY = _iY;
}

int CPlayer::GetCoin() const
{
	return m_iCoin;
}

void CPlayer::PlusCoin()
{
	if (m_iCoin == INT32_MAX)
	{
		return;
	}

	m_iCoin++;
}

void CPlayer::MinusCoin()
{
	if (m_iCoin <= 0)
	{
		m_iCoin = 0;
		return;
	}
	
	m_iCoin--;
}

void CPlayer::SetPosition(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}

bool CPlayer::IsOnGround() const
{
	return m_bIsOnGround;
}

void CPlayer::SetOnGround(bool _bOnGround)
{
	m_bIsOnGround = _bOnGround;
}

bool CPlayer::IsLeftBlock() const
{
	return m_bLeftBlock;
}

void CPlayer::SetLeftBlock(bool _bLeftBlock)
{
	m_bLeftBlock = _bLeftBlock;
}

bool CPlayer::IsRightBlock() const
{
	return m_bRightBlock;
}

void CPlayer::SetRightBlock(bool _bRightBlock)
{
	m_bRightBlock = _bRightBlock;
}

bool CPlayer::Init()
{
	m_iX = g_iSTART_POS_X;
	m_iY = g_iSTART_POS_Y;

	return true;
}

void CPlayer::Update()
{
	//�߷��ۿ�, �÷��̾� �ؿ� ���� ���� ��� �÷��̾� y���� ++
	if (!m_bIsOnGround)
	{
		++m_iY;
	}



	//Ű �Է��� �޴´�.
	//GeyAsyncKeyState �Լ��� Win32 API ���� �����Ǵ� Ű �Է� �Լ��̴�.
	//W Ű�� �������� �ٷ� �����ϰ� �ϱ����ؼ� 0x8000�� &������ �Ͽ�
	//������ ��� true�� ������ �ȴ�.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (IsLeftBlock()) //���ʿ� ���� ������� ������ ����
		{
			return;
		}

		--m_iX;

		if (m_iX < 0)
		{
			m_iX = 0;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (IsRightBlock()) //�����ʿ� ���� ������� ������ ����
		{
			return;
		}

		++m_iX;

		if (m_iX > g_iMAP_WIDTH)
		{
			m_iX = g_iMAP_WIDTH - 1;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		--m_iY;
		if (m_iY < 0)
		{
			m_iY = 0;
		}
	}
}
