#pragma once
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	int		m_iX;
	int		m_iY;
	int		m_iCoin;
	bool	m_bIsOnGround;
	bool	m_bLeftBlock;
	bool	m_bRightBlock;

public:
	int GetX() const;
	void SetX(int _iX);
	int GetY() const;
	void SetY(int _iY);
	int GetCoin() const;
	void PlusCoin();
	void MinusCoin();

	void SetPosition(int _iX, int _iY);
	bool IsOnGround() const;
	void SetOnGround(bool _bOnGround);

	bool IsLeftBlock() const;
	void SetLeftBlock(bool _bLeftBlock);
	bool IsRightBlock() const;
	void SetRightBlock(bool _bRightBlock);

public:
	bool	Init();
	void	Update();
};

