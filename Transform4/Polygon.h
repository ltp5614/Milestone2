#ifndef POLYGON_H
#define POLYGON_H

#include "SVGElements.h"
#include "shape.h"

class polygonSVG : public ShapeSVG
{
private:
    std::vector<std::pair<int, int>> points;
    Transform transform;

public:
    polygonSVG(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform);
    SvgPoint getCenter() const;
    void render(HDC hdc) const override;
};

#endif // POLYGON_H
