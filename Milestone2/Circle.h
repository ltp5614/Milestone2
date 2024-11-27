#ifndef CIRCLE_H
#define CIRCLE_H

#include "SVGElements.h"
#include "Shape.h"

class Circle : public shapeSVG{
private:
    int cx, cy, r;

public:
    Circle(int cx, int cy, int r, const std::string& fill, double fill_opacity,
           const std::string& stroke, int stroke_width, double stroke_opacity);
    
    void render(HDC hdc) const override;  // Ghi đè phương thức render
};

#endif // CIRCLE_H

