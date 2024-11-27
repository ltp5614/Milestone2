#ifndef SHAPE_H
#define SHAPE_H

#include "SVGElements.h"
#include <string>

class shapeSVG : public SVGElements {
protected:
    std::string fill;
    std::string stroke;
    double fill_opacity;
    int stroke_width;
    double stroke_opacity;

public:
    shapeSVG(const std::string& fill, const std::string& stroke, 
             double fill_opacity, int stroke_width, double stroke_opacity)
        : fill(fill), stroke(stroke), fill_opacity(fill_opacity), 
          stroke_width(stroke_width), stroke_opacity(stroke_opacity) {}

    virtual void render(HDC hdc) const override = 0; // Phương thức render thuần ảo
    virtual ~shapeSVG() = default;
};

#endif // SHAPE_H

