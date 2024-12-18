#ifndef SVGELEMENTS_H
#define SVGELEMENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "windows.h"
#include "gdiplus.h"

#pragma comment(lib, "gdiplus.lib")

class SVGElements {
public:
    virtual void render(HDC hdc) const = 0; // Phương thức render ảo
    virtual ~SVGElements() = default;
};

#endif // SVGELEMENTS_H
