#pragma once
#include "value.h"

class CBullet
{
private:
	int		m_iRange;
	POINT	m_tBulletPos;
	int		m_iDamage;
	bool	m_bOnFire;
public:
	CBullet();
	~CBullet();

	bool Init();
	void Update();

	int GetRange(void) const;
	void SetRange(int _iRange);
	POINT GetBulletPos(void) const;
	void SetBulletPos(const POINT& _tBulletPos);
	void SetBulletByXY(LONG _x, LONG _y);

	int GetDamage(void) const;
	void SetDamage(int _iDamage);

	void SetOnFire(bool _bOnFire);
	bool GetOnFire(void) const;

	bool GetEnable(void) const;
};

