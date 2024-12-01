#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "SVGElements.h"
#include <string>  // Required for std::string

class SVGRectangle : public SVGElements {
private:
    int x, y, width, height;  // Position and size of the rectangle
    std::string fill;          // Fill color (could be in hex format or named colors)
    double fill_opacity;       // Fill opacity (0.0 to 1.0)
    std::string stroke;        // Stroke color (could be in hex format or named colors)
    int stroke_width;          // Stroke width
    Transform transform;       // Transform object to apply transformations

public:
    // Constructor to initialize the rectangle attributes
    SVGRectangle(int x, int y, int width, int height, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, Transform transform);

    // Render method to draw the rectangle
    void render(HDC hdc) const override;
};

#endif // RECTANGLE_H
