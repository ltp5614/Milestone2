#ifndef POINT_H
#define POINT_H
#include <vector>
#include <string>
#include <sstream>

// Định nghĩa kiểu svgPoints (có thể là struct hoặc class)
class svgPoints 
{
  private:
    double x;
    double y;
  public:
    svgPoints();
    svgPoints(int, int);
    static std::vector<svgPoints> parsePointForPath(const std::string& d);
    double getX();
    double getY();
    void setX(double);
    void setY(double);
};
#endif
