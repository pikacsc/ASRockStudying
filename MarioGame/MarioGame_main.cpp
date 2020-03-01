#include "CCore.h"


int main()
{
	//게임 초기화
	if (!CCore::GetInst()->Init())
	{
		std::cout << "게임 초기화 실패!!" << std::endl;
		CCore::DestroyInst();
		return 0;
	}

	// 초기화에 성공했다면 게임을 구동시킨다.
	CCore::GetInst()->Run();

	// 동작이 끝나면 CCore 객체를 메모리에서 해제 시킨다
	CCore::DestroyInst();

	return 0;
}