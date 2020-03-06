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
	//이 함수는 그냥 초기화할 목적의 함수이다
	bool Init();
	
	//이 함수는 파일에서 정보를 읽어와서 설정할 목적의 함수이다
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

 