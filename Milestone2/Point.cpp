#include "Point.h"


SvgPoint::SvgPoint()
{
  x = 0;
  y = 0;
}

SvgPoint::SvgPoint(double x, double y)
{
  this->x = x;
  this->y = y;
}

double SvgPoint::getX()
{
  return x;
}

double SvgPoint::getY()
{
  return y;
}

void SvgPoint::setX(double x)
{
  this->x = x;
}

void SvgPoint::setY(double y)
{
  this->y = y;
}
