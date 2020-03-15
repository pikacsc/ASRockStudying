#pragma once
#include "value.h"

class CStage
{
private:
	char	m_cStage[g_iMAP_HEIGHT][g_iMAP_WIDTH] = { 0 };
	POINT	m_startPOS;
	POINT	m_goalPOS;
	//포인터 동적 배열을 만들기 위해서 선언한다.
	//그 이유으는 동적할당한 몬스터 주소를 담아 놓기 위해서 이다.
	class CMonster**	m_pMonsterArray;
	int					m_iMonsterCount;		//몬스터가 몇마리 생성되었는지 체크
	int					m_iMonsterArrayCount;	//몬스터 배열 크기
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
	
	class CMonster* CreateMonster(int _iX, int _iY);
	bool CheckMonster(int _iX, int _iY);
	int GetMonsterCount(void) const;
	class CMonster* GetMonster(int idx) const;
	void DeleteMonster(int _idx);




};

 