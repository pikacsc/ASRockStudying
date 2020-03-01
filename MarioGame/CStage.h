#pragma once
#include "value.h"

class CStage
{
private:
	char m_cStage[g_iMAP_HEIGHT][g_iMAP_WIDTH] = { 0 };


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
};

