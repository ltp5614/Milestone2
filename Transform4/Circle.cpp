// Circle.cpp
#include "Circle.h"
#include "Color.h"

Circle::Circle(int cx, int cy, int r, const std::string& fill, double fill_opacity,
               const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform)
    : ShapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity), 
      cx(cx), cy(cy), r(r), transform(transform) {}


void Circle::render(HDC hdc) const {
    SVGColor fillColor = SVGColor::parseColor(fill);
    SVGColor strokeColor = SVGColor::parseColor(stroke);

    std::cout << fillColor.getBlue() << " " << fill_opacity;

    Gdiplus::Graphics graphics(hdc);

    Gdiplus::SolidBrush fillBrush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Tạo đối tượng Pen cho màu viền và độ trong suốt
    Gdiplus::Pen strokePen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));

    SvgPoint center(cx, cy);
    transform.apply(graphics, center);

    // Vẽ hình tròn (Circle)
    graphics.FillEllipse(&fillBrush, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ nền
    graphics.DrawEllipse(&strokePen, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ viền
}
