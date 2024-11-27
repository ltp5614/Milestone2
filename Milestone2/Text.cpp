#include "Text.h"
#include "Color.h"

Text::Text(int x, int y, int font_size, const std::string& content, const std::string& fill)
    : x(x), y(y), font_size(font_size), content(content), fill(fill) {}

void Text::render(HDC hdc) const {
    std::cout << x << " " << y;
    // Convert the fill color string into a Color object (assuming you use Color class for handling colors)
    Color textColor = Color::parseColor(fill);


        // Create a Graphics object to measure text size
    Gdiplus::Graphics graphics(hdc);

    // Set up the font
    Gdiplus::Font font(L"Arial", font_size);


    Gdiplus::SolidBrush brush(Gdiplus::Color(255, textColor.getRed(), textColor.getGreen(), textColor.getBlue()));

    // Measure the size of the text
    Gdiplus::RectF textBox;
    graphics.MeasureString(
        std::wstring(content.begin(), content.end()).c_str(), // Convert std::string to std::wstring
        -1,  // Length of the string (use -1 for null-terminated string)
        &font,  // Font object
        Gdiplus::PointF(x, y), // Position of the text
        &textBox  // This will store the bounding box for the text
    );

    // Adjust the y position based on the text's height
    float adjustedY = y - textBox.Height;  // Adjust to ensure text is positioned correctly

    // Draw the text at the adjusted position
    graphics.DrawString(
        std::wstring(content.begin(), content.end()).c_str(), // Convert std::string to std::wstring
        -1,  // Length of the string (use -1 for null-terminated string)
        &font,  // Font object
        Gdiplus::PointF(x, adjustedY), // Use the adjusted y position
        &brush  // Brush object for color
    );


}
