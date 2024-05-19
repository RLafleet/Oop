#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape {
public:
    static constexpr const char* NAME = "triangle";

    CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
        : m_vertex1(vertex1),
        m_vertex2(vertex2),
        m_vertex3(vertex3),
        m_outlineColor(outlineColor),
        m_fillColor(fillColor)
    {
		double sideLineTriange1 = GetTriangleSideLength(m_vertex2, m_vertex1);
		double sideLineTriange2 = GetTriangleSideLength(m_vertex3, m_vertex2);
		double sideLineTriange3 = GetTriangleSideLength(m_vertex1, m_vertex3);

        if (   (sideLineTriange1 + sideLineTriange2 <= sideLineTriange3) 
            || (sideLineTriange1 + sideLineTriange3 <= sideLineTriange2)
            || (sideLineTriange2 + sideLineTriange3 <= sideLineTriange1))
        {
            throw std::invalid_argument("Triangle is not valid");
        }
    }

    double GetArea() const override;

    // Что произойдет если не написать override
    double GetPerimeter() const override;

    std::string Info() const override;

    uint32_t GetOutlineColor() const override;

    uint32_t GetFillColor() const override;

    CPoint GetVertex1() const;

    CPoint GetVertex2() const;

    CPoint GetVertex3() const;

    void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
    CPoint m_vertex1;
    CPoint m_vertex2;
    CPoint m_vertex3;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;

    //Этот метод возращает не линию
	static double GetTriangleSideLength(const CPoint& vertex1, const CPoint& vertex2);
};


#endif //CTRIANGLE_H