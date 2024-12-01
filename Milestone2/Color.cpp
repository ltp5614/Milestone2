#include "Color.h"

SVGColor::SVGColor(int red, int green, int blue, float alpha) 
	: red(red), green(green), blue(blue),alpha(alpha) {}

int SVGColor::getRed() {
	return red;
}

int SVGColor::getGreen() {
	return green;
}

int SVGColor::getBlue() {
	return blue;
}

float SVGColor::getAlpha() {
	return alpha;
}

SVGColor SVGColor::parseColor(const std::string& colorStr) {
	if (colorStr.find("rgb") != 0) {
		std::cout << "Invalid color data" << std::endl;

		return SVGColor(-1, -1, -1, -1.0);
	}

	int red = 0, green = 0, blue = 0;
	float alpha = 1.0; // Transparency (default: 1.0)

	size_t start = colorStr.find("(");
	size_t end = colorStr.find(")");

	std::string content = colorStr.substr(start + 1, end - start + 1);
	std::stringstream ss(content);
	std::string temp;

	getline(ss, temp, ',');
	red = stoi(temp);
	getline(ss, temp, ',');
	green = stoi(temp);
	getline(ss, temp);
	blue = stoi(temp);

	return SVGColor(red, green, blue, alpha);
}

bool isValidColor(int color) {
	return (color >= 0 && color <= 255);
}
