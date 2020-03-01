#include <iostream>

class CPoint
{
private:
	int m_iX;
	int m_iY;

public:
	CPoint()
		:m_iX(0), m_iY(0)
	{}

	CPoint(const int& _iX, const int& _iY)
		:m_iX(_iX), m_iY(_iY)
	{}

	CPoint(const CPoint& _Point)
	{
		*this = _Point; //allow shallow copy
	}

	~CPoint()
	{}


	CPoint& operator = (const CPoint& _Point)
	{
		if (this == &_Point)
			return *this;

		*this = _Point;
	}

	void operator += (const CPoint& _Point)
	{
		this->m_iX += _Point.m_iX;
		this->m_iY += _Point.m_iY;
	}

	void operator -= (const CPoint& _Point)
	{
		this->m_iX -= _Point.m_iX;
		this->m_iY -= _Point.m_iY;
	}
	
	friend std::ostream& operator << (std::ostream& out, const CPoint& _point)
	{
		out << "( " << _point.m_iX << ", " << _point.m_iY << " )";
		return out;
	}

	int Get_X()
	{
		return m_iX;
	}

	int Get_Y()
	{
		return m_iY;
	}

	void Set_X(const int& _iX)
	{
		m_iX = _iX;
	}

	void Set_Y(const int& _iY)
	{
		m_iY = _iY;
	}
};

int main()
{
	CPoint point1(1,2);
	CPoint point2(1,3);



	std::cout << point1 << std::endl;
	std::cout << point2 << std::endl;
	point1 += point2;

	std::cout << point1 << std::endl;

	return 0;
}