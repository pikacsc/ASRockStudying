#pragma once
#include "value.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	POINT	m_tPos;
	int		m_iCoin;
	bool	m_bOnGround;
	bool	m_bLeftBlock;
	bool	m_bRightBlock;
	
public:
	int		GetX() const;
	void	SetX(int _iX);
	int		GetY() const;
	void	SetY(int _iY);
	POINT	GetPos() const;
	void	SetPos(const POINT& _tPos);
	void	SetPosByXY(int _iX, int _iY);
	int		GetCoin() const;
	void	PlusCoin();
	void	MinusCoin();

	bool	IsOnGround() const;
	void	SetOnGround(bool _bOnGround);

	bool	IsLeftBlock() const;
	void	SetLeftBlock(bool _bLeftBlock);
	bool	IsRightBlock() const;
	void	SetRightBlock(bool _bRightBlock);

public:
	bool    Init();
	void	Update();
};

