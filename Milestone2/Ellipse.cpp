#include "Ellipse.h"
#include "Color.h"

ellipseSVG::ellipseSVG(int cx, int cy, int rx, int ry, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity)
    : cx(cx), cy(cy), rx(rx), ry(ry), shapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity) {}
void ellipseSVG::render(HDC hdc) const 
{
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    Color fillColor = Color::parseColor(fill);
    Color strokeColor = Color::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen và Brush sử dụng các giá trị màu và độ trong suốt
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Vẽ ellipse
    graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}
