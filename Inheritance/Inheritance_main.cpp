#include <iostream>

/*
��� : Ŭ������ ���ΰ��� �θ�(Base)�� �ڽ�(Derived)���踦 ���� �� �� �ִ�.
�ڽ� Ŭ������ �θ�Ŭ������ ������� ����� �� �ִ�.

�θ�Ŭ�������� public�̳� protected�� �Ǿ��ִ� ������� ��밡�� ������,
private ���� �Ǿ��ִ� ����� �ڽĿ����� ����� �Ұ����ϴ�

����� ���� : public, private ����� �ִ�.


������ : ��Ӱ��迡 �ִ� Ŭ�������� ���� ����ȯ�� ������ ������ ���Ѵ�.

�����Լ� : �Լ� �������̵� �̶�� �θ���. �Լ��� ������ �ϴ� ����̴�.
����Լ� �տ� virtual Ű���带 ���̸� �ش��Լ��� ���� �Լ��� �ȴ�.
���� CParent Ŭ������ virtual void Output() �Լ��� �ִٸ� �ڽ�Ŭ����������
�� �����Լ��� ������ �� �� �ִ�. �����Ǵ� �Լ� �̸��� ���ڰ� ������ �Ȱ��ƾ� �Ѵ�.

���� �Լ��� ������ �ִ� Ŭ������ ���������� �����Լ� ���̺��̶�� ���� �����Ѵ�.
�����Լ� ���̺��� �����Լ����� �޸� �ּҸ� �����ϴ� ���̺��̴�.

���� CParent�� Output�� �����Լ��̰� CChild Ŭ������ Output�� ������ �Ѵٸ�
�׷��� CChild ��ü�� �����ϸ� ���� �Լ� ���̺��� CChild Ŭ������ Output 
�ּҰ� �ö󰡰� �ȴ�.

���� CParent ��ü�� �����Ѵٸ� CParent �� Output �ּҰ� �ö󰡰� �ȴ�.

�׷��� Output �Լ�, �� �����Լ��� ȣ���ϰ� �Ǹ�, ���� �����Լ� ���̺��� �����ؼ�
�޸� �ּҸ� Ȯ���Ѵ�. �����Լ� ���̺� CChild�� Output �ּҰ� �� �ִٸ�
�� �ּ��� �Լ��� ȣ�����ִ� �����̴�.


�θ�Ŭ������ �Ҹ��ڴ� �׻� ���� �Ҹ��ڷ� ������ش�.
�Ҹ��ڵ� �����Լ��� ���� �� �ִ�. �θ��� �Ҹ��ڴ� �����Լ��� ����� ����
*/

class CParent
{
public:
	CParent()
		:m_iA(0),m_iB(0),m_iC(0)
	{
		std::cout << "CParent ������" << std::endl;
	}
	
	virtual ~CParent()
	{
		std::cout << "CParent �Ҹ���" << std::endl;
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

	// ���� ���� �Լ� : �Լ� �ڿ� = 0 �ҿ��ָ� �ش� �����Լ���
	// ���� ���� �Լ��� �ȴ�. ���� ���� �Լ��� �����κ��� �������� �ʴ´�.
	// ���� ���� �Լ��� ������ �ִ� Ŭ������ �߻�Ŭ���� ��� �θ���.
	// �߻�Ŭ������ �ν��Ͻ�(��ü) ������ �Ұ����ϴ�.
	// ���� �����Լ��� �ڽĿ��� �ݵ�� ������ �ؾ� �Ѵ�. �ֳ��ϸ� ���� ���� �Լ���
	// ���� �κ��� ���� ������ �ݵ�� �ڽĿ��� ������ �ؼ� ����� ��������
	// ������ִ� �Լ��̱� �����̴�.
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
		// m_iC�� private �̱� ������ �ڽ� ���ο����� ������ �Ұ��� �ϴ�
		//m_iC = 300; // error
		std::cout << "CChild ������" << std::endl;
	}

	virtual ~CChild()
	{
		std::cout << "CChild �Ҹ���" << std::endl;
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
		std::cout << "CChild1 ������" << std::endl;
		
	}

	~CChild1()
	{
		std::cout << "CChild1 �Ҹ���" << std::endl;
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
		std::cout << "CChildChild ������" << std::endl;
	}

	~CChildChild()
	{
		std::cout << "CChildChild �Ҹ���" << std::endl;

	}

private:
	int		m_iE;
};


int main(void)
{
	/*
	��� ���迡���� ������ ȣ�� ���� : �θ� -> �ڽ� ������ ȣ���
	��Ӱ��迡���� �Ҹ��� ȣ�� ���� : �ڽ� -> �θ� ������ ȣ���
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

	// CChild1 Ŭ������ CParent�� private ����� �ϰ� �����Ƿ� CParent�� 
	// Public���� �����Ǿ��ִ� ����鵵 �ܺο����� ������ �Ұ����ϴ�.
	//child1.m_iA = 300;
	//child1.Output();


	// CChild Ŭ������ CParent Ŭ������ ��ӹް� �ִ�.
	// new CChild�� �ϰ� �Ǹ� CChild ��ü �ϳ��� �������ְ� �� �޸� �ּҸ� ��ȯ�Ѵ�.
	
	// �׷��� �Ʒ������� CParent* Ÿ�� ������ �� ��ȯ�� �ּҸ� �������ְ� �ִ�.
	// �θ� ������ Ÿ�Կ� CChild ��ü�� �޸� �ּҸ� ���� �� �ִ� ������ ��� ���迡
	// �ֱ� �����̴�. �ڽ� �޸� �ּҸ� �θ� ������ Ÿ������ ����ȯ �Ȱ��̱� �����̴�.
	// �̷� ����ȯ�� ��ĳ�����̶�� �Ѵ�.
	// �ڽ� -> �θ� Ÿ�� ����ȯ : �� ĳ����
	// �θ� -> �ڽ� Ÿ�� ����ȯ : �ٿ� ĳ����
	CParent* pParent = new CChild;
	//CParent* pParent1 = new CChild1;
	CParent* pParent2 = new CChildChild;

	//���α׷��� ���鶧 �ϳ��� Parent�� ���� ��� ��ü�� ��ӹްԵǸ�
	// �ϳ��� �迭�� ����, ��� ����ְ�, ��� ����� �ְ� �ҷ��ü� �־, �����ϱ� ����������.
	CParent* pParentArr[2] = {};
	
	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;


	// �Ʒ� �� Ŭ������ ��� CParent Ŭ������ ��� �ް� �ִ�.
	// �׷��Ƿ� pParent�� �� Ÿ�� ��� �ٿ� ĳ���� �����ϴ�.
	// �׷��� pParent�� CChild �� �Ҵ��� ��ü�̴�.
	// �� ��ü�� CChild1 Ÿ������ �ٿ�ĳ���� �Ͽ� �־��ְ� �Ǹ�
	// �� ��ü�� ����� �� ������ �߻��� �� �ִ�. �ֳ��ϸ� ���ʿ� ������ ��ü�� �ƴ� �ٸ� Ÿ������ ��ȯ �Ʊ� �����̴�.
	CChild*		pChild	= (CChild*)pParent;
	CChild1*	pChild1 = (CChild1*)pParent;

	pParent->Output();

	// CChild Ŭ������ �ִ� ChildOutput �Լ��� ������ �� ����.
	// �ֳ��ϸ� pParent�� CParent ������ Ÿ���̱� ������ �ڽ� ����� 
	// ������ �Ұ����ϱ� �����̴�. ���� �����ϰ� �ʹٸ� ����ȯ �ؾ��Ѵ�.
	((CChild*)pParent)->ChildOutput();


	// ���� delete �� �ϰԵǸ� CChild �Ҹ��� -> CParent �Ҹ��ڰ� ȣ��Ǿ���ϴµ�, ������ CParent �Ҹ��ڸ� ȣ��ȴ�.
	// �ֳ��ϸ� �ٺ������� pParent �� CParent ������ Ÿ���̴�. CParent ������ Ÿ���̱� ������
	// CChild �Ҹ��ڰ� ȣ�� �� �� ����.
	delete pParent;
	//delete pParent2;

	//�Ʒ��� ���� ������� �ϸ�, ��� CParent �Ҹ��ڰ� ȣ��ǰ� ������
	for (int i = 0; i < 2; ++i)
	{
		//delete pParentArr[i];
	}


	return 0;
}