#include "CCore.h"


int main()
{
	//���� �ʱ�ȭ
	if (!CCore::GetInst()->Init())
	{
		std::cout << "���� �ʱ�ȭ ����!!" << std::endl;
		CCore::DestroyInst();
		return 0;
	}

	// �ʱ�ȭ�� �����ߴٸ� ������ ������Ų��.
	CCore::GetInst()->Run();

	// ������ ������ CCore ��ü�� �޸𸮿��� ���� ��Ų��
	CCore::DestroyInst();

	return 0;
}