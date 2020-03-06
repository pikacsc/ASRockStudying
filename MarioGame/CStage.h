#pragma once
#include "value.h"

class CStage
{
private:
	char m_cStage[g_iMAP_HEIGHT][g_iMAP_WIDTH] = { 0 };
	POINT m_startPOS;
	POINT m_goalPOS;


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
};

 