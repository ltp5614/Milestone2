#ifndef PATH_H
#define PATH_H

#define M_PI 3.14159265358979323846

#include "SVGElements.h"
#include "PathCommand.h"


class pathSVG : public SVGElements {
private:
    std::vector<PathCommand> commands;
    std::string fill;
    std::string stroke;
    double fill_opacity;
    int stroke_width;
    double stroke_opacity;

    void skipWhitespace(const std::string& str, int& index) const;
    // Hàm đọc một số (float)
    float parseNumber(const std::string& str, int& index) const;


public:
    pathSVG(const std::string& pointsData, const std::string& fill, double fill_opacity,
                 const std::string& stroke, int stroke_width, double stroke_opacity);
    void renderArc(Gdiplus::Graphics& graphics, Gdiplus::GraphicsPath& path, 
                     Gdiplus::PointF& currentPoint, const std::vector<float>& params) const;

    std::vector<Gdiplus::PointF> calculateBezierForArc(float cx, float cy, float rx, float ry, 
                                                         float xAxisRotation, float thetaStart, float thetaEnd) const;

    void calculateArcParameters(const Gdiplus::PointF& currentPoint, const Gdiplus::PointF& endPoint, 
                                  float rx, float ry, float xAxisRotation, int largeArcFlag, int sweepFlag, 
                                  float& cx, float& cy, float& theta1, float& deltaTheta) const;

    void addCommand(const PathCommand& command);
    // Lấy danh sách các lệnh
    const std::vector<PathCommand>& getCommands() const;

    // Chuyển toàn bộ path thành chuỗi SVG
    std::string toSVGString() const;

    // Xóa toàn bộ path
    void clear();

    // Phân tích chuỗi SVG path và nạp vào Path
    void parseFromSVGString(const std::string& svgPath);
    void render(HDC hdc) const override;
};

#endif // PATH_H
