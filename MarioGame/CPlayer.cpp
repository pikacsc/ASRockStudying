#include "CPlayer.h"
#include "value.h"

CPlayer::CPlayer()
	:m_tPos(POINT{ 0,0 }), m_bOnGround(true), m_iCoin(0), m_bLeftBlock(true), m_bRightBlock(false)
{

}

CPlayer::~CPlayer()
{
}

int CPlayer::GetX() const
{
	return m_tPos.x;
}

void CPlayer::SetX(int _iX)
{
	m_tPos.x = _iX;
}

int CPlayer::GetY() const
{
	return m_tPos.y;
}

void CPlayer::SetY(int _iY)
{
	m_tPos.y = _iY;
}

POINT CPlayer::GetPos() const
{
	return m_tPos;
}

void CPlayer::SetPos(const POINT& _tPos)
{
	m_tPos = _tPos;
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


void CPlayer::SetPosByXY(int _iX, int _iY)
{
	m_tPos.x = _iX;
	m_tPos.y = _iY;
}

bool CPlayer::IsOnGround() const
{
	return m_bOnGround;
}

void CPlayer::SetOnGround(bool _bOnGround)
{
	m_bOnGround = _bOnGround;
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

	return true;
}

void CPlayer::Update()
{
	//�߷��ۿ�, �÷��̾� �ؿ� ���� ���� ��� �÷��̾� y���� ++
	if (!m_bOnGround)
	{
		++m_tPos.y;
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

		--m_tPos.x;

		if (m_tPos.x < 0)
		{
			m_tPos.x = 0;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (IsRightBlock()) //�����ʿ� ���� ������� ������ ����
		{
			return;
		}

		++m_tPos.x;

		if (m_tPos.x > g_iMAP_WIDTH)
		{
			m_tPos.x = g_iMAP_WIDTH - 1;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		--m_tPos.y;
		if (m_tPos.y < 0)
		{
			m_tPos.y = 0;
		}
	}
}
