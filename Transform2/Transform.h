#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "SVGElements.h"
#include "Point.h"
#include "gdiplus.h"
#include "rapidxml.hpp"

using namespace Gdiplus;
using namespace rapidxml;

class Transform {
private:
	float translateX, translateY;
	float scaleX, scaleY;
	float rotationAngle;

public:
	//Constructor
	Transform();
	Transform(float translateX, float translateY, float scaleX, float scaleY, float rotationAngle);

	//Apply transform
	void apply(Graphics& graphics, SvgPoint center) const;

	//Load tranform from file
	Transform loadTransform(xml_node<>* node);

	//Getter
	float getTranslateX() const;
	float getTranslateY() const;
	float getScaleX() const;
	float getScaleY() const;
	float getRotationAngle() const;

	//Setter
	void setTranslateX(float translateX);
	void setTranslateY(float translateY);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setRotationAngle(float rotationAngle);
};

#endif