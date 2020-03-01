#pragma once
#include "value.h"


/*
Ŭ���� ���� ���� : �̰����� ���漱���� Ŭ������ �ִ� ��� �ν��ϰ� �����.
���漱���� �κп����� ������ �ϴ� ���̱� ������ ���漱���� Ŭ������ ��ü��
�����ϴ��� ����� ����� ����Ҽ� ����.
�ܼ��� ������ ������ ������ �������� �ַ� ����ϰ� ���漱���� ��������ν�
������� ����� #include �ϴ� ��Ȳ�� �����ְ� cpp���� ���� �����
�� include�� ���־ ������� ���� include �ϴ� ��Ȳ�� ������ �� �ִ�
*/

class CStage;
class CMapManager
{
private:
	CMapManager();
	~CMapManager();

private:
	static CMapManager* m_pInst;
	static const char m_StageNameArr[][g_iSTAGENAME_MAX];
public:
	static CMapManager* GetInst();
	static void DestroyInst();

private:
	CStage* m_pStage[g_iSTAGE_MAX_COUNT];

public:
	bool Init();
	void Update();
	void Render();
	void Run();
};

