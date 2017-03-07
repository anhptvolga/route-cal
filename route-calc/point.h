#pragma once
class Point
{
public:
	Point();
	Point(double _x, double _y, double _z);

	double get_x();
	double get_y();
	double get_z();

private:
	double x;
	double y;
	double z;
};
