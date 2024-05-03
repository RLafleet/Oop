#ifndef INC_1_2_CPOINT_H
#define INC_1_2_CPOINT_H

class CPoint
{
public:
	CPoint(double xCord, double yCord) : m_xCord(xCord), m_yCord(yCord) {}

	double m_xCord;
	double m_yCord;
};

#endif //INC_1_2_CPOINT_H