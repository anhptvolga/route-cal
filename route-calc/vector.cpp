#include "vector.h"


Vector::Vector()
	: x(0), y(0), z(0)
{
}


Vector::Vector(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z)
{
}

Vector::Vector(Point starting, Point ending)
{
	this->x = ending.get_x() - starting.get_x();
	this->y = ending.get_y() - starting.get_y();
	this->z = ending.get_z() - starting.get_z();
}

