#include "Polygon.h"
#include "Color.h"
#include <Gdiplus.h>

polygonSVG::polygonSVG(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform)
    : points(points), ShapeSVG(fill, stroke, fill_opacity, stroke_width, stroke_opacity), transform(transform) {}

void polygonSVG::render(HDC hdc) const 
{
    // Phân tích chuỗi màu để tạo đối tượng SVGColor cho fill và stroke
    SVGColor fillColor = SVGColor::parseColor(fill);
    SVGColor strokeColor = SVGColor::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen và Brush
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Tạo đối tượng GraphicsPath để vẽ đa giác
    Gdiplus::GraphicsPath path;

    // Thêm các điểm vào GraphicsPath
    if (!points.empty()) {
        path.StartFigure();
        path.AddLine(points[0].first, points[0].second, points[1].first, points[1].second);  // Thêm một đường thẳng đầu tiên

        for (size_t i = 1; i < points.size() - 1; ++i) {
            path.AddLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
        }

        path.CloseFigure(); // Đóng đa giác
    }
    
    SvgPoint center = getCenter();
    transform.apply(graphics, center);

    // Vẽ đa giác với màu fill và stroke
    graphics.FillPath(&brush, &path); // Vẽ phần fill
    graphics.DrawPath(&pen, &path);   // Vẽ đường viền (stroke)
}

// Hàm trả về tọa độ trung tâm của đa giác
SvgPoint polygonSVG::getCenter() const
{
	// Tính trung bình tọa độ x và y của các điểm
	double sumX = 0, sumY = 0;
	for (const auto& point : points) {
		sumX += point.first;
		sumY += point.second;
	}

	// Trả về tọa độ trung tâm
	return SvgPoint(sumX / points.size(), sumY / points.size());
}