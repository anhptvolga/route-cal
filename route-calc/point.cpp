#include "point.h"


Point::Point(void)
	: x(0), y(0), z(0)
{
}

Point::Point(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z)
{

}

double Point::get_x()
{
	return this->x;
}

double Point::get_y()
{
	return this->y;
}

double Point::get_z()
{
	return this->z;
}

QString Point::to_string()
{
	QString res("(");
	res = res + QString::number(x) + "; " +
		QString::number(y) + "; " +
		QString::number(z) + ")";
	return res;
}
