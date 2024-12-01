#ifndef TEXT_H
#define TEXT_H

#include "SVGElements.h"

class Text : public SVGElements {
private:
    int x, y;
    std::wstring font_family;
    double font_size;
    std::string content;
    std::string fill;
    Transform transform;

public:
    Text(int x, int y, std::wstring font_family, double font_size, const std::string& content, const std::string& fill, Transform transform);
    void render(HDC hdc) const override;
};

#endif // TEXT_H
