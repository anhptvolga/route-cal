#include "route.h"

Route::Route()
{
}

Route::Route(QString name)
{
	this->name = name;
	this->points.append(Point(0,0,0));
}

Route::~Route()
{

}

QVector<Point> Route::get_points()
{
	return this->points;
}

void Route::update_points(QVector<Point> pts) 
{
	this->points = pts;
}

void Route::calcuate()
{
	
}

