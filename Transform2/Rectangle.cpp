#include "Rectangle.h"
#include "Color.h" // Assuming SVGColor class is used for parsing colors

// Constructor definition
SVGRectangle::SVGRectangle(int x, int y, int width, int height, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, Transform transform)
	: x(x), y(y), width(width), height(height), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width), transform(transform) {}

// Render method definition
void SVGRectangle::render(HDC hdc) const {
	// Parse color for fill and stroke
	SVGColor fillColor = SVGColor::parseColor(fill);  // Assuming SVGColor::parseColor() returns a SVGColor object
	SVGColor strokeColor = SVGColor::parseColor(stroke);

	// Create GDI+ Graphics object
	Gdiplus::Graphics graphics(hdc);

	// Create Pen (stroke) and SolidBrush (fill) for GDI+ rendering
	Gdiplus::Pen pen(Gdiplus::Color(255, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), static_cast<REAL>(stroke_width));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

	// If rotation is applied, calculate the center point of the rectangle
	SvgPoint center(x + width / 2, y + height / 2);
	transform.apply(graphics, center);

	// Draw the filled rectangle
	graphics.FillRectangle(&brush, x, y, width, height);

	// Draw the rectangle outline (stroke)
	graphics.DrawRectangle(&pen, x, y, width, height);

	// Reset the transformation
	graphics.ResetTransform();
}