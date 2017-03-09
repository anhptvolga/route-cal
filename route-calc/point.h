#pragma once
#include <QString>
using namespace std;

class Point
{
public:
	Point();
	Point(double _x, double _y, double _z);

	double get_x();
	double get_y();
	double get_z();

	QString to_string();

private:
	double x;
	double y;
	double z;
};
