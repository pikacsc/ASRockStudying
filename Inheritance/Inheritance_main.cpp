#include <iostream>

/*
상속 : 클래스는 서로간에 부모(Base)와 자식(Derived)관계를 형성 할 수 있다.
자식 클래스는 부모클래스의 멤버들을 사용할 수 있다.

부모클래스에서 public이나 protected로 되어있는 멤버들은 사용가능 하지만,
private 으로 되어있는 멤버는 자식에서도 사용이 불가능하다

상속의 형태 : public, private 상속이 있다.


다형성 : 상속관계에 있는 클래스간에 서로 형변환이 가능한 성질을 말한다.

가상함수 : 함수 오버라이딩 이라고도 부른다. 함수를 재정의 하는 기능이다.
멤버함수 앞에 virtual 키워드를 붙이면 해당함수는 가상 함수가 된다.
만약 CParent 클래스에 virtual void Output() 함수가 있다면 자식클래스에서는
이 가상함수를 재정의 할 수 있다. 재정의는 함수 이름과 인자가 완전히 똑같아야 한다.

가상 함수를 가지고 있는 클래스는 내부적으로 가상함수 테이블이라는 것을 생성한다.
가상함수 테이블은 가상함수들의 메모리 주소를 저장하는 테이블이다.

만약 CParent의 Output이 가상함수이고 CChild 클래스에 Output을 재정의 한다면
그런뒤 CChild 객체를 생성하면 가상 함수 테이블에는 CChild 클래스의 Output 
주소가 올라가게 된다.

만약 CParent 객체를 생성한다면 CParent 의 Output 주소가 올라가게 된다.

그래서 Output 함수, 즉 가상함수를 호출하게 되면, 먼저 가상함수 테이블을 참조해서
메모리 주소를 확인한다. 가상함수 테이블에 CChild의 Output 주소가 들어가 있다면
그 주소의 함수를 호출해주는 개념이다.


부모클래스의 소멸자는 항상 가상 소멸자로 만들어준다.
소멸자도 가상함수로 만들 수 있다. 부모의 소멸자는 가상함수로 만들어 두자
*/

class CParent
{
public:
	CParent()
		:m_iA(0),m_iB(0),m_iC(0)
	{
		std::cout << "CParent 생성자" << std::endl;
	}
	
	virtual ~CParent()
	{
		std::cout << "CParent 소멸자" << std::endl;
	}
public:
	int		m_iA;

protected:
	int		m_iB;

private:
	int		m_iC;

public:
	virtual void Output()
	{
		std::cout << "A : " << m_iA << std::endl;
		std::cout << "B : " << m_iB << std::endl;
		std::cout << "C : " << m_iC << std::endl;
	}

	// 순수 가상 함수 : 함수 뒤에 = 0 불여주면 해당 가상함수는
	// 순수 가상 함수가 된다. 순수 가상 함수는 구현부분이 존재하지 않는다.
	// 순수 가상 함수를 가지고 있는 클래스를 추상클래스 라고 부른다.
	// 추상클래스는 인스턴스(객체) 생성이 불가능하다.
	// 순수 가상함수는 자식에서 반드시 재정의 해야 한다. 왜냐하면 순수 가상 함수는
	// 정의 부분이 없기 때문에 반드시 자식에서 재정의 해서 사용할 목적으로
	// 만들어주는 함수이기 때문이다.
	//virtual void OutputPure() = 0;

protected:
	void protectedOutput()
	{
		std::cout << "Parent Output Function" << std::endl;
	}
};

class CChild : public CParent
{
public:
	CChild()
		:m_iD(0)
	{
		m_iB = 200;
		// m_iC는 private 이기 때문에 자식 내부에서도 접근이 불가능 하다
		//m_iC = 300; // error
		std::cout << "CChild 생성자" << std::endl;
	}

	virtual ~CChild()
	{
		std::cout << "CChild 소멸자" << std::endl;
	}

protected:
	int		m_iD;
public:
	void ChildOutput()
	{
		std::cout << "Child Output Function" << std::endl;
	}

	virtual void Output()
	{
		std::cout << "Child Output Function" << std::endl;
	}
};

class  CChild1 : private CParent
{
public:
	CChild1()
		:m_iD(0)
	{
		m_iA = 100;
		m_iB = 200;
		std::cout << "CChild1 생성자" << std::endl;
		
	}

	~CChild1()
	{
		std::cout << "CChild1 소멸자" << std::endl;
	}

private:
	int		m_iD;
public:
	void ChildOutput()
	{
		std::cout << "Child Output Function" << std::endl;
	}

	virtual void Output()
	{
		CParent::Output();
		std::cout << "Child Output Function" << std::endl;
	}

	/*virtual void OutputPure()
	{

	}*/
};

class CChildChild : public CChild
{
public:
	CChildChild()
		:m_iE(0)
	{
		m_iD = 500;
		std::cout << "CChildChild 생성자" << std::endl;
	}

	~CChildChild()
	{
		std::cout << "CChildChild 소멸자" << std::endl;

	}

private:
	int		m_iE;
};


int main(void)
{
	/*
	상속 관계에서의 생성자 호출 순서 : 부모 -> 자식 순으로 호출됨
	상속관계에서의 소멸자 호출 순서 : 자식 -> 부모 순으로 호출됨
	*/
	/*CParent			parent;
	std::cout << std::endl;
	CChild			child;
	std::cout << std::endl;
	CChild1			child1;
	std::cout << std::endl;
	CChildChild		childchild;
	std::cout << std::endl;

	parent.m_iA = 100;
	

	child.m_iA = 200;*/

	// CChild1 클래스는 CParent를 private 상속을 하고 있으므로 CParent에 
	// Public으로 설정되어있는 멤버들도 외부에서는 접근이 불가능하다.
	//child1.m_iA = 300;
	//child1.Output();


	// CChild 클래스는 CParent 클래스를 상속받고 있다.
	// new CChild를 하게 되면 CChild 객체 하나를 생성해주고 그 메모리 주소를 반환한다.
	
	// 그런데 아래에서는 CParent* 타입 변수에 이 반환된 주소를 대입해주고 있다.
	// 부모 포인터 타입에 CChild 객체의 메모리 주소를 넣을 수 있는 이유는 상속 관계에
	// 있기 때문이다. 자식 메모리 주소를 부모 포인터 타입으로 형변환 된것이기 때문이다.
	// 이런 형변환을 업캐스팅이라고 한다.
	// 자식 -> 부모 타입 형변환 : 업 캐스팅
	// 부모 -> 자식 타입 형변환 : 다운 캐스팅
	CParent* pParent = new CChild;
	//CParent* pParent1 = new CChild1;
	CParent* pParent2 = new CChildChild;

	//프로그램을 만들때 하나의 Parent로 부터 모든 객체가 상속받게되면
	// 하나의 배열을 만들어서, 모두 집어넣고, 모두 지울수 있고 불러올수 있어서, 관리하기 용이해진다.
	CParent* pParentArr[2] = {};
	
	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;


	// 아래 두 클래스는 모두 CParent 클래스를 상속 받고 있다.
	// 그러므로 pParent를 두 타입 모두 다운 캐스팅 가능하다.
	// 그런데 pParent는 CChild 로 할당한 객체이다.
	// 이 객체를 CChild1 타입으로 다운캐스팅 하여 넣어주게 되면
	// 이 객체를 사용할 때 문제가 발생할 수 있다. 왜냐하면 애초에 생성한 객체가 아닌 다른 타입으로 변환 됐기 때문이다.
	CChild*		pChild	= (CChild*)pParent;
	CChild1*	pChild1 = (CChild1*)pParent;

	pParent->Output();

	// CChild 클래스에 있는 ChildOutput 함수에 접근할 수 없다.
	// 왜냐하면 pParent는 CParent 포인터 타입이기 때문에 자식 멤버에 
	// 접근이 불가능하기 때문이다. 만약 접근하고 싶다면 형변환 해야한다.
	((CChild*)pParent)->ChildOutput();


	// 현재 delete 를 하게되면 CChild 소멸자 -> CParent 소멸자가 호출되어야하는데, 지금은 CParent 소멸자만 호출된다.
	// 왜냐하면 근본적으로 pParent 는 CParent 포인터 타입이다. CParent 포인터 타입이기 떄문에
	// CChild 소멸자가 호출 될 수 없다.
	delete pParent;
	//delete pParent2;

	//아래와 같은 방식으로 하면, 모두 CParent 소멸자가 호출되고 끝난다
	for (int i = 0; i < 2; ++i)
	{
		//delete pParentArr[i];
	}


	return 0;
}