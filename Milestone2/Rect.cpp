#include "Rect.h"
#include "Color.h" // Assuming Color class is used for parsing colors

// Constructor definition
Rect::Rect(int x, int y, int width, int height, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width)
    : x(x), y(y), width(width), height(height), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width) {}

// Render method definition
void Rect::render(HDC hdc) const {
    // Parse color for fill and stroke
    Color fillColor = Color::parseColor(fill);  // Assuming Color::parseColor() returns a Color object
    Color strokeColor = Color::parseColor(stroke);

    std::cout << fillColor.getBlue() << " " << fill_opacity << std::endl;


    // Create GDI+ Graphics object
    Gdiplus::Graphics graphics(hdc);

    // Create Pen (stroke) and SolidBrush (fill) for GDI+ rendering
    Gdiplus::Pen pen(Gdiplus::Color(255, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Draw the filled rectangle
    graphics.FillRectangle(&brush, x, y, width, height);

    // Draw the rectangle outline (stroke)
    graphics.DrawRectangle(&pen, x, y, width, height);
}
