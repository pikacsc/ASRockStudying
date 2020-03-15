#pragma once
#include "value.h"


class CMonster
{
public:
	CMonster();
	~CMonster();

private:
	POINT		m_tPos;
	int			m_iDir;
public:
	void SetPos(const POINT& _pos);
	void SetPosByXY(int _iX, int _iY);
	void SetX(int _iX);
	void SetY(int _iY);

	POINT GetPos(void) const;
	int GetX(void) const;
	int GetY(void) const;

public:
	bool Init(void);
	void Update(void);

};

