#include "Transform.h"

//Constructor
Transform::Transform() : translateX(0), translateY(0), scaleX(1), scaleY(1), rotationAngle(0) {}

Transform::Transform(float translateX, float translateY, float scaleX, float scaleY, float rotationAngle)
			: translateX(translateX), translateY(translateY), scaleX(scaleX), scaleY(scaleY), rotationAngle(rotationAngle) {}

//Apply tranform
void Transform::apply(Graphics& graphics, SvgPoint center) const {
	graphics.TranslateTransform(translateX, translateY);
	graphics.TranslateTransform(center.getX(), center.getY());
	graphics.ScaleTransform(scaleX, scaleY);
	graphics.RotateTransform(rotationAngle);
	graphics.TranslateTransform(static_cast<int>(-center.getX()), static_cast<int>(-center.getY()));
}

//Load tranform from file
Transform Transform::loadTransform(xml_node<>* node) {
    Transform transform;
    xml_attribute<>* transformAttr = node->first_attribute("transform");
    if (transformAttr) {
        std::string transformStr = transformAttr->value();
        std::stringstream ss(transformStr);
        std::string command;

        while (ss >> command) {
            if (command.find("rotate") != std::string::npos) {
                float rotationAngle = 0.0f;
                sscanf_s(command.c_str(), "rotate(%f)", &rotationAngle);
                transform.setRotationAngle(rotationAngle);
            }

            else if (command.find("translate") != std::string::npos) {
                float translateX = 0.0f, translateY = 0.0f;
                sscanf_s(command.c_str(), "translate(%f,%f)", &translateX, &translateY);
                transform.setTranslateX(translateX);
            }

            else if (command.find("scale") != std::string::npos) {
                float scaleX = 0.0f, scaleY = 0.0f;
                sscanf_s(command.c_str(), "scale(%f,%f)", &scaleX, &scaleY);
                transform.setScaleX(scaleX);
            }
        }
    }

    return transform;
}

//Getter
float Transform::getTranslateX() const {
	return translateX;
}

float Transform::getTranslateY() const {
	return translateY;
}

float Transform::getScaleX() const {
	return scaleX;
}

float Transform::getScaleY() const {
	return scaleY;
}

float Transform::getRotationAngle() const {
	return rotationAngle;
}

//Setter
void Transform::setTranslateX(float translateX) {
	this->translateX = translateX;
}

void Transform::setTranslateY(float translateY) {
	this->translateY = translateY;
}

void Transform::setScaleX(float scaleX) {
	this->scaleX = scaleX;
}

void Transform::setScaleY(float scaleY) {
	this->scaleY = scaleY;
}

void Transform::setRotationAngle(float rotationAngle) {
	this->rotationAngle = rotationAngle;
}