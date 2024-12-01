#include "Line.h"
#include "Color.h"

Line::Line(int x1, int y1, int x2, int y2, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform)
    : x1(x1), y1(y1), x2(x2), y2(y2), stroke(stroke), stroke_width(stroke_width), stroke_opacity(stroke_opacity), transform(transform) {}

void Line::render(HDC hdc) const 
{
    // Phân tích chuỗi màu để tạo đối tượng SVGColor cho stroke
    SVGColor strokeColor = SVGColor::parseColor(stroke);

    // Tạo đối tượng Graphics   
    Gdiplus::Graphics graphics(hdc);

    SvgPoint center((x1 + x2) / 2, (y1 + y2) / 2);
    transform.apply(graphics, center);

    // Tạo đối tượng Pen sử dụng các giá trị màu và độ trong suốt
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));

    // Vẽ đường thẳng
    graphics.DrawLine(&pen, x1, y1, x2, y2);
}
