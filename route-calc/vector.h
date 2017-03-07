#pragma once

#include "point.h"

class Vector
{
public:
	Vector();
	Vector(double _x, double _y, double _z);
	Vector(Point starting, Point ending);

private:
	double x;
	double y;
	double z;
};
