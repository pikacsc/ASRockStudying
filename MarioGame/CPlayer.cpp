#include "CPlayer.h"
#include "CMapManager.h"
#include "CStage.h"
#include "value.h"

CPlayer::CPlayer()
	:m_tPos(POINT{ 0,0 }), m_bOnGround(true), m_iCoin(0), m_bLeftBlock(true), m_bRightBlock(false), m_iLife(0)
{

}

CPlayer::~CPlayer()
{
}

static void UpdateCoin(CPlayer& _pPlayer);
static void ApplyPhysics(CPlayer& _pPlayer);
static void RenderPlayerState(CPlayer& _Player);

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

void CPlayer::ResetToStart(void)
{
	POINT startPos = CMapManager::GetInst()->GetSelectStage()->GetStartPos();
	SetPos(startPos);
	SetOnGround(true);
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

int CPlayer::GetLifeCount(void) const
{
	return m_iLife;
}

void CPlayer::SetLifeCount(int _iLife)
{
	m_iLife = _iLife;
}

void CPlayer::MinusLife(void)
{
	if (m_iLife <= 0)
	{
		m_iLife = 0;
	}
	else
	{
		--m_iLife;
	}
}

bool CPlayer::Init()
{
	m_iLife = g_iLife_Default;
	m_iCoin = 0;
	return true;
}

void CPlayer::Update()
{
	CStage* selectStage = CMapManager::GetInst()->GetSelectStage();

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

	UpdateCoin(*this);
	ApplyPhysics(*this);
}

void CPlayer::Render()
{
	RenderPlayerState(*this);
}


static void UpdateCoin(CPlayer& _Player)
{
	CStage* selectStage = CMapManager::GetInst()->GetSelectStage();
	eSTAGE_BLOCK_TYPE playerPosBlock = selectStage->GetBlockByPos(_Player.GetPos());
	
	if (playerPosBlock == eSTAGE_BLOCK_TYPE::SBT_COIN)
	{
		selectStage->SetBlockByPos(_Player.GetPos(), eSTAGE_BLOCK_TYPE::SBT_ROAD);
		_Player.PlusCoin();
	}
}

static void ApplyPhysics(CPlayer& _Player)
{
	CStage* selectStage = CMapManager::GetInst()->GetSelectStage();
	
	//�� ����� �ǰ� �ϱ�
	int player_Left = _Player.GetX() - 1;
	
	int player_Right = _Player.GetX() + 1;

	int player_iY = _Player.GetY();

	eSTAGE_BLOCK_TYPE leftBlock = selectStage->GetBlockByXY(player_Left, player_iY);
	eSTAGE_BLOCK_TYPE rightBlock = selectStage->GetBlockByXY(player_Right, player_iY);

	if (leftBlock == eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		_Player.SetLeftBlock(true);
	}
	else
	{
		_Player.SetLeftBlock(false);
	}

	if (rightBlock == eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		_Player.SetRightBlock(true);
	}
	else
	{
		_Player.SetRightBlock(false);
	}

	//�߷�
	//�÷��̾��� x,y ��ǥ�� ���µ� �ٷ� �ؿ� ������, ������� üũ
	int player_iX = _Player.GetX();
	int player_Bottom = _Player.GetY() + 1;

	eSTAGE_BLOCK_TYPE bottomBlock = selectStage->GetBlockByXY(player_iX, player_Bottom);

	if (bottomBlock != eSTAGE_BLOCK_TYPE::SBT_WALL)
	{
		_Player.SetOnGround(false);
	}
	else
	{
		_Player.SetOnGround(true);
	}
}

static void RenderPlayerState(CPlayer& _Player)
{
	int playerCoin = _Player.GetCoin();
	int playerLife = _Player.GetLifeCount();
	std::cout << "coin : " << playerCoin << std::endl;
	std::cout << "Life : ";
	for (int i = 0; i < playerLife; i++)
	{
		std::cout << "��";
	}
	std::cout << std::endl << "Left : �� " << " Right : �� " << std::endl;
	std::cout << "Jump : space bar " << std::endl;
}
