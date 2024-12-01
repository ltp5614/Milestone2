#include "Ellipse.h"
#include "Color.h"

ellipseSVG::ellipseSVG(int cx, int cy, int rx, int ry, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform)
    : cx(cx), cy(cy), rx(rx), ry(ry), ShapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity), transform(transform) {}

void ellipseSVG::render(HDC hdc) const 
{
    // Phân tích chuỗi màu để tạo đối tượng SVGColor cho fill và stroke
    SVGColor fillColor = SVGColor::parseColor(fill);
    SVGColor strokeColor = SVGColor::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen và Brush sử dụng các giá trị màu và độ trong suốt
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    SvgPoint center(cx, cy);
    transform.apply(graphics, center);

    // Vẽ ellipse
    graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}
