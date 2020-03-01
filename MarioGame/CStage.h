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
	//�� �Լ��� �׳� �ʱ�ȭ�� ������ �Լ��̴�
	bool Init();
	
	//�� �Լ��� ���Ͽ��� ������ �о�ͼ� ������ ������ �Լ��̴�
	bool ReadFile(const char* _pFileName);

	void Update();

	void Render();
};

