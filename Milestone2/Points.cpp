#include "Points.h"


svgPoints::svgPoints()
{
  x = 0;
  y = 0;
}

svgPoints::svgPoints(int x, int y)
{
  this->x = x;
  this->y = y;
}

double svgPoints::getX()
{
  return x;
}

double svgPoints::getY()
{
  return y;
}

void svgPoints::setX(double x)
{
  this->x = x;
}

void svgPoints::setY(double y)
{
  this->y = y;
}
