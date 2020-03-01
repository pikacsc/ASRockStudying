#include <iostream>
#include <functional>

//함수 포인터 : 함수의 메모리 주소를 저장하기 위한 포인터 변수를 선언할 수 있다.


int g_Sum(const int& _a, const int& _b)
{
	return _a + _b;
}



class Hanzo
{

public:
	void HelloWorld()
	{
		std::cout << "HelloWorld" << std::endl;
	}

	int c_Sum(const int& _a, const int& _b)
	{
		return _a + _b;
	}
};


int main()
{
	//std::function<int(const int&, const int&)> g_func; //function 객체 선언

	//g_func = std::bind(g_Sum, std::placeholders::_1, std::placeholders::_2);

	//std::cout << g_func(1, 2) << std::endl;


	Hanzo hanzo;

	std::function<int(const int&, const int&)> c_func; //function 객체 선언

	c_func = std::bind(&Hanzo::c_Sum, hanzo, std::placeholders::_1, std::placeholders::_2);

	std::cout << c_func(2, 4) << std::endl;


	return 0;
}