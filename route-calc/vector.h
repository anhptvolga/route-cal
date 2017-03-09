#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>
#include <QString>
#include "Setting.h"
#include "point.h"

using namespace std;

class Vector
{
public:
	Vector();
	Vector(double _x, double _y, double _z);
	Vector(Point starting, Point ending);

	QString to_string();

	bool is_parallel(Vector other);

	double get_x();
	double get_y();
	double get_z();

	double get_len();

private:
	double x;
	double y;
	double z;
};

#endif