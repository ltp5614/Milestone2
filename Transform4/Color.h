#ifndef COLOR_H
#define COLOR_H

#include "SVGElements.h"

class SVGColor {
   private:
       int red, blue, green;
       float alpha; // Transparency (default: 255)

   public:
       SVGColor(int red, int blue, int green, float alpha = 1.0);
       static SVGColor parseColor(const std::string& colorStr);
       
       int getRed();
       int getBlue();
       int getGreen();
       float getAlpha();
};

bool isValidColor(int color);

#endif
