#ifndef POLYLINE_H
#define POLYLINE_H

#include "SVGElements.h"
#include "shape.h"

class polylineSVG : public ShapeSVG {
private:
    std::vector<std::pair<int, int>> points;
    Transform transform;

public:
    polylineSVG(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform);
    SvgPoint getCenter() const;
    void render(HDC hdc) const override;
};

#endif // POLYLINE_H
