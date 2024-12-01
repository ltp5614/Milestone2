#include "Polyline.h"
#include "Color.h"
#include <gdiplus.h>

// Constructor khởi tạo các thuộc tính cho polyline
polylineSVG::polylineSVG(const std::vector<std::pair<int, int>>& points, 
                         const std::string& fill, 
                         double fill_opacity, 
                         const std::string& stroke, 
                         int stroke_width, 
                         double stroke_opacity,
                         Transform transform)
    : points(points), 
      ShapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity), 
      transform(transform) {}

// Hàm render để vẽ polyline lên HDC
void polylineSVG::render(HDC hdc) const {
    // Phân tích chuỗi màu để tạo đối tượng SVGColor cho fill và stroke
    SVGColor fillColor = SVGColor::parseColor(fill);
    SVGColor strokeColor = SVGColor::parseColor(stroke);

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
    ), static_cast<REAL>(stroke_width));

    // Nếu có màu nền (fill), sẽ vẽ polyline với màu nền
    if (!fill.empty()) {
        graphics.FillPolygon(&fillBrush, &gdipPoints[0], gdipPoints.size());
    }

    SvgPoint center = getCenter();
    transform.apply(graphics, center);

    // Vẽ polyline (đường gấp khúc) với viền (stroke)
    graphics.DrawPolygon(&strokePen, &gdipPoints[0], gdipPoints.size());
}

// Hàm trả về tọa độ trung tâm của polyline
SvgPoint polylineSVG::getCenter() const {
	// Tính trung bình tọa độ x và y của các điểm
	double sumX = 0, sumY = 0;
	for (const auto& point : points) {
		sumX += point.first;
		sumY += point.second;
	}

	return SvgPoint(sumX / points.size(), sumY / points.size());
}