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

QString Vector::to_string()
{
	QString res("(");
	res = res + QString::number(x) + "; " +
		QString::number(y) + "; " +
		QString::number(z) + ")";
	return res;
}

double Vector::get_x()
{
	return this->x;
}

double Vector::get_y()
{
	return this->y;
}

double Vector::get_z()
{
	return this->z;
}


bool Vector::is_parallel(Vector other)
{
	double cosalpha = (this->x * other.x + this->y * other.y + this->z * other.z) / (this->get_len() * other.get_len());
	return abs(1 - abs(cosalpha)) < 0.0000001;
}

double Vector::get_len()
{
	return sqrt(x*x + y*y + z*z);
}

