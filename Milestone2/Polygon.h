#ifndef POLYGON_H
#define POLYGON_H

#include "SVGElements.h"
#include "shape.h"

class polygonSVG : public shapeSVG
{
private:
    std::vector<std::pair<int, int>> points;

public:
    polygonSVG(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render(HDC hdc) const override;
};

#endif // POLYGON_H
