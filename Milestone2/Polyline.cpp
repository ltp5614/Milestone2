#include "Polyline.h"
#include "Color.h"
#include <gdiplus.h>

// Constructor khởi tạo các thuộc tính cho polyline
polylineSVG::polylineSVG(const std::vector<std::pair<int, int>>& points, 
                         const std::string& fill, 
                         double fill_opacity, 
                         const std::string& stroke, 
                         int stroke_width, 
                         double stroke_opacity)
    : points(points), 
      shapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity) {}

// Hàm render để vẽ polyline lên HDC
void polylineSVG::render(HDC hdc) const {
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    Color fillColor = Color::parseColor(fill);
    Color strokeColor = Color::parseColor(stroke);

    // Tạo đối tượng Graphics từ HDC
    Gdiplus::Graphics graphics(hdc);

    // Chuyển đổi các điểm (x, y) thành kiểu dữ liệu của GDI+
    std::vector<Gdiplus::Point> gdipPoints;
    for (const auto& point : points) {
        gdipPoints.push_back(Gdiplus::Point(point.first, point.second));
    }

    // Tạo đối tượng Brush cho màu nền và độ trong suốt (sử dụng nếu bạn muốn fill)
    Gdiplus::SolidBrush fillBrush(Gdiplus::Color(
        static_cast<BYTE>(255 * fill_opacity), 
        fillColor.getRed(), 
        fillColor.getGreen(), 
        fillColor.getBlue()
    ));

    // Tạo đối tượng Pen cho màu viền và độ trong suốt
    Gdiplus::Pen strokePen(Gdiplus::Color(
        static_cast<BYTE>(255 * stroke_opacity), 
        strokeColor.getRed(), 
        strokeColor.getGreen(), 
        strokeColor.getBlue()
    ), stroke_width);

    // Nếu có màu nền (fill), sẽ vẽ polyline với màu nền
    if (!fill.empty()) {
        graphics.FillPolygon(&fillBrush, &gdipPoints[0], gdipPoints.size());
    }

    // Vẽ polyline (đường gấp khúc) với viền (stroke)
    graphics.DrawPolygon(&strokePen, &gdipPoints[0], gdipPoints.size());
}
