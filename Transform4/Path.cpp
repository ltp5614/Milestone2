#include "Path.h"
#include "Color.h"
#include <Gdiplus.h>


void pathSVG::skipWhitespace(const std::string& str, int& index) const 
{
    while (index < str.size() && std::isspace(str[index])) {
        ++index;
    }
}

    // Hàm đọc một số (float)
float pathSVG::parseNumber(const std::string& str, int& index) const 
{
    skipWhitespace(str, index);
    int start = index;
    while (index < str.size() &&
            (std::isdigit(str[index]) || str[index] == '.' || str[index] == '-' || str[index] == '+')) {
        ++index;
    }
    if (start == index) throw std::runtime_error("Expected a number");
    return std::stof(str.substr(start, index - start));
}


pathSVG::pathSVG(const std::string& pointsData, const std::string& fill, double fill_opacity,
                 const std::string& stroke, int stroke_width, double stroke_opacity)
{
    this->fill = fill;
    this->fill_opacity = fill_opacity;
    this->stroke = stroke;
    this->stroke_width = stroke_width;
    this->stroke_opacity = stroke_opacity;
    parseFromSVGString(pointsData);  // Gọi hàm phân tích chuỗi SVG vào commands
}


void pathSVG::calculateArcParameters(const Gdiplus::PointF& currentPoint, const Gdiplus::PointF& endPoint, 
                                  float rx, float ry, float xAxisRotation, int largeArcFlag, int sweepFlag, 
                                  float& cx, float& cy, float& theta1, float& deltaTheta) const {
    // (Tính toán theo công thức SVG Arc, không mở rộng ở đây)
}

std::vector<Gdiplus::PointF> pathSVG::calculateBezierForArc(float cx, float cy, float rx, float ry, 
                                                         float xAxisRotation, float thetaStart, float thetaEnd) const {
    std::vector<Gdiplus::PointF> points(4);

    // (Tính toán các điểm control và anchor của Bézier từ tham số cung)

    return points;
}

void pathSVG::renderArc(Gdiplus::Graphics& graphics, Gdiplus::GraphicsPath& path, 
                     Gdiplus::PointF& currentPoint, const std::vector<float>& params) const {
    float rx = params[0];
    float ry = params[1];
    float xAxisRotation = params[2];
    int largeArcFlag = static_cast<int>(params[3]);
    int sweepFlag = static_cast<int>(params[4]);
    Gdiplus::PointF endPoint(params[5], params[6]);

    if (rx == 0 || ry == 0) {
        path.AddLine(currentPoint, endPoint);
        currentPoint = endPoint;
        return;
    }

    // Tính toán tọa độ tâm, góc bắt đầu và góc quét
    float cx, cy, theta1, deltaTheta;
    calculateArcParameters(currentPoint, endPoint, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, 
                           cx, cy, theta1, deltaTheta);

    // Chia cung thành các đoạn nhỏ hơn 90° và thêm vào Path
    int numSegments = static_cast<int>(ceil(fabs(deltaTheta) / (M_PI / 2)));
    float segmentTheta = deltaTheta / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        float thetaStart = theta1 + i * segmentTheta;
        float thetaEnd = thetaStart + segmentTheta;

        auto bezierPoints = calculateBezierForArc(cx, cy, rx, ry, xAxisRotation, thetaStart, thetaEnd);
        path.AddBezier(bezierPoints[0], bezierPoints[1], bezierPoints[2], bezierPoints[3]);
    }

    currentPoint = endPoint;
}


void pathSVG::addCommand(const PathCommand& command) {
        commands.push_back(command);
    }

// Lấy danh sách các lệnh
const std::vector<PathCommand>& pathSVG::getCommands() const {
    return commands;
}

// Chuyển toàn bộ path thành chuỗi SVG
std::string pathSVG::toSVGString() const {
    std::ostringstream oss;
    for (int i = 0; i < commands.size(); ++i) {
        oss << commands[i].toString();
        if (i < commands.size() - 1) oss << " ";
    }
    return oss.str();
}

// Xóa toàn bộ path
void pathSVG::clear() {
    commands.clear();
}

// Phân tích chuỗi SVG path và nạp vào Path
void pathSVG::parseFromSVGString(const std::string& svgPath) {
    int i = 0;

    while (i < svgPath.size()) {
        skipWhitespace(svgPath, i);

        // Lấy lệnh (ký tự đầu tiên)
        if (i >= svgPath.size()) break;
        char command = svgPath[i];
        if (!std::isalpha(command)) {
            throw std::runtime_error("Expected a command");
        }
        ++i;

        // Đọc các tham số
        std::vector<float> parameters;
        if (command != 'Z' && command != 'z') { // Z không có tham số
            while (i < svgPath.size() && !std::isalpha(svgPath[i])) {
                parameters.push_back(parseNumber(svgPath, i));
                skipWhitespace(svgPath, i);
                // Nếu có dấu phẩy, bỏ qua
                if (i < svgPath.size() && svgPath[i] == ',') {
                    ++i;
                }
            }
        }

        // Thêm lệnh vào danh sách
        commands.emplace_back(command, parameters);
    }
}

void pathSVG::render(HDC hdc) const
{
  SVGColor fillColor = SVGColor::parseColor(fill);
  SVGColor strokeColor = SVGColor::parseColor(stroke);

  Gdiplus::Graphics graphics(hdc);
  Gdiplus::SolidBrush fillBrush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));
    // Tạo đối tượng Pen cho màu viền và độ trong suốt
  Gdiplus::Pen strokePen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));

  // Dùng GraphicsPath để lưu các đoạn Path
  Gdiplus::GraphicsPath path;

  Gdiplus::PointF currentPoint(0, 0);

  for (const auto& command : commands) 
  {
        char cmd = command.getCommand();
        const auto& params = command.getParameters();

        switch (cmd) 
        {
        case 'M': // Moveto
            currentPoint = Gdiplus::PointF(params[0], params[1]);
            path.StartFigure(); // Bắt đầu một hình mới
            break;

        case 'L': // Lineto
            path.AddLine(currentPoint, Gdiplus::PointF(params[0], params[1]));
            currentPoint = Gdiplus::PointF(params[0], params[1]);
            break;

        case 'H': // Horizontal lineto
            path.AddLine(currentPoint, Gdiplus::PointF(params[0], currentPoint.Y));
            currentPoint.X = params[0];
            break;

        case 'V': // Vertical lineto
            path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, params[0]));
            currentPoint.Y = params[0];
            break;

        case 'C': // Cubic Bézier curve
            path.AddBezier(currentPoint, 
                           Gdiplus::PointF(params[0], params[1]), 
                           Gdiplus::PointF(params[2], params[3]), 
                           Gdiplus::PointF(params[4], params[5]));
            currentPoint = Gdiplus::PointF(params[4], params[5]);
            break;

        case 'Q': // Quadratic Bézier curve
            path.AddBezier(currentPoint,
                           Gdiplus::PointF((2 * params[0] + currentPoint.X) / 3, 
                                           (2 * params[1] + currentPoint.Y) / 3), 
                           Gdiplus::PointF((2 * params[0] + params[2]) / 3, 
                                           (2 * params[1] + params[3]) / 3), 
                           Gdiplus::PointF(params[2], params[3]));
            currentPoint = Gdiplus::PointF(params[2], params[3]);
            break;

        case 'A': // Elliptical arc
            renderArc(graphics, path, currentPoint, params);
            break;

        case 'Z': // Closepath
            path.CloseFigure();
            break;

        default:
            std::cerr << "Unsupported command: " << cmd << std::endl;
        }
    }

    // Vẽ nền (fill)
    graphics.FillPath(&fillBrush, &path);

    // Vẽ viền (stroke)
    graphics.DrawPath(&strokePen, &path);
}
