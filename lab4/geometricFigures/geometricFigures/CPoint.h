#ifndef CPOINT_H
#define CPOINT_H

class CPoint
{
public:
	CPoint(double x, double y)
		: m_x(x)
		, m_y(y)
	{
	}

	double m_x;
	double m_y;
};

#endif // CPOINT_H