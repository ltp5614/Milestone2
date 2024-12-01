#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "SVGElements.h"
#include "Shape.h"

class ellipseSVG : public ShapeSVG{
private:
    int cx, cy;
    int rx, ry;
    Transform transform;

public:
    ellipseSVG(int cx, int cy, int rx, int ry, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity, Transform transform);
    void render(HDC hdc) const override;
};

#endif // ELLIPSE_H
