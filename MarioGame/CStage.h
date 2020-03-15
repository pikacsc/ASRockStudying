#pragma once
#include "value.h"

class CStage
{
private:
	char	m_cStage[g_iMAP_HEIGHT][g_iMAP_WIDTH] = { 0 };
	POINT	m_startPOS;
	POINT	m_goalPOS;
	//������ ���� �迭�� ����� ���ؼ� �����Ѵ�.
	//�� �������� �����Ҵ��� ���� �ּҸ� ��� ���� ���ؼ� �̴�.
	class CMonster**	m_pMonsterArray;
	int					m_iMonsterCount;		//���Ͱ� ��� �����Ǿ����� üũ
	int					m_iMonsterArrayCount;	//���� �迭 ũ��
public:
	CStage();
	~CStage();

public:
	//�� �Լ��� �׳� �ʱ�ȭ�� ������ �Լ��̴�
	bool Init();
	
	//�� �Լ��� ���Ͽ��� ������ �о�ͼ� ������ ������ �Լ��̴�
	bool ReadFile(const char* _pFileName);

	void Update();

	void Render();

	eSTAGE_BLOCK_TYPE GetBlockByPos(const POINT& _pos) const;
	eSTAGE_BLOCK_TYPE GetBlockByXY(int _x, int _y) const;
	void SetBlockByPos(const POINT& _pos,const eSTAGE_BLOCK_TYPE& _block);
	void SetBlockByXY(int _x, int _y,const eSTAGE_BLOCK_TYPE& _block);
	 
	POINT GetGoalPos(void) const;
	POINT GetStartPos(void) const;
	
	class CMonster* CreateMonster(int _iX, int _iY);
	bool CheckMonster(int _iX, int _iY);
	int GetMonsterCount(void) const;
	class CMonster* GetMonster(int idx) const;
	void DeleteMonster(int _idx);




};

 