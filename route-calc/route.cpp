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
	// 1. 
	int nlines = this->points.count() - 1;
	// 2.
	if (nlines > 0)
	{
		Vector v12(points[0], points[1]);

	}
	else
	{
		// TODO: not enough points
	}
}

void Route::set_free_indexs(QVector<int> frindexs)
{
	this->free_indexs = frindexs;
}


/*
QFile file("out.txt");
if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	return;

QTextStream out(&file);
for (int i = 0; i < this->points.count(); ++i) 
{
	out << points[i].x << ' ' 
		<< points[i].y << ' ' 
		<< points[i].z << ' ' 
		<< "\n";
}
file.close();
*/